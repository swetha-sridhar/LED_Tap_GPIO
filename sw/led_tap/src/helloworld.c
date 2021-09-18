/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

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
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xgpio.h"
#include "sleep.h"
#include "xstatus.h"

#define LED1 0xF
#define LED_DELAY     10000000

#define GPIO_OUTPUT_DEVICE_ID  XPAR_GPIO_0_DEVICE_ID /* Defined device ID */
#define GPIO_INPUT_DEVICE_ID  XPAR_GPIO_1_DEVICE_ID

#define LED_CHANNEL 1

/* Defining instance of the driver for push button */
XGpio GpioOutput;
XGpio GpioInput;


/* LED blinking logic */
int main()
{
//	volatile int Delay;
	int status;
	int readData;
    init_platform();
    xil_printf("\r\nTap LED\r\n");
    xil_printf("Initializing the GPIO output driver \r\n");
    status= XGpio_Initialize(&GpioOutput, GPIO_OUTPUT_DEVICE_ID);
    if(status != XST_SUCCESS){
    	xil_printf("Output GPIO initialization failed \r\n");
    }
    else{
    	xil_printf("Output GPIO initialization Success \r\n");
    }

    xil_printf("Initializing the GPIO input driver \r\n");
        status= XGpio_Initialize(&GpioInput, GPIO_INPUT_DEVICE_ID);
        if(status != XST_SUCCESS){
        	xil_printf("Input GPIO initialization failed \r\n");
        }
        else{
        	xil_printf("Input GPIO initialization Success \r\n");
        }

    XGpio_SetDataDirection(&GpioOutput, LED_CHANNEL, LED1);

    while(1){
//    	XGpio_DiscreteWrite(&GpioOutput, LED_CHANNEL, LED1); /* Set LED High */
//    	sleep(1);
//    	XGpio_DiscreteClear(&GpioOutput, LED_CHANNEL, LED1); /* Clear the LED */
//    	sleep(1);

    	readData= XGpio_DiscreteRead(&GpioInput, LED_CHANNEL);
//    	xil_printf("Data read from GPIO Input is  0x%x \n\r", readData);


		if(readData==0x1){
			XGpio_DiscreteWrite(&GpioOutput, LED_CHANNEL, 0x1);
			xil_printf("SW3, readData=0x%x \r\n", readData);

		}

		else if(readData==0x4){
			XGpio_DiscreteWrite(&GpioOutput, LED_CHANNEL, 0x2);
			xil_printf("SW5, readData=0x%x \r\n", readData);
		}

		else if(readData==0x2){
			XGpio_DiscreteWrite(&GpioOutput, LED_CHANNEL, 0x4);
			xil_printf("SW4, readData=0x%x \r\n", readData);
		}

		else if(readData==0x8){
			XGpio_DiscreteWrite(&GpioOutput, LED_CHANNEL, 0x8);
			xil_printf("SW7, readData=0x%x \r\n", readData);
		}
		else if(readData==0x10){
			XGpio_DiscreteWrite(&GpioOutput, LED_CHANNEL, 0xF);
			xil_printf("SW6, readData=0x%x \r\n", readData);
		}
    }
    cleanup_platform();
    return 0;
}
