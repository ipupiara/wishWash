/*
 * hawaif.c
 *
 * Created: 1/20/2015 10:32:23 AM
 *  Author: ixchel
 */ 

#include <avr/io.h>
#include "hawaif.h"


void enterIdleSleepMode()
{
	MCUCR &= ~((1<<SM0) | (1<<SM1));  // select idle sleep mode
	MCUCR |= (1<<SE) ;  // enter idle sleep mode
	MCUCR &= ~(1<<SE);  // disable sleep mode after wake up
}


void switchRelay15()
{

}

void switchRelay53s()
{
	
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
}

int isILineOn()
{
	return 1;
}