#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "HLRXTxOsWWmAGU00uIqEXzAyuAweooFh";//Enter the Auth code which was send by Blink
int ldrpin = A0;
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "helloworld";
char pass[] = "higgsboson";
int LastTime = millis()-20;
int TimeDelay = 3000;
int sum=0,cnt=0;
SimpleTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  float intensity = sum/cnt;
  Serial.println("sending data");
  Blynk.virtualWrite(V1, intensity);
  Serial.println("Data updated succefully");
  
}

void setup()
{
  Serial.begin(9600); // See the connection status in Serial Monitor
  Blynk.begin(auth, ssid, pass);
  
}

void loop()
{
if(millis()-LastTime >= TimeDelay)
  {
    Blynk.run(); 
    
    sendSensor();
    sum=0;
    cnt=0;
    LastTime = millis();
  }
  float ldrstatus = analogRead(ldrpin);
  sum = sum + ldrstatus;
  Serial.println("current intensity:");
  Serial.println(ldrstatus);
  cnt++;
  delay(200); 
  
}
