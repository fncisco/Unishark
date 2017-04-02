/////////////////////////////////////////////////////////////////////////////////////////////////
/* UniSHark software ,, made for Realac LaForge and Furious and Buzz Fly Module's !!
    All in 1 Firmware
    Buzz user have other options then Furious/Laforge/Realacc
  whe keep inovating if there are errors i try 2 fix them real fast ,,
  and now whe have a universal FIrmware ,
  ,lets Go !!
  added Buzz Scope and Buzz Search quad option for Furious and Realac users
  fixed some other things ,,
  Buzz 27-3-2017
*/
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#include <SPI.h>
#include <avr/pgmspace.h>

#include "Config.h"
#include "Logos.h"
#include "OSD.h"

float rssi ;
float rssi2 ;
float rssi3 ;
float rssi1_MIN = 80;
float rssi1_MAX = 300; // Auto calib stuff
float rssi2_MIN = 80;
float rssi2_MAX = 300;

uint8_t goat = 0;
uint8_t scan = 1;
uint8_t menu = 0;
uint8_t best = 0;
uint8_t memo = 0;
uint8_t selector = 4; // 4 means manual !!
uint16_t scr = 0;
uint8_t swt = 0;
uint16_t HIS1, HIS2;
uint8_t scp = 0;
/*OSD*/
#ifdef osd
uint8_t osdt;
#endif
uint16_t rssiosd1;
uint16_t rssiosd2;
uint8_t mnu = 0;
/*Favorites*/
uint8_t fav1;
uint8_t fav2;
uint8_t fav3;
uint8_t fav4;
uint8_t fav5;
uint8_t fav6;
uint8_t fav7;
uint8_t fav8;
uint8_t favselect;
/*Buttons*/
bool buttonState0 = 1;
bool buttonState1 = 1;
bool buttonState2 = 1;
uint8_t but = 0;
uint8_t sub1 = 0;
uint16_t dp;
/* Channels
    here you set you starting channel
    look below in the channelFreqTable list ch 24 = Immersion ch 1
    1-8 = 24 - 31  and Race Band ch 32 - 39
*/
uint8_t ch = 24;  //starting channel



const uint16_t channelTable[] PROGMEM = {
  // Channel 1 - 8
  0x2A05,    0x299B,    0x2991,    0x2987,    0x291D,    0x2913,    0x2909,    0x289F,    // Band A
  0x2903,    0x290C,    0x2916,    0x291F,    0x2989,    0x2992,    0x299C,    0x2A05,    // Band B
  0x2895,    0x288B,    0x2881,    0x2817,    0x2A0F,    0x2A19,    0x2A83,    0x2A8D,    // Band E
  0x2906,    0x2910,    0x291A,    0x2984,    0x298E,    0x2998,    0x2A02,    0x2A0C,  // Immersion normal
  0x281D,    0x288F,    0x2902,    0x2914,    0x2987,    0x2999,    0x2A0C,    0x2A1E,  // Immersion Raceband
  0x2609,    0x261C,    0x268E,    0x2701,    0x2713,    0x2786,    0x2798,    0x280B     // Band D / 5.3
};

// Channels in mhz
const uint16_t channelFreqTable[] PROGMEM = {
  // Channel 1 - 8
  5865, 5845, 5825, 5805, 5785, 5765, 5745, 5725, // Band A
  5733, 5752, 5771, 5790, 5809, 5828, 5847, 5866, // Band B
  5705, 5685, 5665, 5645, 5885, 5905, 5925, 5945, // Band E
  5740, 5760, 5780, 5800, 5820, 5840, 5860, 5880,  // Immersion normal
  5658, 5695, 5732, 5769, 5806, 5843, 5880, 5917,  // Immersion Raceband
  5362, 5399, 5436, 5473, 5510, 5547, 5584, 5621  // New Band D / 5300 mhz
};
uint8_t channel = 24; // set fixed channel here
uint8_t channelIndex = 0; // set index channel

#define PSTR2(x) PSTRtoBuffer_P(PSTR(x))    // just a Parse String 2 Buffer method ,, 
char PSTR2_BUFFER[30]; // adjust size depending on need.
char *PSTRtoBuffer_P(PGM_P str) {
  uint8_t c = '\0', i = 0;
  for (; (c = pgm_read_byte(str)) && i < sizeof(PSTR2_BUFFER); str++, i++) PSTR2_BUFFER[i] = c;
  PSTR2_BUFFER[i] = c;
  return PSTR2_BUFFER;
}

void turbo() { // making the switching routine faster by dropping al other routines ,, !!
  turboswitch() ;
  display.clearDisplay();
  display.drawBitmap(30, 0, hand, 64, 64, 1);
  return;
}

