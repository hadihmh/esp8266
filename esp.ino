#include <SoftwareSerial.h>

//--------------------------------------------
//set digital pin number for connect esp8266
SoftwareSerial esp8266(10,11);
// 10 ->RX   11->TX
//--------------------------------------------

void setup() {
  esp8266.begin(115200);
  Serial.begin(9600);
}

void loop() {
  getESP8266();
  getSerial();
}
bool getESP8266(){
  
  if (esp8266.available()) {
              
          String command="";
          delay(1000);
          while (esp8266.available())
          {
           command += (char)esp8266.read();
 
           }
           Serial.println(command);
           return true;
           }else{
            return false;
           }

}
bool getSerial(){
  
  if (Serial.available()) {
    String command="";
    delay(1000);
   while (Serial.available())
    {
      command += (char)Serial.read();
 
    }
    esp8266.println(command);
    return true;
  }else{
    return false;
  }
}
