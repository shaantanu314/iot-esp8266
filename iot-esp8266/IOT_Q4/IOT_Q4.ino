#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#ifndef STASSID
#define STASSID "Shantanu"
#define STAPSK  "qmzp1357"
#endif

const int ldrpin = A0;
float cnt = 0 ;
float sum=0;
int LastTime = millis()-15;
int TimeDelay = 30000;
const char* ssid     = STASSID;
const char* password = STAPSK;

const char* host = "api.thingspeak.com";
const uint16_t port = 80;
//String writeAPIkey = "TPWY954KMUL7PE1K";
String writeAPIkey = "CRAFQCLAYT4L9JNG";
String path = "/update";

void setup() {
  Serial.begin(9600);
  pinMode(ldrpin,INPUT);
  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

  if(millis()-LastTime >= TimeDelay)
  {
    // IF DHT SENSOR WORKS
    // float t = random(25,30);
    // float h = random(50,70);
    Serial.print("connecting to ");
    Serial.print(host);
    Serial.print(':');
    Serial.println(port);
  
    WiFiClient client;
    if (!client.connect(host, port)) {
      Serial.println("connection failed");
      delay(5000);
      return;
    }
  
    float intensity = sum/cnt;
    Serial.println("Connected!");
  
  //  String url = path+"?api_key="+writeAPIkey + "&field1="+String(t) + "&field2="+String(h);
    String url = path+"?api_key="+writeAPIkey + "&field1="+String(intensity);
    Serial.println(url);
    client.print(String("GET ") + url + "HTTP/1.1\r\n"+
                "Host: " + host + "\r\n" +
                "Connection: close\r\n\r\n");
     Serial.print(String("GET ") + url + "HTTP/1.1\r\n"+
                "Host: " + host + "\r\n" +
                "Connection: close\r\n\r\n");
    
  
    String line="";
    Serial.println("receiving from remote server...");
    while (client.available()) {
      line = client.readStringUntil('\r');
      
    }
    Serial.print(line);
  
    Serial.println();
    Serial.println("closing connection");
    client.stop();
  
    LastTime = millis(); 
    sum=0;
    cnt=0;
  }
  float ldrstatus = analogRead(ldrpin);
  sum = sum + ldrstatus;
 
  cnt++;
  delay(500);
}
