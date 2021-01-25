#include <Arduino.h>
#include <TMP75.h>

TMP75 mySensor; // mySensor at default i2c address

void setup(){
  Serial.begin(115200);
  Wire.begin(); // initialize i2c library
  int error=mySensor.begin();
  if (error) {
    Serial.println("TMP75 not responding...");
    while(1);
  }

  
}

void loop(){
  int temp = mySensor.readTemperature();
  Serial.print("Temp = ");
  Serial.print(temp); // 4 decimals to see full 12 bits resolution
  Serial.println(" Celsius*10");
  delay(500);
  
}
