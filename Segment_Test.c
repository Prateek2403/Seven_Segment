/*

This program is to drive a 7-Segment LED display with a use of button.
Connections are as Follows -
PORTA - 2 connected to 'd' of 7-Segment 
PORTA - 3 connected to 'a' of 7-Segment
PORTA - 4 connected to 'b' of 7-Segment
PORTA - 5 connected to 'c' of 7-Segment
PORTA - 6 connected to 'e' of 7-Segment
PORTA - 7 connected to 'g' of 7-Segment
PORTE - 1 connected to 'f' of 7-Segment

        b
	_
    a |   | c
	_

    e | d | f
	_
        g

This program is for 'COMMON ANODE' type 7-Segment Display.
This means when the Logic 0 or GND is up for the LED pins then LEDs will low.

*/


#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "drivers/buttons.h"

uint32_t counter = 0, ret_button;
volatile uint32_t ui32Loop;
bool cont = true;

enum ButtonStates { UP, DOWN, PRESS, RELEASE };
 
enum ButtonStates delay_debounce(enum ButtonStates button_state) 
{        
	
    ret_button  = ButtonsPoll(0,0);

    if ((ret_button & ALL_BUTTONS) == LEFT_BUTTON)   /* if pressed     */
    {                      
        if (button_state == PRESS)
        {
            button_state = DOWN;
        } 
        if (button_state == UP)
         {
            SysCtlDelay(500);
            if ((ret_button & ALL_BUTTONS) == LEFT_BUTTON)
            {
                button_state = PRESS;
            }
        } 
    } 
    else 
    {                                 
        if (button_state == RELEASE)  /* if not pressed */
        {
            button_state = UP;
        } 
        if (button_state == DOWN)
        {
            if (!((ret_button & ALL_BUTTONS) == LEFT_BUTTON))
            {
                SysCtlDelay(500); 

                if (!((ret_button & ALL_BUTTONS) == LEFT_BUTTON))
                {
                    button_state = RELEASE;
                }
            }
        }
    }
    return button_state;
}


void Reset_Segment(void)
{
	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, GPIO_PIN_2);
	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, GPIO_PIN_3);
	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, GPIO_PIN_4);
	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, GPIO_PIN_5);
	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, GPIO_PIN_6);
	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, GPIO_PIN_7);
	GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, GPIO_PIN_1);
}


int main ()
{

	enum ButtonStates Bs;
	uint8_t Counter = 0;

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);	 
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    //
    // Check if the peripheral access is enabled.
    //
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
    }

    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA))
    {
    }

    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE))
    {
    }

    //
    // Enable the GPIO pin for the LED (PF3).  Set the direction as output, and
    // enable the GPIO pin for digital function.
    //
	GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_1);

	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_2);
    	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_3);
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_4);
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_5);
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_6);
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_7);

	ButtonsInit();

    //
    // Loop forever.
    //
    while(1)
    {

	ret_button  = ButtonsPoll(0,0);

	Bs = delay_debounce( Bs );

	if (Bs == PRESS)
	{
	  	
		if( Counter >= 10)
			Counter = 0;

		switch(Counter)
		{
			case 0:	Reset_Segment();
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0x00);
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, 0x00);
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, 0x00);
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, 0x00);
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, 0x00);
				GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0x00);
				break;
			case 1: Reset_Segment();
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, 0x00);
				GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0x00);
				break;
			case 2: Reset_Segment();
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, 0x00);
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, 0x00);
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, 0x00);
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, 0x00);
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, 0x00);
				break;
			case 3: Reset_Segment();
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, 0x00);
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, 0x00);
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, 0x00);
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, 0x00);
				GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0x00);
				break;
			case 4: Reset_Segment();
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, 0x00);
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0x00);
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, 0x00);
				GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0x00);
				break;
			case 5: Reset_Segment();
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, 0x00);
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0x00);
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, 0x00);
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, 0x00);
				GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0x00);
				break;
			case 6: Reset_Segment();
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, 0x00);
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0x00);
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, 0x00);
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, 0x00);
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, 0x00);
				GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0x00);
				break;
			case 7: Reset_Segment();
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, 0x00);
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, 0x00);
				GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0x00);
				break;
			case 8: Reset_Segment();
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, 0x00);
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0x00);
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, 0x00);
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, 0x00);
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, 0x00);
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, 0x00);
				GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0x00);
				break;
			case 9: Reset_Segment();
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, 0x00);
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0x00);
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, 0x00);
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, 0x00);
				GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0x00);
				break;
			default:break;
		}
	
		Counter++;
	  
	}
	else
	{
		
	}

    }

}
