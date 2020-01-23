#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 18
#define BRIGHTNESS  128
#define LED_TYPE    WS2811
#define LED_PIN     3 // AT Tiny 85
#define COLOR_ORDER GRB

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() {
  delay( 3000 ); // power-up safety delay
  //FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );  

  leds[0] = CRGB::White;
  leds[1] = CRGB::White;
  leds[2] = CRGB::White;
  leds[3] = CRGB::Green; // Red
  leds[4] = CRGB::White;
  leds[5] = CRGB::Green; // Red
  leds[6] = CRGB::Green; // Red
  leds[7] = CRGB::Green; // Red
  leds[8] = CRGB::Green; // Red
  leds[9] = CRGB::White;
  leds[10] = CRGB::White;
  leds[11] = CRGB::White; // Red
  leds[12] = CRGB::White;
  leds[13] = CRGB::White;
  leds[14] = CRGB::Green; // Red
  leds[15] = CRGB::White;
  leds[16] = CRGB::White;
  leds[17] = CRGB::White;

  FastLED.show();
}

void loop() { 

}
