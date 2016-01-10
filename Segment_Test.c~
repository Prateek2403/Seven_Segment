/*
#
# This program is to drive a 7-Segment LED display with a use of button.
# Connections are as Follows -
# PORTA - 2 connected to 'd' of 7-Segment 
# PORTA - 3 connected to 'a' of 7-Segment
# PORTA - 4 connected to 'b' of 7-Segment
# PORTA - 5 connected to 'c' of 7-Segment
# PORTA - 6 connected to 'e' of 7-Segment
# PORTA - 7 connected to 'g' of 7-Segment
# PORTE - 1 connected to 'f' of 7-Segment
#
#        b
#	 _
#    a |   | c
#	 _
#
#    e | d | f
#	 _
#        g
#
# This program is for 'COMMON ANODE' type 7-Segment Display.
# This means when the Logic 0 or GND is up for the LED pins then LEDs will low.
# Update - Update with the use of Timer and Interrupts.
#	   Timer0A is used. Interrupt for Timer0A.
#	   To start the timer and counting There needs to be an Input on PORT_E - Pin 2.
#
*/


#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/tm4c123gh6pm.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "drivers/buttons.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"


uint32_t Counter = 0, ret_button;
volatile uint32_t ui32Loop;
bool cont = true;
uint8_t ret_pin = 0;

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


void Timer0IntHandler(void)
{

	TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);	

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


int main ()
{

	enum ButtonStates Bs;
	uint32_t ui32Period;

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);	 
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

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
	GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_2);
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_2);
    	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_3);
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_4);
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_5);
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_6);
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_7);

	ButtonsInit();

    //
    // Timer Configuration for TIMER A 
    //

	TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);

	ui32Period = (SysCtlClockGet());
	TimerLoadSet(TIMER0_BASE, TIMER_A, ui32Period -1);

	IntEnable(INT_TIMER0A);

	TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

	IntMasterEnable();

	

    //
    // Loop forever.
    //
    while(1)
    {

	ret_button  = ButtonsPoll(0,0);

	Bs = delay_debounce( Bs );

	ret_pin = GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_2);

	if (ret_pin == GPIO_PIN_2)
	{
	  	TimerEnable(TIMER0_BASE, TIMER_A);
	}
	else if((ret_button & ALL_BUTTONS) == RIGHT_BUTTON)
	{
		TimerDisable(TIMER0_BASE, TIMER_A);
	}

    }

}
