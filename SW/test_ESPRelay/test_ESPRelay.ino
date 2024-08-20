/* Test for LaskaKit ESPrelay
 * 
 * Board:   
 *
 * Libraries:
 * Dallas Temperature:  
 * Adafruit NeoPixel: https://github.com/adafruit/Adafruit_NeoPixel
 * 
 * Email:podpora@laskakit.cz
 * Web:laskakit.cz
 */
 

#include <Wire.h>
#include "WiFi.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_NeoPixel.h>

#define RELE 0
#define IN 2
#define DS18B20 1

OneWire oneWire(DS18B20);
DallasTemperature sensors(&oneWire);

#define BRIGHTNESS 10
#define LED_PIN 3
#define NUM_LED 1
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_LED, LED_PIN, NEO_GRB + NEO_KHZ800);

const char * ssid = "ssid";
const char * wifipw = "wifipw";

void setup() {
  pinMode(RELE, OUTPUT);
  pinMode(IN, INPUT);
  Serial.begin(115200);
  Wire.begin(8, 10);
  sensors.begin();
  pixels.begin();
  pixels.setBrightness(BRIGHTNESS);

  pixels.setPixelColor(0, pixels.Color(255, 0, 0)); // R, G, B
  pixels.show();

  int ii = 0;
  WiFi.begin(ssid, wifipw);
  Serial.println("Connecting Wifi");
  while ((WiFi.status() != WL_CONNECTED) && (ii < 50)) {
    Serial.print(".");
    pixels.setPixelColor(0, pixels.Color(255, 0, 0)); // R, G, B
    pixels.show();
    delay(100);
    pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // R, G, B
    pixels.show();
    delay(100);
    ii++;
  }
  Serial.println();
  
  if (WiFi.status() == WL_CONNECTED){
    Serial.println(WiFi.localIP());
    pixels.setPixelColor(0, pixels.Color(0, 255, 0)); // R, G, B
    pixels.show();
  }else{
    Serial.println("Nepripojeno k WiFi");
    pixels.setPixelColor(0, pixels.Color(255, 0, 0)); // R, G, B
    pixels.show();
  }

}

void loop() {
  sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0);
  Serial.print(temperatureC);
  Serial.println("ºC");
  Serial.println(digitalRead(IN));
  digitalWrite(RELE, HIGH);
  delay(1000);
  digitalWrite(RELE, LOW);
  delay(1000);

}
