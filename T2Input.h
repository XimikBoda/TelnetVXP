#pragma once
#include "main.h"
#include "Telnet.h"

class T2Input
{
public:
	
	VMUINT8* scr_buf;
	int layer_handle;
	
	int key_w, key_h;
	int keyboard_h;

	bool draw_kb;

	int current_key;

	int squares[8][2];

	int get_keycode(int x, int y);

	void send_c(const char*str);

	void numpad_input(int keycode);

	void show_current_pressed_key();

	void handle_penevt(VMINT event, VMINT x, VMINT y);
	void handle_keyevt(VMINT event, VMINT keycode);

	void draw_xy_char(int x, int y, const char*str);

	void draw();
	void init();
	~T2Input(void);
};

