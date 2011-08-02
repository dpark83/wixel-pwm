#ifndef _TIMER4_H
#define _TIMER4_H

#include <cc2511_map.h>
#include <cc2511_types.h>
#include <stdio.h>
#include <timer_defs.h>

/* PreScaler functions */
uint8 getT4PreScaler();
BIT setT4PreScaler(uint8 preScaler);

/* functions to setup channel */
BIT setT4ChannelMode(uint8 channelNum, uint8 mode);
BIT setT4ChannelCompareMode(uint8 channelNum, uint8 compMode);
BIT setT4ChannelFunction(uint8 channelNum, uint8 function);
BIT t4ChannelInit(uint8 channelNum, uint8 mode, uint8 compMode, uint8 function);

/* functions to start/stop a timer */
BIT t4Mode(uint8 mode);
uint8 getT4Mode();

/* functions to set frequency of a timer */
BIT setT4Frequency(uint32 frequency);
uint16 calculateT4CompareValue(uint32 frequency);
uint16 calculateModuloValue(uint32 preScalerTick, uint32 frequency);

/* general checker functions */
BIT checkT4Channel(uint8 channelNum);
BIT checkT4ChannelCompareMode(uint8 channelNum, uint8 compMode);

/* function to initalise a timer */
BIT t4Init(uint8 preScaler);

#endif
