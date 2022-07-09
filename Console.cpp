#include "Console.h"
#include "vmmm.h"
#include "ProFont6x11.h"
const char* Hex_ch = "0123456789ABCDF"; 

void Console::putchar(char c){//todo UTF-8
	switch(c){
		case 0x07:
			vm_vibrator_once();
			break;
		case 0x08:
			text[cursor_y][cursor_x].reset();
			//previos_p();
			break;
		case 0x09:
		case 0x0B:
		case 0x0C:
		case 0x7F:
			putchar('0');
			putchar('x');
			putchar(Hex_ch[(c&0xF0)>>8]);
			putchar(Hex_ch[c&0x0F]);
			break;
		case 0x0A:
			//new_line();
			break;
		case 0x0D:
			cursor_x=0;
			break;
		case 0x1B://ESC
			//args[narg++]=str[i];
			break;
		default:
			text[cursor_y][cursor_x].ch=c;
			text[cursor_y][cursor_x].textcolor=cur_textcolor;
			text[cursor_y][cursor_x].backcolor=cur_backcolor;
			//if(str[i]!=0)
			//	next_p();
			
			break;

	}
}

void Console::putc(char c){
	switch(status){
		case MAIN:
			putchar(c);
			break;
		case ESCAPE:
			break;
		case COMAND:
			break;
	}
}

void Console::putstr(const char *str, int len){
	if(len==-1)
		for(int i=0;str[i];++i)
			putc(str[1]);
	else
		for(int i=0;i<len;++i)
			putc(str[1]);
}

void Console::draw_cur_char(){
	const unsigned char *font_ch=ProFont6x11+5 + 12*text[cursor_y][cursor_x].ch + 1;
	for(int i=0;i<11;++i){
		unsigned short* scr_buf= (unsigned short*)scr_buf + cursor_x+(cursor_y+i)*scr_w;
		for(int j=0;j<6;++j)
				scr_buf[j]=((((*font_ch)>>j)&1)?cur_textcolor:cur_backcolor);
		++font_ch;
	}
}

void Console::draw_all(){
	vm_graphic_fill_rect(scr_buf, 0, 0, scr_w, scr_h, main_color, main_color);
}



void Console::reset(){
	cursor_x = cursor_y = saved_cursor_x = saved_cursor_y = 0;
	status=MAIN;
	cur_textcolor=0xFFFF, cur_backcolor=0x0000; 
}

void Console::init(){
	reset();
	terminal_w=scr_w/char_width;
	terminal_h=scr_h/char_height;
	main_color = 0x0000;

	scr_buf = 0;

	for(int i=0;i<count_of_lines;++i){
		text[i]=(Symbol*)vm_malloc((terminal_w+1)*sizeof(Symbol));
		//clear_line(i);
	}
}

Console::~Console(void){
	for(int i=0;i<count_of_lines;++i)
	vm_free(text[i]);
}
