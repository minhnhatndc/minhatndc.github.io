#include "button_state.h"
void state_handle(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{ 
  nrf_gpio_pin_toggle(20);
  
  switch(pin)
  {
    case (BUTTON1):
          Pin.type = Menupin;
        switch(Mode){
            case(Idle):
              Mode = ModemenuTime;
              display_menu_idle();
              break;
            case(ModemenuTime):
              if(nrf_gpio_pin_read(BUTTON4) == 0){Mode = ModeReadTime;};
              Mode = ModemenuGPS;
              display_menu_time();
              break;
            case(ModemenuGPS):
              if(nrf_gpio_pin_read(BUTTON4) == 0){Mode = ModeReadGPS;};
              Mode = ModemenuBluetooth;
              display_menu_gps();
              break;
            case(ModemenuBluetooth):
              if(nrf_gpio_pin_read(BUTTON4) == 0){Mode = ModeReadBluetooth;};
              Mode = Idle;
              display_menu_bluetooth();
              break;
        }
    break;
    case (BUTTON2)://+/Read pin
         
              
         
          

    break;
    case (BUTTON3):
          Pin.type = Decrpin;
    break;
    case (BUTTON4):
          Pin.type = Enterpin;
          switch(Mode){
            case(Idle):
              Mode = Idle;
              display_menu_idle();
              break;
            case(ModemenuTime):
              
              Mode = ModeReadTime;
              display_time_test();
              display_date();
              display_temparature_dht11();
              if(nrf_gpio_pin_read(BUTTON1) == 0){Mode = Idle;};
              break;
            case(ModemenuGPS):
              Mode = ModeReadGPS;
              display_gps();
              if(nrf_gpio_pin_read(BUTTON1) == 0){Mode = Idle;};
              break;
            case(ModemenuBluetooth):
              Mode = ModeReadBluetooth;
              display_bluetooth();
              if(nrf_gpio_pin_read(BUTTON1) == 0){Mode = Idle;};
              break;
          }
    break;
  
  }

}
ret_code_t err_code;
void gpio_init()
{
  ret_code_t err_code;

  err_code = nrf_drv_gpiote_init();// Init GIPOE
  APP_ERROR_CHECK(err_code);
  //nrf_gpio_cfg_output(20);
  
  
  nrf_drv_gpiote_in_config_t in_config = GPIOTE_CONFIG_IN_SENSE_HITOLO(true);
  in_config.pull = NRF_GPIO_PIN_PULLUP;

  err_code = nrf_drv_gpiote_in_init(BUTTON1,&in_config,state_handle);
  APP_ERROR_CHECK(err_code);
  nrf_drv_gpiote_in_event_enable(BUTTON1,true);  
  
  err_code = nrf_drv_gpiote_in_init(BUTTON2,&in_config,state_handle);
  APP_ERROR_CHECK(err_code);
  nrf_drv_gpiote_in_event_enable(BUTTON2,true);

  err_code = nrf_drv_gpiote_in_init(BUTTON3,&in_config,state_handle);
  APP_ERROR_CHECK(err_code);
  nrf_drv_gpiote_in_event_enable(BUTTON3,true);

    err_code = nrf_drv_gpiote_in_init(BUTTON4,&in_config,state_handle);
  APP_ERROR_CHECK(err_code);
  nrf_drv_gpiote_in_event_enable(BUTTON4,true);

}