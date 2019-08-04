#ifndef PUART_H
#define PUART_H

#include "ton.h"
#include "pwm.h"
#include "channel.h"

//crc is hardware job
//multiple slaves can listen - that is why we can send one command for several slaves
//but only one slave can ask - that is why we read from slave one after another

#define PUART_BUF_LENGTH 16

#define PUART_DELIMITER_END ';'
#define PUART_DELIMITER_BLOCK '_'
#define PUART_READ_BUF_LEN 32
#define PUART_SELECT_PACK_LEN 6
#define PUART_CMD_INT_STR_LENGTH 12
#define PUART_CMD_DOUBLE_STR_LENGTH 16

#define PUART_CMD_IS(v2) (strcmp(item->cmd,v2)==0)

#define PUART_MIN_RAW_PACK_LEN 5
#define PUART_MIN_PACK_LEN 4
#define PUART_TIMEOUT_MS 10000

#define PUART_PRINT_OK Serial.print("OK");Serial.write(PUART_DELIMITER_END);
#define PUART_WAIT_DATA if(Serial.available() <= 0){unsigned long now = millis();  if(now - t1 > PUART_TIMEOUT_MS){return 0; } continue; }
#define PUART_RESET_BUF memset(item->buf, 0, sizeof (*item->buf) * PUART_BUF_LENGTH); item->bi = 0;
#define PUART_SET_CMD strncpy(item->cmd, item->buf, sizeof (*item->cmd) * PUART_BUF_LENGTH);

#define PUART_CMD_SELECT "select"
#define PUART_CMD_END "end"
#define PUART_CMD_SELECTED "selected"

#define SWDB Serial.write(PUART_DELIMITER_BLOCK)
#define SWDE Serial.write(PUART_DELIMITER_END)
#define SPR(v) Serial.print(v)
#define SF Serial.flush()

enum PUARTstateE {
	READ_COMMAND,
	READ_INT,
	READ_DOUBLE
};

struct PUART {
  char buf[PUART_BUF_LENGTH];
  char cmd[PUART_BUF_LENGTH];
  int bi;
  Ton tmr;
  int state;
  int selected;
};

//extern void puart_server(PUART *item, Channel *channels, int len);
	
#endif 
