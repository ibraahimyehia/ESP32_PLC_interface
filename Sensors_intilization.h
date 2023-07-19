#ifndef
#define Sensors_intilization.h


/* DHT*/
#define DHT_SENSOR_PIN  21 
#define DHT_SENSOR_TYPE DHT11

/*ultra Sonic*/
#define trig 13 // ADC RTC OD/IE
#define echo 12  // ADC RTC OD/IE
#define MaxLevel 23;

/*Water Sensor*/
#define POWER_PIN   23 // ESP32 pin GIOP23 connected to sensor's VCC pin
#define SIGNAL_PIN  36 // ESP32 pin GIOP36 (ADC0) connected to sensor's signal pin
#define THRESHOLD   1000

/*PLC Relay*/
#define PLC_SWITCH  V40
#define relay_out 5
#define relay_ultra 18

/* Authorization */
char auth[] = "/*Authontication*/";
char ssid[] = "/*wifi_ssd*/";
char pass[] = "/*wifi_password*/";

/* prototype */
void WaterSensor();
void ultrasonic();
void TEMP();

#endif