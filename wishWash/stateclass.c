
#include <avr/io.h>
#include <stdio.h>
//#include <iostream.h>
//#include <assert.h>
#include <string.h>

#include "TStatechart.h"
#include "StateClass.h"
#include "hawaif.h"

//#include "TriacDefines.h"


extern const uStInt uStIntHandlingDone;
extern const uStInt uStIntNoMatch;


CWishWashEvent* currentEvent;

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

}



void exitTPressedState(void)
{
}

uStInt evTPressedChecker(void)
{
	uStInt res = uStIntNoMatch;
//	printf("check for event in State evStateIdle\n");

/*
	if ((currentEvent->evType == evAstPressed) || (currentEvent->evType == evNumPressed)){
		if (currentEvent->evType == evNumPressed)  {
			if (calibVarInd == 0) {
				calibLowADC = currentVarVal;
				saveCalibLowADC();
			}
			if (calibVarInd == 1) {
				calibHighADC = currentVarVal;
				saveCalibHighADC();
			} 
		}

		if (calibVarInd == 1)   {	
			BEGIN_EVENT_HANDLER(PJoesTriacStateChart, eStateTriacIdle);
				// No event action.
			END_EVENT_HANDLER(PJoesTriacStateChart);
			res =  uStIntHandlingDone;
		}
		if (calibVarInd == 0) {
			currentVarVal = calibHighADC;
			currentTitle = "calibHighADC";
			calibVarInd = 1;
			displayCurrentVar();
		}
		res =  uStIntHandlingDone;
	}

	if (currentEvent->evType == evCharEntered) {
		switch (currentEvent->evData.keyCode) {
			case kp1 : 
				currentVarVal++;
				break;
			case kp2 :
				currentVarVal += 10;
				break ;	
			case kp3 :
				currentVarVal += 100;
				break ;		
			case kp7 : 
				currentVarVal--;
				break;
			case kp8 :
				currentVarVal -= 10;
				break ;	
			case kp9 :
				currentVarVal -= 100;
				break ;									
		}
		if (currentVarVal < 0) currentVarVal = 0;
		if (currentVarVal > 1023) currentVarVal = 1023;
		currentVarChanged();
		res =  uStIntHandlingDone;
	}
	*/
	return (res); 
}

void entryTReleasedState(void)
{

}

void exitTReleasedState(void)
{
//	printf("exit calib\n");
//	stopDurationTimer();
}

uStInt evTReleasedChecker(void)
{
	int8_t res;
	
	res = uStIntNoMatch;
/*
//	printf("inside evCalibratingChecker\n");
	if (currentEvent->evType == evStopPressed)  {	
			BEGIN_EVENT_HANDLER(PJoesTriacStateChart, eStateTriacIdle);
				// No event action.
			END_EVENT_HANDLER(PJoesTriacStateChart);
			res =  uStIntHandlingDone;
	}	
	*/
	return res;
}

void entryIonState(void)
{

}

void exitIonState(void)
{
//	printf("exit I\n");
}

uStInt evIonChecker(void)
{
//	printf("check for event in State evStateIdle\n");
	uStInt res = uStIntNoMatch;
/*
	if (currentEvent->evType == evNumPressed) 
	{	
		BEGIN_EVENT_HANDLER(PJoesTriacStateChart, eStateCalibrateZeroSignal);
		// No event action.
		
		storeAmpsInputPin(avg);

		END_EVENT_HANDLER(PJoesTriacStateChart);
		res =  uStIntHandlingDone;		
	}

	if (currentEvent->evType == evAstPressed) 
	{	
		BEGIN_EVENT_HANDLER(PJoesTriacStateChart, eStateCalibrateZeroSignal);
		// No event action.

		storeAmpsInputPin(rms);

		END_EVENT_HANDLER(PJoesTriacStateChart);
		res =  uStIntHandlingDone;		
	}
	if (currentEvent->evType == evSecondsTick) 
	{	
//		debugEvent1Triggered = 1;	
		res =  uStIntHandlingDone;		
	}
	*/
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


bool processEvent(TStatechart* t,CWishWashEvent* ev)
{
	currentEvent = ev;
	return ProcessEvent(t);
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

