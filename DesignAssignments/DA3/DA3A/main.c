/*
 * uart_hello.c
 *
 * Created: 3/27/2019 8:57:34 PM
 * Author : TheodorePele
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

//NOTE RAND_MAX is 0x7FFF 32767
#define BAUDRATE 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)

//Declaration of our functions
void USART_init(void);
unsigned char USART_receive(void);
void USART_send( unsigned char data);
void USART_putstring(char* StringPtr);

char String[] = "String\n";  //String[] is in fact an array but when we put the text between the " " symbols the compiler threats it as a String and automatically puts the null termination character in the end of the text

int main(void) {
	USART_init();        //Call the USART initialization code
	int zx = 1;
	char stflt[8];
	char stint[6];
	while (zx){
	char gennum [4];
	int num; 
	num = rand();
	itoa(num, gennum, 10);
	
	int i;
	for (i = 0; i < 5; i++){
		stint[i] = gennum[i];
	}
	stint[5] = 0x0a;
	stint[6] = 0x00; 
	
	char genflt [8];
	int nnflt;
	nnflt = random();
	itoa (nnflt, genflt, 10);
	
	stflt[0] = '0';
	stflt[1] = '.';
	for (i = 0; i < 5; i++){
		stflt[i+2] = genflt[i];
	}
	stflt[7] = '\n';
	stflt[8] = '\0';
	zx = 0;
	}
	
	while (1) {      //Infinite loop
		USART_putstring(String);    //Pass the string to the USART_putstring function and sends it over the serial
	//	USART_putstring(stint);    //Pass the string to the USART_putstring function and sends it over the serial
		USART_putstring(stflt);
		_delay_ms(5000);        //Delay for 5 seconds so it will re-send the string every 5 seconds
		zx  = 1;
	}

	return 0;
}

void USART_init(void) {

	UBRR0H = (uint8_t)(BAUD_PRESCALLER >> 8);
	UBRR0L = (uint8_t)(BAUD_PRESCALLER);
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	UCSR0C = (3 << UCSZ00);
}

unsigned char USART_receive(void) {

	while (!(UCSR0A & (1 << RXC0)));
	return UDR0;

}

void USART_send( unsigned char data) {

	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;

}

void USART_putstring(char* StringPtr) {

	while (*StringPtr != 0x00) {
		USART_send(*StringPtr);
		StringPtr++;
	}

}
