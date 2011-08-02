#ifndef _TIMER3_H
#define _TIMER3_H

#include <cc2511_map.h>
#include <cc2511_types.h>
#include <stdio.h>
#include <timer_defs.h>

/* PreScaler functions */
uint8 getT3PreScaler();
BIT setT3PreScaler(uint8 preScaler);

/* IO Location functions*/
BIT setT3IoLocation(uint8 ioLocation);
uint8 getT3IoLocation();

/* functions to setup channel */
BIT setT3ChannelMode(uint8 channelNum, uint8 mode);
BIT setT3ChannelCompareMode(uint8 channelNum, uint8 compMode);
BIT setT3ChannelFunction(uint8 channelNum, uint8 function);
BIT t3ChannelInit(uint8 channelNum, uint8 mode, uint8 compMode, uint8 function);

/* functions to start/stop a timer */
BIT t3Mode(uint8 mode);
uint8 getT3Mode();

/* functions to set frequency of a timer */
BIT setT3Frequency(uint32 frequency);
uint16 calculateT3CompareValue(uint32 frequency);
uint16 calculateT3ModuloValue(uint32 preScalerTick, uint32 frequency);

/* general checker functions */
BIT checkT3Channel(uint8 channelNum);
BIT checkT3ChannelCompareMode(uint8 channelNum, uint8 compMode);

/* function to initalise a timer */
BIT t3Init(uint8 ioLocation, uint8 preScaler);

#endif
