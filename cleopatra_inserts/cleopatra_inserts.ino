#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 32
#define BRIGHTNESS  50
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
992, // UP
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
992,
2032,
4088,
8188,
33562620,
117481468,
260169725,
532938751,
1072168959,
2147483647,
4294967295,
4294966303,
4294965263,
4294963207,
4294959107,
4261404675,
4177485827,
4034797570,
3762028544,
3222798336,
2147483648, // Down
0,
0,
0,
0,
2,
27,
31,
63,
127,
2080375039,
4261413119,
4293919231,
4294935039,
4294935551,
4294939647,
4294942719,
4294959103,
4294967295,
4294967293,
4294967268,
4294967264,
4294967232,
4294967168,
2214592256,
33554176,
1048320,
1048064,
32256,
31744,
27648,
24576,
8192, // Right
8192,
8192,
8192,
27648,
31744,
32256,
1048064,
33554176,
2214592384,
4294967168,
4294967232,
4294967264,
4294967268,
4294967293,
4294967295,
4294959103,
4294939647,
4294935551,
4293919231,
4261413119,
2080374911,
127,
63,
31,
27,
2, // Left
0,
0,
0,
0,
0,
2147483648,
2147483650,
2147483651,
2147483655,
2147483663,
2147483679,
2147483711,
2147483775,
2147483903,
2147484159,
2147484671,
2147485695,
2147487743,
2147491839,
2147508223,
2147516415,
32767,
32765,
32764,
32760,
32752,
32736,
32704,
32640,
32512,
32256,
31744,
30720,
28672,
24576,
8192, //Around
0,
0,
0,
0,
//0,
//2147483648,
//2,
//1,
//4,
//8,
//16,
//32,
//64,
//128,
//256,
//512,
//1024,
//2048,
//4096,
//16384,
//8192,
//2147483648,
//3222798336,
//3762028544,
//4034789376,
//4177461248,
//4261380096,
//4294938628,
//2147454980,
//1072142348,
//532913180,
//260152892,
//117481340,
//33562620,
//4088,
//2032,
//992,
//448,
//128,// Around bis
//0,
//0,
//0,
//0,
};

int nbFrames = 152; // WTF arduino why can't you provide a count method
int frameIndex = 0;

void setup() {
  
  delay(100); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );

  for (int i = 0 ; i <= NUM_LEDS - 1 ; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
  delay(50);

  for (int i = 0 ; i <= NUM_LEDS - 1 ; i++) {
    leds[i] = CRGB::White;
  }
  FastLED.show();
    
  delay(1000);

  for (int i = NUM_LEDS - 1 ; i >= 0 ; i--) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();  

  delay(1000);
}

boolean isLit(long data, int bit) {
  int s = sizeof(data)*8 - 1; //Swap bits
  return bitRead(data, s - bit) == 1;
}

void loop() {

  long data = attract[frameIndex];

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


  frameIndex++;
  if (frameIndex >= nbFrames) {
    frameIndex = 0;
    delay(50);
  }

  delay(25);
  //delay(1000);

  
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
