/******************
 * Global defines *
 ******************/

 /* Sets bits in a with bits from b using mask m
  * http://graphics.stanford.edu/~seander/bithacks.html#MaskedMerge */
#define SET_BITS(a, b, m)	(a ^ ((a ^ b) & m))

/* Toggle bit n of a */
#define TOGGLE_BIT(a, n)	(a ^ (1 << n))

/* Interrupt flag values */
#define	NO_INT_PENDING	0	/* No interrupt pending */
#define	INT_PENDING		1	/* Interrupt pending */

/* Capture select */
#define CAP_SEL_OFFSET	7		/* Bit offset of Timer x channel y capture select */
#define NORM_CAPTURE	0	/* Use normal capture input */
#define	RF_CAPTURE		1	/* Use RF event(s) enabled in the RFIM register to trigger a capture */

/* Interrupt mask */
#define INT_MASK_OFFSET	6		/* Bit offset of Timer x channel y interrupt mask */
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

/* Mode. Select capture or compare mode */
#define	MODE_SELECT_OFFSET	2	/* Bit offset of Timer x channel y mode select */
/* CMP != 111 - Select Timer 1 channel 1 capture or compare mode
   CMP = 111 - Set the DSM speed */
#define	CAPTURE_MODE		0	/* For Timer channel 1 & CMP = 111 - 1/8 of timer tick speed
								   All others - Capture mode*/
#define	COMPARE_MODE		1	/* For Timer channel 1 & CMP = 111 - 1/4 of timer tick speed
								   All others - Compare mode */

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

/* Timer x/USARTx I/O location */
#define	ALT_1_LOC	0 /* Alternative 1 location */
#define	ALT_2_LOC	1 /* Alternative 2 location */

/* Port x function select */
#define GPIO		0 /* General purpose I/O */
#define PERIPHERAL	1 /* Peripheral function */

/****************************************************************************
 ****************************************************************************/

/******************************
 * Timer 1 Registers - 16-bit *
 ******************************/

/*********************************************
 * Timer 1 Counter (T1CNTH/T1CNTL), page 117 *
 *********************************************/

 /* Reset Timer 1 Counter by writing to low byte */
#define T1_CNT_RESET()	{T1CNTL = 0x00;}

/****************************************************************************/

/************************************************
 * Timer 1 Control and Status (T1CTL), page 117 *
 ************************************************/

/*******************************************
 * Timer 1 Channel 2 Interrupt flag, CH2IF *
 *******************************************/
/* Bit offset of Timer 1 Channel 2 Interrupt flag */
#define T1_CH2_INT_FLAG_OFFSET	7
/* Set Timer 1 Channel 2 interrupt flag */
#define T1_CH2_INT_FLAG_SET(v)	{T1CTL = SET_BITS(T1CTL, v << T1_CH2_INT_FLAG_OFFSET, 1 << T1_CH2_INT_FLAG_OFFSET);}
/* Toggle Timer 1 Channel 2 interrupt flag */
#define T1_CH2_INT_FLAG_TOGGLE()	{T1CTL = TOGGLE_BIT(T1CTL, T1_CH2_INT_FLAG_OFFSET);}

/*******************************************
 * Timer 1 Channel 1 Interrupt flag, CH1IF *
 *******************************************/
/* Bit offset of Timer 1 Channel 1 Interrupt flag */
#define T1_CH1_INT_FLAG_OFFSET	6
/* Set Timer 1 Channel 1 interrupt flag */
#define T1_CH1_INT_FLAG_SET(v)	{T1CTL = SET_BITS(T1CTL, v << T1_CH1_INT_FLAG_OFFSET, 1 << T1_CH1_INT_FLAG_OFFSET);}
/* Toggle Timer 1 Channel 1 interrupt flag */
#define T1_CH1_INT_FLAG_TOGGLE()	{T1CTL = TOGGLE_BIT(T1CTL, T1_CH1_INT_FLAG_OFFSET);}

/*******************************************
 * Timer 1 Channel 0 Interrupt flag, CH0IF *
 *******************************************/
/* Bit offset of Timer 1 Channel 0 Interrupt flag */
#define T1_CH0_INT_FLAG_OFFSET	5
/* Set Timer 1 Channel 0 interrupt flag */
#define T1_CH0_INT_FLAG_SET(v)	{T1CTL = SET_BITS(T1CTL, v << T1_CH0_INT_FLAG_OFFSET, 1 << T1_CH0_INT_FLAG_OFFSET);}
/* Toggle Timer 1 Channel 0 interrupt flag */
#define T1_CH0_INT_FLAG_TOGGLE()	{T1CTL = TOGGLE_BIT(T1CTL, T1_CH0_INT_FLAG_OFFSET);}

