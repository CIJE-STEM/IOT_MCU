/*
 * 
 * Sensor and other  Input data 
 * Not implemented as an interface to avoid virtual overhead on MCU
 * 
 */

#ifndef __IOT_SENSE_H__
#define __IOT_SENSE_H__

#include <AHT10.h>
#include <Wire.h>

 class IOT_Sense {

  public:

  IOT_Sense();
  ~IOT_Sense()=default;
  IOT_Sense(const IOT_Sense& other) = delete;
  IOT_Sense& operator=(const IOT_Sense& other) = delete;
  IOT_Sense(IOT_Sense&& other) = delete;
  IOT_Sense& operator=(IOT_Sense&& other) = delete;

  //function will poll and return data of all polled sensors AND return values of any interrupt variables with initiiating new read 
  template<typename T>
  T getData();

  // getSensorList();
  private:
  AHT10 AHT10_1; //temp/humidity sensor
  
  //char** sensor_list
 };

template<typename T>
T IOT_Sense::getData(){
  Serial.println("Nothing here yet!");

}


#endif // __IOT_SENSE_H__
