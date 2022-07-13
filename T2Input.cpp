#include "T2Input.h"
#include "ProFont6x11.h"
#include "Console.h"

extern Telnet telnet;
extern Console console;

static int abs(int a){
	return a<0?-a:a;
}
const char * normal_keyboard[10][10] = 
{
	{"0", " ", "_", "\\", "/", "=", ":", ";", "<", ">"},
	{"1", ".", ",", "\'", "?", "!", "\"", "(', ')", "+", "-"},
	{"2", "a", "b", "c", "", "", "", "", "", ""},
	{"3", "d", "e", "f", "", "", "", "", "", ""},
	{"4", "g", "h", "i", "", "", "", "", "", ""},
	{"5", "j", "k", "l", "", "", "", "", "", ""},
	{"6", "m", "n", "o", "", "", "", "", "", ""},
	{"7", "p", "q", "r", "s", "", "", "", "", ""},
	{"8", "t", "u", "v", "", "", "", "", "", ""},
	{"9", "w", "x", "y", "z", "", "", "", "", ""},
};
const char * big_keyboard[10][10] = 
{
	{"0", " ", "_", "\\", "/", "=", ":", ";", "<", ">"},
	{"1", ".", ",", "\'", "?", "!", "\"", "(', ')", "+", "-"},
	{"2", "A", "B", "C", "", "", "", "", "", ""},
	{"3", "D", "E", "F", "", "", "", "", "", ""},
	{"4", "G", "H", "I", "", "", "", "", "", ""},
	{"5", "J", "K", "L", "", "", "", "", "", ""},
	{"6", "M", "N", "O", "", "", "", "", "", ""},
	{"7", "P", "Q", "R", "S", "", "", "", "", ""},
	{"8", "T", "U", "V", "", "", "", "", "", ""},
	{"9", "W", "X", "Y", "Z", "", "", "", "", ""},
};

