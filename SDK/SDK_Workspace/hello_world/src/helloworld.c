/*
 * Copyright (c) 2009-2012 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 *
 *
 *
 */


#include <stdio.h>
#include "platform.h"
#include "xparameters.h"
#include "xio.h"
#include "vga_periph_mem.h"

void print(char *str);
typedef enum direction {UP,DOWN, LEFT, RIGHT} direction;
direction dir = DOWN, prev_dir = DOWN;

int main()
{
    init_platform();
    unsigned char string_s[] = "IDEMO\n";
    unsigned char c = 'A';

    VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x00, 0x0);// direct mode   0
    VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x04, 0x3);// display_mode  1
    VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x08, 0x1);// show frame      2
    //VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x0C, 0x1);// font size       3
    //VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x10, 0xFFFFFF);// foreground 4
    //VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x14, 0x0000FF);// background color 5
    VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x18, 0xFF0000);// frame color      6

    set_font_size(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, 2);
    set_foreground_color(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, 0xFFFF00);
    set_background_color(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, 0x0000FF);

    print("Hello World\n\r");

    clear_text_screen(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR);
    clear_graphics_screen(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR);
    //draw_square(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR);
    int x = 0, y = 240, t;
    unsigned int a,b, step_y, step_x;
    a =40;
    b = 320;
    step_y = 5;
    step_x = 0;
    while(1) {
    	draw_rectangle(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, x, y, a, b);

    	/*switch(dir) {
    	case UP:
    		step_y = -10;
    		if (y < 240) {
				step_x = 10;
				step_y = 0;
				dir = RIGHT;
			} else if(y == 0) {
				step_x = 10;
				step_y = 0;
				dir = RIGHT;
			}
    		break;
    	case DOWN:
    		step_y = -10;
			if (y < 240) {
				step_x = 10;
				step_y = 0;
				dir = RIGHT;
			}
    		break;
    	case LEFT:
    		step_x = -10;
			if (x == 0) {
				step_x = 0;
				step_y = -10;
				dir = UP;
			}
    		break;
    	case RIGHT:
    		step_x = 10;
			if (x+b+step_x > 640 && prev_dir == UP) {
				step_x = - 10;
				step_y = 0;
				dir = LEFT;
			}
    		break;
    	}*/

    	if (y+a+step_y > 480) {
    		step_y = -5;
    	}
    	if (y == 0) {
			step_y = 5;
		}
    	y+=step_y;
    	//x+=y%2;
    	//x = x > 640 ? 0 : y;
    	t = 1000000;
    	while(t)
    		t--;
    }

    set_cursor(350);
    print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, string_s, 5);
    //print_char(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, c);

    return 0;
}
