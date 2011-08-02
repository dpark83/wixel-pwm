#include <cc2511_types.h>
#include <stdio.h>
#include <timer_defs.h>

/******************
 * Global defines *
 ******************/

#define TIMER_FALSE	1;
#define TIMER_TRUE	0;

/* Helper macros */
#define SET_BITS(input, val, mask)	(input ^ ((input ^ val) & mask))
#define TOGGLE_BIT(input, mask)	(input ^ mask)
#define GET_BITS(input, mask)	(input & mask)

/* Interrupt flag */
#define	NO_INT_PENDING	0	/* No interrupt pending */
#define	INT_PENDING		1	/* Interrupt pending */

/* Capture select */
#define NORM_CAPTURE	0	/* Use normal capture input */
#define	RF_CAPTURE		1	/* Use RF event(s) enabled in the RFIM register to trigger a capture */

/* Interrupt mask */
#define	INT_DISABLED	0	/* Interrupt disabled */
#define	INT_ENABLED		1	/* Interrupt enabled */

/* Capture mode select */
/* CMP != 111 - Timer 1 Channel 1 capture mode select (timer mode)
   CMP = 111 - DSM interpolator and output shaping configuration (DSM mode) */
#define	NO_CAPTURE		0x00 /* For Timer channel 1 & CMP = 111 - DSM interpolator and output shaping enabled
								All others - No capture */
#define	CAPTURE_RISING	0x01 /* For Timer channel 1 & CMP = 111 - DSM interpolator enabled and output shaping disabled
								All others - Capture on rising edge */
#define	CAPTURE_FALLING	0x02 /* For Timer channel 1 & CMP = 111 - DSM interpolator disabled and output shaping enabled
								All others - Capture on falling edge */
#define	CAPTURE_BOTH	0x03 /* For Timer channel 1 & CMP = 111 - DSM interpolator and output shaping disabled
								All others - Capture on both edges */

/* TIMER SPECIFIC DEFINES */
#if defined(TIMER1)
/**********************************
 *             TIMER 1            *
 **********************************/

#include <timer1.h>

/*****************
 *     PERCFG    *
 *****************/

 /* Timer I/O location - T1CFG */
#define TIMER_IO_LOC_REGISTER	PERCFG
#define TIMER_IO_LOC_OFFSET		6
#define TIMER_IO_LOC_MASK		64

/*****************
 * T1CNTH/T1CNTL *
 *****************/

/* Timer Counter - T1CNTH (high byte), T1CNTL (low byte) */
#define	TIMER_COUNTER_HIGH	T1CNTH
#define	TIMER_COUNTER_LOW	T1CNTL

/*****************
 *     T1CTL     *
 *****************/

/* Timer Channel 0 interrupt flag - CH0IF */
#define CHANNEL0_INT_FLAG_REGISTER	T1CTL
#define CHANNEL0_INT_FLAG_OFFSET	5
#define CHANNEL0_INT_FLAG_MASK		32
/* Timer Channel 1 interrupt flag - CH1IF */
#define CHANNEL1_INT_FLAG_REGISTER	T1CTL
#define CHANNEL1_INT_FLAG_OFFSET	6
#define CHANNEL1_INT_FLAG_MASK		64
/* Timer Channel 2 interrupt flag - CH2IF */
#define CHANNEL2_INT_FLAG_REGISTER	T1CTL
#define CHANNEL2_INT_FLAG_OFFSET	7
#define CHANNEL2_INT_FLAG_MASK		128

/* Timer overflow interrupt flag - OVFIF */
#define TIMER_OVFL_INT_FLAG_REGISTER	T1CTL
#define TIMER_OVFL_INT_FLAG_OFFSET		4
#define TIMER_OVFL_INT_FLAG_MASK		16

/* Timer Prescaler - DIV[1:0] */
#define	T1_PRESCALER_1		0x00	/* Tick frequency/1 */
#define	T1_PRESCALER_8		0x04	/* Tick frequency/8 */
#define	T1_PRESCALER_32		0x08	/* Tick frequency/32 */
#define	T1_PRESCALER_128	0x0c	/* Tick frequency/128 */
#define TIMER_PRESCALER_REGISTER	T1CTL
#define TIMER_PRESCALER_OFFSET		2
#define TIMER_PRESCALER_MASK		12