const char * num_keyboard[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

const char* imput_modes[4]={"abc", "Abc", "ABC", "123"};


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

void T2Input::handle_penevt(VMINT event, VMINT x, VMINT y){
	switch(event){
		case VM_PEN_EVENT_DOUBLE_CLICK:
			break;
		case VM_PEN_EVENT_TAP:
			if(y<keyboard_h)
				draw_kb=!draw_kb;
			current_key = get_keycode(x, y);
			if(current_key!=255)
				handle_keyevt(VM_KEY_EVENT_DOWN, current_key);
			break;
		case VM_PEN_EVENT_RELEASE:
		case VM_PEN_EVENT_ABORT:
			if(current_key!=255)
				handle_keyevt(VM_KEY_EVENT_UP, current_key);
			current_key = 255;
			break;
		case VM_PEN_EVENT_MOVE:
			break;
		case VM_PEN_EVENT_LONG_TAP:
			if(current_key!=255)
				handle_keyevt(VM_KEY_EVENT_LONG_PRESS, current_key);
			break;
		case VM_PEN_EVENT_REPEAT:
			if(current_key!=255)
				handle_keyevt(VM_KEY_EVENT_REPEAT, current_key);
			break;

	}
}

void T2Input::send_c(const char*str){
	telnet.send_data((char*)str, strlen(str));
}

void T2Input::numpad_input(int keycode){ //TODO: remake this
	keycode-=VM_KEY_NUM0;
	if(cur_input_mode==NUM)
		send_c(num_keyboard[keycode]);
	else
		if(state==MAIN)
			last_imput_key = keycode, state = SECOND_CLICK;
		else{
			if(cur_input_mode==SMALL)
				send_c(normal_keyboard[last_imput_key][keycode]);
			else
				send_c(big_keyboard[last_imput_key][keycode]);
			state=MAIN;
		}
}

void T2Input::handle_keyevt(VMINT event, VMINT keycode){
	int time = vm_get_tick_count();
	switch(event){
		case VM_KEY_EVENT_UP:
			switch(keycode){
				case VM_KEY_UP:
					send_c("\033[A");
					break;
				case VM_KEY_DOWN:
					send_c("\033[B");
					break;
				case VM_KEY_RIGHT:
					send_c("\033[C");
					break;
				case VM_KEY_LEFT:
					send_c("\033[D");
					break;
				case VM_KEY_RIGHT_SOFTKEY:
					switch(state){
						case SECOND_CLICK:
							state=MAIN;
							break;
						default:
							send_c("\177");
							break;
					}
					break;
				case VM_KEY_LEFT_SOFTKEY:
					draw_kb=!draw_kb;
					break;
				case VM_KEY_OK:
					send_c("\r\n");
					break;
				case VM_KEY_POUND:
					cur_input_mode=Input_mode(((int)cur_input_mode+1)%4);
					last_input_time=time;
					break;
				default:
					if(keycode>=VM_KEY_NUM0&&keycode<=VM_KEY_NUM9)
						numpad_input(keycode);
					break;
			}
			break;
	}
}

void T2Input::draw_xy_char(int x, int y, const char*str){
	const unsigned short textcolor = 0xFFFF , backcolor = tr_color; 
	const unsigned char *font_ch=ProFont6x11+5 + 12*(*str) + 1;

	for(int i=0;i<char_height;++i){
		unsigned short* scr_buf= (unsigned short*)this->scr_buf + x+(y+i)*scr_w;
		for(int j=0;j<char_width;++j)
			if(((*font_ch)>>j)&1)
				scr_buf[j]=textcolor;;
		++font_ch;
	}
}
void T2Input::draw_xy_str(int x, int y, const char*str){
	const unsigned short textcolor = 0xFFFF , backcolor = tr_color; 
	for(int k = 0; str[k];++k){
		const unsigned char *font_ch=ProFont6x11+5 + 12*(str[k]) + 1;

		for(int i=0;i<char_height;++i){
			unsigned short* scr_buf= (unsigned short*)this->scr_buf + x + k*char_width +(y+i)*scr_w;
			for(int j=0;j<char_width;++j)
				if(((*font_ch)>>j)&1)
					scr_buf[j]=textcolor;
			++font_ch;
		}
	}
}

void T2Input::draw_xy_str_color(int x, int y, unsigned short textcolor,  unsigned short backcolor, const char*str){
	for(int k = 0; str[k];++k){
		const unsigned char *font_ch=ProFont6x11+5 + 12*(str[k]) + 1;

		for(int i=0;i<char_height;++i){
			unsigned short* scr_buf= (unsigned short*)this->scr_buf + x+k*char_width+(y+i)*scr_w;
			for(int j=0;j<char_width;++j)
				scr_buf[j]=((((*font_ch)>>j)&1)?textcolor:backcolor);
			++font_ch;
		}
	}
}

void T2Input::draw(){
	int time = vm_get_tick_count();

	if(draw_kb){ // draw screen keyboard
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

		draw_xy_str(key_w+key_w/2 -strlen("\\r\\n")*char_width/2, keyboard_h + (key_h-char_height)/2, "\\r\\n");

		typedef const char * temp[10][10];
		temp *keyboard_t =(temp*)&normal_keyboard; 
		switch(state){
			case MAIN:
				draw_xy_str(key_w*2+key_w/2 -strlen("Backspace")*char_width/2, keyboard_h + (key_h/2-char_height)/2, "Backspace");
				draw_xy_str(key_w*2+key_w/2 -3*char_width/2, scr_h - key_h + (key_h-char_height)/2, imput_modes[(int)cur_input_mode]);
				switch(cur_input_mode){
					case FIRST_BIG:
					case BIG:
						keyboard_t = (temp*)&big_keyboard; 
					case SMALL:
						for(int k=0; k<10; ++k){
							int m_x = ((k-1)%3)*key_w, m_y = ((k-1)/3)*key_h+keyboard_h+key_h;
							if(k==0)
								m_x = key_w, m_y = scr_h - key_h; 
							for(int i=0; i<4; ++i){
								int s_y = char_height/2 + i*(char_height) - 2;
								if(i==3)
									draw_xy_char(m_x+key_w/2 -char_width/2, m_y + s_y, keyboard_t[0][k][0]);
								else
									for(int j=0; j<3; ++j){
										int s_x = key_w/4*(j+1) - char_width/2;
										draw_xy_char(m_x+s_x, m_y + s_y, keyboard_t[0][k][1+i*3+j]);
									}
							}

						}
						break;
					case NUM:
						for(int k=0; k<10; ++k){
							int m_x = ((k-1)%3)*key_w, m_y = ((k-1)/3)*key_h+keyboard_h+key_h;
							if(k==0)
								m_x = key_w, m_y = scr_h - key_h; 
							draw_xy_char(m_x+key_w/2-char_width/2, m_y + key_h/2-char_height/2, num_keyboard[k]);
						}
						break;
				}
				break;
			case SECOND_CLICK:
				draw_xy_str(key_w*2+key_w/2 -strlen("Cancel")*char_width/2, keyboard_h + (key_h/2-char_height)/2, "Cancel");
				//draw_xy_str(key_w*2+key_w/2 -3*char_width/2, scr_h - key_h + (key_h-char_height)/2, imput_modes[(int)cur_input_mode]);
				switch(cur_input_mode){
					case FIRST_BIG:
					case BIG:
						keyboard_t = (temp*)&big_keyboard; 
					case SMALL:
						for(int k=0; k<10; ++k){
							int m_x = ((k-1)%3)*key_w, m_y = ((k-1)/3)*key_h+keyboard_h+key_h;
							if(k==0)
								m_x = key_w, m_y = scr_h - key_h; 
							draw_xy_char(m_x+(key_w-char_width)/2, m_y + key_h/2-char_height/2, keyboard_t[0][last_imput_key][k]);
						}
						break;
				}
				break;
		}
	}

	const unsigned short gray_color = VM_COLOR_888_TO_565(50, 50, 50); 
	if(!(time - last_input_time >= 1000 || last_input_time > time)){ //draw input mode
		int y = (console.cursor_y==0?char_height:0), x = scr_w - 3*char_width;
		draw_xy_str_color(x,y,0xFFFF,gray_color,imput_modes[(int)cur_input_mode]);
		//vm_graphic_fill_rect(scr_buf, 0, scr_h - key_h, key_w, key_h, gray_color, gray_color);
	}
		
}

void T2Input::init(){
	key_w = scr_w/3;
	//key_h = key_w/3*2;
	key_h = char_height*4+2;
	keyboard_h = scr_h - key_h*5;

	current_key = 255;

	draw_kb = vm_is_support_pen_touch();

	cur_input_mode = SMALL;
	last_input_time = 0;

	state = MAIN;

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
