#include <wixel.h>
#include <usb.h>
#include <usb_com.h>
#include <stdio.h>
#include <timer.h>

int32 CODE param_led_change_ms = 500;
int32 CODE param_led_increment = 32;
int32 CODE param_min_led_value = 32;
int32 CODE param_max_led_value = 224;

uint32 lastToggle = 0;
BIT ledDir = 1; /* 0=down; 1=up */

uint8 ledValue = param_min_led_value;

void updateLeds()
{
    usbShowStatusWithGreenLed();

	if (getMs() - lastToggle >= param_led_change_ms/2)
	{
		T1CC1H = 0x00;
		T1CC1L = ledValue&0xFF;
		lastToggle = getMs();
		
		if (ledValue >= param_max_led_value) {
			ledValue -= param_led_increment;
			ledDir = 0;
		} else if (ledValue <= param_min_led_value) {
			ledValue += param_led_increment;
			ledDir = 1;
		} else {
			if (ledDir == 0) {
				ledValue -= param_led_increment;
			} else {
				ledValue += param_led_increment;
			}
		}
	}
}

void main()
{
	uint8 t; /* timer */
	uint8 c; /* channel */
	uint32 f; /* frequency in hz */
	
	t = TIMER1;
	c = CHANNEL1;
	f = 200;

    systemInit();
    usbInit();

	/* PWM duty cycle */
	T1CC1L = 0x40;
	T1CC1H = 0x00;

	/* setup Timer 1, alt location 2 and prescaler 128*/
	timerInit(t, IO_LOC_ALT_2, PRESCALER_128);
	/* setup Channel 1 of Timer 1, compare mode, clear on compare up and peripheral*/
	channelInit(t, c, COMPARE_MODE, CLR_ON_COMP_UP, PERIPHERAL);
	/* start Timer 1 by setting it's mode to up/down */
	timerMode(t, T1_MODE_MODULO);
	/* set Timer 1 frequency */
	setFrequency(TIMER1, f);

    while(1)
    {
        boardService();
        updateLeds();
        usbComService();
    }
}
