#ifndef _TIMER1_H
#define _TIMER1_H

#include <cc2511_map.h>
#include <cc2511_types.h>
#include <stdio.h>

#define	CHANNEL0		0
#define	CHANNEL1		1
#define	CHANNEL2		2

#define	PRESCALER_1			1
#define	PRESCALER_8			8
#define	PRESCALER_32		32
#define	PRESCALER_128		128

#define	SET_ON_COMP		0x00
#define	CLR_ON_COMP		0x08
#define	TOGGLE_ON_COMP	0x10
#define	SET_ON_COMP_UP	0x18
#define	CLR_ON_COMP_UP	0x20
#define	SET_CLR			0x28
#define	CLR_SET			0x30
#define	DSM_MODE_ENABLE	0x38

#define	CAPTURE_MODE	0
#define	COMPARE_MODE	1

#define	IO_LOC_ALT_1	0
#define	IO_LOC_ALT_2	1

#define GPIO		0
#define PERIPHERAL	1

#define	T1_MODE_OFF			0x00
#define	T1_MODE_FREE		0x01
#define	T1_MODE_MODULO		0x02
#define	T1_MODE_UPDOWN		0x03

/* PreScaler functions */
uint8 getT1PreScaler();
BIT setT1PreScaler(uint8 preScaler);

/* IO Location functions*/
BIT setT1IoLocation(uint8 ioLocation);
uint8 getT1IoLocation();

/* functions to setup channel */
BIT setT1ChannelMode(uint8 channelNum, uint8 mode);
BIT setT1ChannelCompareMode(uint8 channelNum, uint8 compMode);
BIT setT1ChannelFunction(uint8 channelNum, uint8 function);
BIT t1ChannelInit(uint8 channelNum, uint8 mode, uint8 compMode, uint8 function);

/* functions to start/stop a timer */
BIT t1Mode(uint8 mode);
uint8 getT1Mode();

/* functions to set frequency of a timer */
BIT setT1Frequency(uint32 frequency);
uint16 calculateT1CompareValue(uint32 frequency);
uint16 calculateModuloValue(uint32 preScalerTick, uint32 frequency);

/* general checker functions */
BIT checkT1Mode(uint8 mode);
BIT checkT1Channel(uint8 channelNum);
BIT checkChannelMode(uint8 mode);
BIT checkT1ChannelCompareMode(uint8 channelNum, uint8 compMode);
BIT checkChannelFunction(uint8 function);

/* function to initalise a timer */
BIT t1Init(uint8 ioLocation, uint8 preScaler);

#endif