/**************************************************
 * Timer 1 Counter overflow Interrupt flag, OVFIF *
 **************************************************/
/* Bit offset of Timer 1 Counter overflow Interrupt flag */
#define T1_CNTOV_INT_FLAG_OFFSET	4
/* Set Timer 1 Counter overflow interrupt flag */
#define T1_CNTOV_INT_FLAG_SET(v)	{T1CTL = SET_BITS(T1CTL, v << T1_CNTOV_INT_FLAG_OFFSET, 1 << T1_CNTOV_INT_FLAG_OFFSET);}
/* Toggle Timer 1 Counter overflow interrupt flag */
#define T1_CNTOV_INT_FLAG_TOGGLE()	{T1CTL = TOGGLE_BIT(T1CTL, T1_CNTOV_INT_FLAG_OFFSET);}

/****************************************
 * Timer 1 Prescaler divider, DIV *
 ****************************************/
#define	T1_PRESCALER_1		0x00	/* Tick frequency/1 */
#define	T1_PRESCALER_8		0x04	/* Tick frequency/8 */
#define	T1_PRESCALER_32		0x08	/* Tick frequency/32*/
#define	T1_PRESCALER_128	0x0c	/* Tick frequency/128 (use as mask) */
/* Set Timer 1 Prescaler divider */
#define T1_PRESCALER_SET(v)		{T1CTL = SET_BITS(T1CTL, v, T1_PRESCALER_128); }

/**********************
 * Timer 1 Mode, MODE *
 **********************/
#define	T1_MODE_OFF			0x00	/* Operation is suspended */
#define	T1_MODE_FREE		0x01	/* Free-running, repeatedly count from 0x0000 to 0xFFFF */
#define	T1_MODE_MODULO		0x02	/* Modulo, repeatedly count from 0x0000 to T1CC0 */
#define	T1_MODE_UPDOWN		0x03	/* Up/down, repeatedly count from 0x0000 to T1CC0 and from T1CC0 down to 0x0000 */
/* Set Timer 1 Mode */
#define T1_MODE_SET(v)		{T1CTL = SET_BITS(T1CTL, v, T1_MODE_UPDOWN); }

/****************************************************************************/

/*****************************************************************
 * Timer 1 Channel 0 Capture/Compare Control (T1CCTL0), page 118 *
 *****************************************************************/

/*******************************************
 * Timer 1 channel 0 capture select, CPSEL *
 *******************************************/
/* Set Timer 1 channel 0 capture select */
#define T1_CH0_CAP_SEL_SET(v)	{T1CCTL0 = SET_BITS(T1CCTL0, v << CAP_SEL_OFFSET, 1 << CAP_SEL_OFFSET);}
/* Toggle Timer 1 channel 0 capture select */
#define T1_CH0_CAP_SEL_TOGGLE()	{T1CCTL0 = TOGGLE_BIT(T1CCTL0, CAP_SEL_OFFSET);}

/****************************************
 * Timer 1 Channel 0 interrupt mask, IM *
 ****************************************/
/* Set Timer 1 Channel 0 interrupt mask */
#define T1_CH0_INT_MASK_SET(v)	{T1CCTL0 = SET_BITS(T1CCTL0, v << INT_MASK_OFFSET, 1 << INT_MASK_OFFSET);}
/* Toggle Timer 1 Channel 0 interrupt mask */
#define T1_CH0_INT_MASK_TOGGLE()	{T1CCTL0 = TOGGLE_BIT(T1CCTL0, INT_MASK_OFFSET);}

/**********************************************
 * Timer 1 Channel 0 compare mode select, CMP *
 **********************************************/
/* Set Timer 1 Channel 0 compare mode */
#define T1_CH0_COMP_MODE_SET(v)		{T1CCTL0 = SET_BITS(T1CCTL0, v, DSM_MODE_ENABLE); }

/****************************************************************
 * Timer 1 channel 0 Mode. Select capture or compare mode, MODE *
 ****************************************************************/
/* Set Timer 1 Channel 0 compare mode */
#define T1_CH0_MODE_SET(v)	{T1CCTL0 = SET_BITS(T1CCTL0, v << MODE_SELECT_OFFSET, 1 << MODE_SELECT_OFFSET);}
/* Toggle Timer 1 Channel 0 compare mode */
#define T1_CH0_MODE_TOGGLE()	{T1CCTL0 = TOGGLE_BIT(T1CCTL0, MODE_SELECT_OFFSET);}

/**********************************************
 * Timer 1 Channel 0 capture mode select, CAP *
 **********************************************/
