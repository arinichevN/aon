#include "channel.h"
#include "puart.h"

//edit this
#define SERIAL_RATE 4800
#define SERIAL_CONFIG SERIAL_8N1
#define SERIAL_TIMEOUT_MS 300
#define CHANNEL_COUNT 8

//edit this
//for each channel
#define ID1 1
#define OUT_PIN1 13
#define ID2 2
#define OUT_PIN2 4

#define FOREACH_CHANNEL for (int i=0; i < CHANNEL_COUNT; i++) {Channel *channel = &channels[i];
  
Channel channels[CHANNEL_COUNT];
PUART puart;

void setup()
{
  Serial.begin(SERIAL_RATE, SERIAL_CONFIG);
  Serial.setTimeout(SERIAL_TIMEOUT_MS);
  puart_init(&puart);
  
  //edit this
  //for each channel
  channel_init(&channels[0], ID1, OUT_PIN1);
  channel_init(&channels[1], ID2, OUT_PIN2);
  
	FOREACH_CHANNEL
		pmem_getChannel(channel, i);
	}
  
}


void loop() {
	FOREACH_CHANNEL
	  channel_control(channel);
	  puart_server(&puart, channels, CHANNEL_COUNT );
	}
}

#undef FOREACH_CHANNEL
