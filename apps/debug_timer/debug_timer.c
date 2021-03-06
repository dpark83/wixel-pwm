#include <wixel.h>
#include <usb.h>
#include <usb_com.h>
#include <stdio.h>
#include <timer1.h>
#include <timer3.h>

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
    case '1':
	
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

		setT1ChannelFunction(CHANNEL0, PERIPHERAL);
		responseLength = sprintf(response, "NOTE=setT1ChannelFunction(CHANNEL0, PERIPHERAL)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();
		
		setT1ChannelFunction(CHANNEL0, GPIO);
		responseLength = sprintf(response, "NOTE=setT1ChannelFunction(CHANNEL0, GPIO)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT1ChannelFunction(CHANNEL1, PERIPHERAL);
		responseLength = sprintf(response, "NOTE=setT1ChannelFunction(CHANNEL1, PERIPHERAL)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();
		
		setT1ChannelFunction(CHANNEL1, GPIO);
		responseLength = sprintf(response, "NOTE=setT1ChannelFunction(CHANNEL1, GPIO)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT1ChannelFunction(CHANNEL2, PERIPHERAL);
		responseLength = sprintf(response, "NOTE=setT1ChannelFunction(CHANNEL2, PERIPHERAL)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();
		
		setT1ChannelFunction(CHANNEL2, GPIO);
		responseLength = sprintf(response, "NOTE=setT1ChannelFunction(CHANNEL2, GPIO)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();
		
		setT1IoLocation(IO_LOC_ALT_1);
		responseLength = sprintf(response, "NOTE=setT1IoLocation(IO_LOC_ALT_1)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT1ChannelFunction(CHANNEL0, PERIPHERAL);
		responseLength = sprintf(response, "NOTE=setT1ChannelFunction(CHANNEL0, PERIPHERAL)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();
		
		setT1ChannelFunction(CHANNEL0, GPIO);
		responseLength = sprintf(response, "NOTE=setT1ChannelFunction(CHANNEL0, GPIO)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT1ChannelFunction(CHANNEL1, PERIPHERAL);
		responseLength = sprintf(response, "NOTE=setT1ChannelFunction(CHANNEL1, PERIPHERAL)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();
		
		setT1ChannelFunction(CHANNEL1, GPIO);
		responseLength = sprintf(response, "NOTE=setT1ChannelFunction(CHANNEL1, GPIO)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT1ChannelFunction(CHANNEL2, PERIPHERAL);
		responseLength = sprintf(response, "NOTE=setT1ChannelFunction(CHANNEL2, PERIPHERAL)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();
		
		setT1ChannelFunction(CHANNEL2, GPIO);
		responseLength = sprintf(response, "NOTE=setT1ChannelFunction(CHANNEL2, GPIO)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();
		
		t1Mode(MODE_FREE);
		responseLength = sprintf(response, "NOTE=t1Mode(MODE_FREE)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		t1Start();
		responseLength = sprintf(response, "NOTE=t1Start()\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		t1Stop();
		responseLength = sprintf(response, "NOTE=t1Stop()\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();
		
		t1Mode(MODE_MODULO);
		responseLength = sprintf(response, "NOTE=t1Mode(MODE_MODULO)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		t1Start();
		responseLength = sprintf(response, "NOTE=t1Start()\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		t1Stop();
		responseLength = sprintf(response, "NOTE=t1Stop()\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();
		
		t1Mode(MODE_UPDOWN);
		responseLength = sprintf(response, "NOTE=t1Mode(MODE_UPDOWN)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		t1Start();
		responseLength = sprintf(response, "NOTE=t1Start()\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		t1Stop();
		responseLength = sprintf(response, "NOTE=t1Stop()\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();
		
		setT1ChannelMode(CHANNEL0, COMPARE_MODE);
		responseLength = sprintf(response, "NOTE=setT1ChannelMode(CHANNEL0, COMPARE_MODE)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();
		
		setT1ChannelMode(CHANNEL0, CAPTURE_MODE);
		responseLength = sprintf(response, "NOTE=setT1ChannelMode(CHANNEL0, CAPTURE_MODE)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT1ChannelMode(CHANNEL1, COMPARE_MODE);
		responseLength = sprintf(response, "NOTE=setT1ChannelMode(CHANNEL1, COMPARE_MODE)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();
		
		setT1ChannelMode(CHANNEL1, CAPTURE_MODE);
		responseLength = sprintf(response, "NOTE=setT1ChannelMode(CHANNEL1, CAPTURE_MODE)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();
		
		setT1ChannelMode(CHANNEL2, COMPARE_MODE);
		responseLength = sprintf(response, "NOTE=setT1ChannelMode(CHANNEL2, COMPARE_MODE)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();
		
		setT1ChannelMode(CHANNEL2, CAPTURE_MODE);
		responseLength = sprintf(response, "NOTE=setT1ChannelMode(CHANNEL2, CAPTURE_MODE)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT1ChannelCompareMode(CHANNEL0, CLR_ON_COMP_UP);
		responseLength = sprintf(response, "NOTE=setT1ChannelCompareMode(CHANNEL0, CLR_ON_COMP_UP)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT1ChannelCompareMode(CHANNEL0, SET_ON_COMP_UP);
		responseLength = sprintf(response, "NOTE=setT1ChannelCompareMode(CHANNEL0, SET_ON_COMP_UP)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT1ChannelCompareMode(CHANNEL0, TOGGLE_ON_COMP);
		responseLength = sprintf(response, "NOTE=setT1ChannelCompareMode(CHANNEL0, TOGGLE_ON_COMP)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT1ChannelCompareMode(CHANNEL0, CLR_ON_COMP);
		responseLength = sprintf(response, "NOTE=setT1ChannelCompareMode(CHANNEL0, CLR_ON_COMP)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT1ChannelCompareMode(CHANNEL0, SET_ON_COMP);
		responseLength = sprintf(response, "NOTE=setT1ChannelCompareMode(CHANNEL0, SET_ON_COMP)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT1ChannelCompareMode(CHANNEL1, DSM_MODE_ENABLE);
		responseLength = sprintf(response, "NOTE=setT1ChannelCompareMode(CHANNEL1, DSM_MODE_ENABLE)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT1ChannelCompareMode(CHANNEL1, CLR_SET);
		responseLength = sprintf(response, "NOTE=setT1ChannelCompareMode(CHANNEL1, CLR_SET)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT1ChannelCompareMode(CHANNEL1, SET_CLR);
		responseLength = sprintf(response, "NOTE=setT1ChannelCompareMode(CHANNEL1, SET_CLR)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();
		
		setT1ChannelCompareMode(CHANNEL1, CLR_ON_COMP_UP);
		responseLength = sprintf(response, "NOTE=setT1ChannelCompareMode(CHANNEL1, CLR_ON_COMP_UP)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();
		
		setT1ChannelCompareMode(CHANNEL1, SET_ON_COMP_UP);
		responseLength = sprintf(response, "NOTE=setT1ChannelCompareMode(CHANNEL1, SET_ON_COMP_UP)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT1ChannelCompareMode(CHANNEL1, TOGGLE_ON_COMP);
		responseLength = sprintf(response, "NOTE=setT1ChannelCompareMode(CHANNEL1, TOGGLE_ON_COMP)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT1ChannelCompareMode(CHANNEL1, CLR_ON_COMP);
		responseLength = sprintf(response, "NOTE=setT1ChannelCompareMode(CHANNEL1, CLR_ON_COMP)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT1ChannelCompareMode(CHANNEL1, SET_ON_COMP);
		responseLength = sprintf(response, "NOTE=setT1ChannelCompareMode(CHANNEL1, SET_ON_COMP)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT1ChannelCompareMode(CHANNEL2, CLR_SET);
		responseLength = sprintf(response, "NOTE=setT1ChannelCompareMode(CHANNEL2, CLR_SET)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT1ChannelCompareMode(CHANNEL2, SET_CLR);
		responseLength = sprintf(response, "NOTE=setT1ChannelCompareMode(CHANNEL2, SET_CLR)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();
		
		setT1ChannelCompareMode(CHANNEL2, CLR_ON_COMP_UP);
		responseLength = sprintf(response, "NOTE=setT1ChannelCompareMode(CHANNEL2, CLR_ON_COMP_UP)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();
		
		setT1ChannelCompareMode(CHANNEL2, SET_ON_COMP_UP);
		responseLength = sprintf(response, "NOTE=setT1ChannelCompareMode(CHANNEL2, SET_ON_COMP_UP)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT1ChannelCompareMode(CHANNEL2, TOGGLE_ON_COMP);
		responseLength = sprintf(response, "NOTE=setT1ChannelCompareMode(CHANNEL2, TOGGLE_ON_COMP)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT1ChannelCompareMode(CHANNEL2, CLR_ON_COMP);
		responseLength = sprintf(response, "NOTE=setT1ChannelCompareMode(CHANNEL2, CLR_ON_COMP)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT1ChannelCompareMode(CHANNEL2, SET_ON_COMP);
		responseLength = sprintf(response, "NOTE=setT1ChannelCompareMode(CHANNEL2, SET_ON_COMP)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();
		
        break;
    case '3':
	
		responseLength = sprintf(response, "NOTE=Initial settings\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT3PreScaler(PRESCALER_128);
		responseLength = sprintf(response, "NOTE=setT3PreScaler(PRESCALER_128)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT3PreScaler(PRESCALER_64);
		responseLength = sprintf(response, "NOTE=setT3PreScaler(PRESCALER_64)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT3PreScaler(PRESCALER_32);
		responseLength = sprintf(response, "NOTE=setT3PreScaler(PRESCALER_32)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT3PreScaler(PRESCALER_16);
		responseLength = sprintf(response, "NOTE=setT3PreScaler(PRESCALER_16)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT3PreScaler(PRESCALER_8);
		responseLength = sprintf(response, "NOTE=setT3PreScaler(PRESCALER_8)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT3PreScaler(PRESCALER_4);
		responseLength = sprintf(response, "NOTE=setT3PreScaler(PRESCALER_4)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT3PreScaler(PRESCALER_2);
		responseLength = sprintf(response, "NOTE=setT3PreScaler(PRESCALER_2)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT3PreScaler(PRESCALER_1);
		responseLength = sprintf(response, "NOTE=setT3PreScaler(PRESCALER_1)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT3IoLocation(IO_LOC_ALT_2);
		responseLength = sprintf(response, "NOTE=setT3IoLocation(IO_LOC_ALT_2)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT3ChannelFunction(CHANNEL0, PERIPHERAL);
		responseLength = sprintf(response, "NOTE=setT3ChannelFunction(CHANNEL0, PERIPHERAL)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();
		
		setT3ChannelFunction(CHANNEL0, GPIO);
		responseLength = sprintf(response, "NOTE=setT3ChannelFunction(CHANNEL0, GPIO)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT3ChannelFunction(CHANNEL1, PERIPHERAL);
		responseLength = sprintf(response, "NOTE=setT3ChannelFunction(CHANNEL1, PERIPHERAL)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();
		
		setT3ChannelFunction(CHANNEL1, GPIO);
		responseLength = sprintf(response, "NOTE=setT3ChannelFunction(CHANNEL1, GPIO)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();
		
		setT3IoLocation(IO_LOC_ALT_1);
		responseLength = sprintf(response, "NOTE=setT3IoLocation(IO_LOC_ALT_1)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT3ChannelFunction(CHANNEL0, PERIPHERAL);
		responseLength = sprintf(response, "NOTE=setT3ChannelFunction(CHANNEL0, PERIPHERAL)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();
		
		setT3ChannelFunction(CHANNEL0, GPIO);
		responseLength = sprintf(response, "NOTE=setT3ChannelFunction(CHANNEL0, GPIO)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT3ChannelFunction(CHANNEL1, PERIPHERAL);
		responseLength = sprintf(response, "NOTE=setT3ChannelFunction(CHANNEL1, PERIPHERAL)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();
		
		setT3ChannelFunction(CHANNEL1, GPIO);
		responseLength = sprintf(response, "NOTE=setT3ChannelFunction(CHANNEL1, GPIO)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		t3Mode(MODE_FREE);
		responseLength = sprintf(response, "NOTE=t3Mode(MODE_FREE)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		t3Start();
		responseLength = sprintf(response, "NOTE=t3Start()\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		t3Stop();
		responseLength = sprintf(response, "NOTE=t3Stop()\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();
		
		t3Mode(MODE_DOWN);
		responseLength = sprintf(response, "NOTE=t3Mode(MODE_DOWN)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		t3Start();
		responseLength = sprintf(response, "NOTE=t3Start()\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		t3Stop();
		responseLength = sprintf(response, "NOTE=t3Stop()\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		t3Mode(MODE_MODULO);
		responseLength = sprintf(response, "NOTE=t3Mode(MODE_MODULO)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		t3Start();
		responseLength = sprintf(response, "NOTE=t3Start()\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		t3Stop();
		responseLength = sprintf(response, "NOTE=t3Stop()\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		t3Mode(MODE_UPDOWN);
		responseLength = sprintf(response, "NOTE=t3Mode(MODE_UPDOWN)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		t3Start();
		responseLength = sprintf(response, "NOTE=t3Start()\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		t3Stop();
		responseLength = sprintf(response, "NOTE=t3Stop()\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT3ChannelMode(CHANNEL0, ENABLE);
		responseLength = sprintf(response, "NOTE=setT3ChannelMode(CHANNEL0, ENABLE)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();
		
		setT3ChannelMode(CHANNEL0, DISABLE);
		responseLength = sprintf(response, "NOTE=setT3ChannelMode(CHANNEL0, DISABLE)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT3ChannelMode(CHANNEL1, ENABLE);
		responseLength = sprintf(response, "NOTE=setT3ChannelMode(CHANNEL1, ENABLE)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();
		
		setT3ChannelMode(CHANNEL1, DISABLE);
		responseLength = sprintf(response, "NOTE=setT3ChannelMode(CHANNEL1, DISABLE)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();


		setT3ChannelCompareMode(CHANNEL0, CLR_SET);
		responseLength = sprintf(response, "NOTE=setT3ChannelCompareMode(CHANNEL0, CLR_SET)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT3ChannelCompareMode(CHANNEL0, SET_CLR);
		responseLength = sprintf(response, "NOTE=setT3ChannelCompareMode(CHANNEL0, SET_CLR)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();
		
		setT3ChannelCompareMode(CHANNEL0, CLR_ON_COMP_UP);
		responseLength = sprintf(response, "NOTE=setT3ChannelCompareMode(CHANNEL0, CLR_ON_COMP_UP)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();
		
		setT3ChannelCompareMode(CHANNEL0, SET_ON_COMP_UP);
		responseLength = sprintf(response, "NOTE=setT3ChannelCompareMode(CHANNEL0, SET_ON_COMP_UP)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT3ChannelCompareMode(CHANNEL0, TOGGLE_ON_COMP);
		responseLength = sprintf(response, "NOTE=setT3ChannelCompareMode(CHANNEL0, TOGGLE_ON_COMP)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT3ChannelCompareMode(CHANNEL0, CLR_ON_COMP);
		responseLength = sprintf(response, "NOTE=setT3ChannelCompareMode(CHANNEL0, CLR_ON_COMP)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT3ChannelCompareMode(CHANNEL0, SET_ON_COMP);
		responseLength = sprintf(response, "NOTE=setT3ChannelCompareMode(CHANNEL0, SET_ON_COMP)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT3ChannelCompareMode(CHANNEL1, CLR_SET);
		responseLength = sprintf(response, "NOTE=setT3ChannelCompareMode(CHANNEL1, CLR_SET)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT3ChannelCompareMode(CHANNEL1, SET_CLR);
		responseLength = sprintf(response, "NOTE=setT3ChannelCompareMode(CHANNEL1, SET_CLR)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();
		
		setT3ChannelCompareMode(CHANNEL1, CLR_ON_COMP_UP);
		responseLength = sprintf(response, "NOTE=setT3ChannelCompareMode(CHANNEL1, CLR_ON_COMP_UP)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();
		
		setT3ChannelCompareMode(CHANNEL1, SET_ON_COMP_UP);
		responseLength = sprintf(response, "NOTE=setT3ChannelCompareMode(CHANNEL1, SET_ON_COMP_UP)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT3ChannelCompareMode(CHANNEL1, TOGGLE_ON_COMP);
		responseLength = sprintf(response, "NOTE=setT3ChannelCompareMode(CHANNEL1, TOGGLE_ON_COMP)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT3ChannelCompareMode(CHANNEL1, CLR_ON_COMP);
		responseLength = sprintf(response, "NOTE=setT3ChannelCompareMode(CHANNEL1, CLR_ON_COMP)\r\n");
		usbComTxSend(response, responseLength);
		debugOutput();

		setT3ChannelCompareMode(CHANNEL1, SET_ON_COMP);
		responseLength = sprintf(response, "NOTE=setT3ChannelCompareMode(CHANNEL1, SET_ON_COMP)\r\n");
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
