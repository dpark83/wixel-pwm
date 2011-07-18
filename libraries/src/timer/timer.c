#include <timer.h>
#include <cc2511_types.h>
#include <stdio.h>

/*

TICKSPD = 000 = 24Mhz
CLKSPD = 000 = 24Mhz

fXOSC = 48Mhz (page 12)
fRef = fXOSC/2 = 24Mhz (page 12)

To calculated Counter Tick frequency:
(fXOSC/2)/pre-scaler

pre-scaler	Counter Tick frequency	
	1			12,000,000
	8			1,500,000
   32			375,000
  128			93,750

The frequency for free running mode should be the same as modulo with T1CC0 = 0xffff.

Modulo calculations

T1CC0 can be any number, used with Counter Tick freq allows rather accurate
frequency generation

To calculate frequency:
Counter Tick frequency/T1CC0 = frequency

To calculate T1CC0:
Counter Tick frequency/frequency = T1CC0

To calculate period in s
frequenct/Counter Tick = period in s

											T1CC0L (T1CC0H = 0x00 for all of these)
pre-scaler		0x01			0x03			0x07			0x0f		0x1f		0x3f		0x7f		0xff
	1		12,000,000.00	4,000,000.00	1,714,285.71	800,000.00	387,096.77	190,476.19	94,488.19	47,058.82 
	8		 1,500,000.00	  500,000.00	  214,285.71	100,000.00	 48,387.10	 23,809.52	11,811.02	 5,882.35 
   32		   375,000.00	  125,000.00	   53,571.43	 25,000.00	 12,096.77	  5,952.38	 2,952.76	 1,470.59 
  128		    93,750.00	   31,250.00	   13,392.86	  6,250.00	  3,024.19	  1,488.10	   738.19	   367.65 
								
											T1CC0H (T1CC0L = 0xff for all of these)
pre-scaler		0x01			0x03			0x07			0x0f		0x1f		0x3f		0x7f		0xff (free running mode)
	1			23,483.37	   11,730.21		5,862.24 	  2,930.40	  1,465.02		732.47	   366.22	   183.11
	8			 2,935.42		1,466.28		  732.78 	    366.30		183.13		 91.56		45.78		22.89
   32			   733.86		  366.57		  183.19		 91.58		 45.78		 22.89		11.44		 5.72
  128			   183.46		   91.64		   45.80 	 	 22.89		 11.45		  5.72		 2.86		 1.43

*/

/* PreScaler functions */
uint8 getPreScaler(uint8 timerNum) {
	uint8 preScaler;
	preScaler = PRESCALER_INVALID;
	switch (timerNum) {
		case TIMER1:
			preScaler = getT1PreScaler();
			break;
		default:
			preScaler = PRESCALER_INVALID;
			break;
	}
	return preScaler;
}

uint8 getT1PreScaler() {
	switch (T1_PRESCALER_GET()) {
		case T1_PRESCALER_1: 
			return PRESCALER_1;
			break;
		case T1_PRESCALER_8: 
			return PRESCALER_8;
			break;
		case T1_PRESCALER_32: 
			return PRESCALER_32;
			break;
		case T1_PRESCALER_128: 
			return PRESCALER_128;
			break;
	}
	return PRESCALER_INVALID;
}

BIT setPreScaler(uint8 timerNum, uint8 preScaler) {
	switch (timerNum) {
		case TIMER1:
			return setT1PreScaler(preScaler);
			break;
	}
	return 1;
}

BIT setT1PreScaler(uint8 preScaler) {
	switch (preScaler) {
		case PRESCALER_1:
			T1_PRESCALER_SET(T1_PRESCALER_1);
			break;
		case PRESCALER_8:
			T1_PRESCALER_SET(T1_PRESCALER_8);
			break;
		case PRESCALER_32:
			T1_PRESCALER_SET(T1_PRESCALER_32);
			break;
		case PRESCALER_128:
			T1_PRESCALER_SET(T1_PRESCALER_128);
			break;
	}
	return 0;
}

/* IO Location functions*/

BIT setIoLocation(uint8 timerNum, uint8 ioLocation) {
	switch (timerNum) {
		case TIMER1:
			return setT1IoLocation(ioLocation);
			break;
	}
	return 1;
}

BIT setT1IoLocation(uint8 ioLocation) {
	switch (ioLocation) {
		case IO_LOC_ALT_1:
		case IO_LOC_ALT_2:
			 T1_IO_LOC_SET(ioLocation);
			break;
		default:
			return 1;
			break;
	}
	return 0;
}

