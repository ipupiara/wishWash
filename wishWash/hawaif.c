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


void switchRelay15()
{
	PORTB &=  ~(1<< RELAYPIN);
}

void switchRelay53s()
{
	PORTB |=  (1<< RELAYPIN);
}

void setWashTimer()
{
	
}

void setWishTimer()
{
	
}

void startADCPolling()
{
	
}

void stopADDCPolling()
{
	
}

void startTickTimer()
{
	
}

void init()
{
	startTickTimer();
	timerReachedEvent = 0;
	iLineOnEvent = 0;
	iLineOffEvent = 0;
	tPressedEvent = 0;
	tReleasedEvent = 0;
	ev53sSwitchedHighEvent = 0;
	ev53sSwitchedLowEvent  = 0;
	counterReachedEvent = 0;
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