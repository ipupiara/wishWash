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

CWishWashEvent curEvent;

int main(void)
{
	CWishWashEvent* ev;
//	startStateCharts();
	initHW();
	
    while(1)
    {
		ev=getNextEvent(&curEvent);
		if (ev != NULL) {
//			processEvent(PWishWashStateChart,ev);
		}

    }
}