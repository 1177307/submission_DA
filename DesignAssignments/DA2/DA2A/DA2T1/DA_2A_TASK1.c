/*
 * DA_2A_TASK1_C.c
 *
 * Created: 3/2/2019 6:01:32 PM
 * Author : TheodorePele
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL //used for the delay function
#include <util/delay.h>

int main(void)
{
	//DESIGN A DELAY SUBROUTINE TO GENERATE A WAVEFORM ON PORTB.2
	//WITH 60% DC AND 0.725 SEC PERIOD
	//so 60% of 0.725 is 0.435 and low for 0.290
	DDRB = 0x00; //SET ALL OF PORT B TO HIGH
	//PORTB |= (1 << PINB2); //SET PIN 2 TO HIGH
    while (1) 
    {
		PORTB |= (1 << PINB2); //SET HIGH
		_delay_ms(435);// 0.435 SECONDS = 435 ms
		PORTB &= (0 << PINB2); //CLEAR TO LOW
		_delay_ms(290);// 0.290 seconds = 290 ms
		// combined total delay is 0.725 to make the period
    }
}

