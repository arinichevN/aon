#include "pwm.h"


void pwm_calc_single_time (PWM *item) {
   //next lines shortly: item->single_time = ( item->duty_cycle_max - item->duty_cycle_min ) / item->resolution;
   double dif = (double)item->duty_cycle_max - (double)item->duty_cycle_min;
   item->single_time = dif / (double) item->resolution;
}

void pwm_calc_delays(PWM *item){
  unsigned long dc = (unsigned long) (item->single_time * (double)item->duty_cycle);
	item->delay_idle = item->period - dc - item->duty_cycle_min;
	item->delay_busy = dc + item->duty_cycle_min;
}

int pwm_setDutyCycle (PWM *item, int v) {
  if (v < 0) {
    return 0;
  }
  unsigned long vu = (unsigned long) v;
	if(vu == item->duty_cycle){
		return 0;
	}
  if (vu > item->resolution) {
   item->duty_cycle=item->resolution;
  }else{
   item->duty_cycle = vu;
  }
	pwm_calc_delays(item);
	//item->toggle_time = millis();
 return 1;
}

void pwm_setResolution (PWM *item, int v) {
	if (v < 0) {
		return;
	}
 unsigned long vu = (unsigned long) v;
 if(vu == item->resolution){
   return;
  }
	item->resolution = (unsigned long)vu;
	pwm_calc_single_time(item);
}

void pwm_setPeriod (PWM *item, int v) {
  if (v < 0) {
    return;
  }
   unsigned long vu = (unsigned long) v;
	if(vu == item->period){
		return;
	}
	if(vu < item->duty_cycle_max){
		return;
	}
	item->period = vu;
	pwm_calc_single_time (item);
	pwm_calc_delays(item);
//	item->toggle_time = millis();
}

void pwm_setDutyCycleMin (PWM *item, int v) {
  if (v < 0) {
    return;
  }
  unsigned long vu = (unsigned long) v;
	if(vu == item->duty_cycle_min){
		return;
	}
	if(vu >= item->duty_cycle_max){
		return;
	}
	item->duty_cycle_min = vu;
	pwm_calc_single_time (item);
	pwm_calc_delays(item);
	//item->toggle_time = millis();
}

void pwm_setDutyCycleMax (PWM *item, int v) {
  if (v < 0) {
    return;
  }
  unsigned long vu = (unsigned long) v;
	if(vu == item->duty_cycle_max){
		return;
	}
 if(vu <= item->duty_cycle_min){
   return;
  }
	if(vu > item->period){
		return;
	}
	item->duty_cycle_max = vu;
	pwm_calc_single_time (item);
	pwm_calc_delays(item);
	//item->toggle_time = millis();
}

//period, resolution, duty_cycle_min, duty_cycle_max are expected to has been set and checked
void pwm_init (PWM *item, int pin) {
   unsigned long  now = millis();
   item->pin = pin;
   item->period = PWM_PERIOD;
   item->duty_cycle_min = 0;
   item->duty_cycle_max = item->period;
   item->resolution = PWM_RESOLUTION;
   item->duty_cycle = 0;
   pinMode(item->pin, OUTPUT);
   digitalWrite(item->pin, LOW);
   item->toggle_time = now;
   pwm_calc_single_time (item);
   pwm_calc_delays(item);
   item->state = PWM_IDLE;
}

int pwm_control (PWM *item, unsigned long *duty_cycle) {
	if(!pwm_setDutyCycle (item, *duty_cycle)){
     *duty_cycle = item->duty_cycle;
	}
	unsigned long now = millis();
	switch (item->state) {
	  case PWM_BUSY: {
			if (now > item->toggle_time) {
			   item->toggle_time = now + item->delay_idle;
			   if(item->delay_idle > 0){
				   digitalWrite(item->pin, LOW);
			   }
			   item->state = PWM_IDLE;
			}
			break;
		 }
	  case PWM_IDLE: {
			if (now > item->toggle_time) {
			   item->toggle_time = now + item->delay_busy;
			   if(item->delay_busy > 0){
				   digitalWrite(item->pin, HIGH);
			   }
			   item->state = PWM_BUSY;
			}
			break;
		 }
	  default:
		 item->state = PWM_IDLE;
		 break;
	}
	return item->state;
}
