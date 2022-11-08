#ifndef CONTROLLERINI_H
#define CONTROLLERINI_H

/* Macros for MQTT transmission setup */
const char SECRET_SSID[]            = "dlink-ENViSEC";
const char SECRET_PASS[]            = "ENViSEC_123";
const char MQTT_CLIENT_ID[]         = "pub1_1";         //naming convention <sub/pub><use case>_<node#>
const char MQTT_BROKER_IP[]         = "192.168.0.101";
const char MQTT_BROKER_NAME[]       = "envisecmqtt1";
const int MQTT_BROKER_PORT          = 1883;
const char MQTT_TOPIC[]             = "uc6_1";
const int UPPER_THRESHOLD           = 399;              //Threholds for event based publisher default 399 (no event triggered)
const int LOWER_THRESHOLD           = 400;              //Threholds for event based publisher default 400 (no event triggered)

/* Macros for controlling sleep interval */
const int SLEEP_INTERVAL_MINUTES    = 1;                 //sleep interval in minutes
const int SECS_IN_ONE_MIN_CONSTANT  = 10;                //altered to get a ten second period

#endif
