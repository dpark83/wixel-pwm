#include <wixel.h>
#include <usb.h>
#include <usb_com.h>
#include <stdio.h>
#include <timer1.h>
#include <timer3.h>
#include <timer4.h>

/* VARIABLES ******************************************************************/

BIT serialProtocolError = 0;
uint8 commandByte;
uint8 dataBytes[32];
uint8 dataBytesLeft = 0;
uint8 dataBytesReceived;
uint8 XDATA response[32];

uint8 responseLength;

/* FUNCTIONS ******************************************************************/

void debugOutput();

void updateLeds()
{
    usbShowStatusWithGreenLed();
    LED_RED(serialProtocolError);
}

void processByte(uint8 byteReceived)
{
    switch(byteReceived)
    {
    case 't':
	
		responseLength = sprintf(response, "NOTE=Initial settings\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT1PreScaler(PRESCALER_128);
		responseLength = sprintf(response, "NOTE=setT1PreScaler(PRESCALER_128)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT1PreScaler(PRESCALER_32);
		responseLength = sprintf(response, "NOTE=setT1PreScaler(PRESCALER_32)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT1PreScaler(PRESCALER_8);
		responseLength = sprintf(response, "NOTE=setT1PreScaler(PRESCALER_8)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT1PreScaler(PRESCALER_1);
		responseLength = sprintf(response, "NOTE=setT1PreScaler(PRESCALER_1)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT1IoLocation(IO_LOC_ALT_2);
		responseLength = sprintf(response, "NOTE=setT1IoLocation(IO_LOC_ALT_2)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT1IoLocation(IO_LOC_ALT_1);
		responseLength = sprintf(response, "NOTE=setT1IoLocation(IO_LOC_ALT_1)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		t1Mode(MODE_FREE);
		responseLength = sprintf(response, "NOTE=t1Mode(MODE_FREE)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();
		
		t1Mode(MODE_MODULO);
		responseLength = sprintf(response, "NOTE=t1Mode(MODE_MODULO)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		t1Mode(MODE_UPDOWN);
		responseLength = sprintf(response, "NOTE=t1Mode(MODE_UPDOWN)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();
		
		t1Mode(MODE_OFF);
		responseLength = sprintf(response, "NOTE=t1Mode(MODE_OFF)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		
        break;
    }
}

void debugOutput() {
	responseLength = sprintf(response, "PERCFG=0x%02x\r\n", PERCFG);
	usbComTxSend(response, responseLength);

	responseLength = sprintf(response, "TIMIF=0x%02x\r\n", TIMIF);
	usbComTxSend(response, responseLength);

	responseLength = sprintf(response, "P0SEL=0x%02x\r\n", P0SEL);
	usbComTxSend(response, responseLength);

	responseLength = sprintf(response, "P1SEL=0x%02x\r\n", P1SEL);
	usbComTxSend(response, responseLength);
	
	responseLength = sprintf(response, "T1CNTH/L=0x%02x%02x\r\n", T1CNTH, T1CNTL);
	usbComTxSend(response, responseLength);

	responseLength = sprintf(response, "T1CTL=0x%02x\r\n", T1CTL);
	usbComTxSend(response, responseLength);

	responseLength = sprintf(response, "T1CCTL0=0x%02x\r\n", T1CCTL0);
	usbComTxSend(response, responseLength);

	responseLength = sprintf(response, "T1CC0H/L=0x%02x%02x\r\n", T1CC0H, T1CC0L);
	usbComTxSend(response, responseLength);

	responseLength = sprintf(response, "T1CCTL1=0x%02x\r\n", T1CCTL1);
	usbComTxSend(response, responseLength);

	responseLength = sprintf(response, "T1CC1H/L=0x%02x%02x\r\n", T1CC1H, T1CC1L);
	usbComTxSend(response, responseLength);

	responseLength = sprintf(response, "T1CCTL2=0x%02x\r\n", T1CCTL2);
	usbComTxSend(response, responseLength);

	responseLength = sprintf(response, "T1CC2H/L=0x%02x%02x\r\n", T1CC2H, T1CC2L);
	usbComTxSend(response, responseLength);
	
	responseLength = sprintf(response, "T3CNT=0x%02x\r\n", T3CNT);
	usbComTxSend(response, responseLength);

	responseLength = sprintf(response, "T3CTL=0x%02x\r\n", T3CTL);
	usbComTxSend(response, responseLength);

	responseLength = sprintf(response, "T3CCTL0=0x%02x\r\n", T3CCTL0);
	usbComTxSend(response, responseLength);

	responseLength = sprintf(response, "T3CC0=0x%02x\r\n", T3CC0);
	usbComTxSend(response, responseLength);

	responseLength = sprintf(response, "T3CCTL1=0x%02x\r\n", T3CCTL1);
	usbComTxSend(response, responseLength);

	responseLength = sprintf(response, "T3CC1=0x%02x\r\n", T3CC1);
	usbComTxSend(response, responseLength);
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
