#pragma once
#include "main.h"

const int temp_unsended_data_max_size = 1024;

class Telnet
{
public:
	enum Status{
		MAIN,
		COMMAND,
		OPTION_DATA
	}; 
	enum Comands{
		SE = 0xF0,
		SB = 0xFA,
		WILL = 0xFB,
		WONT = 0xFC,
		DO = 0xFD,
		DONT = 0xFE,
	};

	bool is_connected;
	int tcp_handle;
	unsigned char temp_data[1024];

	unsigned char temp_unsend_data[temp_unsended_data_max_size];
	int temp_unsend_data_size;

	char temp_option_data[100];
	int temp_option_data_pos;

	unsigned char option, command, data_option;

	Status status, last_status;

	void send_unsended();
	void send_data(char *data, int len);

	void send_response_command(unsigned char command, unsigned char option);
	void send_response_command(unsigned char command);

	void DO_command();
	void DONT_command();

	void update();

	void tcp_callback(VMINT handle, VMINT event);
	void connect_to(const char*ip, int port);

	void init();
	~Telnet(void);
};

