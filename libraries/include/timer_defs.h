#ifndef _TIMER_DEFS_H
#define _TIMER_DEFS_H

#define	CHANNEL0		0
#define	CHANNEL1		1
#define	CHANNEL2		2
#define CHANNEL_INVALID	255

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

#define	MODE_OFF	0x00
#define	MODE_FREE	0x01
#define	MODE_MODULO	0x02
#define MODE_UPDOWN	0x03
#define	MODE_DOWN	0x04

#endif