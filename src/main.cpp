#include <Arduino.h>
#include <HPMA115S0.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel_ZeroDMA.h>
#include <Adafruit_BusIO_Register.h>

#define PIN 5
#define NUM_PIXELS 1

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_NeoPixel_ZeroDMA  Pixels(NUM_PIXELS, PIN, NEO_GRB);

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire, OLED_RESET);
HPMA115S0 hpma115S0(Serial1);


//Create an instance of the hpma115S0 library

#define pm25Out A0 
#define redLEDpin 13

uint32_t red = 0xFF0000;
uint32_t green = 0x00FF00;
uint32_t blue = 0x0000FF;
uint32_t off = 0x000000;
uint32_t yellow = 0xFFFF00;
uint32_t ledcolor[5];
int activecolor = 2;
 
int inByte = 0;         // incoming serial byte
boolean LED_data = false;
boolean  LED_CLEAR = true;


int fcount;
float PM25;
float PM10;

void errors(char *str)
{
  Serial.print("error: ");
  Serial.println(str);
  
  // red LED indicates error
  digitalWrite(redLEDpin, HIGH);
  Pixels.setPixelColor(0,red);
  Pixels.show();
  delay(30);
  
 // while(1);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
  //Pixels.begin();
  //Pixels.setBrightness(255);
  //Pixels.show();
  ledcolor[0] = off;
  ledcolor[1] = red;
  ledcolor[2] = green;
  ledcolor[3] = blue;
 // Pixels.setPixelColor(0,0x6100FF);
 // Pixels.show();

  pinMode(pm25Out, OUTPUT); 
  
  digitalWrite(redLEDpin, HIGH);
  
  
  digitalWrite(redLEDpin, LOW);

  delay(5000);
  Serial.println("Starting...");

  hpma115S0.Init();
  hpma115S0.StartParticleMeasurement();

  Serial.println("OLED test");

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32

  Serial.println("OLED begun");

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(1000);

  // Clear the buffer.
  display.clearDisplay();
  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(1, 0);
  display.println(F("Opacity Sensor"));
  display.display();

  Serial.println("IO test");
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned int pm2_5, pm10;
  digitalWrite(redLEDpin, HIGH);
  display.clearDisplay();
 /// display.setTextSize(1); // Draw 2X-scale text
 // display.setCursor(1, 0);
  //display.println("Opacity Sensor");
  if (hpma115S0.ReadParticleMeasurement(&pm2_5, &pm10)) {
    display.clearDisplay();
    display.setCursor(1, 0);
    display.setTextSize(2);
    Serial.println("PM 2.5: " + String(pm2_5) + " ug/m3" );
    Serial.println("PM 10: " + String(pm10) + " ug/m3" );
    display.println(F("PM 2.5: "));
    display.println(String(pm2_5) + " ug/m3");
   // Pixels.setPixelColor(0,ledcolor[0]);
   // Pixels.show();
    delay(100);
    //Pixels.setPixelColor(0,ledcolor[activecolor]);
    //Pixels.show();
//if (pm2_5>=300){
//      activecolor = 2;
       //Pixels.setPixelColor(0,ledcolor[activecolor]);
//      }
//    else{
//      activecolor = 3;
      // Pixels.setPixelColor(0,blue);
//      }
   
 //  Pixels.setPixelColor(0,ledcolor[activecolor]);
 //  Pixels.show();
 //  Serial.print("led color ");
//   Serial.println(activecolor);
 //  Serial.println (ledcolor[activecolor]);
          
//     analogWrite(pm25Out, map(PM25,0,1000,0,1023));
  }
  display.display();
  delay(1000);
}