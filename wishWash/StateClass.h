
#if !defined(CCtateClassHeader)
#define CCtateClassHeader

#include "TStatechart.h"


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
	evPotiValueChanged
};

// This defines and names the states the class has.
// attention: sequence must be the same as in xaStates (below) !!!
enum eStates
{
	eStateWishWash,
	eStartState = eStateWishWash,
	eStateIdle,
	eStateTPressed,
	eStateTReleased,
	eStateIon,
	eNumberOfStates
};

TStatechart SWishWashStateChart;
TStatechart* PWishWashStateChart;

typedef struct  {
	int evType;
//	int evId;
/*	union {
		int8_t keyCode;
		struct {			// currently not in use
			float   voltage;  
			int8_t  potiPos;
			int8_t  jobType;
		} zeroAdjustingState;
	}  evData;
	*/
} CWishWashEvent ;


CWishWashEvent* getNextEvent(CWishWashEvent* pev);

void startStateCharts();

void stopStateCharts();

bool processEvent(TStatechart* t,CWishWashEvent* ev);

#endif


