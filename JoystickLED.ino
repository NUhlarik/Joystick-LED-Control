#include "FastLED.h"

#define JOYX A0
#define JOYY A1
#define SW 3

#define DATA_PIN 7
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS 255
#define FPS 120
CRGB leds[NUM_LEDS];

int brightness;
int gHue;

void setup() {
  Serial.begin(115200);
  pinMode(JOYX, INPUT);
  pinMode(JOYY, INPUT);
  pinMode(SW, INPUT);
  Serial.print("\nStarting");
  int startup = 10;

  while(startup > 0){
    Serial.print(".");
    startup--;
    delay(333);
  }

  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  
}

void loop() {
  int xDim = analogRead(JOYX);
  int yDim = analogRead(JOYY);
  int swDim = digitalRead(SW);

  int xDimMap = map(xDim, 0, 1023, 125, 0);
  int yDimMap = map(yDim, 0, 1023, 255, 0);
  
  Serial.print(xDimMap);
  Serial.print(" ");
  Serial.print(yDimMap);
  Serial.print(" ");
  Serial.print(swDim);
  Serial.print("\n");

  int scaling = 2;

  rainbow();
  gHue = sidewaysController(xDimMap, gHue, scaling);
  brightness = brightnessController(yDimMap, brightness, scaling);
  FastLED.setBrightness(brightness);
  FastLED.show();
  FastLED.delay(1000/FPS);

}

void rainbow(){
  fill_rainbow(leds, NUM_LEDS, gHue, 7);
}

int sidewaysController(int sideways, int hue, int scaling){
  if(sideways > 70){
    hue += 4;
  }
  
  if(sideways < 54){
    hue -= 4;
  }
  
  return(hue);
  
}

int brightnessController(int vertical, int bright, int scaling){
  if(vertical > 142){
    bright += scaling;
    if(bright >= 255){
      bright = 255;
    }
  }
  
  if(vertical < 126){
    bright -= scaling;
    if(bright <= 0){
      bright = 0;
    }
  }

  return(bright);
  
}

