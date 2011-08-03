/*! \file timer1.h
 *  The <code>timer.lib</code> library allows you to configure the
 *  16-bit timer (Timer 1) and the 8-bit timers (Timer 3 & 4).
 *
 *  To use this library, you must include timer1.h, timer3.h or timer4.h
 *  in your app:
\code
#include <timer1.h>  // for Timer 1
#include <timer3.h>  // for Timer 3
#include <timer4.h>  // for Timer 4
\endcode
 *
 * It is best to look at the API for the timer that you want to use as there
 * slight differences between all the timers.
 *
 * This library does not yet include the ability to set or get interupt flags.
 */

#ifndef _TIMER1_H
#define _TIMER1_H

#include <cc2511_map.h>
#include <cc2511_types.h>
#include <stdio.h>
#include <timer_defs.h>

/*! Initializes the timer with it's pin location and prescaler.
 *
 * \param ioLocation can be: #IO_LOC_ALT_1 (uses pin P0_2 to P0_4)
 * or #IO_LOC_ALT_2 (use pins P1_0 to P1_2)
 * \param preScaler can be: #PRESCALER_1, #PRESCALER_8, #PRESCALER_32
 * or #PRESCALER_128
 *
 * \return 0 if all the parameters are valid, 1 if a parameter was invalid.
 *
 */
BIT t1Init(uint8 ioLocation, uint8 preScaler);

/*! Sets the prescaler, T1CTL.DIV
 *
 * \param preScaler can be: #PRESCALER_1, #PRESCALER_8, #PRESCALER_32
 * or #PRESCALER_128
 *
 */
BIT setT1PreScaler(uint8 preScaler);

/*! Gets the configured prescaler, T1CTL.DIV
 *
 * \return The configured prescaler: #PRESCALER_1, #PRESCALER_8, #PRESCALER_32
 * or #PRESCALER_128
 *
 */
uint8 getT1PreScaler();

/*! Sets the pin location, PERCFG.T1CFG
 *
 * \param ioLocation can be: #IO_LOC_ALT_1 or #IO_LOC_ALT_2
 *
 * \return 0 for success, 1 for failure
 *
 */
BIT setT1IoLocation(uint8 ioLocation);

/*! Gets the configured pin location, PERCFG.T1CFG
 *
 * \return The configured pin location, either #IO_LOC_ALT_1 or
 * #IO_LOC_ALT_2
 *
 */
uint8 getT1IoLocation();

/* functions to setup channel */
BIT setT1ChannelMode(uint8 channelNum, uint8 mode);
BIT setT1ChannelCompareMode(uint8 channelNum, uint8 compMode);
BIT setT1ChannelFunction(uint8 channelNum, uint8 function);
BIT t1ChannelInit(uint8 channelNum, uint8 mode, uint8 compMode, uint8 function);

/*! Sets the timer mode, T1CTL.MODE
 *
 * \param mode can be: 
 *  MODE_FREE, MODE_MODULO or MODE_UPDOWN
 *
 * \return 0 for success, 1 for failure
 *
 */
BIT t1Mode(uint8 mode);

/*! Gets the configured timer mode, T1CTL.MODE
 *
 * \return The configured timer mode, can be: 
 *  MODE_FREE, MODE_MODULO or MODE_UPDOWN
 */
uint8 getT1Mode();

/*! Starts the timer
 */
void t1Start();

/*! Stops the timer
 */
void t1Stop();

/*! Sets the timer frequency, T1CC0H/L
 *
 * This uses the timer mode and prescaler to figure out how to calculate.
 * Free-running mode does not have a configurable frequency.
 *
 * \param frequency the wanted frequency in Hz
 *
 * \return 0 for success, 1 for failure
 *
 */
BIT setT1Frequency(uint32 frequency);

uint16 calculateT1CompareValue(uint32 frequency);

uint16 calculateT1ModuloValue(uint32 preScalerTick, uint32 frequency);

/*! Checks if the channel is valid for the timer
 *
 * \param channelNum can be: #CHANNEL0, #CHANNEL1 or #CHANNEL2
 *
 * \return 0 if the parameter is valid for this timer, 1 if a parameter was
 * invalid.
 *
 */
BIT checkT1Channel(uint8 channelNum);

/*! Checks if the compare mode is valid for the channel on the timer
 *
 * \param channelNum should be either #CHANNEL0, #CHANNEL1 or #CHANNEL2
 * \param compMode can be: SET_ON_COMP, CLR_ON_COMP, TOGGLE_ON_COMP, 
 *  SET_ON_COMP_UP, CLR_ON_COMP_UP, SET_CLR (CHANNEL1/2 only), 
 * CLR_SET (CHANNEL1/2 only) or DSM_MODE_ENABLE (CHANNEL1 only)
 *
 * \return 0 if the parameters are valid for this timer, 1 if a parameter was
 * invalid.
 *
 */
BIT checkT1ChannelCompareMode(uint8 channelNum, uint8 compMode);

#endif /* _TIMER1_H */
