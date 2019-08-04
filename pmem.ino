#include "pmem.h"

#define PMEM_CHANNEL_ADDR ind * sizeof(PmemChannel)

void pmem_getChannel(Channel *item, int ind) {
	PmemChannel buf;
	EEPROM.get(PMEM_CHANNEL_ADDR, buf);
	if(buf.valid == PMEM_VALID){
		item->id = buf.id;
		item->pwm.resolution = buf.resolution;
		item->pwm.period = buf.period;
	    item->pwm.duty_cycle_min = buf.duty_cycle_min;
	    item->pwm.duty_cycle_max = buf.duty_cycle_max;
      item->secure.duty_cycle = buf.secure_duty_cycle;
      item->secure.timeout = buf.secure_timeout;
      item->secure.enable = buf.secure_enable;
	}
}

void pmem_saveChannel(Channel *item, int ind){
	PmemChannel buf;
	buf.id = item->id;
	buf.resolution = item->pwm.resolution;
	buf.period = item->pwm.period;
    buf.duty_cycle_min = item->pwm.duty_cycle_min;
    buf.duty_cycle_max = item->pwm.duty_cycle_max;
    buf.secure_duty_cycle = item->secure.duty_cycle;
    buf.secure_timeout = item->secure.timeout;
    buf.secure_enable = item->secure.enable;
    buf.valid = PMEM_VALID;
	EEPROM.put(PMEM_CHANNEL_ADDR, buf);
}

int pmem_check(){
	unsigned int total_bytes = CHANNEL_COUNT * sizeof(PmemChannel);
	if(total_bytes < EEPROM.length()){
		return 1;
	}
	return 0;
}