#include "Buzz.h"
#include "Furious.h"
#include "Realacc.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////           SETUP            /////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void setup()  // just al the setup and pins //
{
  // Pinmodes of all pins used
#ifdef osd
  Serial.begin(19200);  // forgot to turn it of
#endif
#ifdef v3
  pinMode(OLEDSW, OUTPUT);
  digitalWrite(OLEDSW, HIGH);
#endif
  pinMode(ledPin, OUTPUT);
#ifdef Realac
  pinMode(DIV1_PIN, OUTPUT);
  pinMode(DIV2_PIN, OUTPUT);
  pinMode(BUT1, INPUT);
  digitalWrite(BUT1, INPUT_PULLUP);
  pinMode(BUT2, INPUT);
  digitalWrite(BUT2, INPUT_PULLUP);
  pinMode(BUT3, INPUT);
  digitalWrite(BUT3, INPUT_PULLUP);
  buttonState0 = digitalRead(BUT1);
  buttonState1 = digitalRead(BUT2);
  buttonState2 = digitalRead(BUT3);
  favorread();
#endif
#ifdef Furious
  pinMode(DIV1_PIN, OUTPUT);
  pinMode(DIV2_PIN, OUTPUT);
  pinMode(BUT1, INPUT);
  digitalWrite(BUT1, INPUT_PULLUP);
  pinMode(BUT2, INPUT);
  digitalWrite(BUT2, INPUT_PULLUP);
  pinMode(BUT3, INPUT);
  digitalWrite(BUT3, INPUT_PULLUP);
  buttonState0 = digitalRead(BUT1);
  buttonState1 = digitalRead(BUT2);
  buttonState2 = digitalRead(BUT3);
  favorread();
#endif
#ifdef Buzz
  irrecv.enableIRIn();
  channel = EEPROM.read(1);
  delay (10);
  digitalWrite(DIV1_PIN, HIGH);
  digitalWrite(DIV2_PIN, LOW);  // setting Max4066 IC switch on right output Video 1
  digitalWrite(OSD_PIN, LOW);
  delay (100);
#endif
  pinMode (slaveSelectPin, OUTPUT);
  pinMode (spiDataPin, OUTPUT);
  pinMode (spiClockPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
#ifdef white
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
#endif
#ifdef color
  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);
#endif
  display.clearDisplay();
  display.drawBitmap(30, 0, flagy, 64, 64, 1);
  display.display();
  delay (2000);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(10, 20);
  display.print("Made By Buzz Fly");
  display.setCursor(12, 40);
  display.print(" Special made !");
  display.display();
  display.setTextSize(1);
  delay (1500);
  display.clearDisplay();
  digitalWrite(ledPin, HIGH);
  delay (20);
  channel = EEPROM.read(1);
  HISFILT = EEPROM.read(2);
  delay (10);
  digitalWrite(DIV1_PIN, HIGH);
  digitalWrite(DIV2_PIN, LOW);  // setting Max4066 IC switch on right output Video 1
  delay (100);
  test();   //  channel selector stuff //
  delay (10);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
void test () {  // setting channel true ch 1 ch 2 ch 3 of the module !
  uint8_t i;
  uint16_t channelData;
  if (channel == 48)channelData = pgm_read_word_near(channelTable + fav1);
  if (channel == 49)channelData = pgm_read_word_near(channelTable + fav2);
  if (channel == 50)channelData = pgm_read_word_near(channelTable + fav3);
  if (channel == 51)channelData = pgm_read_word_near(channelTable + fav4);
  if (channel == 52)channelData = pgm_read_word_near(channelTable + fav5);
  if (channel == 53)channelData = pgm_read_word_near(channelTable + fav6);
  if (channel == 54)channelData = pgm_read_word_near(channelTable + fav7);
  if (channel == 55)channelData = pgm_read_word_near(channelTable + fav8);
  if (channel <= 47)channelData = pgm_read_word_near(channelTable + channel);
  EEPROM.write(1, channel);
  SERIAL_ENABLE_HIGH();
  delayMicroseconds(1);
  SERIAL_ENABLE_LOW();
  SERIAL_SENDBIT0();
  SERIAL_SENDBIT0();
  SERIAL_SENDBIT0();
  SERIAL_SENDBIT1();
  SERIAL_SENDBIT0();
  // remaining zeros
  for (i = 20; i > 0; i--)
    SERIAL_SENDBIT0();

  // Clock the data in
  SERIAL_ENABLE_HIGH();
  delay(2);
  delayMicroseconds(1);
  SERIAL_ENABLE_LOW();
  SERIAL_ENABLE_HIGH();
  SERIAL_ENABLE_LOW();
  SERIAL_SENDBIT1();
  SERIAL_SENDBIT0();
  SERIAL_SENDBIT0();
  SERIAL_SENDBIT0();
  SERIAL_SENDBIT1();
  for (i = 16; i > 0; i--)
  {
    // Is bit high or low?
    if (channelData & 0x1)
    {
      SERIAL_SENDBIT1();
    }
    else
    {
      SERIAL_SENDBIT0();
    }

    // Shift bits along to check the next one
    channelData >>= 1;
  }

  // Remaining D16-D19
  for (i = 4; i > 0; i--)
    SERIAL_SENDBIT0();

  // Finished clocking data in
  SERIAL_ENABLE_HIGH();
  delayMicroseconds(1);


  digitalWrite(slaveSelectPin, LOW);   // shuting down the 5v of the spi //
  digitalWrite(spiClockPin, LOW);
  digitalWrite(spiDataPin, LOW);
}

void SERIAL_SENDBIT1()
{
  digitalWrite(spiClockPin, LOW);
  delayMicroseconds(1);

  digitalWrite(spiDataPin, HIGH);
  delayMicroseconds(1);
  digitalWrite(spiClockPin, HIGH);
  delayMicroseconds(1);

  digitalWrite(spiClockPin, LOW);
  delayMicroseconds(1);
}

void SERIAL_SENDBIT0()
{
  digitalWrite(spiClockPin, LOW);
  delayMicroseconds(1);

  digitalWrite(spiDataPin, LOW);
  delayMicroseconds(1);
  digitalWrite(spiClockPin, HIGH);
  delayMicroseconds(1);

  digitalWrite(spiClockPin, LOW);
  delayMicroseconds(1);
}

void SERIAL_ENABLE_LOW()
{
  delayMicroseconds(1);
  digitalWrite(slaveSelectPin, LOW);
  delayMicroseconds(1);
}

void SERIAL_ENABLE_HIGH()
{
  delayMicroseconds(1);
  digitalWrite(slaveSelectPin, HIGH);
  delayMicroseconds(1);
}
//////////////////////////////////////////////////////////////////////////
///////// DEXTERBOT AkA BuzzFLy !! HisTiric filter method !! ////////////
void turboswitch() {
  HIS1 = HIS1 + 1;  /// up counter for switch
  HIS2 = HIS2 + 1;
#ifdef Furious
  rssi2 = analogRead(A6); //rssi main module
  delay (25);
  rssi3 = analogRead(A7); //rssi second mouduleb
#endif
#ifdef Realac
  rssi2 = analogRead(A6); //rssi main module
  delay (25);
  rssi3 = analogRead(A7); //rssi second mouduleb
#endif
#ifdef Buzz
  rssi2 = analogRead(A1); //rssi main module
  delay (25);
  rssi3 = analogRead(A2); //rssi second mouduleb
#endif
  if (rssi2 > rssi1_MAX ) rssi1_MAX = rssi2;
  if (rssi3 > rssi2_MAX ) rssi2_MAX = rssi3;
  if (rssi2 < rssi1_MIN ) rssi1_MIN = rssi2;
  if (rssi3 < rssi2_MIN ) rssi2_MIN = rssi3;
  if (rssi2 > rssi3 )HIS2 = 0; // if main module signal is higer then second module
  if (rssi2 < rssi3 )HIS1 = 0; // if second module signal is higer then main module
  /// his  buffer set  on default 15 ,,
  if (HIS1 > HISFILT)swt = 0;  //if main module has higer signal
  else if (HIS2 > HISFILT)swt = 1;
  if (swt == 0 ) {
    digitalWrite(DIV2_PIN, LOW);
    delay (NOBLACK);
    digitalWrite(DIV1_PIN, HIGH);
    digitalWrite(ledPin, LOW);
    display.setCursor(72, 40);
    if (buttonState1 != LOW && selector == 4) {
      display.print("RX ON 1");
      display.setCursor(75, 58);
      display.print("<<<<");
    }
    display.display();
  }
  if  (swt == 1) {
    digitalWrite(DIV1_PIN, LOW);
    delay (NOBLACK);
    digitalWrite(DIV2_PIN, HIGH);
    digitalWrite(ledPin, HIGH);
    display.setCursor(72, 40);
    if (buttonState1 != LOW && selector == 4) {
      display.print("RX ON 2");
      display.setCursor(98, 58);
      display.print(">>>>");
    }
    display.display();
  }
}


void autocalib() {  // autocalibrating continous when on !
#ifdef Furious
  rssi2 = analogRead(A6); //rssi main module
  delay (25);
  rssi3 = analogRead(A7); //rssi second moudule
#endif
#ifdef Realac
  rssi2 = analogRead(A6); //rssi main module
  delay (25);
  rssi3 = analogRead(A7); //rssi second mouduleb
#endif
#ifdef Buzz
  rssi2 = analogRead(A0); //rssi main module
  delay (25);
  rssi3 = analogRead(A1); //rssi second mouduleb
  rssi2 = constrain(rssi2, rssi1_MIN, rssi1_MAX);
  rssi3 = constrain(rssi3, rssi2_MIN, rssi2_MAX);
#endif
  if (rssi2 > rssi1_MAX ) rssi1_MAX = rssi2;
  if (rssi3 > rssi2_MAX ) rssi2_MAX = rssi3;
  if (rssi2 < rssi1_MIN ) rssi1_MIN = rssi2;
  if (rssi3 < rssi2_MIN ) rssi2_MIN = rssi3;
  rssi2 = map(rssi2, rssi1_MAX, rssi1_MIN, 50, 2); //rssi mapped
  rssi3 = map(rssi3, rssi2_MAX, rssi2_MIN, 50, 2); //rssi mapped
  //ZzzzzzzzzzzzzzzzzzzzzzzaA  if (rssi2 < SIG_ALARM || rssi3 < SIG_ALARM )sigalarm();  //triggers sig alarm !
}