/* Timer Mode - MODE[1:0] */
#define	T1_MODE_OFF			0x00	/* Operation is suspended */
#define	T1_MODE_FREE		0x01	/* Free-running, repeatedly count from 0x0000 to 0xFFFF */
/* #define	T1_MODE_MODULO		0x02	*/	/* Modulo, repeatedly count from 0x0000 to T1CC0 */
/* #define	T1_MODE_UPDOWN		0x03	*/	/* Up/down, repeatedly count from 0x0000 to T1CC0 and from T1CC0 down to 0x0000 */
#define TIMER_MODE_REGISTER	T1CTL
#define TIMER_MODE_OFFSET	0
#define TIMER_MODE_MASK		3

/**********************************
 *            CHANNEL 0           *
 **********************************/

/*****************
 *    T1CCTL0    *
 *****************/

/* Timer Channel 0 capture - CPSEL */
#define CHANNEL0_CAPSEL_REGISTER	T1CCTL0
#define CHANNEL0_CAPSEL_OFFSET		7
#define CHANNEL0_CAPSEL_MASK		128

/* Timer Channel 0 interrupt mask - IM */
#define CHANNEL0_INT_MASK_REGISTER	T1CCTL0
#define CHANNEL0_INT_MASK_OFFSET	6
#define CHANNEL0_INT_MASK_MASK		64

/* Timer Channel 0 compare mode - CMP[2:0] */
#define CHANNEL0_COMP_MODE_REGISTER	T1CCTL0
#define CHANNEL0_COMP_MODE_OFFSET	3
#define CHANNEL0_COMP_MODE_MASK		56

/* Timer Channel 0 capture or compare mode - MODE */
#define CHANNEL0_CAP_COMP_MODE_REGISTER	T1CCTL0
#define CHANNEL0_CAP_COMP_MODE_OFFSET	2
#define CHANNEL0_CAP_COMP_MODE_MASK		4

/* Timer Channel 0 capture mode - CAP[1:0] */
#define CHANNEL0_CAP_MODE_REGISTER	T1CCTL0
#define CHANNEL0_CAP_MODE_OFFSET	0
#define CHANNEL0_CAP_MODE_MASK		3

 /*****************
 * T1CC0H/T1CC0L  *
 *****************/

 /* Timer Channel 0 Capture/Compare Value - T1CC0H (high byte), T1CC0L (low byte) */
#define	CHANNEL0_CAPCOMP_VALUE_HIGH	T1CC0H
#define	CHANNEL0_CAPCOMP_VALUE_LOW	T1CC0L

/**********************************
 *            CHANNEL 1           *
 **********************************/

/*****************
 *    T1CCTL1    *
 *****************/

/* Timer Channel 1 capture - CPSEL */
#define CHANNEL1_CAPSEL_REGISTER	T1CCTL1
#define CHANNEL1_CAPSEL_OFFSET		7
#define CHANNEL1_CAPSEL_MASK		128

/* Timer Channel 1 interrupt mask - IM */
#define CHANNEL1_INT_MASK_REGISTER	T1CCTL1
#define CHANNEL1_INT_MASK_OFFSET	6
#define CHANNEL1_INT_MASK_MASK		64

/* Timer Channel 1 compare mode - CMP[2:0] */
#define CHANNEL1_COMP_MODE_REGISTER	T1CCTL1
#define CHANNEL1_COMP_MODE_OFFSET	3
#define CHANNEL1_COMP_MODE_MASK		56

/* Timer Channel 1 capture or compare mode - MODE */
#define CHANNEL1_CAP_COMP_MODE_REGISTER	T1CCTL1
#define CHANNEL1_CAP_COMP_MODE_OFFSET	2
#define CHANNEL1_CAP_COMP_MODE_MASK		4

/* Timer Channel 1 capture mode - CAP[1:0] */
#define CHANNEL1_CAP_MODE_REGISTER	T1CCTL1
#define CHANNEL1_CAP_MODE_OFFSET	0
#define CHANNEL1_CAP_MODE_MASK		3

 /*****************
 * T1CC1H/T1CC1L  *
 *****************/

 /* Timer Channel 1 Capture/Compare Value - T1CC1H (high byte), T1CC1L (low byte) */
#define	CHANNEL1_CAPCOMP_VALUE_HIGH	T1CC1H
#define	CHANNEL1_CAPCOMP_VALUE_LOW	T1CC1L

/**********************************
 *            CHANNEL 2           *
 **********************************/

/*****************
 *    T1CCTL2    *
 *****************/

/* Timer Channel 2 capture - CPSEL */
#define CHANNEL2_CAPSEL_REGISTER	T1CCTL2
#define CHANNEL2_CAPSEL_OFFSET		7
#define CHANNEL2_CAPSEL_MASK		128

/* Timer Channel 2 interrupt mask - IM */
#define CHANNEL2_INT_MASK_REGISTER	T1CCTL2
#define CHANNEL2_INT_MASK_OFFSET	6
#define CHANNEL2_INT_MASK_MASK		64

