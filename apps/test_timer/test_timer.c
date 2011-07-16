#include <wixel.h>
#include <usb.h>
#include <usb_com.h>
#include <stdio.h>
#include <timer.h>

/* VARIABLES ******************************************************************/

int32 CODE param_led_change_ms = 500;
int32 CODE param_led_increment = 32;
int32 CODE param_min_led_value = 32;
int32 CODE param_max_led_value = 224;

uint32 lastToggle = 0;
BIT ledDir = 1; /* 0=down; 1=up */
BIT ledOn = 0; /* 0=on; 1=off */

int16 ledValue = param_min_led_value;

/** True if a serial protocol error occurred recently. */
BIT serialProtocolError = 0;

/** The binary command byte received from the computer. */
uint8 commandByte;

/** The binary data bytes received from the computer. */
uint8 dataBytes[32];

/** The number of data bytes we are waiting for to complete the current command.
 * If this is zero, it means we are not currently in the middle of processing
 * a binary command. */
uint8 dataBytesLeft = 0;

/** The number of data bytes received so far for the current binary command.
 * If dataBytesLeft==0, this is undefined. */
uint8 dataBytesReceived;

/** A temporary buffer used for composing responses to the computer before
 * they are sent.  Must be bigger than the longest possible response to any
 * command.
 */
uint8 XDATA response[32];

/* FUNCTIONS ******************************************************************/

void updateLeds()
{
    uint8 responseLength;

    usbShowStatusWithGreenLed();
    LED_RED(serialProtocolError);
	if (ledOn == 1) {
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

			/* Debug output to see ledValue and Direction, each time it changes it outputs
               so not advisable to set param_led_change_ms too low as have no idea what may happen*/
			/*
			responseLength = sprintf(response, "ledVal=0x%02x ledDir0x%02x\r\n", ledValue, ledDir);
			usbComTxSend(response, responseLength);
			*/
		}
	}
}

void processByte(uint8 byteReceived)
{
    uint8 responseLength;
    switch(byteReceived)
    {
    case 't':

		responseLength = sprintf(response, "T1CC0H=0x%02x T1CC0L=0x%02x\r\n", T1CC0H, T1CC0L);
        usbComTxSend(response, responseLength);
		// PWM freq
		T1CC0L = 0xff;
		T1CC0H = 0x01;
		responseLength = sprintf(response, "T1CC0H=0x%02x T1CC0L=0x%02x\r\n", T1CC0H, T1CC0L);
        usbComTxSend(response, responseLength);

		responseLength = sprintf(response, "T1CC1H=0x%02x T1CC1L=0x%02x\r\n", T1CC1H, T1CC1L);
        usbComTxSend(response, responseLength);
		// PWM duty cycle
		T1CC1L = 0x40;
		T1CC1H = 0x00;
		responseLength = sprintf(response, "T1CC1H=0x%02x T1CC1L=0x%02x\r\n", T1CC1H, T1CC1L);
        usbComTxSend(response, responseLength);

		responseLength = sprintf(response, "T1CCTL1=0x%02x\r\n", T1CCTL1);
        usbComTxSend(response, responseLength);
		/* Timer 1 channel 1 set compare mode 4 */
		T1_CH1_MODE_SET(COMPARE_MODE);
		responseLength = sprintf(response, "T1CCTL1=0x%02x\r\n", T1CCTL1);
        usbComTxSend(response, responseLength);
		T1_CH1_COMP_MODE_SET(CLR_ON_COMP_UP);
		responseLength = sprintf(response, "T1CCTL1=0x%02x\r\n", T1CCTL1);
        usbComTxSend(response, responseLength);

		responseLength = sprintf(response, "T1CTL=0x%02x\r\n", T1CTL);
        usbComTxSend(response, responseLength);
		/* Prescaler set to Tick Freq / 128 */
		T1_PRESCALER_SET(T1_PRESCALER_128);
		responseLength = sprintf(response, "T1CTL=0x%02x\r\n", T1CTL);
        usbComTxSend(response, responseLength);

		responseLength = sprintf(response, "PERCFG=0x%02x\r\n", PERCFG);
        usbComTxSend(response, responseLength);
		/* Timer 1 CFG set to Alt 2 location */
		T1_IO_LOC_SET(ALT_2_LOC);
		responseLength = sprintf(response, "PERCFG=0x%02x\r\n", PERCFG);
        usbComTxSend(response, responseLength);

		responseLength = sprintf(response, "P1SEL=0x%02x\r\n", P1SEL);
        usbComTxSend(response, responseLength);
		/* P1_1 set peripheral func which associated with Timer 1 output */
		P1_FUNC_SET(1, PERIPHERAL);
		responseLength = sprintf(response, "P1SEL=0x%02x\r\n", P1SEL);
        usbComTxSend(response, responseLength);

		responseLength = sprintf(response, "T1CTL=0x%02x\r\n", T1CTL);
        usbComTxSend(response, responseLength);
		/* set up/dowm mode */
		T1_MODE_SET(T1_MODE_UPDOWN);
		responseLength = sprintf(response, "T1CTL=0x%02x\r\n", T1CTL);
        usbComTxSend(response, responseLength);

		ledOn = 1;
		
        break;
    }
}

/** Checks for new bytes available on the USB virtual COM port
 * and processes all that are available. */
void processBytesFromUsb()
{
    uint8 bytesLeft = usbComRxAvailable();
    while(bytesLeft && usbComTxAvailable() >= sizeof(response))
    {
        processByte(usbComRxReceiveByte());
        bytesLeft--;
    }
}

void main()
{
    systemInit();
    usbInit();

    while(1)
    {
        boardService();
        updateLeds();
        usbComService();
        processBytesFromUsb();
    }
}
