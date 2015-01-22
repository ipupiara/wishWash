/*
 * hawaif.c
 *
 * Created: 1/20/2015 10:32:23 AM
 *  Author: ixchel
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

#include "hawaif.h"

#define RELAYPIN   PB2
#define ILINEPIN   PB1
#define TLINEPIN   PB0
#define PINMASK  ((1<<PB0) | (1<< PB1) | (1<<PB2))
// PB3 used as ADC3
#define FACTORLOW  0.078125
#define FACTORHIGH 0.2

int16_t lastADCVal;
uint16_t  tickCnt;
uint16_t  ticksNeeded;

int8_t  lastPinB;


void switchRelay15()
{
	PORTB &=  ~(1<< RELAYPIN);
}

void switchRelay53s()
{
	PORTB |=  (1<< RELAYPIN);
}


ISR(PCINT0_vect)
{
	int8_t newLinePin =  (PINB & (1<< ILINEPIN));
	int8_t oldLinePin =  (lastPinB  & (1<< ILINEPIN));
	if ( newLinePin & (~oldLinePin) ) {
		iLineOnEvent = 1;
	}
	if ( (~newLinePin) & oldLinePin ) {
		iLineOffEvent = 1;
	}
	newLinePin =  (PINB & (1<< TLINEPIN));
	oldLinePin =  (lastPinB  & (1<< TLINEPIN));
	if ( newLinePin & (~oldLinePin) ) {
		tPressedEvent = 1;
	}
	if ( (~newLinePin) & oldLinePin ) {
		tReleasedEvent = 1;
	}
	newLinePin =  (PINB  & (1<< RELAYPIN));
	oldLinePin =  (lastPinB & (1<< RELAYPIN));
	if ( newLinePin & (~oldLinePin) ) {
		ev53sSwitchedHighEvent = 1;
	}
	if ( (~newLinePin) & oldLinePin ) {
		ev53sSwitchedLowEvent = 1;
	}
	lastPinB = PINB;
}

ISR(ADC_vect)
{
	lastADCVal = ADC;
	if (lastADCVal < 0X0300) {
		ticksNeeded = (uint16_t) (FACTORLOW * lastADCVal);
	} else {
		ticksNeeded = 60 +  (uint16_t) (FACTORHIGH * lastADCVal);
	} 
	
//	startTimer();  // used during debugging
	// call pid and set next correction done asynchronously in main tread
}


ISR(TIMER1_COMPA_vect)
{   
	uint8_t   TIFRmask;
	++tickCnt;
	if (tickCnt > ticksNeeded) {
		timerReachedEvent = 1;
	}  else {
	//	stopTimer();
		ADCSRA  |= (1<<ADSC);   // start one ADC cycle
	}
	TIFRmask = ~(1<< OCF1A);   //  for debugging
	TIFR  &=  TIFRmask;  // during debugging found out, that it is better to do this
}


void stopADCPolling()
{
	TCCR1 &= ~( (1 << CS10) |  (1 << CS11) | (1 << CS12) | (1 << CS13)) ; 
	ADCSRA  &= 	~(1<< ADEN);
}

void startADCPolling()
{
			// Timer 1    prepare  for ADC triggering 

		tickCnt = 0;
		ticksNeeded = 20;   // 10 sec
		TCCR1 = 1 << CTC1; 
		OCR1A = 0xF4;  // counter top value, 0x2FF means approx   2 ADC measures per sec
		GTCCR = 0x00;
		TIMSK  = 1 << OCIE1A;  //  interrupt needed for ADC trigger
		TCNT1 = 0x0000 ;

		//  init ADC

		lastADCVal = -1;

		ADMUX = (1<<REFS0) | (1<<REFS1) | (1 << MUX0) | (1 << MUX1) ; //  VCC as ref.voltage, right adjust, ADC3 input (PB3)
		DIDR0 = (1<<ADC3D);  // disable digital input

		ADCSRA  = (1<<ADEN) | (1<<ADIE) | (1<<ADPS1) | (1<<ADPS2);  // | (1<<ADPS0)  now 64 prescaler wihout ps0 approx 125 kHz
		// ena adc, set single conversion mode, int enable
		ADCSRB = 0x00 ;
		//  timer 1 comp match trigger

		// start Timer 1 and hence also ADC
		TCCR1 |=  (1 << CS10) |  (1 << CS11) | (1 << CS12) | (1 << CS13) ;      //   16384 prescaler... about 488 Hz at 8Mhz CLK
		sei();
}

void startITimer()
{
	startADCPolling();
}

void stopITimer()
{
	stopADCPolling();
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
	
	// enable pcint0..2
	DDRB  &= ~((1<DDB0) | (1<< DDB1) | (1<<DDB2)  );            // one could also use above pin defines here.. it is the same sequence
	PORTB   &= ~((1<PB0) | (1<< PB1) | (1<<PB2)  );			// disable pullups
	PCMSK |= ((1 << PCINT0) |  (1 << PCINT1) | (1 << PCINT2));
	GIMSK |= (1 << PCIE);
	lastPinB = PINB;
}

int isILineOn()
{
	int8_t res = (PINB & (1 << ILINEPIN)) != 0;
	return res;
}


int isTLineOn()
{
		int8_t res = (PINB & (1 << TLINEPIN)) != 0;
		return res;
}