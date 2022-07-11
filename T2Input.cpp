#include "T2Input.h"

static int abs(int a){
	return a<0?-a:a;
}

int T2Input::get_keycode(int x, int y){
	if(y<scr_h-key_h*5)
		return 255;
	int k_x = x/key_w, k_y = (y - keyboard_h)/key_h;
	switch(k_y){
		case 0:
			switch(k_x){
				case 0:
					if((y - keyboard_h)<key_h/2)
						return VM_KEY_LEFT_SOFTKEY;
					break;
				case 1:
					{
						if(abs(key_w+key_w/2-x)<key_w/4 && abs(keyboard_h+key_h/2-y)<key_h/4)
							return VM_KEY_OK;
						float a1 = (float)key_h/(float)key_w, a2 = -a1, b1 = keyboard_h - key_h, b2 = keyboard_h + key_h*2;
						bool p1 = y < a1*(float)x + b1, p2 = y < a2*(float)x + b2;
						if(p1)
							if(p2)
								return VM_KEY_UP;
							else
								return VM_KEY_RIGHT;
						else
							if(p2)
								return VM_KEY_LEFT;
							else
								return VM_KEY_DOWN;
					}
					break;
				case 2:
					if((y - keyboard_h)<key_h/2)
						return VM_KEY_RIGHT_SOFTKEY;
					break;
			}
			break;
		case 1:
			return VM_KEY_NUM1+k_x;
			break;
		case 2:
			return VM_KEY_NUM4+k_x;
			break;
		case 3:
			return VM_KEY_NUM7+k_x;
			break;
		case 4:
			switch(k_x){
				case 0:
					return VM_KEY_STAR;
					break;
				case 1:
					return VM_KEY_NUM0;
					break;
				case 2:
					return VM_KEY_POUND;
					break;
			}
			break;
	}
	return 255;
}

void T2Input::show_current_pressed_key(){
	const unsigned short fill_color = VM_COLOR_888_TO_565(0,128,0);
	vm_graphic_color color;
	color.vm_color_565 = fill_color;
	vm_graphic_setcolor(&color);

	if(current_key==255)
		return;
	if(current_key>=VM_KEY_NUM1 && current_key <= VM_KEY_NUM9)
		vm_graphic_fill_rect(scr_buf, ((current_key-VM_KEY_NUM1)%3)*key_w, 
		((current_key-VM_KEY_NUM1)/3)*key_h + keyboard_h + key_h, key_w, key_h, fill_color, fill_color);
	else
		switch(current_key){
			case VM_KEY_LEFT_SOFTKEY:
				vm_graphic_fill_rect(scr_buf, 0, keyboard_h, key_w, key_h/2, fill_color, fill_color);
				break;
			case VM_KEY_RIGHT_SOFTKEY:
				vm_graphic_fill_rect(scr_buf, key_w*2, keyboard_h, key_w, key_h/2, fill_color, fill_color);
				break;
			case VM_KEY_OK:
				vm_graphic_fill_rect(scr_buf, key_w + key_w/4, keyboard_h + key_h/4, key_w/2, key_h/2, fill_color, fill_color);
				break;
			case VM_KEY_UP:
				{
					vm_graphic_point points[4]=
					{
						{squares[0][0],squares[0][1]},
						{squares[1][0],squares[1][1]},
						{squares[5][0],squares[5][1]},
						{squares[4][0],squares[4][1]},
					};
					vm_graphic_fill_polygon(layer_handle, points, 4);
				}
				break;
			case VM_KEY_DOWN:
				{
					vm_graphic_point points[4]=
					{
						{squares[2][0],squares[2][1]},
						{squares[3][0],squares[3][1]},
						{squares[7][0],squares[7][1]},
						{squares[6][0],squares[6][1]},
					};
					vm_graphic_fill_polygon(layer_handle, points, 4);
				}
				break;
			case VM_KEY_LEFT:
				{
					vm_graphic_point points[4]=
					{
						{squares[3][0],squares[3][1]},
						{squares[0][0],squares[0][1]},
						{squares[4][0],squares[4][1]},
						{squares[7][0],squares[7][1]},
					};
					vm_graphic_fill_polygon(layer_handle, points, 4);
				}
				break;
			case VM_KEY_RIGHT:
				{
					vm_graphic_point points[4]=
					{
						{squares[1][0],squares[1][1]},
						{squares[2][0],squares[2][1]},
						{squares[6][0],squares[6][1]},
						{squares[5][0],squares[5][1]},
					};
					vm_graphic_fill_polygon(layer_handle, points, 4);
				}
				break;
			case VM_KEY_STAR:
				vm_graphic_fill_rect(scr_buf, 0, scr_h - key_h, key_w, key_h, fill_color, fill_color);
				break;
			case VM_KEY_NUM0:
				vm_graphic_fill_rect(scr_buf, key_w, scr_h - key_h, key_w, key_h, fill_color, fill_color);
				break;
			case VM_KEY_POUND:
				vm_graphic_fill_rect(scr_buf, key_w*2, scr_h - key_h, key_w, key_h, fill_color, fill_color);
				break;
		}
}