/* Set Timer 1 Channel 0 capture mode */
#define T1_CH0_CAP_MODE_SET(v)		{T1CCTL0 = SET_BITS(T1CCTL0, v, CAPTURE_BOTH); }

/****************************************************************************/

/*********************************************************************
 * Timer 1 Channel 0 Capture/Compare Value (T1CC0H/T1CC0L), page 118 *
 *********************************************************************/
/* Set the DSM sample rate in DSM mode */
 
/****************************************************************************/

/*****************************************************************
 * Timer 1 Channel 1 Capture/Compare Control (T1CCTL1), page 119 *
 *****************************************************************/

/*******************************************
 * Timer 1 channel 1 capture select, CPSEL *
 *******************************************/
/* Set Timer 1 channel 1 capture select */
#define T1_CH1_CAP_SEL_SET(v)	{T1CCTL1 = SET_BITS(T1CCTL1, v << CAP_SEL_OFFSET, 1 << CAP_SEL_OFFSET);}
/* Toggle Timer 1 channel 1 capture select */
#define T1_CH1_CAP_SEL_TOGGLE()	{T1CCTL1 = TOGGLE_BIT(T1CCTL1, CAP_SEL_OFFSET);}

/****************************************
 * Timer 1 Channel 1 interrupt mask, IM *
 ****************************************/
/* Set Timer 1 Channel 1 interrupt mask */
#define T1_CH1_INT_MASK_SET(v)	{T1CCTL1 = SET_BITS(T1CCTL1, v << INT_MASK_OFFSET, 1 << INT_MASK_OFFSET);}
/* Toggle Timer 1 Channel 1 interrupt mask */
#define T1_CH1_INT_MASK_TOGGLE()	{T1CCTL1 = TOGGLE_BIT(T1CCTL1, INT_MASK_OFFSET);}

/**********************************************
 * Timer 1 Channel 1 compare mode select, CMP *
 **********************************************/
/* Set Timer 1 Channel 1 compare mode */
#define T1_CH1_COMP_MODE_SET(v)		{T1CCTL1 = SET_BITS(T1CCTL1, v, DSM_MODE_ENABLE); }

/****************************************************************
 * Timer 1 channel 1 Mode. Select capture or compare mode, MODE *
 ****************************************************************/
/* Set Timer 1 Channel 1 compare mode */
#define T1_CH1_MODE_SET(v)	{T1CCTL1 = SET_BITS(T1CCTL1, v << MODE_SELECT_OFFSET, 1 << MODE_SELECT_OFFSET);}
/* Toggle Timer 1 Channel 1 compare mode */
#define T1_CH1_MODE_TOGGLE()	{T1CCTL1 = TOGGLE_BIT(T1CCTL1, MODE_SELECT_OFFSET);}

/**********************************************
 * Timer 1 Channel 1 capture mode select, CAP *
 **********************************************/
/* Set Timer 1 Channel 1 capture mode */
#define T1_CH1_CAP_MODE_SET(v)		{T1CCTL1 = SET_BITS(T1CCTL1, v, CAPTURE_BOTH); }

/****************************************************************************/

/*********************************************************************
 * Timer 1 Channel 1 Capture/Compare Value (T1CC1H/T1CC1L), page 119 *
 *********************************************************************/
/* DSM data */
 
/****************************************************************************/

/*****************************************************************
 * Timer 1 Channel 2 Capture/Compare Control (T1CCTL2), page 120 *
 *****************************************************************/

/*******************************************
 * Timer 1 channel 2 capture select, CPSEL *
 *******************************************/
/* Set Timer 1 channel 2 capture select */
#define T1_CH2_CAP_SEL_SET(v)	{T1CCTL2 = SET_BITS(T1CCTL2, v << CAP_SEL_OFFSET, 1 << CAP_SEL_OFFSET);}
/* Toggle Timer 1 channel 2 capture select */
#define T1_CH2_CAP_SEL_TOGGLE()	{T1CCTL2 = TOGGLE_BIT(T1CCTL2, CAP_SEL_OFFSET);}

/****************************************
 * Timer 1 Channel 2 interrupt mask, IM *
 ****************************************/
/* Set Timer 1 Channel 2 interrupt mask */
#define T1_CH2_INT_MASK_SET(v)	{T1CCTL2 = SET_BITS(T1CCTL2, v << INT_MASK_OFFSET, 1 << INT_MASK_OFFSET);}
/* Toggle Timer 1 Channel 2 interrupt mask */
#define T1_CH2_INT_MASK_TOGGLE()	{T1CCTL2 = TOGGLE_BIT(T1CCTL2, INT_MASK_OFFSET);}

