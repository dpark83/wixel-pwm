#include <timer.h>

/*
MCU is running at 24Mhz - maybe add a macro to get the configured speed

To calculated Counter Tick frequency:
MCU speed/pre-scaler

pre-scaler	Counter Tick frequency
	1			24,000,000
	8			3,000,000
	32			750,000
	128			187,500

Not sure if TxCC0 has to be a string of ones or not, if so then these are the
valid frequencies.

Counter Tick frequency	Frequency		TxCC0
		187,500			2.86hz 			0xFFFF
		187,500			5.72hz 			0x7FFF
		187,500			11.44hz 		0x3FFF
		187,500			22.89hz 		0x1FFF
		187,500			45.79hz 		0x0FFF
		187,500			91.60hz 		0x07FF
		187,500			183.28hz 		0x03FF
		187,500			366.93hz 		0x01FF
		187,500			735.29hz 		0x00FF
		187,500			1,476.38hz 		0x007F
		187,500			2,976.19hz 		0x003F
		187,500			6,048.39hz 		0x001F
		187,500			12,500.00hz 	0x000F
		187,500			26,785.71hz 	0x0007
		187,500			62,500.00hz 	0x0003
		187,500			187,500.00hz 	0x0001
	
*/

void timercfg() {
	return;
}