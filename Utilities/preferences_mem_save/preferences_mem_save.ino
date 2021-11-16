//Short script to get credentials onto a board for later use

#include <Preferences.h>

Preferences pref_mem;


const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

void setup() {


  pref_mem.begin("credentials",false);
  pref_mem.putString("ssid",ssid);
  pref_mem.putString("password",password);

  pref_mem.end();


  //Now write to Serial monitor to verify, read only    
  Serial.begin(115200);


  pref_mem.begin("credentials",true); //true -> read only
  Serial.print("SSID: ");
  Serial.println(pref_mem.getString("ssid",""));
  Serial.print("PASS: ");
  Serial.println(pref_mem.getString("password",""));
  pref_mem.end();

}

void loop() {
  // put your main code here, to run repeatedly:

}