uint8 getIoLocation(uint8 timerNum) {
	switch (timerNum) {
		case TIMER1:
			return getT1IoLocation();
			break;
	}
	return IO_LOC_INVALID;
}

uint8 getT1IoLocation() {
	uint8 ioLoc;
	ioLoc = T1_IO_LOC_GET();
	switch (ioLoc) {
		case IO_LOC_ALT_1:
		case IO_LOC_ALT_2: 
			return ioLoc;
			break;
	}
	return IO_LOC_INVALID;
}

/* functions to setup channel */

BIT setChannelMode(uint8 timerNum, uint8 channelNum, uint8 mode) {
	switch (timerNum) {
		case TIMER1:
			return setT1ChannelMode(channelNum, mode);
			break;
	}
	return 1;
}

BIT setT1ChannelMode(uint8 channelNum, uint8 mode) {
	switch (channelNum) {
		case CHANNEL0: 
			T1_CH0_MODE_SET(mode);
			break;
		case CHANNEL1: 
			T1_CH1_MODE_SET(mode);
			break;
		case CHANNEL2: 
			T1_CH2_MODE_SET(mode);
			break;
		default: 
			return 1;
			break;
	}
	return 0;
}

BIT setChannelCompareMode(uint8 timerNum, uint8 channelNum, uint8 compMode) {
	switch (timerNum) {
		case TIMER1:
			return setT1ChannelCompareMode(channelNum, compMode);
			break;
	}
	return 1;
}

BIT setT1ChannelCompareMode(uint8 channelNum, uint8 compMode) {
	switch (channelNum) {
		case CHANNEL0: 
			T1_CH0_COMP_MODE_SET(compMode);
			break;
		case CHANNEL1: 
			T1_CH1_COMP_MODE_SET(compMode);
			break;
		case CHANNEL2: 
			T1_CH2_COMP_MODE_SET(compMode);
			break;
		default: 
			return 1;
			break;
	}
	return 0;
}

BIT setChannelFunction(uint8 timerNum, uint8 channelNum, uint8 function) {
	switch (timerNum) {
		case TIMER1:
			return setT1ChannelFunction(channelNum, function);
			break;
	}
	return 1;
}

BIT setT1ChannelFunction(uint8 channelNum, uint8 function) {
	uint8 ioLoc;
	uint8 pin;
	ioLoc = getIoLocation(TIMER1);
	
	switch (ioLoc) {
		case IO_LOC_ALT_1: 
			pin = channelNum + 2;
			P0_FUNC_SET(pin, function);
			break;
		case IO_LOC_ALT_2: 
			pin = (channelNum ^ 3) - 1;
			P1_FUNC_SET(pin, function);
			break;
		default:
			return 1;
			break;
	}
	return 0;
}

BIT channelInit(uint8 timerNum, uint8 channelNum, uint8 mode, uint8 compMode, uint8 function) {
	if (checkTimer(timerNum) == 0 && checkChannel(timerNum, channelNum) == 0) {
		if (checkChannelMode(mode) == 0) {
			if (setChannelMode(timerNum, channelNum, mode) == 1) {
				return 1;
			}
		}
		if (checkChannelCompareMode(timerNum, channelNum, compMode) == 0) {
			if (setChannelCompareMode(timerNum, channelNum, compMode) == 1) {
				return 1;
			}
		}
		if (checkChannelFunction(function) == 0) {
			if (setChannelFunction(timerNum, channelNum, function) == 1) {
				return 1;
			}
		}
		return 0;
	}
	return 1;
}

/* functions to start/stop a timer */

BIT setTimerMode(uint8 timerNum, uint8 mode) {
	switch (timerNum) {
		case TIMER1:
			T1_MODE_SET(mode);
			return 0;
			break;
	}
	return 1;
}

BIT timerMode(uint8 timerNum, uint8 mode) {
	if (checkTimer(timerNum) == 0) {
		if (checkTimerMode(timerNum, mode) == 0) {
			if (setTimerMode(timerNum, mode) == 1) {
				return 1;
			}
		}
		return 0;
	}
	return 1;
}

uint8 getTimerMode(uint8 timerNum) {
	switch (timerNum) {
		case TIMER1:
			return getT1TimerMode();
			break;
	}
	/* will need to change this later */
	return T1_MODE_INVALID;
}

uint8 getT1TimerMode() {
	uint8 tMode;
	tMode = T1_MODE_GET();
	switch (tMode) {
		case T1_MODE_OFF:
		case T1_MODE_FREE:
		case T1_MODE_MODULO:
		case T1_MODE_UPDOWN:
			return tMode;
			break;
	}
	return T1_MODE_INVALID;
}

