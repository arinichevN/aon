#include "puart.h"

#define CMD_SET_DUTY_CYCLE "scpwmdc"
#define CMD_SET_RESOLUTION "scpwmr"
#define CMD_SET_PERIOD "scpwmp"
#define CMD_SET_DUTY_CYCLE_MIN "scpwmdcmin"
#define CMD_SET_DUTY_CYCLE_MAX "scpwmdcmax"
#define CMD_SET_SECURE_STATE "scpwmss"
#define CMD_SET_SECURE_TIMEOUT "scpwmstm"
#define CMD_SET_SECURE_DUTY_CYCLE "scpwmsdc"

#define CMD_GET_FTS "gfts"
#define CMD_GET_DUTY_CYCLE "gcpwmdc"
#define CMD_GET_RESOLUTION "gcpwmr"
#define CMD_GET_PERIOD "gcpwmp"
#define CMD_GET_DUTY_CYCLE_MIN "gcpwmdcmin"
#define CMD_GET_DUTY_CYCLE_MAX "gcpwmdcmax"
#define CMD_GET_SECURE_STATE "gcpwmss"
#define CMD_GET_SECURE_TIMEOUT "gcpwmstm"
#define CMD_GET_SECURE_DUTY_CYCLE "gcpwmsdc"

#define CHI i
#define FOREACH_CHANNEL for(int CHI=0;CHI<len;CHI++){Channel *channel = &channels[i];
#define FOREACH_SCH FOREACH_CHANNEL if(channel->selected){
#define END_FOREACH_SCH }}
#define SAVE_CHANNEL pmem_saveChannel(channel, CHI)

