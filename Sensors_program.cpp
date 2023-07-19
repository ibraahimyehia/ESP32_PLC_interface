#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

#include <Sensors_intilization.h>


DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);
BlynkTimer timer;


void WaterSensor(){
  pinMode(POWER_PIN, OUTPUT);   
  digitalWrite(POWER_PIN, HIGH);  // turn the sensor ON
  delay(10);                      
  int value = analogRead(SIGNAL_PIN); // read the analog value from sensor
    	Serial.print("Water level: ");
	Serial.println(value);
    delay(10000);                   
  digitalWrite(POWER_PIN, LOW);   // turn the sensor OFF
int Lrate = value / 35 ;
if (value > 0 && value < 1000){
      Serial.print("nnn no leakage nnn");
      Blynk.virtualWrite(V0, "SYSTEM STABLE");
      Blynk.virtualWrite(V30, 2);
        
        pinMode(relay_out,INPUT);
        digitalWrite(relay_out,LOW);

        Blynk.virtualWrite(V5, "PUMPS WORK");
        Blynk.virtualWrite(V1, 0);
}

if (value > 1000 && value < 2000){
      Serial.print("nnn DRY nnn");
      Blynk.virtualWrite(V0, "SYSTEM STABLE - pumps are dry");
      Blynk.virtualWrite(V30, Lrate);
             
          pinMode(relay_out,INPUT);
          digitalWrite(relay_out,LOW);

          Blynk.virtualWrite(V5, "PUMPS WORK");
          Blynk.virtualWrite(V1, 0);

}

if (value > 2000){
      Serial.print("nnn leakage detected nnn");
      Blynk.virtualWrite(V0, "SYSTEM UNSTABLE - There is leakage");
      Blynk.virtualWrite(V30, value);
        pinMode(relay_out,OUTPUT);
        digitalWrite(relay_out,HIGH);
              Blynk.virtualWrite(V5, "System Stopped and PUMPS NOTWORKing");
                    Blynk.virtualWrite(V1, 1);
                    delay(3000);
}

}


void ultrasonic() {
  digitalWrite(trig, LOW);
  delayMicroseconds(4);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long t = pulseIn(echo, HIGH);
  int distance = t / 29 / 2;
  int blynkDistance = (distance - MaxLevel) * -1;  // at 1st distance(=23) - max lvl(23) *-1 =0 then water get into and distanse decrese to 22 -maxlve *-1 = 1cm  
  Blynk.virtualWrite(V4, blynkDistance); //ko
  
  delay(1000);
  int Wrate = blynkDistance * 1800 ; /* review again */
  Blynk.virtualWrite(V50, Wrate);
  /* remember to detect pump speed */

if (blynkDistance < 17 ){
pinMode(relay_ultra,INPUT);
  digitalWrite(relay_ultra,LOW);

}
else{
  pinMode(relay_ultra,OUTPUT);
  digitalWrite(relay_ultra,HIGH);
}

}





void TEMP(){
   
  float tempC = dht_sensor.readTemperature();
          Blynk.virtualWrite(V20, tempC);

   if (tempC < 35.1) {
     Serial.print("/n PLC ON /n");
     pinMode(relay_out,INPUT);
     digitalWrite(relay_out,LOW);
     Blynk.virtualWrite(V5, "System working");                                          
     Blynk.virtualWrite(V0, "SYSTEM STABLE");
    } else if (tempC > 35.1) {
         Serial.print("/n PLC OFF /n");
         pinMode(relay_out,OUTPUT);
         digitalWrite(relay_out,HIGH);                
	 Blynk.virtualWrite(V5, "System Stopped-PUMPS NOTWORKing");                               
	 Blynk.virtualWrite(V0, "SYSTEM UNSTABLE-HIGH TEMP");
	}
  // check whether the reading is successful or not
  if ( isnan(tempC) ) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
        Serial.print("Temperature: ");
    Serial.print(tempC);
              Blynk.virtualWrite(V20, tempC);


    Serial.print("°C  ~  ");

  }

  // wait a 2 seconds between readings
  delay(2000);
}




