/* Timer Channel 2 compare mode - CMP[2:0] */
#define CHANNEL2_COMP_MODE_REGISTER	T1CCTL2
#define CHANNEL2_COMP_MODE_OFFSET	3
#define CHANNEL2_COMP_MODE_MASK		56

/* Timer Channel 2 capture or compare mode - MODE */
#define CHANNEL2_CAP_COMP_MODE_REGISTER	T1CCTL2
#define CHANNEL2_CAP_COMP_MODE_OFFSET	2
#define CHANNEL2_CAP_COMP_MODE_MASK		4

/* Timer Channel 2 capture mode - CAP[1:0] */
#define CHANNEL2_CAP_MODE_REGISTER	T1CCTL2
#define CHANNEL2_CAP_MODE_OFFSET	0
#define CHANNEL2_CAP_MODE_MASK		3

 /*****************
 * T1CC2H/T1CC2L  *
 *****************/

 /* Timer Channel 2 Capture/Compare Value - T1CC2H (high byte), T1CC2L (low byte) */
#define	CHANNEL2_CAPCOMP_VALUE_HIGH	T1CC2H
#define	CHANNEL2_CAPCOMP_VALUE_LOW	T1CC2L

/*****************
 *     TIMIF     *
 *****************/
 
/* Timer overflow interrupt mask - OVFIM */
#define TIMER_OVFL_INT_MASK_REGISTER	TIMIF
#define TIMER_OVFL_INT_MASK_OFFSET		6
#define TIMER_OVFL_INT_MASK_MASK		64

/*****************
 *    FUNCTIONS  *
 *****************/
#define getTNPreScaler				getT1PreScaler
#define setTNPreScaler				setT1PreScaler
#define setTNIoLocation				setT1IoLocation
#define getTNIoLocation				getT1IoLocation
#define setTNChannelMode			setT1ChannelMode
#define setTNChannelCompareMode		setT1ChannelCompareMode
#define setTNChannelFunction		setT1ChannelFunction
#define tNChannelInit				t1ChannelInit
#define tNMode						t1Mode
#define getTNMode					getT1Mode
#define	tNStart						t1Start
#define	tNStop						t1Stop
#define setTNFrequency				setT1Frequency
#define calculateTNCompareValue		calculateT1CompareValue
#define calculateTNModuloValue		calculateT1ModuloValue
#define checkTNChannel				checkT1Channel
#define checkTNChannelCompareMode	checkT1ChannelCompareMode
#define tNInit						t1Init

#elif defined(TIMER3)
/**********************************
 *             TIMER 3            *
 **********************************/
#include <timer3.h>

#define	T34_MODE_FREE		0x00
#define	T34_MODE_DOWN		0x01
#define	T34_MODE_MODULO		0x02
#define	T34_MODE_UPDOWN		0x03

/*****************
 *     PERCFG    *
 *****************/

 /* Timer I/O location - T3CFG */
#define TIMER_IO_LOC_REGISTER	PERCFG
#define TIMER_IO_LOC_OFFSET		5
#define TIMER_IO_LOC_MASK		32

/*****************
 *     T3CNT     *
 *****************/

/* Counter register */
#define	TIMER_COUNTER_REGISTER	T3CNT

/*****************
 *     T3CTL     *
 *****************/

/* Timer Prescaler - DIV[2:0] */
#define TIMER_PRESCALER_REGISTER	T3CTL
#define TIMER_PRESCALER_OFFSET		5
#define TIMER_PRESCALER_MASK		224

/* Timer start - START */
#define TIMER_START_REGISTER	T3CTL
#define TIMER_START_OFFSET		4
#define TIMER_START_MASK		16

/* Timer overflow interrupt mask - OVFIM */
#define TIMER_OVFL_INT_MASK_REGISTER	T3CTL
#define TIMER_OVFL_INT_MASK_OFFSET		3
#define TIMER_OVFL_INT_MASK_MASK		8

/* Timer counter clear - CLR */
#define TIMER_CLEAR_REGISTER	T3CTL
#define TIMER_CLEAR_OFFSET		2
#define TIMER_CLEAR_MASK		4

/* Timer Mode - MODE[1:0] */
#define TIMER_MODE_REGISTER	T3CTL
#define TIMER_MODE_OFFSET	0
#define TIMER_MODE_MASK		3

/**********************************
 *            CHANNEL 0           *
 **********************************/

 /*****************
 *    T3CCTL0    *
 *****************/