/* functions to set frequency of a timer */

BIT setFrequency(uint8 timerNum, uint32 frequency) {
	uint16 val;
	if (frequency == 0) {
		return 1;
	}
	val = calculateCompareValue(timerNum, frequency);
	if (val != 0) {
		switch (timerNum) {
			case TIMER1:
				return setT1Frequency(val);
				break;
		}
	}
	return 1;
}

BIT setT1Frequency(uint16 val) {
	if (val == 0 || val == 0xffff) {
		return 1;
	}
	T1_CH0_CAP_VAL_SET(val);
	return 0;
}

uint16 calculateCompareValue(uint8 timerNum, uint32 frequency) {
	switch (timerNum) {
		case TIMER1:
			return calculateT1CompareValue(frequency);
			break;
	}
	return 0;
}

uint16 calculateT1CompareValue(uint32 frequency) {
	switch (getTimerMode(TIMER1)) {
		case T1_MODE_MODULO:
			switch (getPreScaler(TIMER1)) {
				case PRESCALER_1:
					return calculateModuloValue(PRESCALER_1_TICK, frequency);
					break;
				case PRESCALER_8:
					return calculateModuloValue(PRESCALER_8_TICK, frequency);
					break;
				case PRESCALER_32:
					return calculateModuloValue(PRESCALER_32_TICK, frequency);
					break;
				case PRESCALER_128:
					return calculateModuloValue(PRESCALER_128_TICK, frequency);
					break;
			}
			break;
	}
	return 0;
}

uint16 calculateModuloValue(uint32 preScalerTick, uint32 frequency) {
	uint32 val;
	val = preScalerTick/frequency;
	if ((val >> 16) != 0) {
		val = 0;
	}
	return val;
}

/* general checker functions */

BIT checkTimer(uint8 timerNum) {
	switch (timerNum) {
		case TIMER1:
			return 0;
			break;
	}
	return 1;
}

BIT checkTimerMode(uint8 timerNum, uint8 mode) {
	switch (timerNum) {
		case TIMER1:
			switch (mode) {
				case T1_MODE_OFF:
				case T1_MODE_FREE:
				case T1_MODE_MODULO:
				case T1_MODE_UPDOWN:
					return 0;
					break;
			}
		break;
	}
	return 1;
}

BIT checkChannel(uint8 timerNum, uint8 channelNum) {
	switch (timerNum) {
		case TIMER1:
			switch (channelNum) {
				case CHANNEL0:
				case CHANNEL1:
				case CHANNEL2:
					return 0;
					break;
			}
		break;
	}
	return 1;
}

BIT checkChannelMode(uint8 mode) {
	switch (mode) {
		case CAPTURE_MODE:
		case COMPARE_MODE:
			return 0;
			break;
	}
	return 1;
}

BIT checkChannelCompareMode(uint8 timerNum, uint8 channelNum, uint8 compMode) {
	switch (timerNum) {
		case TIMER1:
			return checkT1ChannelCompareMode(channelNum, compMode);
			break;
	}
	return 1;
}

BIT checkT1ChannelCompareMode(uint8 channelNum, uint8 compMode) {
	switch (channelNum) {
		case CHANNEL0:
			switch (compMode) {
				case SET_ON_COMP: 
				case CLR_ON_COMP: 
				case TOGGLE_ON_COMP: 
				case SET_ON_COMP_UP: 
				case CLR_ON_COMP_UP: 
					return 0;
					break;
			}
			break;
		case CHANNEL1:
		case CHANNEL2:
			switch (compMode) {
				case SET_ON_COMP: 
				case CLR_ON_COMP: 
				case TOGGLE_ON_COMP: 
				case SET_ON_COMP_UP: 
				case CLR_ON_COMP_UP: 
				case SET_CLR: 
				case CLR_SET: 
				case DSM_MODE_ENABLE: 
					return 0;
					break;
			}
	}
	return 1;
}

BIT checkChannelFunction(uint8 function) {
	switch (function) {
		case GPIO: 
		case PERIPHERAL: 
			return 0;
			break;
	}
	return 1;
}

/* function to initalise a timer */

BIT timerInit(uint8 timerNum, uint8 ioLocation, uint8 preScaler) {
	if (checkTimer(timerNum) == 0) {
		if (setIoLocation(timerNum, ioLocation) == 1) {
			return 1;
		}
		/* set perScaler if invalud return false */
		if (setPreScaler(timerNum, preScaler) == 1) {
			return 1;
		}
		return 0;
	}
	return 1;
}
