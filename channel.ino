#include "channel.h"

void channel_setDutyCycle(Channel *item, int v){
if (v < 0) {
  item->duty_cycle = 0;
    return;
  }
  unsigned long vu = (unsigned long) v;
 if(vu > item->pwm.resolution){
    item->duty_cycle = item->pwm.resolution;
  }else{
    item->duty_cycle = vu;
  }
}

void channel_init(Channel *item, int id, int pin){
	item->id = id;
	item->selected = 0;
 item->duty_cycle = 0.0;
	pwm_init(&item->pwm, pin);
	secure_init(&item->secure);
	
}

void channel_control(Channel *item){
	secure_control(&item->secure, &item->duty_cycle);
	pwm_control (&item->pwm, &item->duty_cycle);
}
