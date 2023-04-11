#include "Adafruit_seesaw.h"

#define PUMP_PIN 6
Adafruit_seesaw soilSensor;

bool test = false;
void setup() {
  Serial.begin(115200);

   if (!soilSensor.begin(0x36)) {
    Serial.println("ERROR! seesaw not found");
    while(1) delay(1);
  } else {
    Serial.print("seesaw started! version: ");
    Serial.println(soilSensor.getVersion(), HEX);
  }

  pinMode(PUMP_PIN, OUTPUT);
}

void pump_water(){
  if(!test){
    digitalWrite(PUMP_PIN, HIGH);
    delay(10000);
    digitalWrite(PUMP_PIN, LOW);
    test = true;
  }
}

void loop() {
  //pump_water();
  // delay(10000);
  // test = false;
  float tempC = soilSensor.getTemp();
  uint16_t capread = soilSensor.touchRead(0);

  if(capread < 500){
    digitalWrite(PUMP_PIN, HIGH);
  }else{
    digitalWrite(PUMP_PIN, LOW);
  }

  Serial.print("Temperature: "); Serial.print(tempC); Serial.println("*C");
  Serial.print("Capacitive: "); Serial.println(capread);
  delay(100);
}