/* Timer Channel 0 interrupt mask - IM */
#define CHANNEL0_INT_MASK_REGISTER	T3CCTL0
#define CHANNEL0_INT_MASK_OFFSET	6
#define CHANNEL0_INT_MASK_MASK		64

/* Timer Channel 0 compare mode - CMP[2:0] */
#define CHANNEL0_COMP_MODE_REGISTER	T3CCTL0
#define CHANNEL0_COMP_MODE_OFFSET	3
#define CHANNEL0_COMP_MODE_MASK		56

/* Timer Channel 0 capture or compare mode - MODE */
#define CHANNEL0_CAP_COMP_MODE_REGISTER	T3CCTL0
#define CHANNEL0_CAP_COMP_MODE_OFFSET	2
#define CHANNEL0_CAP_COMP_MODE_MASK		4

 /*****************
 *      T3CC0     *
 *****************/

 /* Timer Channel 0 Compare Value */
#define	CHANNEL0_COMP_VALUE	T3CC0

/**********************************
 *            CHANNEL 1           *
 **********************************/

 /*****************
 *    T3CCTL1    *
 *****************/

/* Timer Channel 1 interrupt mask - IM */
#define CHANNEL1_INT_MASK_REGISTER	T3CCTL1
#define CHANNEL1_INT_MASK_OFFSET	6
#define CHANNEL1_INT_MASK_MASK		64

/* Timer Channel 1 compare mode - CMP[2:0] */
#define CHANNEL1_COMP_MODE_REGISTER	T3CCTL1
#define CHANNEL1_COMP_MODE_OFFSET	3
#define CHANNEL1_COMP_MODE_MASK		56

/* Timer Channel 1 capture or compare mode - MODE */
#define CHANNEL1_CAP_COMP_MODE_REGISTER	T3CCTL1
#define CHANNEL1_CAP_COMP_MODE_OFFSET	2
#define CHANNEL1_CAP_COMP_MODE_MASK		4

 /*****************
 *      T3CC1     *
 *****************/

 /* Timer Channel 1 Compare Value */
#define	CHANNEL1_COMP_VALUE	T3CC1

 /*****************
 *      TIMIF     *
 *****************/
 
/* Timer Channel 0 interrupt flag - T3CH0IF */
#define CHANNEL0_INT_FLAG_REGISTER	TIMIF
#define CHANNEL0_INT_FLAG_OFFSET	1
#define CHANNEL0_INT_FLAG_MASK		2
/* Timer Channel 1 interrupt flag - T3CH1IF */
#define CHANNEL1_INT_FLAG_REGISTER	TIMIF
#define CHANNEL1_INT_FLAG_OFFSET	2
#define CHANNEL1_INT_FLAG_MASK		4

/* Timer overflow interrupt flag - T3OVFIF */
#define TIMER_OVFL_INT_FLAG_REGISTER	TIMIF
#define TIMER_OVFL_INT_FLAG_OFFSET		0
#define TIMER_OVFL_INT_FLAG_MASK		1

/*****************
 *    FUNCTIONS  *
 *****************/
#define getTNPreScaler				getT3PreScaler
#define setTNPreScaler				setT3PreScaler
#define setTNIoLocation				setT3IoLocation
#define getTNIoLocation				getT3IoLocation
#define setTNChannelMode			setT3ChannelMode
#define setTNChannelCompareMode		setT3ChannelCompareMode
#define setTNChannelFunction		setT3ChannelFunction
#define tNChannelInit				t3ChannelInit
#define tNMode						t3Mode
#define getTNMode					getT3Mode
#define	tNStart						t3Start
#define	tNStop						t3Stop
#define setTNFrequency				setT3Frequency
#define calculateTNCompareValue		calculateT3CompareValue
#define calculateTNModuloValue		calculateT3ModuloValue
#define checkTNChannel				checkT3Channel
#define checkTNChannelCompareMode	checkT3ChannelCompareMode
#define tNInit						t3Init

#elif defined(TIMER4)
/**********************************
 *             TIMER 4            *
 **********************************/

 #include <timer4.h>

 /*****************
 *     PERCFG    *
 *****************/

/* Timer I/O location - T4CFG */
#define TIMER_IO_LOC_REGISTER	PERCFG
#define TIMER_IO_LOC_OFFSET		4
#define TIMER_IO_LOC_MASK		16

/*****************
 *     T4CNT     *
 *****************/

/* Counter register */
#define	TIMER_COUNTER_REGISTER	T4CNT

/*****************
 *     T4CTL     *
 *****************/

/* Timer Prescaler - DIV[2:0] */
#define TIMER_PRESCALER_REGISTER	T4CTL
#define TIMER_PRESCALER_OFFSET		5
#define TIMER_PRESCALER_MASK		224

