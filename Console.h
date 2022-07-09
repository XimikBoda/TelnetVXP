#pragma once
#include "main.h"

const int char_width = 6, char_height = 11;
const int count_of_lines = 500;

struct Symbol{
	char ch;
	unsigned short textcolor, backcolor;
	Symbol(){
		ch=0, textcolor=0xFFFF, backcolor=0x0000;
	}
	void reset(){
		ch=0, textcolor=0xFFFF, backcolor=0x0000;
	}
};

class Console
{
public:
	Symbol *text[count_of_lines];

	enum Status{
		MAIN,
		ESCAPE,
		COMAND
	};

	int cursor_x, cursor_y;
	int saved_cursor_x, saved_cursor_y;
	int terminal_w, terminal_h;
	unsigned short main_color;
	unsigned short cur_textcolor, cur_backcolor; 

	VMUINT8* scr_buf;

	unsigned char narg, args[16];

	Status status;

	void putchar(char c);

	void putc(char c);
	void putstr(const char *str, int len = -1);

	void draw_cur_char();

	
	void draw_all();

	void init();
	void reset();
	~Console(void);
};

