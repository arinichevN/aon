#ifndef SECURE_H
#define SECURE_H

#include "ton.h"
#include "pmem.h"
#include "common.h"

struct Secure{
	unsigned long timeout;
    unsigned long duty_cycle;
    int enable;
    
    Ton tmr;
    int state;
};

extern void secure_control (Secure *item, unsigned long *v);

extern void secure_init (Secure *item);

extern void secure_setTimeout (Secure *item, unsigned long v) ;
extern void secure_setDutyCycle(Secure *item, double v);
extern void secure_setState(Secure *item, int v);

extern void secure_touch (Secure *item) ;

#endif 
