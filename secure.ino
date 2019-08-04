#include "secure.h"

void secure_init (Secure *item) {
	item->duty_cycle = 0.0;
 item->timeout = 0;
 item->enable = 0;
	ton_setInterval(&item->tmr, item->timeout);
	item->state = INIT;
}

void secure_setTimeout (Secure *item, int v) {
	if (v < 0) {
		return;
	}
 item->timeout = (unsigned long) v;
	ton_setInterval(&item->tmr, item->timeout);
	ton_reset(&item->tmr);
}

void secure_setDutyCycle(Secure *item, int v){
  if (v < 0) {
    return;
  }
  unsigned long vu = (unsigned long) v;
  item->duty_cycle = vu;
}

void secure_setState(Secure *item, int v){
  if(!(v == 1 || v==0)) return;
  item->enable = v;
  if(item->enable){
    if(item->state == OFF){
    item->state = INIT;
    }
  }else{
    item->state = OFF;
  }
}

void secure_touch (Secure *item) {
	item->state = INIT;
}

void secure_control (Secure *item, unsigned long *v) {
	switch(item->state){
		case WAIT:
			if(ton(&item->tmr)){
				item->state = DO;
				*v = item->duty_cycle;
			}
			break;
    case OFF:
    break;
		case DO:
			*v = item->duty_cycle;
			break;
		case INIT:
    if(item->enable){
			ton_reset(&item->tmr);
			item->state = WAIT;
    }else{
      item->state = OFF;
    }
			break;
	}
}
