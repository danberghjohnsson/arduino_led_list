#include <Adafruit_NeoPixel.h>

static const int LEDS = 360;
static const int PIN = 10;


Adafruit_NeoPixel list = Adafruit_NeoPixel(LEDS, PIN, NEO_GRB);

int delay_time = 800;
// Gamingstation 80
int hue_step = 80; 
//Gamingstation 800
// 5m slinga = 80
float bright_slowdown = 100;
// Gamingstatin 1
int bright_max = 5;
// Gaming 100


uint16_t colour_hue = 0;
uint8_t bright_phase = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  
  list.begin();
  list.clear();

  list.show();
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, HIGH);

    shiftLeft();  
    //list.show();
    
    //delay(delay_time);
    int bright = list.sine8(bright_phase/bright_slowdown) * bright_max / 255;
    list.setPixelColor(0, list.ColorHSV(colour_hue, 255, bright));    
    list.show();
    
    delay(delay_time);  
    
    colour_hue = colour_hue + hue_step;  
    bright_phase = bright_phase + 1;
}

void shiftLeft() {
  for(int i=LEDS-1;i>0;i--) {
    uint32_t rgb = list.getPixelColor(i-1);
    list.setPixelColor(i, rgb);
  }
  list.setPixelColor(0, list.Color(0, 0, 0));  
}

void slide(int fromred, int fromgreen, int fromblue, 
  int tored, int togreen, int toblue, int delay_time) {
  for(int i=0;i<LEDS;i++) {
    
    int red = fromred + (tored-fromred)*i/60;
    int green = fromgreen + (togreen-fromgreen)*i/60;
    int blue = fromblue + (toblue-fromblue)*i/60;
    list.setPixelColor(i, list.Color(red, green, blue));
  }
  list.setPixelColor(0, list.Color(0, 0, 0));
  list.show();
}


  
