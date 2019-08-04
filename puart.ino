#include "puart.h"

void puart_init(PUART *item){
	Serial.setTimeout(300);
	ton_setInterval(&item->tmr, 10000);
	ton_reset(&item->tmr);
    item->bi = 0;
    item->selected = 0;
    item->state = READ_COMMAND;
}


int puart_readInt(int *v) {
  char str[PUART_CMD_INT_STR_LENGTH];
  memset(str, 0, sizeof str);
  int i = 0;
  unsigned long t1 = millis();
  while (1) {
    PUART_WAIT_DATA
    if (i >= (PUART_CMD_INT_STR_LENGTH - 1)) {
      return 0;
    }
    int c = Serial.read();
    if (isDigit(c)) {
      str[i] = (char)c;
      i++;
    } else if (c == PUART_DELIMITER_END) {
      *v = atoi(str);
      return 1;
    }
  }
  return 0;
}

int puart_readDouble(double *v) {
  Serial.println("read double");
  char str[PUART_CMD_DOUBLE_STR_LENGTH];
  memset(str, 0, sizeof str);
  int i = 0;
  unsigned long t1 = millis();
  while (1) {
    PUART_WAIT_DATA
    if (i >= (PUART_CMD_DOUBLE_STR_LENGTH - 1)) {
      return 0;
    }
    int c = Serial.read();
    if (isDigit(c)) {
      str[i] = (char)c;
      i++;
    } else if (c == '.') {
      str[i] = (char)c;
      i++;
    } else if (c == PUART_DELIMITER_END) {
      *v = atof(str);
      return 1;
    }
  }
  return 0;
}

int puart_readStr(char *v, int len) {
  char buf[len];
  memset(buf, 0, sizeof (*buf) * len);
  int i = 0;
  unsigned long t1 = millis();
  while (1) {
    PUART_WAIT_DATA
    if (i >= len) {
      return 0;
    }
    int c = Serial.read();
    if (c == PUART_DELIMITER_END) {
      memset(v, 0, sizeof (*v) * len);
      strcpy(v, buf);
      return 1;
    } else {
      buf[i] = (char)c;
      i++;
    }
  }

  return 0;
}

int puart_readPack(PUART *item){
	if(Serial.available() > 0){
		int c = Serial.read();
        if (c == '\n'){
            return 0;
        }
		if (c == PUART_DELIMITER_END){
            item->buf[item->bi] = '\0';
			return 1;
		}else{
            if(item->bi < PUART_BUF_LENGTH){
                item->buf[item->bi] = (char)c;
                item->bi++;
            }else{
                item->bi = 0;
            }
		}
	}
	return 0;
}

int puart_parseInt(PUART *item, int *v) {
  for (int i = 0; i < item->bi; i++) {
    if (!isDigit(item->buf[i])) {
      return 0;
    }
  }
  *v = atoi(item->buf);
  return 1;
}

int puart_parseDouble(PUART *item, double *v) {
  for (int i = 0; i < item->bi; i++) {
    if (!(isDigit(item->buf[i]) || item->buf[i] == '.')) {
      return 0;
    }
  }
  double _v = atof(item->buf);
  if(isinf(_v)) return 0;
  if(isnan(_v)) return 0;
  *v = _v;
  return 1;
}
