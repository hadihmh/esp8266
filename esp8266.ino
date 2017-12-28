#include <SoftwareSerial.h>
#include <stdio.h>
#include <string.h>

bool sendMessage(String ,int = -1);





//--------------------------------------------
//set digital pin number for connect esp8266
SoftwareSerial esp8266(10,11);
// 10 ->RX   11->TX
//--------------------------------------------
//variables
String recive="0";
//--------------------------------------------
//wifi conf
String ssid="";
String password="";
//--------------------------------------------
//ip and port for connect to server
String ip_client="";
String port_client="";
//--------------------------------------------
//ip and port for create server
String ip_server="";
String port_server="";
//--------------------------------------------
//AT Comands
String CIPSTART="AT+CIPSTART=";
String CIPSEND="AT+CIPSEND=";
String CWJAP="AT+CWJAP=";
String CIPMUX="AT+CIPMUX=";
String CWJAP_q="AT+CWJAP?";
String RST="AT+RST";
String CIPCLOSE="AT+CIPCLOSE";
String CIPSTATUS="AT+CIPSTATUS";
String CIFSR="AT+CIFSR";
String CIPSERVER="AT+CIPSERVER=";

//---------------------------------------------
//extra words
String db_quot="\"";
String TCP="TCP";
String UDP="UDP";
String sign=",";


//----------------------------------------------

void setup() {
  esp8266.begin(115200);
  Serial.begin(9600);
  
 //this is test for connect to a AP
 connectToWifi("ssid","password");
 
 
 //get ip from AP
 getIP();
  
}
 
void loop() {



  //this is for send commends to esp8266
  setSerial();

  if(getClearRecive()!=""){
    //it is for test 
    //by this code you can see what happane with your serial monitor
  Serial.println(getLastRecive());

  }
 

       }



bool tcpServer(String port){
  
  closeConnection();
  bool contenue=true;
  int del=1000;
    String command=CIPSERVER+"1"+sign+port;
    delay(50);
    sendToESP(CIPMUX+"1");
   // Serial.println(CIPMUX+"1");
    delay(1000);
    getClearRecive();
    while(contenue){
       sendToESP(command);
    //Serial.println(command);
    delay(del);
    String response=getClearRecive();
    //Serial.println(response);
  if(response!="" & find_text("OK",response)!=-1){
   Serial.println("server create");
   contenue=false;
   return true; 
  }
  if(response!="" & find_text("no",response)!=-1){
   Serial.println("server before create");
   contenue=false;
   return true; 
  }
  del+=500;
    }
   
    return false;
}
bool udpServer(String port){
  
}
bool connectToServer(String conType,String ip,String port){
    String command=CIPSERVER+"0";
    
    
    delay(50);
    String test=getClearRecive(); 
  if(test!=""){
    Serial.println("("+test+")");
  }
  
    sendToESP(command);
   
  
    //Serial.println(command);
    delay(1000);
    sendToESP(CIPMUX+"0");
      test=getClearRecive(); 
  if(test!=""){
    Serial.println("("+test+")");
  }
    getClearRecive();
    delay(50);
    
    //Serial.println(CIPMUX+"0");
    delay(1000);
    getClearRecive();
    
  bool contenue=true;
  String temp=CIPSTART+db_quot+conType+db_quot+sign+db_quot+ip+db_quot+sign+port;
  delay(10);
   test=getClearRecive(); 
  if(test!=""){
    Serial.println("("+test+")");
  }
  
 // Serial.println(temp);
  
  while (contenue){
    
    sendToESP(temp);
    delay(3000);
    String response=getClearRecive();
    //Serial.println(response);
    if(response !="" && find_text("OK",response)!=-1 ){
      Serial.println("connected");
      return true;
 
    }
    if(response !="" && find_text("ALR",response)!=-1){
      Serial.println("Already hmh connected");
      return true;
    }
    if(response !="" && find_text("ERR",response)!=-1){
      Serial.println("ERROR to Connect");
    return false;
    }
    }
    
    return false;    
}
bool sendMessage(String message,int chanel){
  String command=CIPSEND;
  String leng=(String)message.length();
  if(chanel == -1){
    command=command+leng;
  }else{
    command=command+chanel+sign+leng;
  }
  
  delay(10);
//  Serial.println(command);
//  esp8266.println(command);
//  Serial.println(getClearRecive());
  sendToESP(command);
  delay(5000);
  sendToESP(message);
  String response=getClearRecive();
  if(response!="" & find_text("OK",response)!=-1){
   Serial.println("message sended");
   return true; 
  }
  return false;
}
String getIP(){
  int dell=500;
  String cleer="";
  String command=CIFSR;
  bool trying=true;
  while(trying){
    sendToESP(command);
    delay(dell);
  if(getESP8266()){
    String command=getLastRecive();
    String aaa="";
    //Serial.println("------------------2");
    //Serial.println(command);
    for ( int i=0 ; i<command.length() ; i++ ) {
      //Serial.print(command[i]);
      if(command[i]=='"' ){
        for ( int j=i+1 ; j<command.length() ; j++ ) {
          
          if(command[j]=='"'){
            //Serial.println("------------------3");
            Serial.println(aaa);
            //return aaa;
            goto lable1;
          }
          aaa+=(String)command[j];
        }
        
         
          }
        }
        lable1:
        cleer="";
        //Serial.println("hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh");
        //Serial.println(aaa.length());
        bool test=false;
        for ( int k=0 ; k<aaa.length() ; k++ ) {
          if(aaa[k]=='0' | aaa[k]=='1' | aaa[k]=='2' | aaa[k]=='3' | aaa[k]=='4' | aaa[k]=='5' | aaa[k]=='6' | aaa[k]=='7' | aaa[k]=='8' | aaa[k]=='9'){
            cleer+=aaa[k];
            test=false;
          }else{
            cleer+=".";
            if(test){
             trying=true; 
             //Serial.println("hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh");
             //goto lable2;
             dell+=500;
             break;
            }else{
              trying=false;
            }
            test=true;
          }
          
          }
          Serial.println(cleer);
          
    
  }
  //lable2:
  }
  return cleer;
  
  //return "";
  
}
bool closeConnection(){
  delay(50);
  sendToESP(CIPCLOSE);
  delay(1000);
  String response=getClearRecive();
    //Serial.println(response);
    if(response !="" && find_text("OK",response)!=-1 ){
      Serial.println("close");
      return true;
 
    }
    return false;
}

