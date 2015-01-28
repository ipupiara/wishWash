
#include <avr/io.h>
#include <stdio.h>
//#include <iostream.h>
//#include <assert.h>
#include <string.h>

#include "TStatechart.h"
#include "StateClass.h"
#include "hawaif.h"

extern const uStInt uStIntHandlingDone;
extern const uStInt uStIntNoMatch;


CWishWashEvent* currentEvent;

int8_t wishCounter;

CWishWashEvent* getNextEvent(CWishWashEvent* pev)
{
	CWishWashEvent* res = NULL;
	if (timerReachedEvent ==  1) {
		timerReachedEvent = 0;
		pev->evType = evTimerExpired;
		res = pev;
	}
	if (iLineOnEvent ==  1) {
		iLineOnEvent = 0;
		pev->evType = evISwitchedOn;
		res = pev;
	}
	if (iLineOffEvent ==  1) {
		iLineOffEvent = 0;
		pev->evType = evISwitchedOff;
		res = pev;
	}
	if (tPressedEvent ==  1) {
		tPressedEvent = 0;
		pev->evType = evTPressed;
		res = pev;
	}
	if (tReleasedEvent ==  1) {
		tReleasedEvent = 0;
		pev->evType = evTReleased;
		res = pev;
	}
	if (ev53sSwitchedHighEvent ==  1) {
		ev53sSwitchedHighEvent = 0;
		pev->evType = ev53sSwitchedHigh;
		res = pev;
	}
	if (ev53sSwitchedLowEvent ==  1) {
		ev53sSwitchedLowEvent = 0;
		pev->evType = ev53sSwitchedLow;
		res = pev;
	}
	return res;
}


uStInt evWishWashChecker(void)
{
	uStInt res = uStIntNoMatch;
	return res;
}

void entryIdleState(void)
{
	switchRelay53s();
	if(isTangoLineOn()) {
		tPressedEvent = 1;
	} else if (isIndiaLineOn()) {
		iLineOnEvent = 1;		
	}
}

void exitIdleState(void)
{

}

uStInt evIdleChecker(void)
{
	uStInt res = uStIntNoMatch;

	if (currentEvent->evType == ev53sSwitchedLow) 
	{	
//			BEGIN_EVENT_HANDLER(PJoesTriacStateChart, eStateTriacIdle);
				// No event action.
			switchRelay53s();	
//			END_EVENT_HANDLER(PJoesTriacStateChart);
			res =  uStIntHandlingDone;
	}
	if (currentEvent->evType == evTPressed)
	{	
			BEGIN_EVENT_HANDLER(PWishWashStateChart, eStateTPressed);
				// No event action.
			END_EVENT_HANDLER(PWishWashStateChart);
			res =  uStIntHandlingDone;
	}
	if (currentEvent->evType == evISwitchedOn) 
	{	
			BEGIN_EVENT_HANDLER(PWishWashStateChart, eStateIon);
				// No event action.
			END_EVENT_HANDLER(PWishWashStateChart);
			res =  uStIntHandlingDone;
	}
	return (res); 
}

void entryTPressedState(void)
{
	switchRelay15();
}



void exitTPressedState(void)
{
}

uStInt evTPressedChecker(void)
{
	uStInt res = uStIntNoMatch;

	if (currentEvent->evType == evTReleased){
	
		BEGIN_EVENT_HANDLER(PWishWashStateChart, eStateTReleased);
			// No event action.
		END_EVENT_HANDLER(PWishWashStateChart);

		res =  uStIntHandlingDone;
	}
	return (res); 
}

void entryTReleasedState(void)
{
	wishCounter = 0;
}

void exitTReleasedState(void)
{

}

uStInt evTReleasedChecker(void)
{
	int8_t res;
	
	res = uStIntNoMatch;

	if (currentEvent->evType == ev53sSwitchedHigh)  {	
		wishCounter ++;
		if ( wishCounter >= 3 )
		{
			BEGIN_EVENT_HANDLER(PWishWashStateChart, eStateIdle);
				// No event action.
			END_EVENT_HANDLER(PWishWashStateChart);
			res =  uStIntHandlingDone;
		}
	}	
	
	return res;
}

void entryIonState(void)
{
	startADCPolling();
	switchRelay15();
}

void exitIonState(void)
{
//	printf("exit I\n");
	stopADCPolling();
}

