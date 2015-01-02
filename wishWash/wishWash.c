/*
 * wishWash.c
 *
 * Created: 1/2/2015 1:26:04 PM
 *  Author: ixchel
 */ 


#include <avr/io.h>

enum eEventTypes
{
	evNone = 0,
	evTPressed,
	evTReleased,
	evISwitchedOn,
	evISwitchedOff,
	ev53sSwitchedLow,
	ev53sSwitchedHigh,
	evTimerExpired,
	evTimerTick,
	evPotiValueChanged
} ;


enum eStateTypes
{
	eStateIdle =1,
	eStartStateWash,
	eStateWishInterval
} eStateType;


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

int8_t currentState;
int8_t currentEvent;

int main(void)
{
    while(1)
    {
		
        //TODO:: Please write your application code 
		
		
		

    }
}