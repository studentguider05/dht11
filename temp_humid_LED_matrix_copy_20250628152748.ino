#include <DHT.h>
#include <DHT_U.h>
#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"


#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
ArduinoLEDMatrix matrix;

void setup() {
  dht.begin();
  matrix.begin();
}

void loop() {
  delay(1500);  // Wait for sensor data to stabilize

  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temp) || isnan(humidity)) {
    matrix.beginDraw();

    matrix.stroke(0xFFFFFFFF);
    matrix.textScrollSpeed(50);

    // add the text
    const char text[] = "   SENSOR ERROR!     ";
    matrix.textFont(Font_5x7);
    matrix.beginText(0, 1, 0xFFFFFF);
    matrix.println(text);
    matrix.endText(SCROLL_LEFT);

    matrix.endDraw();
    
  } 
  else {
    char displayText[60];
    snprintf(displayText, sizeof(displayText), "  Temp: %.1fC Hum: %.1f%%", temp, humidity);

    matrix.beginDraw();

    matrix.stroke(0xFFFFFFFF);
    matrix.textScrollSpeed(50);

    // add the text
    matrix.textFont(Font_5x7);
    matrix.beginText(0, 1, 0xFFFFFF);
    matrix.println(displayText);
    matrix.endText(SCROLL_LEFT);

    matrix.endDraw();
  }
}
