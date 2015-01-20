/*
 * GccApplication1.c
 *
 * Created: 1/19/2015 2:01:44 PM
 *  Author: ixchel
 */ 


#include <avr/io.h>
#include "StateClass.h"

uint8_t  fatalErrorOccurred;

int main(void)
{
	CWishWashEvent ev;
	startStateCharts();	
    while(1)
    {
		//		checkDebugBuffer();

		if (fatalErrorOccurred) {     // do this with highest priority (at the beginning)
			//			fatalErrorOccurred = 0;	  // once occurred state stays until restart/reset
			ev.evType = evFatalError;
			processTriacEvent(&SWishWashStateChart,&ev);
		}
			
    }
}