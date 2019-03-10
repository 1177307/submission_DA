/*
 * Cprogram.c
 *
 * Created: 3/9/2019 5:50:31 PM
 * Author : TheodorePele
 * Demo code from venki's video
 * Plus the code used from 2a.2
 */ 

/*Goal: connect interupt to portd.2 to poll for an event to turn on LED portb.2
  For 1.250*/
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0x00; //WANT TO TURN OFF ALL OTHER LEDs
	DDRB |= (1<<2);//SET PB2 AS AN OUTPUT
	PORTB |= (1 << 2); // TURN OFF FIRST
	PORTD |= 1<<2; //PULL ACTIVATED
	EICRA = 0X2;   //ACTIVATED ON A FALLING EDGE
	EIMSK = (1 << INT0); //ENABLE EXTERNAL INTERUPT 0
	sei (); //ENABLE INTERUPTS
	while (1) //NEEDED TO KEEP THE PROGRAM RUNNING OTHERWISE NOTHING HAPPENS
	{
		
	}
	/*
    while (1) 
    {
		PORTB ^= (1 << 4); // WAIT HERE
		_delay_ms(1000);
    }
	*/
}

ISR (INT0_vect) //ISR for external interrupt 0
{
	PORTB &= (0 << 2); //TURN ON
	_delay_ms(1250);   //will remain on for 1.25 seconds
	PORTB |= (1 << 2); //TURN OFF
}



