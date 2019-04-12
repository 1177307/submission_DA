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
	DDRB |= (1 << DDB1)|(1 << DDB2);
	// PB1 and PB2 is now an output
	ICR1 = 0xFFFF;
	// set TOP to 16bit
	OCR1A = 0x0000;
	// set PWM for 0% duty cycle @ 16bit
	OCR1B = 0xF332;
	// set PWM for 95% duty cycle @ 16bit
	TCCR1A |= (1 << COM1A1)|(1 << COM1B1);
	// set none-inverting mode
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12)|(1 << WGM13);
	// set Fast PWM mode using ICR1 as TOP
	TCCR1B |= (1 << CS10);
	// START the timer with no prescaler
    DDRD = 0x0F;  //activate portd lower pins as output
	PORTD = 0x01; //using the PIND.1 for the VCC of the DC MOTOR
	DDRC &= (0 << 2) || (0 << 0);  /* SET PORTC.1 as the PUSHBUTTON AND PINC0 as the POTENTIOMETER*/
	PORTC |= (1 << 2); //enable pull-up
    while (1) 
    {
		if (!(PINC & (1 << PINC1))){
		  PORTD  ^= 0x01;
		}
		
    }
	return 0;
}

