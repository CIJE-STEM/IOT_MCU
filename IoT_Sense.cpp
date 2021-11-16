/*
 * 
 * some comments hers
 */

 #include "IoT_Sense.h"


 IOT_Sense::IOT_Sense(){

  //initialize sensors, will need something that checks if these are successful

  AHT10 AHT10_1(AHT10_ADDRESS_0X38);
  //this isn't going to work long term, gonna need to figure out a better way
  while (AHT10_1.begin() != true) 
    {
      Serial.println(F("AHT10 not connected or fail to load calibration coefficient")); //(F()) save string to flash & keeps dynamic memory free
      delay(1000);
    }

     Serial.println(F("DEMO 1: read 12-bytes, show 255 if communication error is occurred"));
  Serial.print(F("Temperature: ")); Serial.print(AHT10_1.readTemperature()); Serial.println(F(" +-0.3C")); //by default "AHT10_FORCE_READ_DATA"
  Serial.print(F("Humidity...: ")); Serial.print(AHT10_1.readHumidity());    Serial.println(F(" +-2%"));   //by default "AHT10_FORCE_READ_DATA"

 
 }
