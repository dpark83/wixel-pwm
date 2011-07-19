#include <cc2511_types.h>
#include <stdio.h>

/******************
 * Global defines *
 ******************/

#define TIMER_FALSE	1;
#define TIMER_TRUE	0;

/* Every timer has Channel 0 & 1 */
#define	CHANNEL0		0
#define	CHANNEL1		1
#define CHANNEL_INVALID	255

/* Helper macros */
#define SET_BITS(input, val, mask)	(input ^ ((input ^ val) & mask))
#define TOGGLE_BIT(input, mask)	(input ^ mask)
#define GET_BITS(input, mask)	(input & mask)

/* Interrupt flag */
#define	NO_INT_PENDING	0	/* No interrupt pending */
#define	INT_PENDING		1	/* Interrupt pending */

/* Capture select */
#define CAP_SEL_OFFSET	7	/* Bit offset of Timer x channel y capture select */
#define NORM_CAPTURE	0	/* Use normal capture input */
#define	RF_CAPTURE		1	/* Use RF event(s) enabled in the RFIM register to trigger a capture */

/* Interrupt mask */
#define INT_MASK_OFFSET	6	/* Bit offset of Timer x channel y interrupt mask */
#define	INT_DISABLED	0	/* Interrupt disabled */
#define	INT_ENABLED		1	/* Interrupt enabled */

/* Compare output mode */
#define	COMP_OUT_OFFSET	5		/* Bit offset of Timer x channel y compare output mode */
#define	SET_ON_COMP		0x00	/* Set output on compare */
#define	CLR_ON_COMP		0x08	/* Clear output on compare */
#define	TOGGLE_ON_COMP	0x10	/* Toggle output on compare */
#define	SET_ON_COMP_UP	0x18	/* Set output on compare-up, clear on 0 (clear on compare-down in up/down mode) */
#define	CLR_ON_COMP_UP	0x20	/* Clear output on compare-up, set on 0 (set on compare-down in up/down mode) */
#define	SET_CLR			0x28	/* For Timer 1 channel 0 - Reserved
								   For Timer 1 channel 1/2 - Set when equal to TxCCy, clear when equal to TxCC0
								   For Timer 3/4 channel 0 - Set output on compare, clear on 0xFF
								   For Timer 3/4 channel 1 - Set output on compare, clear on TxCC0 */
#define	CLR_SET			0x30	/* For Timer 1 channel 0 - Reserved
								   For Timer 1 channel 1/2 - Clear when equal to TxCCy, set when equal to TxCC0
								   For Timer 3/4 channel 0 - Clear output on compare, set on 0x00
								   For Timer 3/4 channel 1 - Clear output on compare, set on TxCC0 */
#define	DSM_MODE_ENABLE	0x38	/* For Timer 1 channel 0 - Reserved
								   For Timer 1 channel 1 - DSM mode enable
								   All others - Not used
								   (use as mask) */
/*!@} */

/*! \name Mode. Select capture or compare mode
@{*/
/* Mode. Select capture or compare mode */
#define	MODE_SELECT_OFFSET	2	/* Bit offset of Timer x channel y mode select
 CMP != 111 - Select Timer 1 channel 1 capture or compare mode
 CMP = 111 - Set the DSM speed */
#define	CAPTURE_MODE		0	/* For Timer channel 1 & CMP = 111 - 1/8 of timer tick speed
								   All others - Capture mode*/
#define	COMPARE_MODE		1	/* For Timer channel 1 & CMP = 111 - 1/4 of timer tick speed
								   All others - Compare mode */
/*!@} */

/*! \name Capture mode select
@{*/
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
/*!@} */

/*! \name Timer x/USARTx I/O location
@{*/
/* Timer x/USARTx I/O location */
#define	IO_LOC_ALT_1	0	/* Alternative 1 location */
#define	IO_LOC_ALT_2	1	/* Alternative 2 location */
#define	IO_LOC_INVALID	255 /* Invalid location */
/*!@} */

/*! \name Port x function select
@{*/
/* Port x function select */
#define GPIO		0 /* General purpose I/O */
#define PERIPHERAL	1 /* Peripheral function */
/*!@} */



/* TIMER SPECIFIC DEFINES */
#if defined(TIMER1)
/**********************************
 *             TIMER 1            *
 **********************************/

 #include <timer1.h>

/* only Timer 1 has a channel 2 */
#define	CHANNEL2		2

/* Prescalers */
#define	PRESCALER_1			1
#define	PRESCALER_8			8
#define	PRESCALER_32		32
#define	PRESCALER_128		128
#define	PRESCALER_INVALID	255

/* Prescaler Tick */
/* need to check if this a valid for all timers or not, if they are then they
   can be used for all timers. */
#define	PRESCALER_1_TICK	12000000
#define	PRESCALER_8_TICK	1500000
#define	PRESCALER_32_TICK	375000
#define	PRESCALER_128_TICK	93750

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
#define	T1_MODE_MODULO		0x02	/* Modulo, repeatedly count from 0x0000 to T1CC0 */
#define	T1_MODE_UPDOWN		0x03	/* Up/down, repeatedly count from 0x0000 to T1CC0 and from T1CC0 down to 0x0000 */
#define T1_MODE_INVALID		0xff
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
 *      TIMIF     *
 *****************/
 
/* Timer overflow interrupt mask - OVFIM */
#define TIMER_OVFL_INT_MASK_REGISTER	TIMIF
#define TIMER_OVFL_INT_MASK_OFFSET		6
#define TIMER_OVFL_INT_MASK_MASK		64


