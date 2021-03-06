
#if !defined(CCtateClassHeader)
#define CCtateClassHeader

#include "TStatechart.h"


enum eEventTypes
{
	evNone = 0,
	evTangoPressed,
	evTangoReleased,
	evIndiaSwitchedOn,
	evIndiaSwitchedOff,
	evMotorOutput53sSwitchedLow,
	evMotorOutput53sSwitchedHigh,
	evTimerExpired
};

// This defines and names the states the class has.
// attention: sequence must be the same as in xaStates (below) !!!
enum eStates
{
	eStateWishWash,
	eStartState = eStateWishWash,
	eStateIdle,
	eStateTangoPressed,
	eStateTangoReleased,
	eStateIndiaOn,
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