uStInt evIonChecker(void)
{
//	printf("check for event in State evStateIdle\n");
	uStInt res = uStIntNoMatch;

	if ((currentEvent->evType == evTPressed) || (currentEvent->evType == evISwitchedOff))
	{	
		BEGIN_EVENT_HANDLER(PWishWashStateChart, eStateIdle);
		// No event action.

		END_EVENT_HANDLER(PWishWashStateChart);
		res =  uStIntHandlingDone;		
	}

	if (currentEvent->evType == ev53sSwitchedHigh) 
	{	
		switchRelay53s();
		res =  uStIntHandlingDone;		
	}
	if (currentEvent->evType == ev53sSwitchedLow) 
	{	
		startIntervalTimer();
		res =  uStIntHandlingDone;		
	}
	if (currentEvent->evType == evTimerExpired)
	{
		stopIntervalTimer();
		switchRelay15();
		res =  uStIntHandlingDone;
	}
	return (res);
}



#ifndef  sdccNULL 

#define tfNull 0

#else

t_fvoid  tfNull;

#endif 

// attention: sequence must be the same as above enum eStates

xStateType xaStates[eNumberOfStates] = {
 	{eStateWishWash,    // name
 	-1,									//parent
 	eStateIdle,    // default substate
 	0,    // keep history
 	evWishWashChecker,    // event checking fu
	tfNull,       // def state entry function
 	tfNull,     //    entering state
 	tfNull},     // exiting state

 	{eStateIdle,
 	eStateWishWash,
 	-1,
 	0,									
 	evIdleChecker,
 	tfNull,
 	entryIdleState,
 	exitIdleState},


 	{eStateTPressed,
 	eStateWishWash,
 	-1,
 	0,									
 	evTPressedChecker,
 	tfNull,
 	entryTPressedState,
 	exitTPressedState},

 	{eStateTReleased,
 	eStateWishWash,
 	-1,
 	0,									
 	evTReleasedChecker,
 	tfNull,
 	entryTReleasedState,
 	exitTReleasedState} 	 
};


void startStateCharts()
{

#ifdef  sdccNULL 

	tfNull = (t_fvoid ) NULL;

#endif 

 	PWishWashStateChart = & SWishWashStateChart; 
	createTStatechart (& SWishWashStateChart, xaStates, eNumberOfStates, eStartState);
	
}


void stopStateCharts()
{
	destructTStatechart(&SWishWashStateChart);
}


bool processEvent(TStatechart* ts,CWishWashEvent* ev)
{
	currentEvent = ev;
	return ProcessEvent(ts);
}





/*
void entry...State(void)
{
//	printf("entry I\n");
}

void exit...State(void)
{
//	printf("exit I\n");
}

uStInt ev...Checker(void)
{
//	printf("check for event in State evStateIdle\n");

//	if (currentEvent->evType == eValueAssignement) 
//	{	if (HumidifyingLowerLimit > currentEvent->humidity)
//		{
//			BEGIN_EVENT_HANDLER(PJoesTriacStateChart, eStateHumidifying);
//				// No event action.
//			END_EVENT_HANDLER(PJoesTriacStateChart);
//			return (u32HandlingDone);
//		}
//	}
	return (u32NoMatch);
}

*/

/*

enum eStates
{
	eStateJoesTriac,
	eStartState = eStateJoesTriac,
	eStateAskForCalibration,
	eStateCalibrating,
	eNumberOfStates
};


uStInt evJoesTriacChecker(void)
{
	return (uStIntNoMatch);
}

uStInt evAskForCalibrationChecker(void)
{
	return (uStIntNoMatch);
}

uStInt evCalibratingChecker(void)
{
	return (uStIntNoMatch);
}


#ifndef  sdccNULL 

#define tfNull 0

#else

t_fvoid  tfNull;

#endif 

xStateType xaStates[eNumberOfStates] = {
 	{eStateJoesTriac,    // name
 	-1,									//parent
 	eStateAskForCalibration,    // default substate
 	0,    // keep history
 	evJoesTriacChecker,    // event checking fu
	tfNull,       // def state entry function
 	tfNull,     //    entering state
 	tfNull},     // exiting state

 	{eStateAskForCalibration,
 	eStateJoesTriac,
 	-1,
 	0,									
 	evAskForCalibrationChecker,
 	tfNull,
 	tfNull,
 	tfNull},

 	{eStateCalibrating,
 	eStateJoesTriac,
 	-1,
 	0,
 	evCalibratingChecker,
 	tfNull,
 	tfNull,
 	tfNull},
	 

};
*/

