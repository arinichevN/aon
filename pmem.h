#ifndef PMEM_H
#define PMEM_H

#include <EEPROM.h>
#include "channel.h"

#define PMEM_VALID 12345

struct PmemChannel{
	int valid;
	int id;
	double resolution;
	unsigned long period;
  unsigned long duty_cycle_min;
  unsigned long duty_cycle_max;
  double secure_duty_cycle;
  unsigned long secure_timeout;
  int secure_enable;
};



//extern void pmem_getChannel(Channel *item, int ind) ;

//extern void pmem_saveChannel(Channel *item, int ind);

//extern int pmem_check();

#endif 
