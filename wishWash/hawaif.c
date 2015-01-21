/*
 * hawaif.c
 *
 * Created: 1/20/2015 10:32:23 AM
 *  Author: ixchel
 */ 

#include <avr/io.h>
#include "hawaif.h"

#define RELAYPIN   PB2
#define ILINEPIN   PB1
#define TLINEPIN   PB0

void stopTimer()
{
	
}

void startTimer()
{
	
}


void switchRelay15()
{
	PORTB &=  ~(1<< RELAYPIN);
}

void switchRelay53s()
{
	PORTB |=  (1<< RELAYPIN);
}

void stopADCPolling()
{
	
}

/*
ISR(ADC_vect)
{
	lastADCVal = ADC;
	++ adcCnt;
	++ adcCount;

	if (adcCnt == pidStepDelays)  {
		adcCnt = 0;
		adcTick = 1;
	}
	
	
	startTimer();  // used during debugging
	// call pid and set next correction done asynchronously in main tread
}




ISR(TIMER1_COMPA_vect)
{    // needed for ADC so far..
	uint8_t   TIFRmask;
	++t1Count;
	ADCSRA  |= (1<<ADSC);   // start one ADC cycle
	stopTimer();  //
	TIFRmask = ~(1<< OCF1A);   //  for debuging
	TIFR1  &=  TIFRmask;  // during debugging found out, that it is better to do this
	
}
*/

void startADCPolling()
{
			// Timer 1    prepare  for ADC triggering 

		TCCR1 = 1 << CTC1; 
		OCR1A = 0xFF;  // counter top value, 0x2FF means approx  1 - 2 ADC measures per sec
		GTCCR = 0x00;
		TIMSK  = 1 << OCIE1A;  //  interrupt needed for ADC trigger
		TCNT1 = 0x0000 ;


		//  init ADC
/*
		lastADCVal = 0;

		ADMUX = (1<<REFS0); //  AVCC as ref.voltage, right adjust, ADC0 input
		DIDR0 = (1<<ADC0D);  // disable digital input

		ADCSRB = 0x00 ;
		//  timer 1 comp match trigger

		ADCSRA  = (1<<ADEN) | (1<<ADIE) | (1<<ADPS1) | (1<<ADPS2);  // | (1<<ADPS0)  now 64 prescaler wihout ps0
		// ena adc, set single conversion mode, int enable,  128 prescaler

		//	ADCSRA  = 0b00000111;  // disa ADC, ADATE, ADIE


		// start Timer 1 and hence also ADC
		*/
		TCCR1 =  (1 << CS10) |  (1 << CS11) | (1 << CS12) | (1 << CS13) ;      //   16394 prescaler... about 488 Hz at 8Mhz CLK
//		sei();
}

void startPotiTimer()
{
	
}

void stopPotiTimer()
{
	
}

void init()
{
	timerReachedEvent = 0;
	iLineOnEvent = 0;
	iLineOffEvent = 0;
	tPressedEvent = 0;
	tReleasedEvent = 0;
	ev53sSwitchedHighEvent = 0;
	ev53sSwitchedLowEvent  = 0;
}

int isILineOn()
{
	int8_t res = (PORTB & (1 << ILINEPIN)) != 0;
	return res;
}


int isTLineOn()
{
		int8_t res = (PORTB & (1 << TLINEPIN)) != 0;
		return res;
}