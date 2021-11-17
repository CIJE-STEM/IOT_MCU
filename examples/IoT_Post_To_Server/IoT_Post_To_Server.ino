/* POST data to server. Here specifically the measurememtn server set up at Glitch for ease of implementation
 *  
 *  NOTE: This is a good way to prototype, check, and run low throughput data. Eventually, for longer times and larger data sets, a move to a dedicated server is suggested. 
 */

#include "IoT_WiFi.h"
#include <string.h>
#define ANALOG_PIN 34

IOT_WiFi IOT_WiFi; //initialize the IOT instance

struct Measurement {
  
  char timestamp[40];
  float value;
  char* units; // a measurement is meaningless without units. if it is miliVolts, then "mV", etc. 
  char* measure_type; //e.g BATTERY, to help user catalog where this is from
  char* mac_address; 
  char* ip_address;
  char* device_id;  // currently, this is self-identified. Use somehting that will be unique. 
  char* note; //OPTIONAL: any additional info that can be helpful in later analysis. 
   
} measurement_now{}; //this creates a Measurement called measurement_now wiht all values initialized to zero or equivalent



void setup() {
 Serial.begin(115200);

 //Here we use the initWiFi() that assumes that SSID and PASSWORD have been stored on the board already
 //Use Utilities/preferences_mem_save/preferences_mem_save.ino in the library to do that.
 //Use initWiFi(const char* WIFI_SSID, const char* WIFI_PASSWORD) if don't want to save

  IOT_WiFi.initWiFi();
  delay(1000);
  
  Serial.print("TIMESTAMP: ");Serial.println(IOT_WiFi.getTime()); //returns UTC time

}

void loop() {

  //measure a sensor. Here an analog read.
  int val_now = analogRead(ANALOG_PIN);
  //convert to a voltage assuming 3.3V is my peak, not necessarily a good assumption, but 
  float volts_now = (float)val_now*(3.3/4095.); //important to use the decimal points to indicate decimal division
  
  Serial.print("Analog, Volts: ");Serial.print(val_now);Serial.print(" ");Serial.println(volts_now);

  /*
   * PREPARE MEASUREMENTS FOR POSTING TO DB
   */
  //measurement_now.timestamp=IOT_WiFi.getTime();
  strcpy(measurement_now.timestamp,IOT_WiFi.getTime());
  measurement_now.value=volts_now;
  measurement_now.units="V";
  measurement_now.measure_type="POTENTIOMETER";
  measurement_now.mac_address=(IOT_WiFi.getMACAddress()).c_str();
  // most likely this device is on a local router, so sendign the local IP Address is useless. We will get this from the HTTP header on the other end
  measurement_now.device_id="CIJEJAY0001";
  measurement_now.note="TESTING FOR IOT SERVER";
   
  //post the data
  
}
