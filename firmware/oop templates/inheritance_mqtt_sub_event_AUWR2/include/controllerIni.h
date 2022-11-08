#ifndef CONTROLLERINI_H
#define CONTROLLERINI_H

/* Macros for MQTT transmission setup */
const char SECRET_SSID[]      = "dlink-ENViSEC";
const char SECRET_PASS[]      = "ENViSEC_123";
const char MQTT_CLIENT_ID[]   = "sub1_1";         //naming convention <sub/pub><use case>_<node#>
const char MQTT_BROKER_IP[]   = "192.168.0.102";
const char MQTT_BROKER_NAME[] = "envisecmqtt1";
const int MQTT_BROKER_PORT    = 1883;
const char MQTT_TOPIC[]       = "UnoTestTopic";

/* Macros for controlling sleep interval */
const int SLEEP_INTERVAL_MINUTES = 1;             //sleep interval in minutes
const int SECS_IN_ONE_MIN_CONSTANT = 60;          //Do not alter

/* Macros for controlling transmission events 
  Only applies for event based message publishing*/
const int UPPER_THRESHOLD = 400;                  //set upper event limit as an integer
const int LOWER_THRESHOLD = 399;                  //set lower event limit as an integer

#endif