/**********************************************
 * Timer 1 Channel 2 compare mode select, CMP *
 **********************************************/
/* Set Timer 1 Channel 2 compare mode */
#define T1_CH2_COMP_MODE_SET(v)		{T1CCTL2 = SET_BITS(T1CCTL2, v, DSM_MODE_ENABLE); }

/****************************************************************
 * Timer 1 channel 2 Mode. Select capture or compare mode, MODE *
 ****************************************************************/
/* Set Timer 1 Channel 2 mode */
#define T1_CH2_MODE_SET(v)	{T1CCTL2 = SET_BITS(T1CCTL2, v << MODE_SELECT_OFFSET, 1 << MODE_SELECT_OFFSET);}
/* Toggle Timer 1 Channel 2 mode */
#define T1_CH2_MODE_TOGGLE()	{T1CCTL2 = TOGGLE_BIT(T1CCTL2, MODE_SELECT_OFFSET);}

/**********************************************
 * Timer 1 Channel 2 capture mode select, CAP *
 **********************************************/
/* Set Timer 1 Channel 2 capture mode */
#define T1_CH2_CAP_MODE_SET(v)		{T1CCTL2 = SET_BITS(T1CCTL2, v, CAPTURE_BOTH); }

/****************************************************************************/

/*********************************************************************
 * Timer 1 Channel 2 Capture/Compare Value (T1CC2H/T1CC2L), page 120 *
 *********************************************************************/
/* Timer 1 channel 2 capture/compare value, */
 
/****************************************************************************
 ****************************************************************************/

/*****************
 * I/O Registers *
 *****************/

/****************************************
 * Peripheral Control (PERCFG), page 92 *
 ****************************************/
 
/*******************************
 * Timer 1 I/O location, T1CFG *
 *******************************/
/* Bit offset of Timer 1 I/O location */
#define T1_IO_LOC_OFFSET	6
/* Set Timer 1 I/O location */
#define T1_IO_LOC_SET(v)	{PERCFG = SET_BITS(PERCFG, v << T1_IO_LOC_OFFSET, 1 << T1_IO_LOC_OFFSET);}
/* Toggle Timer 1 I/O location */
#define T1_IO_LOC_TOGGLE()	{PERCFG = TOGGLE_BIT(PERCFG, T1_IO_LOC_OFFSET);}

/*******************************
 * Timer 3 I/O location, T3CFG *
 *******************************/
/* Bit offset of Timer 3 I/O location */
#define T3_IO_LOC_OFFSET	5
/* Set Timer 3 I/O location */
#define T3_IO_LOC_SET(v)	{PERCFG = SET_BITS(PERCFG, v << T3_IO_LOC_OFFSET, 1 << T3_IO_LOC_OFFSET);}
/* Toggle Timer 3 I/O location */
#define T3_IO_LOC_TOGGLE()	{PERCFG = TOGGLE_BIT(PERCFG, T3_IO_LOC_OFFSET);}

/*******************************
 * Timer 4 I/O location, T4CFG *
 *******************************/
/* Bit offset of Timer 4 I/O location */
#define T4_IO_LOC_OFFSET	4
/* Set Timer 4 I/O location */
#define T4_IO_LOC_SET(v)	{PERCFG = SET_BITS(PERCFG, v << T4_IO_LOC_OFFSET, 1 << T4_IO_LOC_OFFSET);}
/* Toggle Timer 4 I/O location */
#define T4_IO_LOC_TOGGLE()	{PERCFG = TOGGLE_BIT(PERCFG, T4_IO_LOC_OFFSET);}

/****************************************************************************/

/*******************************************
 * Port 0 Function Select (P0SEL), page 93 *
 *******************************************/

 /*******************************
 * Port 0 Pin p Function Select, SELP0_[7:0] *
 *******************************/
/* Set Port 0 Pin p function select */
#define P0_FUNC_SET(p, v)	{P0SEL = SET_BITS(P0SEL, v << p, 1 << p);}
/* Toggle Port 0 Pin p function select */
#define P0_FUNC_TOGGLE(p)	{P0SEL = TOGGLE_BIT(P0SEL, p);}

/****************************************************************************/

/*******************************************
 * Port 1 Function Select (P1SEL), page 93 *
 *******************************************/

 /*******************************
 * Port 1 Pin p Function Select, SELP1_[7:0] *
 *******************************/
/* Set Port 1 Pin p function select */
#define P1_FUNC_SET(p, v)	{P1SEL = SET_BITS(P1SEL, v << p, 1 << p);}
/* Toggle Port 1 Pin p function select */
#define P1_FUNC_TOGGLE(p)	{P1SEL = TOGGLE_BIT(P1SEL, p);}