/* Timer start - START */
#define TIMER_START_REGISTER	T4CTL
#define TIMER_START_OFFSET		4
#define TIMER_START_MASK		16

/* Timer overflow interrupt mask - OVFIM */
#define TIMER_OVFL_INT_MASK_REGISTER	T4CTL
#define TIMER_OVFL_INT_MASK_OFFSET		3
#define TIMER_OVFL_INT_MASK_MASK		8

/* Timer counter clear - CLR */
#define TIMER_CLEAR_REGISTER	T4CTL
#define TIMER_CLEAR_OFFSET		2
#define TIMER_CLEAR_MASK		4

/* Timer Mode - MODE[1:0] */
#define TIMER_MODE_REGISTER	T4CTL
#define TIMER_MODE_OFFSET	0
#define TIMER_MODE_MASK		3

/**********************************
 *            CHANNEL 0           *
 **********************************/

 /*****************
 *    T4CCTL0    *
 *****************/

/* Timer Channel 0 interrupt mask - IM */
#define CHANNEL0_INT_MASK_REGISTER	T4CCTL0
#define CHANNEL0_INT_MASK_OFFSET	6
#define CHANNEL0_INT_MASK_MASK		64

/* Timer Channel 0 compare mode - CMP[2:0] */
#define CHANNEL0_COMP_MODE_REGISTER	T4CCTL0
#define CHANNEL0_COMP_MODE_OFFSET	3
#define CHANNEL0_COMP_MODE_MASK		56

/* Timer Channel 0 capture or compare mode - MODE */
#define CHANNEL0_CAP_COMP_MODE_REGISTER	T4CCTL0
#define CHANNEL0_CAP_COMP_MODE_OFFSET	2
#define CHANNEL0_CAP_COMP_MODE_MASK		4

 /*****************
 *      T4CC0     *
 *****************/

 /* Timer Channel 0 Compare Value */
#define	CHANNEL0_COMP_VALUE	T4CC0

/**********************************
 *            CHANNEL 1           *
 **********************************/

 /*****************
 *    T4CCTL1    *
 *****************/

/* Timer Channel 1 interrupt mask - IM */
#define CHANNEL1_INT_MASK_REGISTER	T4CCTL1
#define CHANNEL1_INT_MASK_OFFSET	6
#define CHANNEL1_INT_MASK_MASK		64

/* Timer Channel 1 compare mode - CMP[2:0] */
#define CHANNEL1_COMP_MODE_REGISTER	T4CCTL1
#define CHANNEL1_COMP_MODE_OFFSET	3
#define CHANNEL1_COMP_MODE_MASK		56

/* Timer Channel 1 capture or compare mode - MODE */
#define CHANNEL1_CAP_COMP_MODE_REGISTER	T4CCTL1
#define CHANNEL1_CAP_COMP_MODE_OFFSET	2
#define CHANNEL1_CAP_COMP_MODE_MASK		4

 /*****************
 *      T4CC1     *
 *****************/

 /* Timer Channel 1 Compare Value */
#define	CHANNEL1_COMP_VALUE	T4CC1

/*****************
 *      TIMIF     *
 *****************/
 
/* Timer Channel 0 interrupt flag - T4CH0IF */
#define CHANNEL0_INT_FLAG_REGISTER	TIMIF
#define CHANNEL0_INT_FLAG_OFFSET	4
#define CHANNEL0_INT_FLAG_MASK		16
/* Timer Channel 1 interrupt flag - T4CH1IF */
#define CHANNEL1_INT_FLAG_REGISTER	TIMIF
#define CHANNEL1_INT_FLAG_OFFSET	5
#define CHANNEL1_INT_FLAG_MASK		32

/* Timer overflow interrupt flag - T4OVFIF */
#define TIMER_OVFL_INT_FLAG_REGISTER	TIMIF
#define TIMER_OVFL_INT_FLAG_OFFSET		3
#define TIMER_OVFL_INT_FLAG_MASK		8

#endif


/*****************
 *     P0SEL     *
 *****************/
 
/* P0_7 to P0_0 function - SELP0_[7:0] */
#define PORT0_FUNCTION_REGISTER	P0SEL

/*****************
 *     P1SEL     *
 *****************/
 
/* P1_7 to P1_0 function - SELP1_[7:0] */
#define PORT1_FUNCTION_REGISTER	P1SEL

/*****************
 *     MACROS    *
 *****************/

