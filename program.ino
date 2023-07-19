
#include <Sensors_intilization.h>

void setup() {
  Serial.begin(4800);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);  
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  dht_sensor.begin(); 

  //Call the functions
  timer.setInterval(5000L, ultrasonic);
  delay(100);
  timer.setInterval(3000L, WaterSensor);
  delay(100);
  timer.setInterval(3000L, TEMP);

}

void loop() {
  Blynk.run();//Run the Blynk library
  timer.run();//Run the Blynk timer

}



