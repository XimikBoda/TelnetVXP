#include "Console.h"
#include "vmmm.h"
#include "ProFont6x11.h"
const char* Hex_ch = "0123456789ABCDF"; 

const unsigned short maincolors[8] = 
{
	VM_COLOR_888_TO_565(0,0,0),
	VM_COLOR_888_TO_565(170,0,0),
	VM_COLOR_888_TO_565(0,170,0),
	VM_COLOR_888_TO_565(170,85,0),
	VM_COLOR_888_TO_565(0,0,170),
	VM_COLOR_888_TO_565(170,0,170),
	VM_COLOR_888_TO_565(0,170,170),
	VM_COLOR_888_TO_565(170,170,170)
};
const unsigned short brightcolors[8] = 
{
	VM_COLOR_888_TO_565(85,85,85),
	VM_COLOR_888_TO_565(255,85,85),
	VM_COLOR_888_TO_565(85,255,85),
	VM_COLOR_888_TO_565(255,255,85),
	VM_COLOR_888_TO_565(85,85,255),
	VM_COLOR_888_TO_565(255,85,255),
	VM_COLOR_888_TO_565(85,255,255),
	VM_COLOR_888_TO_565(255,255,255)
};

static bool isdigit(int c){
	return c>='0' && c<='9';
}
int Console::get_n_param(int n, int a){
	return args[n]?args[n]:a;
}

void Console::attributes(){
	for(int i=0;i<narg;++i){
		int pp=get_n_param(i), p=pp%10;

		if(pp==0)
			if(i==0)
				cur_textcolor=0xFFFF, cur_backcolor=0x0000, bright=0;

		if(bright&&p!=8&&((pp/10)==3||(pp/10)==4))
			pp+=60;

		switch(pp/10){
			case 0:
				switch(p){
					case 1:
						bright=1;
						break;
				}
				break;
			case 2:
				switch(p){
					case 1:
						bright=0;
						break;
				}
				break;
			case 3:
				if(p==9)
					cur_textcolor=0xFFFF;
				else if(p==8){
					if(i==0&&get_n_param(1)==2)
						cur_textcolor=VM_COLOR_888_TO_565(get_n_param(2),
						get_n_param(3),get_n_param(4));
					return;
				}else
					cur_textcolor=maincolors[p];
				break;
			case 4:
				if(p==9)
					cur_backcolor=0x0000;
				else if(p==8){
					if(i==0&&get_n_param(1)==2)
						cur_backcolor=VM_COLOR_888_TO_565(get_n_param(2),
						get_n_param(3),get_n_param(4));
					return;
				}
				else
					cur_backcolor=maincolors[p];
				break;
			case 9:
				if(p==9)
					cur_textcolor=0xFFFF;
				else
					cur_textcolor=brightcolors[p];
				break;
			case 10:
				if(p==9)
					cur_backcolor=0x0000;
				else
					cur_backcolor=brightcolors[p];
				break;
		}
	}
}

void Console::clear_args(){
	for(int i=0; i<narg; ++i)
		args[i]=0;
	narg=0;
}

void Console::analise_args(char c){
	if(narg==16)
		status=MAIN;
	else if(isdigit(c))
		args[narg]=args[narg]*10+(c-'0');
	else if(c==';')
		++narg;
	else{
		++narg;
		status=last_status;
		put_c(c);
	}
}

void Console::analise_CSI(char c){
	if(isdigit(c)||c==';'){
		clear_args();
		last_status=CSI;
		status=ARGS;
		analise_args(c);
	}else
		switch(c){
			case 'm':
				attributes();
				status=MAIN;
				break;

			default:
				printf("%c\n", c);
				status=MAIN;
				break;
		}
}

void Console::analise_escape(char c){
	switch(c){
		case '[':
			status=CSI;
			break;
		default:
			printf("%c\n", c);
			status=MAIN;
			break;
	}
}

void Console::put_char(char c){//todo UTF-8
	switch(c){
		case 0x07:
			vm_vibrator_once();
			break;
		case 0x08:
			main_text[cursor_y][cursor_x].reset();
			previos_p();
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
			new_line();
			break;
		case 0x0D:
			cursor_x=0;
			break;
		case 0x1B://ESC
			status = ESCAPE;
			break;
		default:
			main_text[cursor_y][cursor_x].ch=c;
			main_text[cursor_y][cursor_x].textcolor=cur_textcolor;
			main_text[cursor_y][cursor_x].backcolor=cur_backcolor;
			draw_cur_char();
			if(c!=0)
				next_p();
			
			break;

	}
}

void Console::put_c(char c){
	switch(status){
		case MAIN:
			put_char(c);
			break;
		case ESCAPE:
			analise_escape(c);
			break;
		case ARGS:
			analise_args(c);
			break;
		case CSI:
			analise_CSI(c);
			break;
	}
	//vm_graphic_flush_layer(layer_hdls, 1);
}

void Console::putstr(const char *str, int len){
	if(len==-1)
		for(int i=0;str[i];++i)
			put_c(str[i]);
	else
		for(int i=0;i<len;++i)
			put_c(str[i]);
}


void Console::previos_p(){
	if(cursor_x>0)
		cursor_x--;
}
void Console::next_p(){
	if(cursor_x>=terminal_w-1){//TODO: fix this
		new_line();
	}else{
		cursor_x++;
	}
}

void Console::new_line(){
	cursor_y=cursor_y+1;
	cursor_x=0;
	if(cursor_y>terminal_h)
		cursor_y=terminal_h;
}


void Console::draw_cur_char(){
	const unsigned char *font_ch=ProFont6x11+5 + 12*main_text[cursor_y][cursor_x].ch + 1;
	for(int i=0;i<char_height;++i){
		unsigned short* scr_buf= (unsigned short*)this->scr_buf + cursor_x*char_width+(cursor_y*char_height+i)*scr_w;
		for(int j=0;j<char_width;++j)
				scr_buf[j]=((((*font_ch)>>j)&1)?cur_textcolor:cur_backcolor);
		++font_ch;
	}
}

void Console::draw_all(){
	vm_graphic_fill_rect(scr_buf, 0, 0, scr_w, scr_h, main_color, main_color);
}



void Console::reset(){
	cursor_x = cursor_y = saved_cursor_x = saved_cursor_y = 0;
	last_status=status=MAIN;
	cur_textcolor=0xFFFF, cur_backcolor=0x0000; 
	bright=0;
}

void Console::init(){
	terminal_w=scr_w/char_width;
	terminal_h=scr_h/char_height;

	scroll_start_row = 0;
	scroll_end_row = terminal_w;
	scroll_value = 0;

	main_color = 0x0000;

	narg=16;
	clear_args();

	scr_buf = 0;

	reset();

	main_text=(Symbol**)vm_malloc((terminal_h+1)*sizeof(Symbol*));

	for(int i=0; i<=terminal_h; ++i){
		main_text[i]=(Symbol*)vm_malloc((terminal_w+1)*sizeof(Symbol));
		for(int j=0; j<= terminal_w; ++j)
			main_text[i][j].reset();
	}
		

	//for(int i=0;i<count_of_lines;++i){
	//	text[i]=(Symbol*)vm_malloc((terminal_w+1)*sizeof(Symbol));
		//clear_line(i);
	//}
}

Console::~Console(void){
	for(int i=0;i<terminal_h;++i)
		vm_free(main_text[i]);
	vm_free(main_text);
}