#if defined(TIMER1)
#define SET_TIMER_PRESCALER(v)	{ TIMER_PRESCALER_REGISTER = SET_BITS(TIMER_PRESCALER_REGISTER, v, TIMER_PRESCALER_MASK); }
#define GET_TIMER_PRESCALER()	( GET_BITS(TIMER_PRESCALER_REGISTER, TIMER_PRESCALER_MASK) )
#else
#define SET_TIMER_PRESCALER(v)	{ TIMER_PRESCALER_REGISTER = SET_BITS(TIMER_PRESCALER_REGISTER, v << TIMER_PRESCALER_OFFSET, TIMER_PRESCALER_MASK); }
#define GET_TIMER_PRESCALER()	( GET_BITS(TIMER_PRESCALER_REGISTER, TIMER_PRESCALER_MASK) >> TIMER_PRESCALER_OFFSET )
#endif

#define SET_TIMER_IO_LOC(v)	{ TIMER_IO_LOC_REGISTER = SET_BITS(TIMER_IO_LOC_REGISTER, v << TIMER_IO_LOC_OFFSET, TIMER_IO_LOC_MASK); }
#define GET_TIMER_IO_LOC()	( GET_BITS(TIMER_IO_LOC_REGISTER, TIMER_IO_LOC_MASK) >> TIMER_IO_LOC_OFFSET )

#define SET_CHANNEL0_CAP_COMP_MODE(v)	{CHANNEL0_CAP_COMP_MODE_REGISTER = SET_BITS(CHANNEL0_CAP_COMP_MODE_REGISTER, v << CHANNEL0_CAP_COMP_MODE_OFFSET, CHANNEL0_CAP_COMP_MODE_MASK);}
#define SET_CHANNEL1_CAP_COMP_MODE(v)	{CHANNEL1_CAP_COMP_MODE_REGISTER = SET_BITS(CHANNEL1_CAP_COMP_MODE_REGISTER, v << CHANNEL1_CAP_COMP_MODE_OFFSET, CHANNEL1_CAP_COMP_MODE_MASK);}
#define SET_CHANNEL2_CAP_COMP_MODE(v)	{CHANNEL2_CAP_COMP_MODE_REGISTER = SET_BITS(CHANNEL2_CAP_COMP_MODE_REGISTER, v << CHANNEL2_CAP_COMP_MODE_OFFSET, CHANNEL2_CAP_COMP_MODE_MASK);}

#define SET_CHANNEL0_COMP_MODE(v)		{CHANNEL0_COMP_MODE_REGISTER = SET_BITS(CHANNEL0_COMP_MODE_REGISTER, v, CHANNEL0_COMP_MODE_MASK); }
#define SET_CHANNEL1_COMP_MODE(v)		{CHANNEL1_COMP_MODE_REGISTER = SET_BITS(CHANNEL1_COMP_MODE_REGISTER, v, CHANNEL1_COMP_MODE_MASK); }
#define SET_CHANNEL2_COMP_MODE(v)		{CHANNEL2_COMP_MODE_REGISTER = SET_BITS(CHANNEL2_COMP_MODE_REGISTER, v, CHANNEL2_COMP_MODE_MASK); }

#define SET_P0_FUNC(p, v)	{PORT0_FUNCTION_REGISTER = SET_BITS(PORT0_FUNCTION_REGISTER, v << p, 1 << p);}
#define SET_P1_FUNC(p, v)	{PORT1_FUNCTION_REGISTER = SET_BITS(PORT1_FUNCTION_REGISTER, v << p, 1 << p);}

#define SET_TIMER_MODE(v)	{ TIMER_MODE_REGISTER = SET_BITS(TIMER_MODE_REGISTER, v, TIMER_MODE_MASK); }
#define GET_TIMER_MODE()	( GET_BITS(TIMER_MODE_REGISTER, TIMER_MODE_MASK) )

#if defined(TIMER1)
#define SET_CHANNEL0_CAPCOMP_VALUE(v)	{CHANNEL0_CAPCOMP_VALUE_HIGH = (uint8)(v >> 8); CHANNEL0_CAPCOMP_VALUE_LOW = (uint8)v;}
#else
#define SET_CHANNEL0_CAPCOMP_VALUE(v)	{CHANNEL0_COMP_VALUE = v;}

#define SET_TIMER_START(v)		{TIMER_START_REGISTER = SET_BITS(TIMER_START_REGISTER, v << TIMER_START_OFFSET, TIMER_START_MASK); }
#endif

#if defined(TIMER1)
uint8 _t1Mode = T1_MODE_OFF;
#endif