void  T2Input::handle_penevt(VMINT event, VMINT x, VMINT y){
	current_key = get_keycode(x, y);
	switch(event){
		case VM_PEN_EVENT_TAP:
		case VM_PEN_EVENT_DOUBLE_CLICK:
			break;
		case VM_PEN_EVENT_RELEASE:
		case VM_PEN_EVENT_ABORT:
			break;
		case VM_PEN_EVENT_MOVE:
		case VM_PEN_EVENT_LONG_TAP:
		case VM_PEN_EVENT_REPEAT:
			break;

	}
}

void T2Input::draw(){
	show_current_pressed_key();
	for(int i=0; i<5; ++i)
		vm_graphic_line(scr_buf, 0, scr_h - (i+1)*key_h, scr_w,  scr_h - (i+1)*key_h, 0xFFFF);

	vm_graphic_line(scr_buf, key_w, keyboard_h, key_w,  scr_h, 0xFFFF);
	vm_graphic_line(scr_buf, key_w*2, keyboard_h, key_w*2,  scr_h, 0xFFFF);

	vm_graphic_line(scr_buf, 0, keyboard_h + key_h/2, key_w, keyboard_h + key_h/2, 0xFFFF);
	vm_graphic_line(scr_buf, key_w*2, keyboard_h + key_h/2, scr_w, keyboard_h + key_h/2, 0xFFFF);

	for(int i=0; i<4; ++i){
		vm_graphic_line(scr_buf, squares[i][0], squares[i][1], squares[i+4][0], squares[i+4][1], 0xFFFF);
		vm_graphic_line(scr_buf, squares[i+4][0], squares[i+4][1], squares[(i+1)%4+4][0], squares[(i+1)%4+4][1], 0xFFFF);
	}
}

void T2Input::init(){
	key_w = scr_w/3;
	key_h = key_w/3*2;
	keyboard_h = scr_h - key_h*5;

	current_key = 255;

	squares[0][0] = key_w, squares[0][1] = keyboard_h;
	squares[1][0] = key_w*2, squares[1][1] = keyboard_h;
	squares[2][0] = key_w*2, squares[2][1] = keyboard_h + key_h;
	squares[3][0] = key_w, squares[3][1] = keyboard_h + key_h;
	squares[4][0] = key_w + key_w/4, squares[4][1] = keyboard_h + key_h/4;
	squares[5][0] = key_w*2 - key_w/4, squares[5][1] = keyboard_h + key_h/4;
	squares[6][0] = key_w*2 - key_w/4, squares[6][1] = keyboard_h + key_h - key_h/4;
	squares[7][0] = key_w + key_w/4, squares[7][1] = keyboard_h + key_h - key_h/4;
}

T2Input::~T2Input(void)
{
}
