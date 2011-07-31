#ifndef _TIMER_DEFS_H
#define _TIMER_DEFS_H

/* Timer Channels
		   +---------+-----------+
		   | Timer 1 | Timer 3/4 |
+----------+---------+-----------+
| CHANNEL0 |   YES   |    YES    |
+----------+---------+-----------+
| CHANNEL1 |   YES   |    YES    |
+----------+---------+-----------+
| CHANNEL2 |   YES   |    NO     |
+----------+---------+-----------+
*/
#define	CHANNEL0		0
#define	CHANNEL1		1
#define	CHANNEL2		2
#define CHANNEL_INVALID	255

/* Prescalers
	  +---------+-----------+
	  | Timer 1 | Timer 3/4 |
+-----+---------+-----------+
| 1   |   YES   |    YES    |
+-----+---------+-----------+
| 2   |	  NO    |    YES    |
+-----+---------+-----------+
| 4   |	  NO    |    YES    |
+-----+---------+-----------+
| 8   |	  YES   |    YES    |
+-----+---------+-----------+
| 16  |	  NO    |    YES    |
+-----+---------+-----------+
| 32  |	  YES   |    YES    |
+-----+---------+-----------+
| 64  |	  NO    |    YES    |
+-----+---------+-----------+
| 128 |	  YES   |    YES    |
+-----+---------+-----------+
*/
#define	PRESCALER_1			1
#define	PRESCALER_2			2
#define	PRESCALER_4			4
#define	PRESCALER_8			8
#define	PRESCALER_16		16
#define	PRESCALER_32		32
#define	PRESCALER_64		64
#define	PRESCALER_128		128
#define	PRESCALER_INVALID	255

/* Prescalers Tick frequencies
These are used in calculating the values for frequencies
*/
#define	PRESCALER_1_TICK	24000000
#define	PRESCALER_2_TICK	12000000
#define	PRESCALER_4_TICK	6000000
#define	PRESCALER_8_TICK	3000000
#define	PRESCALER_16_TICK	1500000
#define	PRESCALER_32_TICK	750000
#define	PRESCALER_64_TICK	375000
#define	PRESCALER_128_TICK	187500

/* Compare mode values
				  +-----------------------------------+-------------+
				  |              Timer 1              |  Timer 3/4  |
				  +-----------+-----------+-----------+-------------+
				  | Channel 0 | Channel 1 | Channel 2 | Channel 0/1 |
+-----------------+-----------+-----------+-----------+-------------+
| SET_ON_COMP     |    YES    |    YES    |    YES    |     YES     |
+-----------------+-----------+-----------+-----------+-------------+
| CLR_ON_COMP     |    YES    |    YES    |    YES    |     YES     |
+-----------------+-----------+-----------+-----------+-------------+
| TOGGLE_ON_COMP  |    YES    |    YES    |    YES    |     YES     |
+-----------------+-----------+-----------+-----------+-------------+
| SET_ON_COMP_UP  |    YES    |    YES    |    YES    |     YES     |
+-----------------+-----------+-----------+-----------+-------------+
| CLR_ON_COMP_UP  |    YES    |    YES    |    YES    |     YES     |
+-----------------+-----------+-----------+-----------+-------------+
| SET_CLR         |    NO     |    YES    |    YES    |     YES     |
+-----------------+-----------+-----------+-----------+-------------+
| CLR_SET         |    NO     |    YES    |    YES    |     YES     |
+-----------------+-----------+-----------+-----------+-------------+
| DSM_MODE_ENABLE |    NO     |    YES    |    NO     |     NO      |
+-----------------+-----------+-----------+-----------+-------------+
*/
#define	SET_ON_COMP		0x00
#define	CLR_ON_COMP		0x08
#define	TOGGLE_ON_COMP	0x10
#define	SET_ON_COMP_UP	0x18
#define	CLR_ON_COMP_UP	0x20
#define	SET_CLR			0x28
#define	CLR_SET			0x30
#define	DSM_MODE_ENABLE	0x38

/* Channel mode */
#define	CAPTURE_MODE	0
#define	COMPARE_MODE	1

#define	IO_LOC_ALT_1	0
#define	IO_LOC_ALT_2	1

#define GPIO		0
#define PERIPHERAL	1

/* Timer mode
			  +---------+-----------+
			  | Timer 1 | Timer 3/4 |
+-------------+---------+-----------+
| MODE_OFF    |   YES   |    NO     |
+-------------+---------+-----------+
| MODE_FREE   |	  YES   |    YES    |
+-------------+---------+-----------+
| MODE_MODULO |	  YES   |    YES    |
+-------------+---------+-----------+
| MODE_UPDOWN |	  YES   |    YES    |
+-------------+---------+-----------+
| MODE_DOWN   |	  NO    |    YES    |
+-------------+---------+-----------+
*/
#define	MODE_OFF	0x00
#define	MODE_FREE	0x01
#define	MODE_MODULO	0x02
#define MODE_UPDOWN	0x03
#define	MODE_DOWN	0x04

#endif