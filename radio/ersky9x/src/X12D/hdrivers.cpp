


#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "hal.h"

#include "..\ersky9x.h"
#include "..\logicio.h"


void init_rotary_encoder()
{
	configure_pins( 0x0C00, PIN_INPUT | PIN_PULLUP | PIN_PORTH ) ;
	configure_pins( 0x0002, PIN_INPUT | PIN_PULLUP | PIN_PORTC ) ;
//	RotaryDivisor = 2 ;
//	g_eeGeneral.rotaryDivisor = 2 ;
}

extern volatile int32_t Rotary_position ;
extern volatile int32_t Rotary_count ;
extern int32_t LastRotaryValue ;
extern int32_t Rotary_diff ;

void checkRotaryEncoder()
{
  register uint32_t dummy ;
	
	dummy = GPIOENCODER->IDR ;	// Read Rotary encoder ( PE11, PE9 )
	dummy >>= 10 ;
//	dummy = (dummy & 1) | ( ( dummy >> 1 ) & 2 ) ;	// pick out the two bits
	dummy &= 0x03 ;
	if ( dummy != ( Rotary_position & 0x03 ) )
	{
		if ( ( Rotary_position & 0x01 ) ^ ( ( dummy & 0x02) >> 1 ) )
		{
			Rotary_count -= 1 ;
		}
		else
		{
			Rotary_count += 1 ;
		}
		Rotary_position &= ~0x03 ;
		Rotary_position |= dummy ;
	}
}

