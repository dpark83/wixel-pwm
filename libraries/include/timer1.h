#ifndef _TIMER1_H
#define _TIMER1_H

#include <cc2511_map.h>
#include <cc2511_types.h>
#include <stdio.h>
#include <timer_defs.h>

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
uint16 calculateT1ModuloValue(uint32 preScalerTick, uint32 frequency);

/* general checker functions */
BIT checkT1Channel(uint8 channelNum);
BIT checkT1ChannelCompareMode(uint8 channelNum, uint8 compMode);

/* function to initalise a timer */
BIT t1Init(uint8 ioLocation, uint8 preScaler);

#endif
