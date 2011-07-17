#include <timer.h>
#include <cc2511_types.h>
#include <stdio.h>

/*
Wixel is running at 24Mhz - maybe add a macro to get the configured speed

To calculated Counter Tick frequency:
Wixel speed/pre-scaler

pre-scaler	Counter Tick frequency
	1			24,000,000
	8			3,000,000
   32			750,000
  128			187,500

Don't think T1CC0H/L has to be a string of ones. Just incase below are some frequencies.

To calculate frequency:
Counter Tick frequency/T1CC0

											T1CC0L (T1CC0H = 0x00 for all of these)
pre-scaler		0x01			0x03			0x07			0x0f			0x1f		0x3f		0x7f		0xff
    1		24,000,000.00	8,000,000.00	3,428,571.43	1,600,000.00	774,193.55	380,952.38	188,976.38	94,117.65
    8		 3,000,000.00	1,000,000.00	  428,571.43	  200,000.00	 96,774.19	 47,619.05	 23,622.05	11,764.71
   32		   750,000.00	  250,000.00	  107,142.86	   50,000.00	 24,193.55	 11,904.76	  5,905.51	 2,941.18
  128		   187,500.00	   62,500.00	   26,785.71	   12,500.00	  6,048.39	  2,976.19	  1,476.38	   735.29

											T1CC0H (T1CC0L = 0xff for all of these)
pre-scaler		0x01			0x03			0x07			0x0f			0x1f		0x3f		0x7f		0xff
	1			46,966.73	   23,460.41	   11,724.47	    5,860.81	  2,930.05	  1,464.93	    732.44	   366.22
	8			 5,870.84		2,932.55		1,465.56		  732.60		366.26		183.12		 91.56		45.78
   32			 1,467.71		  733.14		  366.39		  183.15		 91.56		 45.78		 22.89		11.44
  128			   366.93		  183.28		   91.60		   45.79	  	 22.89		 11.44		  5.72		 2.86


  
*/

/* PreScaler functions */
uint8 getPreScaler(uint8 timerNum) {
	uint8 preScaler;
	preScaler = PRESCALER_INVALID;
	switch (timerNum) {
		case TIMER1:
			getT1PreScaler();
			break;
		default:
			preScaler = PRESCALER_INVALID;
			break;
	}
	return preScaler;
}

uint8 getT1PreScaler() {
	uint8 preScaler;
	preScaler = PRESCALER_INVALID;
	switch (T1_PRESCALER_GET()) {
		case T1_PRESCALER_1: 
			preScaler = PRESCALER_1;
			break;
		case T1_PRESCALER_8: 
			preScaler = PRESCALER_8;
			break;
		case T1_PRESCALER_32: 
			preScaler = PRESCALER_32;
			break;
		case T1_PRESCALER_128: 
			preScaler = PRESCALER_128;
			break;
		default:
			preScaler = PRESCALER_INVALID;
			break;
	}
	return preScaler;
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

/* functions to set frequency of a timer */

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
