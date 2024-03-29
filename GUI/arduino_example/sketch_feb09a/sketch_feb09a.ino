/*
   라이브러리를 설치 하고 시작해야 한다.
   1. https://github.com/adafruit/Adafruit_Sensor
   2. https://www.arduino.cc/reference/en/libraries/dht-sensor-library/
   3. json 라이브러리 arduinojson 을 검색 설치 
*/

#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

StaticJsonDocument<300> doc;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < 360; i++)
  {
  doc["x"] = i;
  doc["y"] = i;
  doc["z"] = 200*sin(radians(i/2));
  doc["ex"] = 360;
  doc["ey"] = 360;
  doc["airx"] = float(i+1)/2;
  doc["airy"] = i;
  doc["airz"] = float(i+1)/3;
  doc["pitch"] =-float(i)/150;
  doc["roll"] = 0;//-float(i)/100;
  doc["yaw"] = -float(i)/150;
  doc["t"] = 17;
  doc["h"] = 40.5;
  doc["at"] = 1013;
  serializeJson(doc, Serial);
  Serial.println();
  }
  

  delay(100);
}
