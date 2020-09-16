
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include<bits/stdc++.h>
#include <Servo.h>
int ledPWMred = 0;
int ledPWMgreen =0;
Servo servo_1;
//  WEBPAGE 

const char* MAIN_PAGE PROGMEM = R"=====(
<!DOCTYPE html><html>
<head><meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="icon" href="data:,">
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}
</style></head>
<body onload="setVal()"><div class="alert alert-success" role="alert">
<h4 class="alert-heading">Welcome To ESP8266 - WebServer!</h4>
<p>Hey There! You can control remote Leds from this web page</p>
<hr></div>

<div class="container">
<form action="/updatered">
  <div class="form-group">
    <label for="formControlRange">control light intensity of Red LED</label>
    <input name="ledPWM" type="range" class="form-control-range" value=50 id="ledval">
    
  </div>
  <button type="submit" class="btn btn-warning">change red</button>
</form>
<form action="/updategreen">
  <div class="form-group">
    <label for="formControlRange">control light intensity of green LED</label>
    <input name="ledPWM" type="range" class="form-control-range" value=50 id="ledval">
   
  </div>
  <button type="submit" class="btn btn-warning">change green</button>
</form>
<form action="/Setservo">
  <div class="form-group">
    <label for="formControlRange">control light intensity of green LED</label>
    <input name="servo" type="number" class="form-control"  id="servo">
  </div>
  <button type="submit" class="btn btn-warning">Set servo</button>
</form>
</div>
</body></html>

)=====";


const char* ssid     = "helloworld";
const char* password = "higgsboson";
ESP8266WebServer server(80);
const int Led1 = D1;
const int Led2 = D2;

int toNum(String s)
{
  int value=0,cnt=0;
  for(int i=s.length()-1;i>=0;i--)
  {
    value+=(s[i]-'0')*pow(10,cnt);
    cnt++;
  }
  return value;
}
void handleRoot()
{
  auto s = MAIN_PAGE;
  server.send(200,"text/html", s);
}
void handleUpdatered()
{
  String PWM = server.arg("ledPWM");
  
  ledPWMred = toNum(PWM);
    Serial.println(ledPWMred);
  analogWrite(D4,(ledPWMred*1023)/100 );
  
  handleRoot();
  return;
}
void handleUpdategreen()
{
  String PWM = server.arg("ledPWM");
  
  ledPWMgreen = toNum(PWM);
    Serial.println(ledPWMgreen);
  analogWrite(D3,(ledPWMgreen*1023)/100 );
  
  handleRoot();
  return;
}
void handleservo()
{
  String servo = server.arg("servo");
  
  int motorangle = toNum(servo);

  servo_1.write(motorangle);
  
  handleRoot();
  return;
}
void setup() {
  servo_1.attach(D5);
  Serial.begin(9600);
  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/updatered", handleUpdatered); 
  server.on("/updategreen",handleUpdategreen);
  server.on("/Setservo",handleservo);
  server.begin();
  Serial.println("Server started! ");
}

void loop(){
  server.handleClient();
}
