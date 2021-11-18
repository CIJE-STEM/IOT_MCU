/* POST data to server. Here specifically the measurememtn server set up at Glitch for ease of implementation
 *  
 *  NOTE: This is a good way to prototype, check, and run low throughput data. Eventually, for longer times and larger data sets, a move to a dedicated server is suggested. 
 */

#include "IoT_WiFi.h"
#include <string.h>
#include <stdio.h>
#include <HTTPClient.h>

#define ANALOG_PIN 34

IOT_WiFi IOT_WiFi; //initialize the IOT instance

struct Measurement {
  
  char timestamp[40];
  float value;
  char* units; // a measurement is meaningless without units. if it is miliVolts, then "mV", etc. 
  char* measurement_type; //e.g BATTERY, to help user catalog where this is from
  char mac_address[20]; 
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
  //measurement_now.timestamp=IOT_WiFi.getTime(); !! Doesn't work with const char* type
  strcpy(measurement_now.timestamp,IOT_WiFi.getTime());//we can't directly assign timestamp in C-style strings. We have to make a copy if being safe. String copy, strcpy(destination, source) does this. 
  measurement_now.value=volts_now;
  measurement_now.units="V";
  measurement_now.measurement_type="POTENTIOMETER";
  strcpy(measurement_now.mac_address,IOT_WiFi.getMACAddress()); //same thing as in timestamp
  // most likely this device is behind a local router, so sendign the local IP Address is useless. We will get this from the HTTP header on the other end
  measurement_now.device_id="CIJEJAY0001";
  measurement_now.note="TESTING FOR IOT SERVER";
   
  //post the data
  postData2Server("https://cije-basic-iot-server.glitch.me/measurements/",measurement_now);
  delay(1000);
}

bool postData2Server(const char* route, Measurement& measure){

  //Build the JSON for sending
  //TODO: do a more accurate size count
  size_t json_size=1000;
  char body_json[json_size];
  snprintf(body_json,json_size,"{ \"new_measure\": {\"timestamp\": \"%s\", \"measurement_value\":\"%f\", \"measurement_units\":\"%s\",\"measurement_type\":\"%s\",\
  \"mac_addr\":\"%s\",\"device_id\":\"%s\",\"note\":\"%s\" }}",measure.timestamp, measure.value, measure.units, measure.measurement_type,\
  measure.mac_address,measure.device_id,measure.note);

  Serial.print("JSON OUT ");Serial.println(body_json);

  //HTTP POST Headers etc.  using HTTP Client
  HTTPClient http;

  http.begin(route);
  http.addHeader("Content-Type","application/json");
//  http.addHeader("Content-Length",

  
  int httpResponseCode=http.POST(body_json);

  if (httpResponseCode>0){
    String response = http.getString();                       //Get the response to the request
  
    Serial.println(httpResponseCode);   //Print return code
    Serial.println(response);           //Print request answer
  
   }else{
  
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
  
   }
  
   http.end();  //Free resources
    
  

  return true; //if successful return true
}
