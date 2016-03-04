/*
 * Author: Jose Nunez (http://costaricamakers.com/?page_id=87)
 * Copyright Intel Corporation 2016
 * This sketch provides 
 * 1) AP Mode: An AccessPoint mode for initial configuration 
 * 2) CLI Mode: A Client mode that connects to a configured WiFi and pvCloud Client
 * 3) Config Server: Web Server for configuration in both AP and CLI modes.
 * 4) pvCloud Integration: It transmits to and consumes data from pvCloud as configured to collect sensors data or control effectors.
 */


#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

const char *ssid = "SF_ESP8266_AAAA";
const char *password = "intelrocks!";
ESP8266WebServer server(80);

void handleRoot() {
  String result = "<!DOCTYPE html><html><head><title>WELCOME TO SF_ESP8266 CONFIG</title><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><style>table tr td:first-child{color:navy;text-align:right}</style></head><body><form action='configure/' method='post'><h1>SF_ESP8266 Config</h1><hr><fieldset title='WiFi Connection'><legend>WiFi Connection</legend><table><tr><td style='text-align: right'>SSID:</td><td><input id='ssid' name='ssid' type='text'/></td></tr><tr><td>PASSWORD:</td><td><input type='text' id='wifi_password' name='wifi_password'></td></tr></table></fieldset><br><fieldset><legend>pvCloud Connection</legend><table><tr><td>Base URL:</td><td><input placeholder='pvCloud Server URL' type='text' id='pvcloudURL' name='pvcloudURL'></td></tr><tr><td>Account:</td><td><input placeholder='Type your maker account' type='text' id='pvc_username' name='pvc_username'></td></tr><tr><td>Password:</td><td><input placeholder='Password will be clear text' type='text' id='pvc_password' name='pvc_password'></td></tr><tr><td>App:</td><td><input placeholder='Type ID or Name' type='text' id='pvc_app_id_or_name' name='pvc_app_id_or_name'></td></tr><tr><td>&nbsp;</td><td><input type='submit' value='Configure Now'></td></tr></table></fieldset><fieldset><legend>GPIO Labels and Direction</legend><table><tr><td>Label&nbsp;D0</td><td><input type='text' id='label_0' name='label_0'></td><td><select><option>INPUT</option><option>OUTPUT</option></select></td></tr><tr><td>Label D4</td><td><input type='text' id='label_4' name='label_4'></td><td><select><option>INPUT</option><option>OUTPUT</option></select></td></tr><tr><td>Label D5</td><td><input type='text' id='label_5' name='label_5'></td><td><select><option>INPUT</option><option>OUTPUT</option></select></td></tr><tr><td>Label A0</td><td><input type='text' id='label_A0' name='label_A0'></td><td>ANALOG&nbsp;INPUT</td></tr><tr><td>Time: </td><td><select><option>5 Sec</option><option>10 Sec</option><option>20 Sec</option><option>60 Sec</option><option>5 min</option><option>15 min</option><option>30 min</option><option>1 hour</option><option>2 hour</option><option>6 hour</option><option>12 hour</option><option>1 day</option></select></td><td></td></tr></table></fieldset></form></body></html>";
 
  server.send(200, "text/html", result);
}

void setInitialAPMode(){
  Serial.println("Setting initial AP Mode");
  randomSeed(analogRead(0));
  long randomNumber = random(1000,9999);

  Serial.print("Random Number: ");
  Serial.println(randomNumber);
  
  String new_ssid = "SF_ESP8266_";
  new_ssid += randomNumber;
  Serial.print("NEW SSID: ");
  Serial.println(new_ssid);
  
  ssid = new_ssid.c_str();

  Serial.print("SSID: ");
  Serial.print(ssid);
  Serial.print(" PWD: ");
  Serial.println(password);
  
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");  
  
}


void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println("SETUP ROUTINE BEGIN");
  setInitialAPMode();
}
long c = 0;
void loop() {
  c++;
  if(c<3){Serial.println(c);}

  server.handleClient();
}


