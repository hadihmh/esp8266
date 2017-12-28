# esp8266
a simple code for use esp8266 with arduino
this code help to have a quick start 
it has some method for control esp8266 with arduino

this code isnt compelet and I am going to compelete it 
if you want any problem with this code plz send me :)

useage 
config your rx & tx pin in arduino and esp
upload esp8266.ino in your arduino
use methods :)


tcpServer(String port); => for start a tcp server

connectToServer(String conType,String ip,String port); => for connect to a tcp server

sendMessage(String message,int chanel); => send massage //if you use single connection, you dont enter any channel number

getIP(); => get current IP

closeConnection(); => close any connection

connectToWifi(String ssid,String pass); => connect to AP

sendToESP(String command); => send AT commands to esp

getESP8266(); => get everything from esp

getLastRecive(); => get last recive from esp

getClearRecive(); => get last clear recive from esp

setSerial(); => send everything you enter in serial monitor to esp //you can send AT commands to esp by serial monitor
