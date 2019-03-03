/*
 * RW_GPIO.c
 *
 * Created: 3/2/2019 5:22:30 PM
 * Author : TheodorePele
 */ 

/*connect a sw to portc.2 to poll for an event to turn on 
LED at portb.2 for 1.250 sec after envt*/
#define F_CPU 16000000UL //used for the delay header file

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRB |= (1 << 2);  //activate portb.2 as output
	PORTB |= (1 << 2); //TURN LED OFF
	DDRC &= (0 << 2);  /* SET PORTC.1 FOR INPUT */
	PORTC |= (1 << 2); //enable pull-up
    while (1) 
    {
		if (!(PINC & (1 << PINC2))){
		  PORTB  &= ~(1 << 2); //active high so 0 will set LED on
		  _delay_ms(1250);
		}
		else
		  PORTB |= (1 << 2);
    }
	return 0;
}

