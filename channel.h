#ifndef CHANNEL_H
#define CHANNEL_H

#include "pwm.h"
#include "secure.h"

struct Channel{
	PWM pwm;
	Secure secure;
  unsigned long duty_cycle;
    int selected;
    int id;
};


#endif 
