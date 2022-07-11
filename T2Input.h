#pragma once
#include "main.h"

class T2Input
{
public:
	
	VMUINT8* scr_buf;
	int layer_handle;
	
	int key_w, key_h;
	int keyboard_h;

	int current_key;

	int squares[8][2];

	int get_keycode(int x, int y);

	void show_current_pressed_key();

	void handle_penevt(VMINT event, VMINT x, VMINT y);

	void draw();
	void init();
	~T2Input(void);
};

