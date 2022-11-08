#include "CController.h"



/* Constructor */
CController::CController(): mqttClient(wifiClient) 
{
/* debug: leds */
  PORTD_PIN6CTRL |= PORT_PULLUPEN_bm;
  PORTD_DIRSET |= PIN6_bm;  //Set PD6 to output
  PORTE_PIN0CTRL |= PORT_PULLUPEN_bm;
  PORTE_DIRSET |= PIN0_bm;  //Set PE0 to output

/*Sleep*/
  set_sleep_mode(SLPCTRL_SMODE_PDOWN_gc);
  /* Wake up timer setup (PIT) */
  RTC_PITCTRLA = RTC_PERIOD_CYC32768_gc    //Set period length for periodic interrupt (1 sec)
                  | RTC_RTCEN_bm;           //Enable RTC peridoc interrupt
  RTC_PITINTCTRL = RTC_PI_bm;              //PIT interrupt enable

/*Transmission*/
  mqttClient.setServer(MQTT_BROKER_IP, MQTT_BROKER_PORT);
  
  mqttClient.setCallback([](char* topic, byte* payload, unsigned int length){
     CController::instance().m_callBack(topic,payload,length);
   });
  

};


/**************************************************
*         CCONTROLLER MEMBER FUNCTIONS            *
**************************************************/

/* Function for setting data member */
void CController::m_setData(int data) {this->mi_pubData = data;}

/* Function for getting data member */
int CController::m_getData() {return this->mi_subData;}

/* Function for controlling process of 
  the device */
void CController::m_processController()
{
  if(this->m_checkForWakeup())
  {
    // PORTE_OUTTGL = PIN0_bm;
    // PORTD_OUTTGL = PIN6_bm;
    //mainFunctionallity();
    // this->m_connect_to_MQTT();
    // this->mqttClient.loop();
    // this->m_disconnect_from_MQTT();
    this->m_deviceSleep();
  }
  else this->m_deviceSleep();
}


/* Function for disabling ports on device */
void CController::m_disablePorts(void){
  for (volatile uint8_t* p = &PORTA.PIN0CTRL; p <= &PORTF.PIN0CTRL; p +=0x20)
  {
    for(uint8_t i = 0; i < 8; i++) p[i] = PORT_ISC_INPUT_DISABLE_gc; //pin dinput disable
  }
}


/**************************************************
*              SLEEP FUNCTIONALITY                *
**************************************************/

  /* Function for checking for device wake up, 
   wakeing up involves commencing device's 
   Main Functionality and transmission of data
   to broker */
bool CController::m_checkForWakeup()
{
  if(this->mi_sleepCntr >= (SLEEP_INTERVAL_MINUTES * SECS_IN_ONE_MIN_CONSTANT) ) 
  {
    this->m_resetSleepCounter();
    return true;
  } 
  else return false; 
}


/* Function for putting 
   device to sleep */
void CController::m_deviceSleep()
{
  sleep_enable();                 //avr/sleep.h
  sei();                          //avr/interrupt.h
  sleep_cpu();                    //avr/sleep.h

  /* increment sleep counter 
     for application run time */
  this->m_incrementSleepCounter();
  
  sleep_disable();                //avr/sleep.h
  cli();                          //avr/interrupt.h
}


/* Function for Incrementing sleep counter,
   used for  checking for wake up interval */
void CController::m_incrementSleepCounter()
{
  this->mi_sleepCntr++;
}


/* Function for resetting sleep counter after 
   transmission of data to MQTT broker*/
void CController::m_resetSleepCounter()
{
  this->mi_sleepCntr = 0;
}


/* Function for allowing external interrupts
  to make the PIT wake up the device from sleep*/
ISR(RTC_PIT_vect)
{
  RTC_PITINTFLAGS |= RTC_PITEN_bm;
}

/**************************************************
*           TRANSMISSION FUNCTIONALITY            *
**************************************************/
void CController::m_callBack(char* topic, byte* payload, unsigned int length) 
{

  for (int i=0; i<length; i++) 
  {
    buffer[i]=payload[i];
    //Serial.print((char)payload[i]);
    PORTE_OUTTGL = PIN0_bm;
    PORTD_OUTTGL = PIN6_bm;

  }
}

/* Threshold check for event based publishing */
bool CController::m_ThresholdCheck()
{
  if(this->mi_pubData > UPPER_THRESHOLD || this->mi_pubData < LOWER_THRESHOLD) return true;
  else return false;
}


/* Function for connectin device to
   WLAN and MQTT broker */
void CController::m_connect_to_MQTT()
{
  /* check MQTT broker connection */
  // if(!mqttClient.connected())
  // {
  //   mqttClient.connect(MQTT_CLIENT_ID);
  //   PORTD_OUTSET |= PIN6_bm;
  // }
  
  if (mqttClient.connect(MQTT_CLIENT_ID)) 
  {
    boolean r= mqttClient.subscribe(MQTT_TOPIC,1);
  }
  
} 


/* Function for disconnecting device 
   from MQTT broker and WLAN */
void CController::m_disconnect_from_MQTT()
{
  /* disconnect from MQTT broker */
  if(mqttClient.connected())
  {
    mqttClient.disconnect();
    PORTD_OUTCLR |= PIN6_bm;
  }
}








