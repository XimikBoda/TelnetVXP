#include "main.h"
#include "Console.h"

//Global
int scr_w = 0, scr_h =0;
VMUINT8 *layer_bufs[2] = {0,0};
VMINT layer_hdls[2] = {-1,-1};

Console console;

void handle_sysevt(VMINT message, VMINT param);
void handle_keyevt(VMINT event, VMINT keycode);
void handle_penevt(VMINT event, VMINT x, VMINT y);


void vm_main(void){
	scr_w = vm_graphic_get_screen_width(); 
	scr_h = vm_graphic_get_screen_height();

	console.init();
	vm_reg_sysevt_callback(handle_sysevt);
	vm_reg_keyboard_callback(handle_keyevt);
	//vm_reg_pen_callback(handle_penevt);
}

void draw(){
	vm_graphic_fill_rect(layer_bufs[1], 0, 0, scr_w, scr_h, tr_color, tr_color);
	vm_graphic_flush_layer(layer_hdls, 2);
}

void handle_sysevt(VMINT message, VMINT param) {
	switch (message) {
	case VM_MSG_CREATE:
	case VM_MSG_ACTIVE:
		layer_hdls[0] = vm_graphic_create_layer(0, 0, scr_w, scr_h, -1);
		layer_hdls[1] = vm_graphic_create_layer(0, 0, scr_w, scr_h, tr_color);
		
		vm_graphic_set_clip(0, 0, scr_w, scr_h);

		layer_bufs[0]=vm_graphic_get_layer_buffer(layer_hdls[0]);
		layer_bufs[1]=vm_graphic_get_layer_buffer(layer_hdls[1]);

		vm_switch_power_saving_mode(turn_off_mode);

		console.scr_buf=layer_bufs[0];
		console.draw_all();

		console.putstr("Test\n");

		{
			char tmp[100];
			int i, j, n;

			for (i = 0; i < 11; i++) {
				for (j = 0; j < 10; j++) {
					n = 10 * i + j;
					if (n > 107) break;
					sprintf(tmp,"\033[%dm %3d\033[m", n, n);
					console.putstr(tmp);
				}
				console.putstr("\n\033[m");
			}
		}
		break;
		
	case VM_MSG_PAINT:
		draw();
		break;
		
	case VM_MSG_INACTIVE:
		vm_switch_power_saving_mode(turn_on_mode);
		if( layer_hdls[0] != -1 ){
			vm_graphic_delete_layer(layer_hdls[0]);
			vm_graphic_delete_layer(layer_hdls[1]);
		}
		break;	
	case VM_MSG_QUIT:
		if( layer_hdls[0] != -1 ){
			vm_graphic_delete_layer(layer_hdls[0]);
			vm_graphic_delete_layer(layer_hdls[1]);
		}
		break;	
	}
}

void handle_keyevt(VMINT event, VMINT keycode) {
	switch(event){
		case VM_KEY_EVENT_DOWN:
			console.putstr("Test scroll\n");
			draw();
			switch(event){
				case VM_KEY_OK:
				case VM_KEY_VOL_UP:
					break;
				case VM_KEY_LEFT_SOFTKEY:
					break;
			}
			break;
	}
}