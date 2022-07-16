#include "Telnet.h"
#include "Console.h"
#include "vmsock.h"
#include "Console_io.h"

extern Console console;
extern Telnet telnet;

static void Telnet_tcp_callback(VMINT handle, VMINT event){
	telnet.tcp_callback(handle, event);
}

void Telnet::tcp_callback(VMINT handle, VMINT event){
	char tmp[200];

	if(handle!=tcp_handle)
		return;

	switch(event){
		case VM_TCP_EVT_CONNECTED:
			is_connected=1;
			break;
		case VM_TCP_EVT_CAN_WRITE:
			break;
		case VM_TCP_EVT_CAN_READ:
			update();
			break;
		case VM_TCP_EVT_PIPE_BROKEN:
		case VM_TCP_EVT_HOST_NOT_FOUND:
		case VM_TCP_EVT_PIPE_CLOSED:
			vm_tcp_close(tcp_handle);
			is_connected=0;
			tcp_handle=-1;
			sprintf(tmp, "\n\033[mConnect is close (code %d)\n", event);
			console_str_in(tmp);
			break;
	}
}
void Telnet::send_unsended(){
	if(temp_unsend_data_size){
		int sended = vm_tcp_write(tcp_handle, temp_unsend_data, temp_unsend_data_size);
		if(sended<=0)
			return;
		if(sended==temp_unsend_data_size)
			temp_unsend_data_size=0;
		else{
			memmove(temp_unsend_data, temp_unsend_data + sended, temp_unsend_data_size-sended);
			temp_unsend_data_size-=sended;
		}
	}
}

void Telnet::send_data(char *data, int len){
	if(len==-1)
		len=strlen(data);
	send_unsended();
	int sended = vm_tcp_write(tcp_handle, data, len);
	if(sended<=0)
		return;
	if(sended<len && temp_unsend_data_size + len - sended < temp_unsended_data_max_size){
		memmove(temp_unsend_data+temp_unsend_data_size, data+sended, len-sended);
		temp_unsend_data_size += len - sended;
	}
}

void Telnet::send_response_command(unsigned char command, unsigned char option){
	unsigned char data[3]={255, command, option};
	send_data((char*)data, 3);
}
void Telnet::send_response_command(unsigned char command){
	unsigned char data[2]={255, command};
	send_data((char*)data, 2);
}

void Telnet::DO_command(){
	switch(option){
		case 1: //Echo
			send_response_command(WILL, option);
			break;
		case 3: //Suppress Go Ahead
			send_response_command(WILL, option);
			break;
		case 24: //Terminal Type
			{
				send_response_command(WILL, option);
				unsigned char data[8]={0xff, 0xfa, 0x18, 0x00, 0x41, 0x4e, 0x53, 0x49}; //SB
				send_data((char*)data, 8);
				send_response_command(SE);
			}
			break;
		case 31://Negotiate About Window Size.
			{
				send_response_command(WILL, option);
				unsigned char data[7]={255, 0xfa, 0x1f, 0x00, console.terminal_w, 0x00, console.terminal_h}; //SB
				send_data((char*)data, 7);
				send_response_command(SE);
			}
			break;
		default:
			send_response_command(WONT, option);
			break;
	}
}

void Telnet::DONT_command(){
	switch(option){
		case 1: //Echo
			send_response_command(WONT, option);
			break;
		case 3: //Suppress Go Ahead
			send_response_command(WONT, option);
			break;
		default:
			send_response_command(WONT, option);
			break;
	}
}

void Telnet::update(){
	if(!is_connected)
		return;
	send_unsended();

	int readed = vm_tcp_read(tcp_handle, temp_data, 10240);
	if(readed>0)
		for(int i=0; i<readed; ++i)
			switch(status){
				case MAIN:
					if((temp_data[i])==0xFF)
						status = COMMAND, last_status = MAIN;
					else
						console_char_in(temp_data[i]);
					break;
				case COMMAND:
					switch(temp_data[i]){
						case 0xF0://SE
							//todo: doing something
							temp_option_data_pos=0;
							status=MAIN;
							break;
						case 0xF1://NOP
							status=last_status;
							break;
						case 0xF2:
						case 0xF3:
						case 0xF4:
						case 0xF5:
						case 0xF6:
						case 0xF7:
						case 0xF8:
						case 0xF9:
							status=last_status;
							my_printf("Telnet %#2X\n");
							break;
						case 0xFA://SB
						case 0xFB://WILL 
						case 0xFC://WON'T
						case 0xFD://DO 
						case 0xFE://DON'T 
							status = COMMAND;
							command = temp_data[i];
							break;
						case 0xFF://IAC
							status=last_status;
							break;
						default:
							if((temp_data[i])<=255){
								option = temp_data[i];
								switch(command){
									case 0xFA: //SB
										last_status=status;
										status=OPTION_DATA;
										data_option = option;
										break;
									case 0xFB://WILL 
										status=last_status;
										break;
									case 0xFC://WON'T
										status=last_status;
										break;
									case 0xFD://DO 
										DO_command();
										status=last_status;
										break;
									case 0xFE://DON'T 
										DONT_command();
										status=last_status;
										break;
									default:
										status=last_status;
										break;
								}
							}else
								status=last_status;
							break;
					}
					break;
				case OPTION_DATA:
					if(((unsigned char)temp_data[i])==0xFF)
						status = COMMAND, last_status = OPTION_DATA;
					else if(temp_option_data_pos<100)
						temp_option_data[temp_option_data_pos++]=temp_data[i];
					else{
						console_str_with_length_in(temp_option_data, temp_option_data_pos);
						status=MAIN;
					}
					break;
			}
}

void Telnet::connect_to(const char*ip, int port){
	is_connected = 0;
	tcp_handle = vm_tcp_connect(ip, port, 1, Telnet_tcp_callback);
}

void Telnet::init(){
	is_connected=0;
	tcp_handle=-1;
	temp_option_data_pos=0;
	status=last_status=MAIN;
	option=0;
	temp_unsend_data_size=0;
}

Telnet::~Telnet(void){
	vm_tcp_close(tcp_handle);
}
