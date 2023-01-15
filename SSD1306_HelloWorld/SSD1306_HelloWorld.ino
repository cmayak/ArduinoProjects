#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 4 //PIN 4
#define BAUD_RATE 57600
#define DEVICE_COUNT 1

byte address_array[DEVICE_COUNT];
Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT,&Wire,OLED_RESET);

void get_hardware_addr(){ //Function searches for Hardware addresses on I2c wire for displays address
  Wire.begin();
  while(!Serial);
  int n=0;
  for(byte addr=1;addr<127;addr++){
    Wire.beginTransmission(addr);
    byte error = Wire.endTransmission();
    if(error==0){
      address_array[n] = addr;
      n++;
    }
  }
}

void testPrint(int txt_size,char Str[],int val){ // Function Changes text size, string input, int value
  display.clearDisplay();
  display.setTextSize(txt_size);
  display.setTextColor(SSD1306_WHITE);
  display.print(Str);
  display.print(val);
  display.display();
  delay(100);
}

void setup() {
  Serial.begin(BAUD_RATE);
  get_hardware_addr();
  if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C)){
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.begin(SSD1306_SWITCHCAPVCC,address_array[0]);
  testPrint(2,"HELLO");
}
int i=0;
void loop() {
  testPrint(2,"HELLO WORLD: ", i);
  display.setCursor(0, 0);
  i++;
}
