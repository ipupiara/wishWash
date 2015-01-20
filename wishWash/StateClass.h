
#if !defined(CCtateClassHeader)
#define CCtateClassHeader

#include "TStatechart.h"

TStatechart SWishWashStateChart;
TStatechart* PWishWashStateChart;


enum eEventTypes
{
	evCharEntered,
	evF1Pressed,
	evF2Pressed,
	evAstPressed,
	evNumPressed,
	evTimeOutDurationTimer,
	evSecondsTick,
	evStartPressed,
	evStopPressed,
	evZeroSignalOK,
	evAdcTick,
	evTWIDataReceived,
	evFatalError
};


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




void startStateCharts();


void stopStateCharts();


bool processEvent(TStatechart* t,CWishWashEvent* ev);




#endif


