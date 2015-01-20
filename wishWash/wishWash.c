/*
 * wishWash.c
 *
 * Created: 1/2/2015 1:26:04 PM
 *  Author: ixchel
 */ 


#include <avr/io.h>
#include "StateClass.h"
#include "hawaif.h"

uint8_t  fatalErrorOccurred;
CWishWashEvent ev;


/*
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
	eStateTPressed,
	eStateTReleased,
	eStateIon
};
*/

int main(void)
{
	startStateCharts();
	init();
	
    while(1)
    {
		enterIdleSleepMode();
		if (fatalErrorOccurred) {     // do this with highest priority (at the beginning)
			//			fatalErrorOccurred = 0;	  // once occurred state stays until restart/reset
			ev.evType = evFatalError;
			processEvent(&SWishWashStateChart,&ev);
		}
		
    }
}