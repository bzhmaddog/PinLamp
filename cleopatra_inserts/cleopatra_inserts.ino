#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 32
#define BRIGHTNESS  100
#define LED_TYPE    WS2811
//#define LED_PIN     3 // AT Tiny 85
#define LED_PIN     5 // Arduino UNO
#define COLOR_ORDER GRB

// Define the array of leds
CRGB leds[NUM_LEDS];

long attract[] = {
0,
2147483648,
3222798336,
3762028544,
4034797570,
4177485827,
4261404675,
4294963207,
4294965263,
4294966303,
4294967295,
2147483647,
1072168959,
532938751,
260169725,
117481468,
33562620,
4088,
2032,
992
};

int nbFrames = 20; // WTF arduino why can't you provide a count method
int frameIndex = 0;

void setup() {
  //Serial.begin(9600);

  //Serial.print(nbFrames);
  //Serial.print("\n");
  
  delay(1000); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );

  for (int i = 0 ; i <= NUM_LEDS - 1 ; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();

  delay(50);

  for (int i = 0 ; i <= NUM_LEDS - 1 ; i++) {
    leds[i] = CRGB::White;
    FastLED.show();
    delay(10);
  }

  delay(50);

  for (int i = NUM_LEDS - 1 ; i >= 0 ; i--) {
    leds[i] = CRGB::Black;
    FastLED.show();
    delay(10);
  }

  delay(1000);
}

boolean isLit(long data, int bit) {
  int s = sizeof(data)*8 - 1; //Swap bits
  return bitRead(data, s - bit) == 1;
}

void loop() {

  //Serial.print(frameIndex);
  //Serial.print(" -> ");

  long data = attract[frameIndex];

  //Serial.print(data, BIN);
  //Serial.print("\n");
  //Serial.print(sizeof(data)*8 - 1);
  //Serial.print("\n");

  for( int i = 0 ; i <= NUM_LEDS - 1 ; i++) {
    //Serial.print(i);
    //Serial.print(":");
    if (isLit(data,i)) {
      //Serial.print("1,");
      leds[i] = CRGB::White;
    } else {
      //Serial.print("0,");
      leds[i] = CRGB::Black;
    }
  }
    FastLED.show();  

  //Serial.print("\n");
  

  frameIndex++;
  if (frameIndex >= nbFrames) {
    frameIndex = 0;
    delay(50);
  }

  delay(20);

  
  /*int r = random(NUM_LEDS);

    for (int i = 0 ; i <= NUM_LEDS -1 ; i++){
    if (i == r) {
      leds[i] = CRGB::White;
    } else {
      leds[i] = CRGB::Black;
    }
    }
    FastLED.show();
    delay(500);*/
}
