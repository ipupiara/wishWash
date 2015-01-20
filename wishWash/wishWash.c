/*
 * wishWash.c
 *
 * Created: 1/2/2015 1:26:04 PM
 *  Author: ixchel
 */ 


#include <avr/io.h>
#include <stddef.h>
#include "StateClass.h"
#include "hawaif.h"

CWishWashEvent currentEvent;

int main(void)
{
	CWishWashEvent* ev;
	startStateCharts();
	init();
	
    while(1)
    {
		enterIdleSleepMode();
		ev=getNextEvent(&currentEvent);
		if (ev != NULL) {
			processEvent(PWishWashStateChart,ev);
		}

    }
}