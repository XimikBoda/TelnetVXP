#include "Console_io.h"
extern Console console;
extern Telnet telnet;
extern T2Input t2input;

void console_char_in(char ch){
	console.put_c(ch);
}

void console_str_in(const char* str){
	console.putstr(str);
}

void console_str_with_length_in(const char* str, int length){
	console.putstr(str, length);
}

void console_char_out(char ch){
	static char temp_str[2] = {ch, 0};
	telnet.send_data(temp_str);
}

void console_str_out(const char* str){
	telnet.send_data((char*)str);
}

void console_str_with_length_out(const char* str, int length){
	telnet.send_data((char*)str, length);
}