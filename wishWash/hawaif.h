/*
 * hawaif.h
 *
 * Created: 1/20/2015 10:31:44 AM
 *  Author: ixchel
 */ 


#ifndef HAWAIF_H_
#define HAWAIF_H_

int8_t  timerReachedEvent;
int8_t  iLineOnEvent;
int8_t   iLineOffEvent;
int8_t   tPressedEvent;
int8_t	 tReleasedEvent;
int8_t   ev53sSwitchedHighEvent;
int8_t   ev53sSwitchedLowEvent ;
int8_t   counterReachedEvent;


void switchRelay15();

void switchRelay53s();

void setWashTimer();

void setWishTimer();

void startADCPolling();

void stopADDCPolling();

void startTickTimer();

int isILineOn();
int isTLineOn();

void init();




#endif /* HAWAIF_H_ */