#include "state_machine.h"
Mode_t                Mode           = Idle;
Mode_config_t         Mode_cfg       = -1;
Mode_time_t           Mode_time      = Mode24h;
Mode_bluetooth_t      Mode_bluetooth = ModeDisconnect;
Bluetooth_status_t    Bluetooth_status = Bluetooth_disconnect;
Type_pin              Pin;
uint8_t               flag = 0;
uint8_t               flagFinishCfg = 0;
uint8_t               flagDisplay = 0;

void state_month(int Month, char buffer[])
{
  switch(Month){
	case (1):
	  sprintf(buffer, "Jan");
	  break;
	case (2):
          sprintf(buffer, "Feb");
	break;
	case (3):
          sprintf(buffer, "Mar");
	break;
	case (4):
          sprintf(buffer, "Apr");
	break;
	case(5):
          sprintf(buffer,"May");
	break;
	case(6):
          sprintf(buffer,"Jun");
		break;
	case(7):
          sprintf(buffer,"Jul");
		break;
	case(8):
          sprintf(buffer,"Aug");
		break;
	case(9):
          sprintf(buffer,"Sep");
		break;
	case(10):
          sprintf(buffer,"Oct");
		break;
	case(11):
          sprintf(buffer,"Nov");
		break;
	case(12):
          sprintf(buffer,"Dec");
		break;

	}
}
void state_day(int Day, char buffer[])
{
  switch(Day){
	case (1):
	  sprintf(buffer, "MON");
	  break;
	case (2):
          sprintf(buffer, "TUS");
	break;
	case (3):
          sprintf(buffer, "WED");
	break;
	case (4):
          sprintf(buffer, "THU");
	break;
	case(5):
          sprintf(buffer,"FRI");
	break;
	case(6):
          sprintf(buffer,"SAT");
		break;
	case(7):
          sprintf(buffer,"SUN");
          break;
             }
}
