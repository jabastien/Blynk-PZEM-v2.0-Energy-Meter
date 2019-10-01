/*************************************************************
  https://www.hackster.io/PDAControl/meter-pzem-004-esp8266-platform-iot-blynk-app-0d4973

  PZEM004T library by olehs                          https://github.com/olehs/PZEM004T

  Complete Tutorial English:   http://pdacontrolen.com/meter-pzem-004-esp8266-platform-iot-blynk-app/

  PZem 004T V2.0 to nodemcu

  5v to vin
  RX to TX
  TX to RX
  GND to GND

 

/* Comment this out to disable prints and save space */

//#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <PZEM004T.h> //https://github.com/olehs/PZEM004T
PZEM004T pzem(&Serial);                                        /// use Serial
IPAddress ip(192, 168, 1, 1);

float voltage_blynk = 0;
float current_blynk = 0;
float power_blynk = 0;
float energy_blynk = 0;


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "your blynk auth code here";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "wifi username here";                    //WiFi Credential
char pass[] = "wifi password here";              //WiFi Password

unsigned long lastMillis = 0;


void setup()
{
  //No  Debug console
  Serial.begin(9600);              // Note : Do not use Serial0 port, for serial debugging!

  pzem.setAddress(ip);
  Blynk.begin(auth, ssid, pass, IPAddress(xxx, xxx, xx, xxx), 8080);

}

void loop()
{
  Blynk.run();

  float v = pzem.voltage(ip);
  if (v <= 0.0) v = 0.0; {
  Serial.print("Voltage: ");
  Serial.print(v);
  Serial.println("V; ");
  
    voltage_blynk = v;
  }  
  

  float i = pzem.current(ip);
  
  if (i <= 0.0) i = 0.0; {
    Serial.print("Current: ");
    Serial.print(i);
    Serial.println("A; ");
    current_blynk = i;
  }


  float p = pzem.power(ip);

  if (p <= 0.0) p = 0.0; {
    Serial.print("Watts: ");
    Serial.print(p);
    Serial.println("W; ");
    power_blynk = p;
  }

  float e = pzem.energy(ip);

  if (e <= 0.0) e = 0.0; {
    Serial.print("Energy: ");
    Serial.print(e);
    Serial.println("Wh; ");
    energy_blynk = e;
  }

  Serial.println();
  Serial.println("========================");
  Serial.println();

  //delay(1000);

  //Publish data every 10 seconds (10000 milliseconds). Change this value to publish at a different interval.
  if (millis() - lastMillis > 10000) {
    lastMillis = millis();

    Blynk.virtualWrite(V1, voltage_blynk);
    Blynk.virtualWrite(V2, current_blynk  );
    Blynk.virtualWrite(V3, power_blynk);
    Blynk.virtualWrite(V4, energy_blynk  );
    Blynk.virtualWrite(V5, lastMillis  );

  }

}