bool connectToWifi(String ssid,String pass){
  //using for connect to AP
  String temp=CWJAP+db_quot+ssid+db_quot+sign+db_quot+pass+db_quot;
  bool contenue=true;
  bool retrying=true;
  while(retrying){
      sendToESP(RST);
  delay(1500);
  int i=0;
  getClearRecive();
  sendToESP(temp);
  //Serial.println("---------------");
  contenue=true;
  while(contenue){
    delay(6000);
    String response=getClearRecive();
    if(response !="" && find_text("OK",response)!=-1 ){
    contenue=false;
    retrying=false;
    Serial.println("OK");
    return true;
  }else{
    Serial.println("retrying...");
    i++;
    if(i>3){
      contenue=false;
      }
  }
      
  }
  }

  return false;
     
}
void sendToESP(String command){
  //send AT commands to ESP
  esp8266.println(command);
}
bool getESP8266(){
  //for get everythings from esp8266
  if (esp8266.available()) {
              
          String command="";
          delay(1000);
          while (esp8266.available())
          {
           command += (char)esp8266.read();
 
           }
           //Serial.print(command);
           recive=command;
           return true;
           }else{
            return false;
           }

}
String getLastRecive(){
  //get last recieve
  return recive;
}
String getClearRecive(){
  //get last clear recieve from ESP
  if(getESP8266()==true){
   return getMessageRecieve(getLastRecive());
  }else{
    return "";
  }
 }
bool setSerial(){
  //for get everythings from Serial
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
String getMessageRecieve(String command ){
  //get clear string  from esp on everytime
    String aaa="";
    int found=0;
    for ( int i=command.length() ; i>0 ; i-- ) {
      if(command[i]==':' ){
       //Serial.println(i);
       found++;
       if(found==2){
        aaa+=(String)command[i+1];
        break; 
       }
     
      
      }
      if(command[i]==';'){
         if(found==2){
          aaa+=(String)command[i+1];
        break; 
       }
        }
        if(command[i]=='='){
         if(found==2){
          aaa+=(String)command[i+1];
        break; 
       }
        }
      if(found==0){
         aaa+=(String)command[i];
      }
   
    
    }
    //Serial.println(aaa);
     String cr="";
     for ( int i=aaa.length() ; i>=0 ; i-- ) {
      
    cr+=(String)aaa[i];
     }
   
    return cr;
    
  }
 bool sensitivePin(int pinNum,int scope,int first,int dela){
  //for supervision on selected pin
  delay(dela);
  int val=analogRead(pinNum);
  int valChange=val-first;
  if(valChange > scope ){

    Serial.println(analogRead(pinNum));
    return true;
    
    }
    return false;
 }
 
 int find_text(String needle, String haystack) {
  //find substring
  int foundpos = -1;
  for (int i = 0; i <= haystack.length() - needle.length(); i++) {
    if (haystack.substring(i,needle.length()+i) == needle) {
      foundpos = i;
    }
  }
  return foundpos;
}
 