void puart_server(PUART *item, Channel *channels, int len) {
  if (!puart_readPack(item)) {
    return;
  }
  //Serial.print("BUF: "); Serial.println(item->buf);
  switch (item->state) {
    case READ_COMMAND:
		PUART_SET_CMD
		ton_reset(&item->tmr);
		if (PUART_CMD_IS(PUART_CMD_SELECT) ) {//Serial.println("PUART_CMD_SELECT");
			item->state = READ_INT;
		} else if (PUART_CMD_IS(PUART_CMD_END) ) {
			item->selected = 0;
			FOREACH_CHANNEL
				channel->selected = 0;
			}
		} else if (item->selected) {
			if (PUART_CMD_IS(CMD_SET_DUTY_CYCLE) || PUART_CMD_IS(CMD_SET_PERIOD) || PUART_CMD_IS(CMD_SET_DUTY_CYCLE_MIN) || PUART_CMD_IS(CMD_SET_DUTY_CYCLE_MAX) || PUART_CMD_IS(CMD_SET_SECURE_STATE) || PUART_CMD_IS(CMD_SET_SECURE_TIMEOUT) || PUART_CMD_IS(CMD_SET_RESOLUTION) || PUART_CMD_IS(CMD_SET_SECURE_DUTY_CYCLE)) {
			    item->state = READ_INT;
      }else if (0){
        item->state = READ_DOUBLE;
		} else if (PUART_CMD_IS(PUART_CMD_SELECTED)) {
			    FOREACH_SCH
				    SPR(channel->id); SWDE; SF;
				END_FOREACH_SCH
    }else if (PUART_CMD_IS(CMD_GET_DUTY_CYCLE)) {
        FOREACH_SCH
            SPR(channel->id); SWDB; SPR(channel->pwm.duty_cycle); SWDE; SF;
        END_FOREACH_SCH
		}else if (PUART_CMD_IS(CMD_GET_PERIOD)) {
				FOREACH_SCH
				    SPR(channel->id); SWDB; SPR(channel->pwm.period); SWDE; SF;
				END_FOREACH_SCH
	    }else if (PUART_CMD_IS(CMD_GET_RESOLUTION)) {
	      FOREACH_SCH
	          SPR(channel->id); SWDB; SPR(channel->pwm.resolution); SWDE; SF;
	      END_FOREACH_SCH
			}else if (PUART_CMD_IS(CMD_GET_DUTY_CYCLE_MIN)) {
				FOREACH_SCH
				    SPR(channel->id); SWDB; SPR(channel->pwm.duty_cycle_min); SWDE; SF;
				END_FOREACH_SCH
			}else if (PUART_CMD_IS(CMD_GET_DUTY_CYCLE_MAX)) {
				FOREACH_SCH
				    SPR(channel->id); SWDB; SPR(channel->pwm.duty_cycle_max); SWDE; SF;
				END_FOREACH_SCH
      }else if (PUART_CMD_IS(CMD_GET_SECURE_STATE)) {
        FOREACH_SCH
            SPR(channel->id); SWDB; SPR(channel->secure.enable); SWDE; SF;
        END_FOREACH_SCH
      }else if (PUART_CMD_IS(CMD_GET_SECURE_TIMEOUT)) {
        FOREACH_SCH
            SPR(channel->id); SWDB; SPR(channel->secure.timeout); SWDE; SF;
        END_FOREACH_SCH
      }else if (PUART_CMD_IS(CMD_GET_SECURE_DUTY_CYCLE)) {
        FOREACH_SCH
            SPR(channel->id); SWDB; SPR(channel->secure.duty_cycle); SWDE; SF;
        END_FOREACH_SCH
		} else if (PUART_CMD_IS(CMD_GET_FTS)) { //Serial.println("CMD_GET_FTS");
					FOREACH_SCH
					    //SPR(channel->id); SWDB; SPR(channel->pwm.duty_cycle / channel->pwm.resolution * 100.0); SWDB; SPR(1); SWDB; SPR(millis()); SWDE; SF;
              SPR(channel->id); SWDB; SPR(channel->pwm.duty_cycle); SWDB; SPR(1); SWDB; SPR(millis()); SWDE; SF;
					    //SPR(channel->id);SWDB;SPR(33.18);SWDB;SPR(1);SWDB;SPR(millis());SWDE;SF;
					END_FOREACH_SCH
			} else {
			  //Serial.println("unknown command");
			}
		}else{
			//Serial.println("no selected channels");
		}
		PUART_RESET_BUF
		break;
	case READ_INT://Serial.println("READ_INT");Serial.print("CMD: ");Serial.println(item->cmd);
		{int v = -1;
		if (ton(&item->tmr)) {
		  PUART_RESET_BUF
		  item->state = READ_COMMAND;//Serial.println("READ_INT timeout");
		  return;
		}
		if (!puart_parseInt(item, &v)) { //Serial.println("READ_INT failed");
		  PUART_RESET_BUF
		  return;
		}
		//Serial.print("INT: "); Serial.println(v);
		if (PUART_CMD_IS(PUART_CMD_SELECT)) {
			FOREACH_CHANNEL
			  if (channel->id == v) {
			    channel->selected = 1;
			    item->selected = 1;
			    //Serial.print("channel selected ");	Serial.println(v);
			    break;
			  }
			}
    }else if (PUART_CMD_IS(CMD_SET_DUTY_CYCLE)) {
      FOREACH_SCH
        channel_setDutyCycle(channel, v);
        secure_touch(&channel->secure);
      END_FOREACH_SCH
		}else if (PUART_CMD_IS(CMD_SET_PERIOD)) {
			FOREACH_SCH
				pwm_setPeriod (&channel->pwm, v);SAVE_CHANNEL;
			END_FOREACH_SCH
		}else if (PUART_CMD_IS(CMD_SET_DUTY_CYCLE_MIN)) {
			FOREACH_SCH
				pwm_setDutyCycleMin (&channel->pwm, v);SAVE_CHANNEL;
			END_FOREACH_SCH
		}else if (PUART_CMD_IS(CMD_SET_DUTY_CYCLE_MAX)) {
			FOREACH_SCH
				pwm_setDutyCycleMax (&channel->pwm, v);SAVE_CHANNEL;
			END_FOREACH_SCH
    }else if (PUART_CMD_IS(CMD_SET_SECURE_STATE)) {
      FOREACH_SCH
        secure_setState (&channel->secure, v);SAVE_CHANNEL;
      END_FOREACH_SCH
    }else if (PUART_CMD_IS(CMD_SET_SECURE_TIMEOUT)) {
      FOREACH_SCH
        secure_setTimeout (&channel->secure, v);SAVE_CHANNEL;
      END_FOREACH_SCH
    } else if (PUART_CMD_IS(CMD_SET_RESOLUTION)) {
      FOREACH_SCH
        pwm_setResolution (&channel->pwm, v);SAVE_CHANNEL;
      END_FOREACH_SCH
    } else if (PUART_CMD_IS(CMD_SET_SECURE_DUTY_CYCLE)) {
      FOREACH_SCH
        secure_setDutyCycle (&channel->secure, v);SAVE_CHANNEL;
      END_FOREACH_SCH
		} else {
		 // Serial.println("READ_INT no command found");
		}
		item->state = READ_COMMAND;
		PUART_RESET_BUF
		break;}
	case READ_DOUBLE://Serial.println("READ_DOUBLE");Serial.print("CMD: ");Serial.println(item->cmd);
		{double v = 0.0;
		if (ton(&item->tmr)) {
		  PUART_RESET_BUF
		  item->state = READ_COMMAND;//Serial.println("READ_DOUBLE timeout");
		  return;
		}
		if (!puart_parseDouble(item, &v)) { //Serial.println("READ_DOUBLE failed");
		  PUART_RESET_BUF
		  return;
		}
		//Serial.print("DOUBLE: "); Serial.println(v);
    //
		item->state = READ_COMMAND;
		PUART_RESET_BUF
		break;}
	default:
		//Serial.println("? state");
	return;
}
return;
}

// select;1;cgfts;end;