#elif defined(TIMER3)
/**********************************
 *             TIMER 3            *
 **********************************/
#include <timer3.h>

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
#define TIMER_PRESCALER_REGISTER	T3CTL
#define TIMER_PRESCALER_OFFSET		0
#define TIMER_PRESCALER_MASK		3

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
#define TIMER_PRESCALER_REGISTER	T4CTL
#define TIMER_PRESCALER_OFFSET		0
#define TIMER_PRESCALER_MASK		3

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

#define SET_TIMER_PRESCALER(v)	{ TIMER_PRESCALER_REGISTER = SET_BITS(TIMER_PRESCALER_REGISTER, v, TIMER_PRESCALER_MASK); }
#define GET_TIMER_PRESCALER()	( GET_BITS(TIMER_PRESCALER_REGISTER, TIMER_PRESCALER_MASK) )

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

#define SET_CHANNEL0_CAPCOMP_VALUE(v)	{CHANNEL0_CAPCOMP_VALUE_HIGH = (uint8)(v >> 8); CHANNEL0_CAPCOMP_VALUE_LOW = (uint8)v;}


/* PreScaler functions */
uint8 getT1PreScaler() {
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
}

BIT setT1PreScaler(uint8 preScaler) {
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
}

/* IO Location functions*/
BIT setT1IoLocation(uint8 ioLocation) {
	switch (ioLocation) {
		case IO_LOC_ALT_1:
		case IO_LOC_ALT_2:
			 SET_TIMER_IO_LOC(ioLocation);
			break;
		default:
			return 1;
			break;
	}
	return 0;
}

uint8 getT1IoLocation() {
	uint8 ioLoc;
	ioLoc = GET_TIMER_IO_LOC();
	switch (ioLoc) {
		case IO_LOC_ALT_1:
		case IO_LOC_ALT_2: 
			return ioLoc;
			break;
	}
	return IO_LOC_INVALID;
}

/* functions to setup channel */
BIT setT1ChannelMode(uint8 channelNum, uint8 mode) {
	switch (channelNum) {
		case CHANNEL0: 
			SET_CHANNEL0_CAP_COMP_MODE(mode);
			break;
		case CHANNEL1: 
			SET_CHANNEL1_CAP_COMP_MODE(mode);
			break;
		case CHANNEL2: 
			SET_CHANNEL2_CAP_COMP_MODE(mode);
			break;
		default: 
			return 1;
			break;
	}
	return 0;
}

BIT setT1ChannelCompareMode(uint8 channelNum, uint8 compMode) {
	switch (channelNum) {
		case CHANNEL0: 
			SET_CHANNEL0_COMP_MODE(compMode);
			break;
		case CHANNEL1: 
			SET_CHANNEL1_COMP_MODE(compMode);
			break;
		case CHANNEL2: 
			SET_CHANNEL2_COMP_MODE(compMode);
			break;
		default: 
			return 1;
			break;
	}
	return 0;
}

BIT setT1ChannelFunction(uint8 channelNum, uint8 function) {
	uint8 ioLoc;
	uint8 pin;
	ioLoc = getT1IoLocation();
	
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

BIT t1ChannelInit(uint8 channelNum, uint8 mode, uint8 compMode, uint8 function) {
	if (checkT1Channel(channelNum) == 0) {
		if (checkChannelMode(mode) == 0) {
			if (setT1ChannelMode(channelNum, mode) == 1) {
				return 1;
			}
		}
		if (checkT1ChannelCompareMode(channelNum, compMode) == 0) {
			if (setT1ChannelCompareMode(channelNum, compMode) == 1) {
				return 1;
			}
		}
		if (checkChannelFunction(function) == 0) {
			if (setT1ChannelFunction(channelNum, function) == 1) {
				return 1;
			}
		}
		return 0;
	}
	return 1;
}

/* functions to start/stop a timer */
BIT t1Mode(uint8 mode) {
	if (checkT1Mode(mode) == 0) {
		SET_TIMER_MODE(mode);
		return 0;
	}
	return 1;
}

uint8 getT1Mode() {
	uint8 tMode;
	tMode = GET_TIMER_MODE();
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
BIT setT1Frequency(uint32 frequency) {
	uint16 val;
	if (frequency == 0) {
		return 1;
	}
	val = calculateT1CompareValue(frequency);
	if (val == 0 || val == 0xffff) {
		return 1;
	}
	SET_CHANNEL0_CAPCOMP_VALUE(val);
	return 0;
}

uint16 calculateT1CompareValue(uint32 frequency) {
	switch (getT1Mode()) {
		case T1_MODE_MODULO:
			switch (getT1PreScaler()) {
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
BIT checkT1Mode(uint8 mode) {
	switch (mode) {
		case T1_MODE_OFF:
		case T1_MODE_FREE:
		case T1_MODE_MODULO:
		case T1_MODE_UPDOWN:
			return 0;
			break;
	}
	return 1;
}

BIT checkT1Channel(uint8 channelNum) {
	switch (channelNum) {
		case CHANNEL0:
		case CHANNEL1:
		case CHANNEL2:
			return 0;
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
BIT t1Init(uint8 ioLocation, uint8 preScaler) {
	if (setT1IoLocation(ioLocation) == 1) {
		return 1;
	}
	/* set perScaler if invalud return false */
	if (setT1PreScaler(preScaler) == 1) {
		return 1;
	}
	return 0;
}
