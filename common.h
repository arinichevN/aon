#ifndef COMMON_H
#define COMMON_H

enum StateE {
	INIT,
	OFF,
	FAILURE,
  DISABLE,
	
	DONE,
	DO,
	RUN,
	WAIT

	
};

typedef enum {
	BLOCK_DISABLE=0,
	BLOCK_ENABLE=1
} CmdState;

struct FTS {
	double value;
	unsigned long tm;
	int state;
};

#endif 
