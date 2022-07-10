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
	Symbol **main_text;
	Symbol *history_text[count_of_lines];

	enum Status{
		MAIN,
		ESCAPE,
		ARGS,
		CSI
	};

	int cursor_x, cursor_y;
	int saved_cursor_x, saved_cursor_y;
	int terminal_w, terminal_h;

	int scroll_start_row, scroll_end_row, scroll_value; 

	bool bright;


	unsigned short main_color;
	unsigned short cur_textcolor, cur_backcolor; 

	VMUINT8* scr_buf;

	int narg, args[16];

	Status status, last_status;

	int get_n_param(int n, int a=0);
	void attributes();

	void clear_args();

	void analise_args(char c);
	void analise_CSI(char c);
	void analise_escape(char c);
	void put_char(char c);

	void put_c(char c);
	void putstr(const char *str, int len = -1);


	void previos_p();
	void next_p();
	void new_line();

	void draw_cur_char();

	
	void draw_all();

	void init();
	void reset();
	~Console(void);
};

