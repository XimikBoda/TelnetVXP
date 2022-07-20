#include "main.h"
#include "Console.h"
#include "Console_io.h"
#include "Telnet.h"
#include "T2Input.h"
#include "vmtimer.h"

//Global
int scr_w = 0, scr_h =0;
VMUINT8 *layer_bufs[2] = {0,0};
VMINT layer_hdls[2] = {-1,-1};

Console console;
Telnet telnet;
T2Input t2input;

int main_timer_id = -1;

int prompt_timer_id = -1; // Timer for prompt
int timeout_timer_id = -1; // Timer for waiting telnet to connect
int timeout = 0; // Timeout counter

// Telnet host and port
char ip[BUF_SIZE];
int port = -3;

#ifndef WIN32
extern "C" void* malloc(int size){
	return vm_malloc(size);
}
extern "C" void free(void*prt){
	return vm_free(prt);
}

extern "C" void _sbrk(){}
extern "C" void _write(){}
extern "C" void _close(){}
extern "C" void _lseek(){}
extern "C" void _open(){}
extern "C" void _read(){}
extern "C" void _exit(){}
extern "C" void _getpid(){}
extern "C" void _kill(){}
extern "C" void _fstat(){}
extern "C" void _isatty(){}
#endif

void handle_sysevt(VMINT message, VMINT param);
void handle_keyevt(VMINT event, VMINT keycode);
void handle_penevt(VMINT event, VMINT x, VMINT y);


void vm_main(void){
	scr_w = vm_graphic_get_screen_width(); 
	scr_h = vm_graphic_get_screen_height();

	console.init();
	telnet.init();
	t2input.init();

	vm_reg_sysevt_callback(handle_sysevt);
	vm_reg_keyboard_callback(handle_keyevt);
	vm_reg_pen_callback(handle_penevt);
}

void draw(){
	vm_graphic_fill_rect(layer_bufs[1], 0, 0, scr_w, scr_h, tr_color, tr_color);
	vm_graphic_line(layer_bufs[1], console.cursor_x*char_width, (console.cursor_y+1)*char_height,
		(console.cursor_x+1)*char_width, (console.cursor_y+1)*char_height, console.cur_textcolor);
	t2input.draw();
	vm_graphic_flush_layer(layer_hdls, 2);
} 

void timer(int tid){
	telnet.update();
	draw();
}

void timeout_f(int tid){
	if (telnet.is_connected == 1) {
		// Connected
		t2input.input_mode = 0; // Change the input mode to telnet
		vm_delete_timer(timeout_timer_id); // Delete the timeout counter
	} else {
		timeout++; // Increase the timeout counter

		if(timeout > 25) {
			// After 25 seconds (you can change this duration) -> timeout and exit
			console_str_in("\nTimed out, exiting...");
			vm_exit_app(); // Exit
		}
	}
}

/*
 * We use port as the status flag before input it actual value
 * If port == -3 -> prompt for host input, then set port = -2
 * If port == -2 -> Check if the input has been done and if yes,
 * save the ip and prompt for port input, then set port = -1
 * If port == -1 -> Check if the input has been done, if yes set
 * the actual port value.
 */

void prompt(int tid) {
	if (port == -3) {
		// Prompt for host input
		console_str_in("Please enter the host name/ip: ");
		port = -2;
	} else if (port == -2 && t2input.input_done == 1){
		strcpy(ip, t2input.str_buf); // Save the ip

		console_str_in("\nPlease enter the port: ");
		
		// Free the buffer
		t2input.free_buffer();
		port = -1;
	} else if (port == -1 && t2input.input_done == 1){
		port = strtoi(t2input.str_buf); // Convert port to number
		
		if (port < 0) {
			// Invaild port or number
			console_str_in("\nInvaild port! Please enter the port: ");
		
			// Free the buffer
			t2input.free_buffer();
		} else {
			telnet.connect_to(ip, port); // Try connecting to host

			timeout_timer_id = vm_create_timer(1000, timeout_f);
			vm_delete_timer(prompt_timer_id); // Remove the prompt
		}
	}
}

void handle_sysevt(VMINT message, VMINT param) {
	switch (message) {
	case VM_MSG_CREATE:
	case VM_MSG_ACTIVE:
		layer_hdls[0] = vm_graphic_create_layer(0, 0, scr_w, scr_h, -1);
		layer_hdls[1] = vm_graphic_create_layer(0, 0, scr_w, scr_h, tr_color);
		
		vm_graphic_set_clip(0, 0, scr_w, scr_h);

		layer_bufs[0]=vm_graphic_get_layer_buffer(layer_hdls[0]);
		layer_bufs[1]=vm_graphic_get_layer_buffer(layer_hdls[1]);

		vm_switch_power_saving_mode(turn_off_mode);

		console.scr_buf=layer_bufs[0];
		console.draw_all();

		t2input.scr_buf=layer_bufs[1];
		t2input.layer_handle=layer_hdls[1];

		if(message == VM_MSG_CREATE){ //only when app start
			// Prompt for host & port to connect
			t2input.input_mode = 1; // Get input from keyboard to buffer

			console_str_in("Welcome to TelnetVXP!\n");
			console_str_in("Written by Ximik_Boda & TelnetVXP contributors\n");

			prompt_timer_id = vm_create_timer(1000, prompt); // Check the prompt for every 1 second
		}
		if(main_timer_id==-1)
			main_timer_id = vm_create_timer(1000/15, timer); //15 fps
		break;
		
	case VM_MSG_PAINT:
		draw();
		break;
		
	case VM_MSG_INACTIVE:
		vm_switch_power_saving_mode(turn_on_mode);
		if( layer_hdls[0] != -1 ){
			vm_graphic_delete_layer(layer_hdls[0]);
			vm_graphic_delete_layer(layer_hdls[1]);
		}
		if(main_timer_id!=-1)
			vm_delete_timer(main_timer_id);
		break;	
	case VM_MSG_QUIT:
		if( layer_hdls[0] != -1 ){
			vm_graphic_delete_layer(layer_hdls[0]);
			vm_graphic_delete_layer(layer_hdls[1]);
		}
		if(main_timer_id!=-1)
			vm_delete_timer(main_timer_id);
		break;	
	}
}

void handle_keyevt(VMINT event, VMINT keycode) {
#ifdef WIN32
	if(keycode>=VM_KEY_NUM1&&keycode<=VM_KEY_NUM3)
		keycode+=6;
	else if(keycode>=VM_KEY_NUM7&&keycode<=VM_KEY_NUM9)
		keycode-=6;
#endif
	t2input.handle_keyevt(event, keycode);
}

void handle_penevt(VMINT event, VMINT x, VMINT y){
	t2input.handle_penevt(event, x, y);
	draw();
}