/* PreScaler functions */
uint8 getTNPreScaler() {
#if defined(TIMER1)
	switch (GET_TIMER_PRESCALER()) {
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
#else
	return GET_TIMER_PRESCALER();
#endif
}

BIT setTNPreScaler(uint8 preScaler) {
#if defined(TIMER1)
	switch (preScaler) {
		case PRESCALER_1:
			SET_TIMER_PRESCALER(T1_PRESCALER_1);
			return 0;
			break;
		case PRESCALER_8:
			SET_TIMER_PRESCALER(T1_PRESCALER_8);
			return 0;
			break;
		case PRESCALER_32:
			SET_TIMER_PRESCALER(T1_PRESCALER_32);
			return 0;
			break;
		case PRESCALER_128:
			SET_TIMER_PRESCALER(T1_PRESCALER_128);
			return 0;
			break;
	}
	return 1;
#else
	SET_TIMER_PRESCALER(preScaler);
	return 0;
#endif
}

/* IO Location functions
  These are only valid for Timer 1 and Timer 3*/
#if defined(TIMER1) || defined(TIMER3)
BIT setTNIoLocation(uint8 ioLocation) {
	SET_TIMER_IO_LOC(ioLocation);
	return 0;
}

uint8 getTNIoLocation() {
	return GET_TIMER_IO_LOC();
}
#endif

/* functions to setup channel
  Only Timer 1 has a channel 2 */
BIT setTNChannelMode(uint8 channelNum, uint8 mode) {
	switch (channelNum) {
		case CHANNEL0: 
			SET_CHANNEL0_CAP_COMP_MODE(mode);
			break;
		case CHANNEL1: 
			SET_CHANNEL1_CAP_COMP_MODE(mode);
			break;
#if defined(TIMER1)
		case CHANNEL2: 
			SET_CHANNEL2_CAP_COMP_MODE(mode);
			break;
#endif
		default: 
			return 1;
			break;
	}
	return 0;
}

BIT setTNChannelCompareMode(uint8 channelNum, uint8 compMode) {
	switch (channelNum) {
		case CHANNEL0: 
			SET_CHANNEL0_COMP_MODE(compMode);
			break;
		case CHANNEL1: 
			SET_CHANNEL1_COMP_MODE(compMode);
			break;
#if defined(TIMER1)
		case CHANNEL2: 
			SET_CHANNEL2_COMP_MODE(compMode);
			break;
#endif
		default: 
			return 1;
			break;
	}
	return 0;
}

BIT setTNChannelFunction(uint8 channelNum, uint8 function) {
	uint8 ioLoc;
	uint8 pin;
	ioLoc = getTNIoLocation();
	
	switch (ioLoc) {
		case IO_LOC_ALT_1: 
			pin = channelNum + 2;
			SET_P0_FUNC(pin, function);
			break;
		case IO_LOC_ALT_2: 
			pin = (channelNum ^ 3) - 1;
			SET_P1_FUNC(pin, function);
			break;
		default:
			return 1;
			break;
	}
	return 0;
}

BIT tNChannelInit(uint8 channelNum, uint8 mode, uint8 compMode, uint8 function) {
	if (checkTNChannel(channelNum) == 0) {
		if (setTNChannelMode(channelNum, mode) == 1) {
			return 1;
		}
		if (checkTNChannelCompareMode(channelNum, compMode) == 0) {
			if (setTNChannelCompareMode(channelNum, compMode) == 1) {
				return 1;
			}
		}
		if (setTNChannelFunction(channelNum, function) == 1) {
			return 1;
		}
		return 0;
	}
	return 1;
}

/* functions to start/stop a timer
  Timer 1 setting the mode starts/stops the timer
  Timer 3/4 settings this does not start the timer */
BIT tNMode(uint8 mode) {
	uint8 tMode;
	switch (mode) {
#if defined(TIMER1)
//		case MODE_OFF:
//			tMode = T1_MODE_OFF;
//			break;
#endif
		case MODE_FREE:
#if defined(TIMER1)
			tMode = T1_MODE_FREE;
#else
			tMode = T34_MODE_FREE;
#endif
			break;
		case MODE_MODULO:
			tMode = MODE_MODULO;
			break;
		case MODE_UPDOWN:
			tMode = MODE_UPDOWN;
			break;
#if defined(TIMER3) || defined(TIMER4)
		case MODE_DOWN:
			tMode = T34_MODE_DOWN;
			break;
#endif
		default:
			return 1;
			break;
	}
#if defined(TIMER1)
	_t1Mode = tMode;
#else
	SET_TIMER_MODE(tMode);
#endif
	return 0;
}

uint8 getTNMode() {
#if defined(TIMER1)
	return _t1Mode;
#else
	return GET_TIMER_MODE();
#endif
}

BIT tNStart() {
#if defined(TIMER1)
	SET_TIMER_MODE(_t1Mode);
#else
	SET_TIMER_START(TIMER_NORMAL_OPERATION);
#endif
	return 0;
}

BIT tNStop() {
#if defined(TIMER1)
	SET_TIMER_MODE(T1_MODE_OFF);
#else
	SET_TIMER_START(TIMER_SUSPENDED);
#endif
	return 0;
}

/* functions to set frequency of a timer */
BIT setTNFrequency(uint32 frequency) {
	uint16 val;
	if (frequency == 0) {
		return 1;
	}
	val = calculateTNCompareValue(frequency);
	if (val == 0 || val == 0xffff) {
		return 1;
	}
	SET_CHANNEL0_CAPCOMP_VALUE(val);
	return 0;
}

uint16 calculateTNCompareValue(uint32 frequency) {
	switch (getTNMode()) {
		case MODE_MODULO:
			switch (getTNPreScaler()) {
				case PRESCALER_1:
					return calculateTNModuloValue(PRESCALER_1_TICK, frequency);
					break;
#if defined(TIMER3) || defined(TIMER4)
				case PRESCALER_2:
					return calculateTNModuloValue(PRESCALER_2_TICK, frequency);
					break;
				case PRESCALER_4:
					return calculateTNModuloValue(PRESCALER_4_TICK, frequency);
					break;
#endif
				case PRESCALER_8:
					return calculateTNModuloValue(PRESCALER_8_TICK, frequency);
					break;
#if defined(TIMER3) || defined(TIMER4)
				case PRESCALER_16:
					return calculateTNModuloValue(PRESCALER_16_TICK, frequency);
					break;
#endif
				case PRESCALER_32:
					return calculateTNModuloValue(PRESCALER_32_TICK, frequency);
					break;
#if defined(TIMER3) || defined(TIMER4)
				case PRESCALER_64:
					return calculateTNModuloValue(PRESCALER_64_TICK, frequency);
					break;
#endif
				case PRESCALER_128:
					return calculateTNModuloValue(PRESCALER_128_TICK, frequency);
					break;
			}
			break;
	}
	return 0;
}

uint16 calculateTNModuloValue(uint32 preScalerTick, uint32 frequency) {
	uint32 val;
	val = preScalerTick/frequency;
#if defined(TIMER1)
	if ((val >> 16) != 0) {
#else
	if ((val >> 8) != 0) {
#endif
		val = 0;
	}
	return val;
}

/* general checker functions */
BIT checkTNChannel(uint8 channelNum) {
	switch (channelNum) {
		case CHANNEL0:
		case CHANNEL1:
#if defined(TIMER1)
		case CHANNEL2:
#endif
			return 0;
			break;
	}
	return 1;
}

BIT checkTNChannelCompareMode(uint8 channelNum, uint8 compMode) {
	switch (channelNum) {
		case CHANNEL0:
			switch (compMode) {
				case SET_ON_COMP: 
				case CLR_ON_COMP: 
				case TOGGLE_ON_COMP: 
				case SET_ON_COMP_UP: 
				case CLR_ON_COMP_UP: 
#if defined(TIMER3) || defined(TIMER4)
				case SET_CLR: 
				case CLR_SET: 
#endif
					return 0;
					break;
			}
			break;
		case CHANNEL1:
			switch (compMode) {
				case SET_ON_COMP: 
				case CLR_ON_COMP: 
				case TOGGLE_ON_COMP: 
				case SET_ON_COMP_UP: 
				case CLR_ON_COMP_UP: 
				case SET_CLR: 
				case CLR_SET: 
#if defined(TIEMR1)
				case DSM_MODE_ENABLE: 
#endif
					return 0;
					break;
			}
#if defined(TIMER1)
		case CHANNEL2:
			switch (compMode) {
				case SET_ON_COMP: 
				case CLR_ON_COMP: 
				case TOGGLE_ON_COMP: 
				case SET_ON_COMP_UP: 
				case CLR_ON_COMP_UP: 
				case SET_CLR: 
				case CLR_SET: 
					return 0;
					break;
			}
#endif
	}
	return 1;
}

/* function to initalise a timer */
#if defined(TIMER1) || defined(TIMER3)
BIT tNInit(uint8 ioLocation, uint8 preScaler) {
	if (setTNIoLocation(ioLocation) == 1) {
		return 1;
	}
#else
BIT tNInit(uint8 preScaler) {
#endif
	/* set perScaler if invalud return false */
	if (setTNPreScaler(preScaler) == 1) {
		return 1;
	}
	return 0;
}
	