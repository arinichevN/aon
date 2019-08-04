#ifndef PWM_H
#define PWM_H

#include "pmem.h"

#define PWM_RESOLUTION 1000
#define PWM_PERIOD 5000

enum PWMstateE {
  PWM_BUSY,
  PWM_IDLE
};

struct PWM{
	int pin;
    PWMstateE state;
    unsigned long delay_busy;
    unsigned long delay_idle;
    unsigned long toggle_time;//time when we must change state from busy to idle or reverse
    double single_time;//(duty_cycle_max - duty_cycle_min)/resolution
    
    unsigned long resolution;//0 is 0% of power (duty_cycle will be set to PWM.duty_cycle_min) PWM.resolution is 100% of power (duty_cycle will be set to PWM.duty_cycle_max)
    unsigned long period;
    unsigned long duty_cycle_min; //0% of power
    unsigned long duty_cycle_max;//100% of power
    unsigned long  duty_cycle;
};

extern int pwm_control (PWM *item, double duty_cycle);

extern void pwm_init (PWM *item, int pin);

extern void pwm_setResolution (PWM *item, int v) ;

extern int pwm_setDutyCycle (PWM *item, int v) ;

extern void pwm_setPeriod (PWM *item, int v) ;

extern void pwm_setDutyCycleMin (PWM *item, int v) ;

extern void pwm_setDutyCycleMax (PWM *item, int v);

#endif 
