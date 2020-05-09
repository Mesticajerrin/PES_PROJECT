/*Circuit:
 - Arduino Nano 33 BLE Board

Reading HTS221 Sensor

 Group:3
 Babar Bashir
 Simi George 
 Deepa Gopi
 Neethu Joseph

*/

#include"Air_Quality.h"
#include"Arduino.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

AirQuality airqualitysensor;
int current_quality =-1;
const int pin19 = A0;   // input pin
//const int pin20 = A1;   // output pin
const int ledPin3 = 24;   // output pin
String apiKey="AXF5A14LOCS6425F"; 
 char* ssid="D-Link_DIR-600M";
 char* password="Ahanaamruth04";
const char* server="api.thingspeak.com";
WiFiClient client;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Serial.println();
  Serial.print("connecting to");
  Serial.println(ssid);
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED){
    delay (500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("wifi connected");
  Serial.println(WiFi.localIP());
  airqualitysensor.init(A0);
  pinMode(24, OUTPUT);
  }
  

 // pinMode(D2,OUTPUT);
 


void loop() {
  // put your main code here, to run repeatedly:

  current_quality=airqualitysensor.slope();
    if (current_quality >= 0)// if a valid data returned.
    {
        if (current_quality ==0){
           // Serial.println("High pollution! Force signal active");
            Serial.println("LED ON");
            digitalWrite(ledPin3, LOW);
        }
            
        else if (current_quality == 1){
         // Serial.println("High pollution!");
            Serial.println("LED ON");
            digitalWrite(ledPin3, LOW);
        }
            
        else if (current_quality == 2){
           //Serial.println("Low pollution!");
            Serial.println("LED OFF");
            digitalWrite(ledPin3, HIGH);
        }
            
        else if (current_quality == 3){
          //Serial.println("Air fresh");
            Serial.println("LED OFF");
            digitalWrite(ledPin3, HIGH);
        }
     
    }

//ISR(TIMER2_OVF_vect)
//AttachInterrupt()
//{
    //if(airqualitysensor.counter==122)//set 2 seconds as a detected duty
    if(airqualitysensor.counter==61)//set 2 seconds as a detected duty
    {
        airqualitysensor.last_val=airqualitysensor.first_val;
        airqualitysensor.first_val=analogRead(A0);
        airqualitysensor.counter=0;
        airqualitysensor.timer_index=1;
       // PORTB=PORTB^0x20;
    }
    else
    {
        airqualitysensor.counter++;
    }
//}

     
     
     delay(100);

     if(client.connect(server,80)){
      String postStr=apiKey;
      postStr+="andfield1=";
      postStr+=String(A0);
      client.print("POST/update HTTP/1.1\n");
      client.print("Host:api.thingspeak.com\n");
      client.print("Connection:close\n");
/*      client.print("X-THINGSPEAKAPI:"apiKey+"\n");*/
      client.print("Content-Type:application/x/www/form/urlencoded\n");
      client.print("Content-Length:");
      client.print(postStr.length());
      client.print("\n\n");
      client.print(postStr);
     }
     client.stop();  
     
      

}
