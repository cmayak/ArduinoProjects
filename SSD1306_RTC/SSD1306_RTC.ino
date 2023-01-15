#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RTClib.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 4 //PIN 4
#define BAUD_RATE 57600
#define DEVICE_COUNT 2

byte address_array[DEVICE_COUNT];
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT,&Wire,OLED_RESET);
RTC_DS1307 rtc;

void get_hardware_addr(){
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

void testPrint(int txt_size,char Str[],int val){
  display.clearDisplay();
  display.setTextSize(txt_size);
  display.setTextColor(SSD1306_WHITE);
  display.print(Str);
  display.print(val);
  display.display();
  delay(100);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUD_RATE);
  rtc.begin();
  if(!rtc.isrunning()){
    rtc.adjust(DateTime(2023,1,12,4,48,0));
  }
  get_hardware_addr();
  if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C)){
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.begin(SSD1306_SWITCHCAPVCC,address_array[0]);
  
  //testPrint(2,"HELLO");
}
int i=0;
void loop() {
  // put your main code here, to run repeatedly:
  //testPrint(2,"HELLO: ");
  DateTime now = rtc.now();
  //Serial.print(now.year(),DEC);
  //Serial.print(now.month(),DEC);
  //Serial.println();
  display.setCursor(0, 0);
  testPrint(1,"HELLO: ",now.year());
  i++;
}
