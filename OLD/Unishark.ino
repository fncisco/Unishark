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
#define Realac  // Realac // Furious// Buzz     // for Ubad = LaForge select Realac !
//#define v1  //v1//v3  define one if used for furious
#define osdoff // osd // osdoff for Minimosd mod !!
#define white // color // white  // oled white or 2 color versions 
////////////////////////////////////////////////////////////////////////////////////////////////
uint8_t NOBLACK = 10; // stil Beta Value !!
uint8_t HISFILT = 10; // setting set in menu
#define SIG_ALARM 20 // signal alarm treshold ,, between 0-50  // works onley on PIEZO enabled Modules ,, 
#define screentime 100
/////////////////////////////////////////////////////////////////
#ifdef Furious
#ifdef v1
#define BUT1 10 // 
#define BUT2 8 // Buttons pins !?! 
#define BUT3 3 // 
#endif
#ifdef v3
#define BUT1 10 // 
#define BUT2 8 // Buttons pins !?! 
#define BUT3 3 // 
#define sp1 12 // 
#define sp2 13 // Fatsharky pins !?! 
#define sp3 14 // 
#define OLEDSW  29//
#endif
#endif
#ifdef Realac
#define BUT1 2 // 
#define BUT2 3 // Buttons pins !?! 
#define BUT3 4 //  
#endif
#ifdef Buzz
#define VOLT_PIN  A3
#define RECV_PIN  2
#define DIV1_PIN  5
#define DIV2_PIN  6
#define OSD_PIN  8
#define Ircode1 0x17B4A228   // IR LOCK OFF
#define Ircode2 0x1AB4A6E1   // IR LOCK ON
#define Ircode3 0x967BB80C    // CH UP
#define Ircode4 0x937BB355  // CH DOWN
#define Ircode5 0x940EAE71 // SCAN
#define Ircode6 0x970EB328 // Search RADAR 
#define Ircode7 0x971BB598  // Scope
#define Ircode11 0x530DB67C
#define Ircode22 0x560DBB35
#define Ircode33 0xD1D4CC60
#define Ircode44 0xCED4C7A9
#define Ircode55 0x58B59A1D
#define Ircode66 0x5BB59ED4
#define Ircode77 0x5BC2A144
float rssi ;
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////
float rssi2 ;
float rssi3 ;
float rssi1_MIN = 80;
float rssi1_MAX = 300; // Auto calib stuff
float rssi2_MIN = 80;
float rssi2_MAX = 300;
uint8_t goat = 0;
// DO Not TOuCH BelOw If not Knowing what you are doing !!
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#include <SPI.h>
#include <avr/pgmspace.h>
#ifdef Furious
#define spiDataPin A3
#define slaveSelectPin A2
#define spiClockPin A1
#define ledPin 13
#define DIV1_PIN  6
#define DIV2_PIN  5
#endif
#ifdef Realac
#define spiDataPin 10
#define slaveSelectPin 11
#define spiClockPin 12
#define ledPin 13
#define DIV1_PIN  14
#define DIV2_PIN  15
#define PIEZO  6
#endif
#ifdef Buzz
#define ledPin 13
#define spiDataPin 10
#define slaveSelectPin 11
#define spiClockPin 12
#include <IRremote.h>
IRrecv irrecv(RECV_PIN);
decode_results results;
uint16_t volt ;
#endif
#include <EEPROM.h>
uint8_t scan = 1;
uint8_t menu = 0;
uint8_t best = 0;
uint8_t memo = 0;
uint8_t selector = 4; // 4 means manual !!
uint16_t scr = 0;
uint8_t swt = 0;
uint16_t HIS1, HIS2;
uint8_t scp = 0;
//////////////////////////
uint16_t rssiosd1;
uint16_t rssiosd2;
#ifdef osd
uint8_t osdt;
#endif
uint8_t mnu = 0;
/////////////////////////////  new favo part !
uint8_t fav1;
uint8_t fav2;
uint8_t fav3;
uint8_t fav4;
uint8_t fav5;
uint8_t fav6;
uint8_t fav7;
uint8_t fav8;
uint8_t favselect;
////////////////////////////////
bool buttonState0 = 1;
bool buttonState1 = 1;
bool buttonState2 = 1;
uint8_t but = 0;
uint8_t sub1 = 0;
uint16_t dp;
// Channels
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint8_t ch = 24;  // here you set you starting channel ,, look below in the channelFreqTable list ch 24 = Immersion ch 1 ,  1-8 = 24 - 31  and Race Band ch 32 - 39
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////// MAIN LOGO IMAGE //////////////////////////////////////////////////////////////////////////////////////

const unsigned char border [] PROGMEM = {
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xF7, 0xFF, 0xFF, 0xEF, 0xFF, 0x7F, 0xBF, 0x7B, 0xDE, 0xFD, 0xFE, 0xFF, 0xF7, 0xFF, 0xFF, 0xEF,
  0xF8, 0xF9, 0xF9, 0xF3, 0xF7, 0x3F, 0x3F, 0x71, 0x9C, 0xF8, 0xFC, 0xCF, 0xCF, 0x9F, 0x9F, 0x1F,
  0xFC, 0x1C, 0x7C, 0x71, 0xF1, 0x1F, 0x1F, 0x21, 0x8C, 0xB8, 0xF8, 0x8F, 0x8E, 0x3E, 0x38, 0x3F,
  0xE6, 0x00, 0x0C, 0x38, 0x70, 0x0E, 0x06, 0x00, 0x08, 0x10, 0x70, 0x1E, 0x18, 0x38, 0x00, 0x67,
  0xF0, 0x00, 0x00, 0x08, 0x18, 0x02, 0x02, 0x00, 0x00, 0x00, 0x60, 0x18, 0x10, 0x60, 0x00, 0x1F,
  0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F,
  0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
  0xF1, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xCF,
  0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F,
  0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
  0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF,
  0xF1, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x8F,
  0xFC, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x3F,
  0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
  0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF,
  0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07,
  0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F,
  0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
  0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF,
  0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F,
  0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF,
  0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F,
  0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF,
  0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F,
  0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F,
  0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F,
  0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF,
  0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F,
  0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F,
  0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07,
  0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF,
  0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFF,
  0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF,
  0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F,
  0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F,
  0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F,
  0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F,
  0xC3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xC3,
  0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF,
  0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F,
  0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF,
  0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F,
  0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF,
  0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF,
  0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F,
  0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F,
  0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F,
  0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x3F,
  0xF1, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x8F,
  0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF,
  0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
  0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F,
  0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x8F,
  0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
  0xFC, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x3F,
  0xF8, 0x00, 0x06, 0x00, 0x18, 0x0E, 0x08, 0x00, 0x00, 0x10, 0x70, 0x00, 0x10, 0x00, 0x00, 0x1F,
  0xE6, 0x00, 0x1C, 0x00, 0x70, 0x1E, 0x08, 0x10, 0x08, 0x10, 0x78, 0x00, 0x18, 0x00, 0x00, 0x67,
  0xFC, 0x1C, 0x7C, 0x01, 0xF1, 0x1F, 0x1C, 0x31, 0x8C, 0x38, 0xF8, 0x8C, 0x0E, 0x36, 0x38, 0x3F,
  0xF8, 0xF9, 0xF8, 0x73, 0xF3, 0xBF, 0x3C, 0x79, 0x9C, 0x38, 0xFD, 0xCF, 0x8F, 0x9F, 0x9F, 0x1F,
  0xF7, 0xFF, 0xFF, 0xEF, 0xFF, 0xFF, 0xBD, 0x7B, 0xDE, 0xBD, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xEF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

const unsigned char flagy [] PROGMEM = {   // Main logo ,, //
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x40, 0x00,
  0x00, 0x03, 0xC0, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x07, 0xC0, 0x38, 0x00, 0x01, 0xC0, 0x00,
  0x00, 0x07, 0xC0, 0x78, 0x06, 0x01, 0xC0, 0x00, 0x00, 0x07, 0xC3, 0xFE, 0x3F, 0x81, 0xC0, 0x00,
  0x00, 0x07, 0xCF, 0xFF, 0xFF, 0xF1, 0xC0, 0x00, 0x00, 0x07, 0xFF, 0xFE, 0x3F, 0xF9, 0xC0, 0x00,
  0x00, 0x07, 0xFF, 0xFC, 0x3F, 0xFF, 0xC0, 0x00, 0x00, 0x07, 0xFF, 0xF8, 0x1F, 0xFF, 0xC0, 0x00,
  0x00, 0x07, 0x9F, 0xF8, 0x9F, 0xFF, 0xC0, 0x00, 0x00, 0x03, 0x9F, 0xFB, 0xEF, 0xFC, 0xC0, 0x00,
  0x00, 0x03, 0x9F, 0xF7, 0xEF, 0xF8, 0xC0, 0x00, 0x00, 0x03, 0x8F, 0xEF, 0xF7, 0xF8, 0xC0, 0x00,
  0x00, 0x03, 0x87, 0xCF, 0xF3, 0xF0, 0xC0, 0x00, 0x00, 0x03, 0x80, 0x1F, 0xF8, 0x00, 0xC0, 0x00,
  0x00, 0x03, 0x83, 0x3F, 0xFC, 0x00, 0xC0, 0x00, 0x00, 0x03, 0xC3, 0xFF, 0xFF, 0x80, 0xC0, 0x00,
  0x00, 0x01, 0xE3, 0xFF, 0xFF, 0xC1, 0xC0, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xF7, 0x80, 0x00,
  0x00, 0x01, 0xFF, 0xF7, 0xEF, 0xFF, 0x80, 0x00, 0x00, 0x01, 0xFF, 0xEF, 0xF7, 0xFF, 0x80, 0x00,
  0x00, 0x18, 0xFF, 0xEF, 0xF7, 0xFF, 0x90, 0x00, 0x00, 0x7C, 0xFF, 0xE4, 0x27, 0xFF, 0x3E, 0x00,
  0x01, 0xFE, 0xFF, 0xE3, 0xC7, 0xFF, 0x7F, 0x80, 0x07, 0xFF, 0x7F, 0x80, 0x01, 0xFE, 0xFF, 0xE0,
  0x3F, 0xFF, 0xFF, 0x39, 0x9C, 0xFC, 0xFF, 0xFC, 0x7F, 0xFF, 0xFF, 0x65, 0xA6, 0xFF, 0xFF, 0xFE,
  0x7F, 0xFF, 0xFF, 0xF6, 0x6F, 0xFF, 0xFF, 0xFE, 0x3F, 0xFF, 0xFF, 0xF2, 0x4F, 0xFF, 0xFF, 0xFC,
  0x1F, 0xFF, 0xFF, 0xFA, 0x5F, 0xFF, 0xFF, 0xF8, 0x1F, 0xFF, 0x3F, 0xFE, 0x7F, 0xFC, 0xFF, 0xF8,
  0x1F, 0xF0, 0x7F, 0xFC, 0x3F, 0xFE, 0x0F, 0xF8, 0x1F, 0x30, 0xFF, 0xE3, 0x87, 0xFF, 0x0C, 0xF8,
  0x06, 0x11, 0xFF, 0xFF, 0xFF, 0xFF, 0x88, 0xE0, 0x07, 0x19, 0xF8, 0x7F, 0xFE, 0x7F, 0x90, 0xE0,
  0x07, 0x1F, 0xFC, 0x3F, 0xFC, 0x3F, 0xF9, 0xE0, 0x03, 0xBF, 0xFC, 0x3F, 0xF8, 0x3F, 0xFD, 0xC0,
  0x01, 0xFF, 0xFC, 0x1F, 0xF8, 0x3F, 0xFF, 0x80, 0x01, 0xFF, 0xFE, 0x7F, 0xFE, 0x7F, 0xFF, 0x80,
  0x00, 0xFF, 0xFE, 0xFF, 0xFE, 0x7F, 0xFF, 0x00, 0x00, 0x3F, 0xFE, 0x3F, 0xFC, 0x7F, 0xFC, 0x00,
  0x00, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x00, 0x00, 0x1F, 0xF0, 0x3F, 0xF8, 0x0F, 0xFC, 0x00,
  0x00, 0x3F, 0xC0, 0x18, 0x18, 0x03, 0xF8, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x00,
  0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char myBitmap2 [] PROGMEM = {   // Main logo ,, //
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xF0, 0x00,
  0x00, 0x00, 0x00, 0x03, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xC0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x03, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xC0, 0x00, 0x00,
  0x00, 0x00, 0x02, 0x0F, 0xE0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x02, 0x7F, 0xFC, 0x40, 0x00, 0x00,
  0x00, 0x00, 0x02, 0x7F, 0xFE, 0x40, 0x20, 0x00, 0x00, 0x04, 0x02, 0x7F, 0xFE, 0x40, 0x20, 0x00,
  0x00, 0x00, 0x07, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xBF, 0xFF, 0xFF, 0xE0, 0x00,
  0x00, 0x07, 0xFF, 0xFF, 0xFB, 0xFF, 0xE0, 0x00, 0x00, 0x0F, 0x3D, 0xFF, 0xF7, 0xBD, 0xF0, 0x00,
  0x00, 0x0F, 0x18, 0xFF, 0xFF, 0x18, 0xF0, 0x00, 0x00, 0x1F, 0x18, 0xFF, 0xFF, 0x18, 0xF0, 0x00,
  0x00, 0x1F, 0xBD, 0xFF, 0xFF, 0xBD, 0xF8, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00,
  0x00, 0x1F, 0x83, 0xFF, 0xFF, 0xC3, 0xF8, 0x00, 0x00, 0x1F, 0x38, 0xFE, 0xFF, 0x18, 0xF8, 0x00,
  0x00, 0x1E, 0xFE, 0x7D, 0x7E, 0x7E, 0x78, 0x00, 0x00, 0x1D, 0xFF, 0x7E, 0x7C, 0xFF, 0x38, 0x00,
  0x00, 0x1D, 0x01, 0xAF, 0xED, 0x00, 0xB8, 0x00, 0x00, 0x19, 0x11, 0xA7, 0xED, 0x01, 0xB8, 0x00,
  0x00, 0x1B, 0xFF, 0xBF, 0xFD, 0xFF, 0xB8, 0x00, 0x00, 0x19, 0x11, 0xA7, 0xED, 0x99, 0xB8, 0x00,
  0x00, 0x19, 0x01, 0xA7, 0xED, 0x00, 0xB8, 0x00, 0x00, 0x1D, 0xFF, 0x7C, 0x3C, 0xFF, 0x38, 0x00,
  0x00, 0x1E, 0xFE, 0x7D, 0xBE, 0x7E, 0x78, 0x00, 0x00, 0x1F, 0x38, 0xFD, 0xBF, 0x3C, 0xF8, 0x00,
  0x00, 0x1F, 0x83, 0xFD, 0xFF, 0x81, 0xF8, 0x00, 0x00, 0x1F, 0xFF, 0xFC, 0x7F, 0xFF, 0xF8, 0x00,
  0x00, 0x1F, 0xD3, 0xFC, 0x7F, 0xDB, 0xF8, 0x00, 0x00, 0x1F, 0xDF, 0xFF, 0xFF, 0xDB, 0xF8, 0x00,
  0x00, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x1F, 0xFF, 0x80, 0x21, 0xFF, 0xF8, 0x00,
  0x00, 0x1F, 0x9F, 0x00, 0x01, 0xF9, 0xF8, 0x00, 0x00, 0x1F, 0x1F, 0x00, 0x01, 0xF8, 0xF0, 0x00,
  0x00, 0x1F, 0x37, 0x00, 0x01, 0xE8, 0xF0, 0x00, 0x00, 0x0F, 0x23, 0x00, 0x01, 0xCC, 0xF0, 0x00,
  0x00, 0x0F, 0x23, 0x00, 0x01, 0xC5, 0xF0, 0x00, 0x00, 0x0F, 0xFF, 0x00, 0x01, 0xFF, 0xE0, 0x00,
  0x00, 0x07, 0xFF, 0x00, 0x01, 0xFF, 0xE0, 0x00, 0x00, 0x03, 0xFF, 0xBF, 0xFD, 0xFF, 0xC0, 0x00,
  0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x1D, 0xFF, 0xFF, 0x20, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char hand [] PROGMEM = {   // Main logo ,, //
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x71, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF1, 0xF3, 0xE0, 0x00,
  0x00, 0x00, 0x00, 0x01, 0xF1, 0xF3, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF1, 0xF3, 0xE0, 0x00,
  0x00, 0x00, 0x00, 0x03, 0xF1, 0xE3, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xF3, 0xE3, 0xE0, 0x00,
  0x00, 0x00, 0x00, 0x01, 0xF3, 0xE3, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x01, 0xC3, 0xE3, 0xE0, 0x00,
  0x00, 0x00, 0x00, 0x03, 0xE3, 0xE3, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xE3, 0xE3, 0xC0, 0x00,
  0x00, 0x00, 0x00, 0x03, 0xE3, 0xC3, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xE3, 0x83, 0xE1, 0xE0,
  0x00, 0x00, 0x00, 0x03, 0xE3, 0x83, 0xE3, 0xF0, 0x00, 0x00, 0x00, 0x01, 0xC3, 0x83, 0xE3, 0xF8,
  0x00, 0x00, 0x00, 0x01, 0x07, 0xC3, 0xC3, 0xF8, 0x00, 0x00, 0x00, 0x03, 0x87, 0xC3, 0xC3, 0xF8,
  0x00, 0x00, 0x00, 0x07, 0xC7, 0xC3, 0x83, 0xF0, 0x00, 0x00, 0x00, 0x07, 0x87, 0xC7, 0xC3, 0xF0,
  0x00, 0x00, 0x00, 0x0F, 0x87, 0xC7, 0xC1, 0xF0, 0x00, 0x00, 0x00, 0x0F, 0x87, 0xCF, 0xC0, 0xF0,
  0x00, 0x00, 0x00, 0x0F, 0x83, 0x8F, 0xC3, 0xF0, 0x00, 0x00, 0x00, 0x07, 0x80, 0x0F, 0xC3, 0xF0,
  0x00, 0x00, 0x00, 0x01, 0x00, 0x07, 0x83, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0xE0,
  0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x03, 0xE0, 0x10, 0x00, 0x00, 0x07, 0xE6, 0x00, 0x07, 0xC0,
  0x3C, 0x00, 0x00, 0x0F, 0xFF, 0xF8, 0x0F, 0xC0, 0x7E, 0x00, 0x00, 0x0F, 0xFF, 0xFC, 0x0F, 0xC0,
  0x3F, 0x80, 0x00, 0x0F, 0xFF, 0xFE, 0x0F, 0xC0, 0x1F, 0xC0, 0x00, 0x0F, 0xFF, 0xFF, 0xC7, 0x80,
  0x0F, 0xC0, 0x00, 0x0F, 0xBF, 0xDF, 0xF7, 0x00, 0x07, 0xC0, 0x00, 0x0F, 0x7F, 0xEF, 0xFC, 0x00,
  0x03, 0xC0, 0x00, 0x0F, 0x7F, 0xEF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x06, 0x7F, 0xE7, 0xFE, 0x00,
  0x00, 0x00, 0x00, 0x02, 0x7F, 0xE7, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x07, 0x30, 0xEF, 0xFF, 0x00,
  0x00, 0x00, 0x00, 0x3F, 0x06, 0x0F, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x0F, 0x0F, 0xFF, 0x00,
  0x00, 0x00, 0x03, 0xFC, 0x00, 0x03, 0xFF, 0x00, 0x00, 0x00, 0x07, 0xF0, 0x0F, 0x00, 0xFF, 0x00,
  0x00, 0x00, 0x0F, 0xC0, 0x0F, 0x06, 0x3F, 0x00, 0x00, 0x00, 0x1F, 0xDE, 0x4F, 0xA7, 0x9F, 0x00,
  0x00, 0x00, 0x1F, 0xBF, 0x7F, 0x6F, 0xDF, 0x00, 0x00, 0x00, 0x3F, 0xBF, 0x20, 0x4F, 0xFF, 0x00,
  0x00, 0x00, 0x3F, 0xBF, 0x90, 0x5F, 0xFE, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xC0, 0x3F, 0xFC, 0x00,
  0x00, 0x00, 0x7F, 0xFF, 0xE0, 0x7F, 0xF8, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xE6, 0x3F, 0xF0, 0x00,
  0x00, 0x00, 0x3F, 0xFF, 0xCF, 0x1F, 0xE0, 0x00, 0x00, 0x00, 0x1F, 0xFE, 0x3F, 0xC1, 0xC0, 0x00,
  0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xFC, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x3F, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xF0, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x03, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
///////////////////////////////////////////////////////////////////////////////////////////////////////
//
#define PSTR2(x) PSTRtoBuffer_P(PSTR(x))    // just a Parse String 2 Buffer method ,, 
char PSTR2_BUFFER[30]; // adjust size depending on need.
char *PSTRtoBuffer_P(PGM_P str) {
  uint8_t c = '\0', i = 0;
  for (; (c = pgm_read_byte(str)) && i < sizeof(PSTR2_BUFFER); str++, i++) PSTR2_BUFFER[i] = c;
  PSTR2_BUFFER[i] = c;
  return PSTR2_BUFFER;
}
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
#endif
#ifdef Furious
  pinMode(DIV1_PIN, OUTPUT);
  pinMode(DIV2_PIN, OUTPUT);
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
#ifdef Realac
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
#ifdef Realac
///////////////////////////////////////////////////////////////////////
void loop () {  //  loop used onley for switching //
  if (dp > screentime) {
    turbo();
    dp = screentime + 5;
    buttonState0 = digitalRead(BUT1);
    buttonState1 = digitalRead(BUT2);
    buttonState2 = digitalRead(BUT3);
    if (buttonState0 == LOW || buttonState1 == LOW || buttonState2 == LOW) dp = 0;
    return;
  }
  turboswitch();
  dp++;
#ifdef osd
  osdt ++;
  if (osdt > 2) {
    osd();
    osdt = 0;
  }
#endif
  if (selector == 1) {
    search();
    return;
  }
  if (selector == 2) {
    filter();
    return;
  }
  if (selector == 3) {
    scope();
    return;
  }
  if (selector == 4) {
    manual();
    return;
  }
  if (selector == 5) {
    favor();
    return;
  }
  buttonState0 = digitalRead(BUT1);
  buttonState1 = digitalRead(BUT2);
  buttonState2 = digitalRead(BUT3);
  if (buttonState0 == LOW) {
    scan = scan - 1;
    dp = 0;
  }
  if (buttonState1 == LOW) {
    selector = scan;
    dp = 0;
  }
  if (buttonState2 == LOW) {
    scan = scan + 1;
    dp = 0;
  }
  if (scan >= 5)scan = 1;
  if (scan < 1)scan = 1;
  display.clearDisplay();
  display.drawBitmap(0, 0, border, 128, 64, 1);
  display.setTextSize(1);
  display.fillRect(3, 10 * scan + 3, 120, 10, WHITE);
  display.setTextColor(scan == 0 ? BLACK : WHITE);
  display.setCursor(0, 1);
  display.print(PSTR2("      "));
  display.setTextColor(scan == 1 ? BLACK : WHITE);
  display.setCursor(2, 10 * 1 + 5);
  display.print(PSTR2("       SEARCH "));
  display.setTextColor(scan == 2 ? BLACK : WHITE);
  display.setCursor(2, 10 * 2 + 5);
  display.print(PSTR2("  SET FILTER L M H"));
  display.setTextColor(scan == 3 ? BLACK : WHITE);
  display.setCursor(2, 10 * 3 + 5);
  display.print(PSTR2("       SCOPE "));
  display.setTextColor(scan == 4 ? BLACK : WHITE);
  display.setCursor(2, 10 * 4 + 5);
  display.print(PSTR2("        BACK  "));
  display.display();
  digitalWrite(ledPin, LOW);
}
#endif
#ifdef Furious
///////////////////////////////////////////////////////////////////////
void loop () {  //  loop used onley for switching //
  if (dp > screentime) {
    turbo();
    dp = screentime + 5;
    buttonState0 = digitalRead(BUT1);
    buttonState1 = digitalRead(BUT2);
    buttonState2 = digitalRead(BUT3);
    if (buttonState0 == LOW || buttonState1 == LOW || buttonState2 == LOW) dp = 0;
    return;
  }
  turboswitch();
  dp++;
#ifdef osd
  osdt ++;
  if (osdt > 2) {
    osd();
    osdt = 0;
  }
#endif
  if (selector == 1) {
    search();
    return;
  }
  if (selector == 2) {
    filter();
    return;
  }
  if (selector == 3) {
    scope();
    return;
  }
  if (selector == 4) {
    manual();
    return;
  }
  if (selector == 5) {
    favor();
    return;
  }
  buttonState0 = digitalRead(BUT1);
  buttonState1 = digitalRead(BUT2);
  buttonState2 = digitalRead(BUT3);
  if (buttonState0 == LOW) {
    scan = scan - 1;
    dp = 0;
  }
  if (buttonState1 == LOW) {
    selector = scan;
    dp = 0;
  }
  if (buttonState2 == LOW) {
    scan = scan + 1;
    dp = 0;
  }
  if (scan >= 5)scan = 1;
  if (scan < 1)scan = 1;
  display.clearDisplay();
  display.drawBitmap(0, 0, border, 128, 64, 1);
  display.setTextSize(1);
  display.fillRect(3, 10 * scan + 3, 120, 10, WHITE);
  display.setTextColor(scan == 0 ? BLACK : WHITE);
  display.setCursor(0, 1);
  display.print(PSTR2("        "));
  display.setTextColor(scan == 1 ? BLACK : WHITE);
  display.setCursor(2, 10 * 1 + 5);
  display.print(PSTR2("       SEARCH "));
  display.setTextColor(scan == 2 ? BLACK : WHITE);
  display.setCursor(2, 10 * 2 + 5);
  display.print(PSTR2("  SET FILTER L M H"));
  display.setTextColor(scan == 3 ? BLACK : WHITE);
  display.setCursor(2, 10 * 3 + 5);
  display.print(PSTR2("       SCOPE "));
  display.setTextColor(scan == 4 ? BLACK : WHITE);
  display.setCursor(2, 10 * 4 + 5);
  display.print(PSTR2("        BACK  "));
  display.display();
  digitalWrite(ledPin, LOW);
}
#endif
#ifdef Buzz
void loop() {
  turboswitch();
  delay (20);
  autocalib();
  scr = scr + 1;
  display.clearDisplay();
  // Ir reactions //
  if (irrecv.decode(&results)) {
    scp = 0;
    display.clearDisplay();
    while (scp < 10) {
      scp++;
      display.drawCircle(63, display.height() / 2, scp * 2, WHITE);
      display.display();
      digitalWrite(ledPin, HIGH);
    }
    scp = 0;
    if (results.value == Ircode2 || results.value == Ircode22) {
      channel = channel - 8;
      if (channel < 1)channel = 0;
      mnu = 2;
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.print(" BAND -");  // disable
      display.display();
      delay (200);
      display.clearDisplay();
      test();
      scr = 95;
      delay (10);
    }
    if (results.value == Ircode1 || results.value == Ircode11) {
      channel = channel + 8;
      if (channel > 47)channel = 0;
      mnu = 2;
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.print(" BAND +");  // disable
      display.display();
      delay (200);
      display.clearDisplay();
      test();
      scr = 95;
      delay (10);
    }
    if (results.value  == Ircode3 || results.value == Ircode33) {
      channel = channel + 1;
      display.clearDisplay();
      display.setTextSize(4);
      display.setCursor(0, 20);
      display.print("  UP   ");  // disable
      display.display();
      delay (200);
      display.setTextSize(1);
      test();
      scr = 95;
      delay (10);
    }
    if (results.value == Ircode4 || results.value == Ircode44) {
      channel = channel - 1;
      display.clearDisplay();
      display.setTextSize(4);
      display.setCursor(0, 20);
      display.print(" DOWN   ");  // disable
      display.display();
      delay (200);
      display.setTextSize(1);
      test();
      scr = 95;
      delay (10);
    }
    if (results.value == Ircode5 || results.value == Ircode55) {
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.print("    SCAN   ");  // disable
      display.display();
      delay (200);
      display.setTextSize(1);
      best = 0;
      strong();
    }
    if (results.value == Ircode6 || results.value == Ircode66) {
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.print("   SEARCH   ");  // disable
      display.display();
      delay (200);
      display.setTextSize(1);
      best = 0;
      search();
    }
    if (results.value == Ircode7 || results.value == Ircode77) {
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.print("   SCOPE   ");  // disable
      display.display();
      delay (200);
      display.setTextSize(1);
      best = 0;
      scope();
    }
    irrecv.resume(); // Receive the next value
    delay (100);
    if (channel > 47)channel = 0;
    if (channel < 1  )channel = 0;
    display.clearDisplay();
  }
  // Oled Stuff //
  display.clearDisplay();
  if (scr < 40) {
    display.drawBitmap(1, 1, myBitmap2, 64, 64, 1);
  }
  display.setTextSize(1);
  if (scr > 40 && scr < 95) {  // NOT USED IN V2 DISABLE FOR USE
    volt = analogRead(A1);
    volt = map(volt, 1024, 0, 50, 0);
    delay (10);
    display.fillRect(30, 0, 1, 63, WHITE);
    display.fillRect(33, volt, 30, 63, WHITE);
    display.fillRect(64, 0, 1, 63, WHITE);
    display.fillRect(45, 37, 5, 40, BLACK);
    display.fillRect(40, 40, 15, 63, BLACK);
    display.setCursor(0, 50);
    display.print("BATT");
    display.setCursor(8, volt);
    volt = analogRead(A1);
    volt = map(volt, 1024, 0, 0, 60);
    display.print(volt);
    display.print(">");
  }
  if (scr > 95 ) {
    display.setCursor(10, 10);
    display.setTextSize(2);
    display.print(pgm_read_word_near(channel + channelFreqTable));
    display.setCursor(10, 35);
    display.print("MHZ");
    display.setTextSize(1);
    if (scr > 115)scr = 0;
  }
  display.setTextSize(1);
  if (rssi2 < 20 || rssi3 < 20) {
    display.setCursor(71, 13);
    display.print("LOW SIG !");
    delay (10);
  }
  else if (rssi2 > 35 && rssi3 > 35 ) {
    display.setCursor(71, 13);
    display.print("GOOD SIG ");
    delay (10);
  }
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(2, 0);
  display.print("           CH < ");
  display.print(memo);
  display.print(" >");
  delay (10);
  display.fillRect(72, 27, 55, 2, WHITE);
  display.fillRect(72, 29, rssi2, 2, WHITE);
  display.fillRect(72, 34, rssi3, 2, WHITE);
  display.fillRect(72, 36, 55, 2, WHITE);
  display.display();
  delay(10);
  display.setCursor(72, 48);
  if (channel > 39) {
    memo = channel - 39;
    display.print("D/5.3");
  }
  else if (channel > 31) {
    memo = channel - 31;
    display.print("C/Race");
  }
  else if (channel > 23) {
    memo = channel - 23;
    display.print("F/Airwave");
  }
  else if (channel > 15) {
    memo = channel - 15;
    display.print("E");
  }
  else if (channel > 7) {
    memo = channel - 7;
    display.print("B");
  }
  else if (channel < 7) {
    display.print("A");
    memo = channel + 1 ;
  }
  display.display();
}
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef Realac
///////////////////  MAIN SCREEN LOOP ///////////////////////////////////////////////////////////////
void manual() {  // just manual main screen mode //
  display.clearDisplay();
  buttonState0 = digitalRead(BUT1);
  buttonState1 = digitalRead(BUT2);
  buttonState2 = digitalRead(BUT3);
  if (buttonState1 == HIGH )  but = 0;
  if (buttonState0 == LOW ) {
    channel = channel + 1;
    if (channel >= 55)channel = 55;
    display.clearDisplay();
    display.setTextSize(4);
    display.setCursor(0, 20);
    display.print("  UP   ");  // disable
    display.display();
    delay (200);
    display.setTextSize(1);
    test();
    scr = 95;
    mnu = 1;
    dp = 0;
    delay (10);
  }
  if (buttonState2 == LOW ) {
    channel = channel - 1;
    if (channel <= 0)channel = 0;
    display.clearDisplay();
    display.setTextSize(4);
    display.setCursor(0, 20);
    display.print(" DOWN   ");  // disable
    display.display();
    delay (200);
    display.setTextSize(1);
    test();
    scr = 95;
    mnu = 2;
    dp = 0;
    delay (10);
  }
  if (buttonState1 == LOW  ) {  // middle presh menu test !!??!! dexters way of doing shit !
    but = but + 1;
    scp = 0;
    dp = 0;
    while (scp < 10) {
      scp++;
      display.drawCircle(63, display.height() / 2, scp * 2, WHITE);
      display.display();
      digitalWrite(ledPin, HIGH);
    }
    if (but > 5)but = 0;
    if (but == 1) { // band up
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.print(" BAND + ");  // disable
      display.display();
      delay (600);
      display.setTextSize(1);
      display.clearDisplay();
      delay (100);
      buttonState1 = digitalRead(BUT2);
      if (buttonState1 == LOW )return;
      but = 0;
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.print(" OK ");  // disable
      display.display();
      channel = channel + 8;
      if (channel >= 47)channel = 47;
      test();
      scr = 80;
      delay (320);
      display.setTextSize(1);
      display.clearDisplay();
      delay (320);
      return;
    }
    if (but == 2 ) {
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.print(" BAND - ");  // disable
      display.display();
      delay (600);
      display.setTextSize(1);
      display.clearDisplay();
      buttonState1 = digitalRead(BUT2);
      if (buttonState1 == LOW )return;
      but = 0;
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.print(" OK ");  // disable
      display.display();
      channel = channel - 8;
      if (channel <= 0)channel = 0;
      test();
      scr = 80;
      delay (320);
      display.setTextSize(1);
      display.clearDisplay();
      delay (320);
      sub1 = 0;
      return;
    }
    if (but == 3) {
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.print(" SFAVO ");  // disable
      display.display();
      delay (600);
      display.clearDisplay();
      buttonState1 = digitalRead(BUT2);
      if (buttonState1 == LOW )return;
      but = 0;
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.print(" OK ");  // disable
      display.display();
      delay (320);
      display.setTextSize(1);
      display.clearDisplay();
      delay (320);
      selector = 5;
    }
    if (but == 4) {
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.print(" MENU ");  // disable
      display.display();
      delay (600);
      display.clearDisplay();
      buttonState1 = digitalRead(BUT2);
      if (buttonState1 == LOW )return;
      but = 0;
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.print(" OK ");  // disable
      display.display();
      delay (320);
      display.setTextSize(1);
      display.clearDisplay();
      delay (320);
      selector = 0;
    }
    display.setTextSize(1);
    display.clearDisplay();
    delay (320);
  }
  delay (20);
  autocalib();
  scr = scr + 1;
  display.clearDisplay();             ////////////////////////////////////////////////////////////////////////////////  SCREENSAVER PART //////
  if (scr < 40) {
    display.drawBitmap(1, 1, myBitmap2, 64, 64, 1);
    /////////////////////////////////////////////////////////////////////////////////////
    //display.drawCircle(33, 15, rssi3 / 4, WHITE);    // Biohazard up   //also used for RotorRiot
    //display.drawCircle(33, 15, rssi2 / 4, WHITE);    // Biohazard up
    //display.drawCircle(17, 42, rssi2 / 4, WHITE);    // Biohazrd left
    //display.drawCircle(48, 42, rssi2 / 4, WHITE);    // Biohazrd right

    //display.drawCircle(33, 33, rssi3 / 2, WHITE);    // Biohazard up
    //display.drawCircle(33, 33, rssi2 / 2, WHITE);    // Biohazard up

    //display.drawCircle(33, 15, rssi3 / 6, WHITE);    // Biohazard up
    //display.drawCircle(33, 15, rssi2 / 6, WHITE);    // Biohazard up
    //display.drawCircle(17, 42, rssi2 / 6, WHITE);    // Biohazrd left
    //display.drawCircle(48, 42, rssi2 / 6, WHITE);    // Biohazrd right
    ////////////////////////////////////////////////////////////////////////////////
    display.drawCircle(52, 6, rssi3 / 4, WHITE);    // TX Bubbles
    display.drawCircle(52, 6, rssi2 / 4, WHITE);         // TX Bubbles
    ////////////////////////////////////////////////////////////////////////////////////
    // display.drawCircle(20, 5, rssi3 / 6, WHITE);     // fish bubbles
    // display.drawCircle(35, 2, rssi2 / 4, WHITE);     // fish bubbles
    // display.drawCircle(10, 9, rssi3 / 6, WHITE);     // fish bubbles
    // display.drawCircle(5, 12, rssi2 / 4, WHITE);     // fish bubbles
  }
  if (scr > 40 && scr < 95 ) {
    display.setCursor(10, 5);
    display.setTextSize(8);
    display.print(memo);
    display.setTextSize(1);
  }
  if (scr > 95 ) {
    display.setCursor(10, 10);
    display.setTextSize(2);
    if (channel == 48)display.print(pgm_read_word_near(fav1 + channelFreqTable));
    if (channel == 49)display.print(pgm_read_word_near(fav2 + channelFreqTable));
    if (channel == 50)display.print(pgm_read_word_near(fav3 + channelFreqTable));
    if (channel == 51)display.print(pgm_read_word_near(fav4 + channelFreqTable));
    if (channel == 52)display.print(pgm_read_word_near(fav5 + channelFreqTable));
    if (channel == 53)display.print(pgm_read_word_near(fav6 + channelFreqTable));
    if (channel == 54)display.print(pgm_read_word_near(fav7 + channelFreqTable));
    if (channel == 55)display.print(pgm_read_word_near(fav8 + channelFreqTable));
    if (channel <= 47)display.print(pgm_read_word_near(channel + channelFreqTable));
    display.setCursor(10, 35);
    display.print("MHZ");
    display.setTextSize(1);
    if (scr > 115)scr = 0;
  }
  if (rssi2 < 20 || rssi3 < 20) {
    display.setCursor(71, 13);
    display.print("LOW SIG !");
    delay (10);
  }
  else if (rssi2 > 35 && rssi3 > 35 ) {
    display.setCursor(71, 13);
    display.print("GOOD SIG ");
    delay (10);
  }
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(2, 0);
  display.print("            CH < ");
  display.print(memo);
  display.print(" >");
  delay (10);
  display.fillRect(72, 27, 55, 2, WHITE);
  display.fillRect(72, 29, rssi2, 2, WHITE);
  display.fillRect(72, 34, rssi3, 2, WHITE);
  display.fillRect(72, 36, 55, 2, WHITE);
  display.fillRect(72, 29, HIS1, 3, BLACK); // new
  display.fillRect(72, 34, HIS2, 3, BLACK); // new
  display.setCursor(72, 48);
  if (channel > 47) {
    memo = channel - 47;
    display.print("!FAV!");
  }
  else if (channel > 39) {
    memo = channel - 39;
    display.print("D/5.3");
  }
  else if (channel > 31) {
    memo = channel - 31;
    display.print("C/Race");
  }
  else if (channel > 23) {
    memo = channel - 23;
    display.print("F/Airwave");
  }
  else if (channel > 15) {
    memo = channel - 15;
    display.print("E");
  }
  else if (channel > 7) {
    memo = channel - 7;
    display.print("B");
  }
  else display.print("A");
  display.display();
  delay(10);
  if (channel > 55)channel = 0;
  if (channel < 1 )channel = 55;
}
#endif
#ifdef Furious
///////////////////  MAIN SCREEN LOOP ///////////////////////////////////////////////////////////////
void manual() {  // just manual main screen mode //
  display.clearDisplay();
  buttonState0 = digitalRead(BUT1);
  buttonState1 = digitalRead(BUT2);
  buttonState2 = digitalRead(BUT3);
  if (buttonState1 == HIGH )  but = 0;
  if (buttonState0 == LOW ) {
    channel = channel + 1;
    if (channel >= 55)channel = 55;
    display.clearDisplay();
    display.setTextSize(4);
    display.setCursor(0, 20);
    display.print("  UP   ");  // disable
    display.display();
    delay (200);
    display.setTextSize(1);
    test();
    scr = 95;
    mnu = 1;
    dp = 0;
    delay (10);
  }
  if (buttonState2 == LOW ) {
    channel = channel - 1;
    if (channel <= 0)channel = 0;
    display.clearDisplay();
    display.setTextSize(4);
    display.setCursor(0, 20);
    display.print(" DOWN   ");  // disable
    display.display();
    delay (200);
    display.setTextSize(1);
    test();
    scr = 95;
    mnu = 2;
    dp = 0;
    delay (10);
  }
  if (buttonState1 == LOW  ) {  // middle presh menu test !!??!! dexters way of doing shit !
    but = but + 1;
    scp = 0;
    dp = 0;
    while (scp < 10) {
      scp++;
      display.drawCircle(63, display.height() / 2, scp * 2, WHITE);
      display.display();
      digitalWrite(ledPin, HIGH);
    }
    if (but > 5)but = 0;
    if (but == 1) { // band up
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.print(" BAND + ");  // disable
      display.display();
      delay (600);
      display.setTextSize(1);
      display.clearDisplay();
      delay (100);
      buttonState1 = digitalRead(BUT2);
      if (buttonState1 == LOW )return;
      but = 0;
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.print(" OK ");  // disable
      display.display();
      channel = channel + 8;
      if (channel >= 47)channel = 47;
      test();
      scr = 80;
      delay (320);
      display.setTextSize(1);
      display.clearDisplay();
      delay (320);
      return;
    }
    if (but == 2 ) {
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.print(" BAND - ");  // disable
      display.display();
      delay (600);
      display.setTextSize(1);
      display.clearDisplay();
      buttonState1 = digitalRead(BUT2);
      if (buttonState1 == LOW )return;
      but = 0;
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.print(" OK ");  // disable
      display.display();
      channel = channel - 8;
      if (channel <= 0)channel = 0;
      test();
      scr = 80;
      delay (320);
      display.setTextSize(1);
      display.clearDisplay();
      delay (320);
      sub1 = 0;
      return;
    }
    if (but == 3) {
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.print(" SFAVO ");  // disable
      display.display();
      delay (600);
      display.clearDisplay();
      buttonState1 = digitalRead(BUT2);
      if (buttonState1 == LOW )return;
      but = 0;
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.print(" OK ");  // disable
      display.display();
      delay (320);
      display.setTextSize(1);
      display.clearDisplay();
      delay (320);
      selector = 5;
    }
    if (but == 4) {
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.print(" MENU ");  // disable
      display.display();
      delay (600);
      display.clearDisplay();
      buttonState1 = digitalRead(BUT2);
      if (buttonState1 == LOW )return;
      but = 0;
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.print(" OK ");  // disable
      display.display();
      delay (320);
      display.setTextSize(1);
      display.clearDisplay();
      delay (320);
      selector = 0;
    }
    display.setTextSize(1);
    display.clearDisplay();
    delay (320);
  }
  delay (20);
  autocalib();
  scr = scr + 1;
  display.clearDisplay();             ////////////////////////////////////////////////////////////////////////////////  SCREENSAVER PART //////
  if (scr < 40) {
    display.drawBitmap(1, 1, myBitmap2, 64, 64, 1);
    /////////////////////////////////////////////////////////////////////////////////////
    //display.drawCircle(33, 15, rssi3 / 4, WHITE);    // Biohazard up   //also used for RotorRiot
    //display.drawCircle(33, 15, rssi2 / 4, WHITE);    // Biohazard up
    //display.drawCircle(17, 42, rssi2 / 4, WHITE);    // Biohazrd left
    //display.drawCircle(48, 42, rssi2 / 4, WHITE);    // Biohazrd right

    //display.drawCircle(33, 33, rssi3 / 2, WHITE);    // Biohazard up
    //display.drawCircle(33, 33, rssi2 / 2, WHITE);    // Biohazard up

    //display.drawCircle(33, 15, rssi3 / 6, WHITE);    // Biohazard up
    //display.drawCircle(33, 15, rssi2 / 6, WHITE);    // Biohazard up
    //display.drawCircle(17, 42, rssi2 / 6, WHITE);    // Biohazrd left
    //display.drawCircle(48, 42, rssi2 / 6, WHITE);    // Biohazrd right
    ////////////////////////////////////////////////////////////////////////////////
    display.drawCircle(52, 6, rssi3 / 4, WHITE);    // TX Bubbles
    display.drawCircle(52, 6, rssi2 / 4, WHITE);         // TX Bubbles
    ////////////////////////////////////////////////////////////////////////////////////
    // display.drawCircle(20, 5, rssi3 / 6, WHITE);     // fish bubbles
    // display.drawCircle(35, 2, rssi2 / 4, WHITE);     // fish bubbles
    // display.drawCircle(10, 9, rssi3 / 6, WHITE);     // fish bubbles
    // display.drawCircle(5, 12, rssi2 / 4, WHITE);     // fish bubbles
  }
  if (scr > 40 && scr < 95 ) {
    display.setCursor(10, 5);
    display.setTextSize(8);
    display.print(memo);
    display.setTextSize(1);
  }
  if (scr > 95 ) {
    display.setCursor(10, 10);
    display.setTextSize(2);
    if (channel == 48)display.print(pgm_read_word_near(fav1 + channelFreqTable));
    if (channel == 49)display.print(pgm_read_word_near(fav2 + channelFreqTable));
    if (channel == 50)display.print(pgm_read_word_near(fav3 + channelFreqTable));
    if (channel == 51)display.print(pgm_read_word_near(fav4 + channelFreqTable));
    if (channel == 52)display.print(pgm_read_word_near(fav5 + channelFreqTable));
    if (channel == 53)display.print(pgm_read_word_near(fav6 + channelFreqTable));
    if (channel == 54)display.print(pgm_read_word_near(fav7 + channelFreqTable));
    if (channel == 55)display.print(pgm_read_word_near(fav8 + channelFreqTable));
    if (channel <= 47)display.print(pgm_read_word_near(channel + channelFreqTable));
    display.setCursor(10, 35);
    display.print("MHZ");
    display.setTextSize(1);
    if (scr > 115)scr = 0;
  }
  if (rssi2 < 20 || rssi3 < 20) {
    display.setCursor(71, 13);
    display.print("LOW SIG !");
    delay (10);
  }
  else if (rssi2 > 35 && rssi3 > 35 ) {
    display.setCursor(71, 13);
    display.print("GOOD SIG ");
    delay (10);
  }
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(2, 0);
  display.print("            CH < ");
  display.print(memo);
  display.print(" >");
  delay (10);
  display.fillRect(72, 27, 55, 2, WHITE);
  display.fillRect(72, 29, rssi2, 2, WHITE);
  display.fillRect(72, 34, rssi3, 2, WHITE);
  display.fillRect(72, 36, 55, 2, WHITE);
  display.fillRect(72, 29, HIS1, 3, BLACK); // new
  display.fillRect(72, 34, HIS2, 3, BLACK); // new
  display.setCursor(72, 48);
  if (channel > 47) {
    memo = channel - 47;
    display.print("!FAV!");
  }
  else if (channel > 39) {
    memo = channel - 39;
    display.print("D/5.3");
  }
  else if (channel > 31) {
    memo = channel - 31;
    display.print("C/Race");
  }
  else if (channel > 23) {
    memo = channel - 23;
    display.print("F/Airwave");
  }
  else if (channel > 15) {
    memo = channel - 15;
    display.print("E");
  }
  else if (channel > 7) {
    memo = channel - 7;
    display.print("B");
  }
  else display.print("A");
  display.display();
  delay(10);
  if (channel > 55)channel = 0;
  if (channel < 1 )channel = 55;
}
#endif
#ifdef Realac
void filter() {  // menu to set filter treshold //
  buttonState0 = digitalRead(BUT1);
  buttonState1 = digitalRead(BUT2);
  buttonState2 = digitalRead(BUT3);
  if (buttonState0 == LOW) {
    HISFILT = HISFILT - 1;
    delay (100);;
  }
  if (buttonState1 == LOW) {
    selector = 0;
    delay (100);
  }
  if (buttonState2 == LOW) {
    HISFILT = HISFILT + 1;
    delay (100);
  }
  if (HISFILT > 25)HISFILT = 5;
  if (HISFILT < 5)HISFILT = 5;
  EEPROM.write(2, HISFILT);
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(2, 0);
  display.print("  << SET FILTER >>");
  display.setCursor(61, 20);
  display.print(HISFILT);
  display.setCursor(32, 40);
  if (HISFILT <= 10)display.print("FILTER LOW");
  if (HISFILT > 10  && HISFILT < 15)display.print("FILTER MEDIUM");
  if (HISFILT >= 15)display.print("FILTER HIGH");
  display.display();
  digitalWrite(ledPin, LOW);
}
#endif
#ifdef Furious
void filter() {  // menu to set filter treshold //
  buttonState0 = digitalRead(BUT1);
  buttonState1 = digitalRead(BUT2);
  buttonState2 = digitalRead(BUT3);
  if (buttonState0 == LOW) {
    HISFILT = HISFILT - 1;
    delay (100);;
  }
  if (buttonState1 == LOW) {
    selector = 0;
    delay (100);
  }
  if (buttonState2 == LOW) {
    HISFILT = HISFILT + 1;
    delay (100);
  }
  if (HISFILT > 25)HISFILT = 5;
  if (HISFILT < 5)HISFILT = 5;
  EEPROM.write(2, HISFILT);
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(2, 0);
  display.print("  << SET FILTER >>");
  display.setCursor(61, 20);
  display.print(HISFILT);
  display.setCursor(32, 40);
  if (HISFILT <= 10)display.print("FILTER LOW");
  if (HISFILT > 10  && HISFILT < 15)display.print("FILTER MEDIUM");
  if (HISFILT >= 15)display.print("FILTER HIGH");
  display.display();
  digitalWrite(ledPin, LOW);
}
#endif
#ifdef Realac
void favor() {  // menu to set filter treshold //
  buttonState0 = digitalRead(BUT1);
  buttonState1 = digitalRead(BUT2);
  buttonState2 = digitalRead(BUT3);
  if (buttonState0 == LOW) {
    favselect = favselect - 1;

    delay (100);

  }
  if (buttonState1 == LOW) {
    selector = 4;
    /////////////////////////////////////////////////////
    if (favselect == 1)fav1 = channel;
    if (favselect == 2)fav2 = channel;
    if (favselect == 3)fav3 = channel;
    if (favselect == 4)fav4 = channel;
    if (favselect == 5)fav5 = channel;
    if (favselect == 6)fav6 = channel;
    if (favselect == 7)fav7 = channel;
    if (favselect == 8)fav8 = channel;
    ///////////////////////////////////////////////// new Favorite part !

    delay (100);

    favorsave();
  }
  if (buttonState2 == LOW) {
    favselect = favselect + 1;

    delay (100);

  }
  if (favselect > 8)favselect = 1;
  if (favselect < 1)favselect = 8;
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(2, 0);
  display.print("  << SET FAVO CH >>");
  display.setCursor(61, 20);
  display.print(favselect);
  display.display();
  digitalWrite(ledPin, LOW);
}
#endif
#ifdef Furious
void favor() {  // menu to set filter treshold //
  buttonState0 = digitalRead(BUT1);
  buttonState1 = digitalRead(BUT2);
  buttonState2 = digitalRead(BUT3);
  if (buttonState0 == LOW) {
    favselect = favselect - 1;

    delay (100);

  }
  if (buttonState1 == LOW) {
    selector = 4;
    /////////////////////////////////////////////////////
    if (favselect == 1)fav1 = channel;
    if (favselect == 2)fav2 = channel;
    if (favselect == 3)fav3 = channel;
    if (favselect == 4)fav4 = channel;
    if (favselect == 5)fav5 = channel;
    if (favselect == 6)fav6 = channel;
    if (favselect == 7)fav7 = channel;
    if (favselect == 8)fav8 = channel;
    ///////////////////////////////////////////////// new Favorite part !

    delay (100);

    favorsave();
  }
  if (buttonState2 == LOW) {
    favselect = favselect + 1;

    delay (100);

  }
  if (favselect > 8)favselect = 1;
  if (favselect < 1)favselect = 8;
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(2, 0);
  display.print("  << SET FAVO CH >>");
  display.setCursor(61, 20);
  display.print(favselect);
  display.display();
  digitalWrite(ledPin, LOW);
}
#endif
/////////////////////////////////////////
#ifdef Realac
void favorsave() {
  EEPROM.write(3, fav1);
  EEPROM.write(4, fav2);
  EEPROM.write(5, fav3);
  EEPROM.write(6, fav4);
  EEPROM.write(7, fav5);
  EEPROM.write(8, fav6);
  EEPROM.write(9, fav7);
  EEPROM.write(10, fav8);
}
#endif
#ifdef Furious
void favorsave() {
  EEPROM.write(3, fav1);
  EEPROM.write(4, fav2);
  EEPROM.write(5, fav3);
  EEPROM.write(6, fav4);
  EEPROM.write(7, fav5);
  EEPROM.write(8, fav6);
  EEPROM.write(9, fav7);
  EEPROM.write(10, fav8);
}
#endif
/////////////////////////////////////////////
#ifdef Realac
void favorread() {
  fav1 = EEPROM.read(3);
  fav2 = EEPROM.read(4);
  fav3 = EEPROM.read(5);
  fav4 = EEPROM.read(6);
  fav5 = EEPROM.read(7);
  fav6 = EEPROM.read(8);
  fav7 = EEPROM.read(9);
  fav8 = EEPROM.read(10);
  if (fav1 < 0 || fav1 > 55)fav1 = 24;
  if (fav2 < 0 || fav2 > 55)fav2 = 31;
  if (fav3 < 0 || fav3 > 55)fav3 = 24;
  if (fav4 < 0 || fav4 > 55)fav4 = 31;
  if (fav5 < 0 || fav5 > 55)fav5 = 24;
  if (fav6 < 0 || fav6 > 55)fav6 = 31;
  if (fav7 < 0 || fav7 > 55)fav7 = 24;
  if (fav8 < 0 || fav8 > 55)fav8 = 31;
}
#endif
#ifdef Furious
void favorread() {
  fav1 = EEPROM.read(3);
  fav2 = EEPROM.read(4);
  fav3 = EEPROM.read(5);
  fav4 = EEPROM.read(6);
  fav5 = EEPROM.read(7);
  fav6 = EEPROM.read(8);
  fav7 = EEPROM.read(9);
  fav8 = EEPROM.read(10);
  if (fav1 < 0 || fav1 > 55)fav1 = 24;
  if (fav2 < 0 || fav2 > 55)fav2 = 31;
  if (fav3 < 0 || fav3 > 55)fav3 = 24;
  if (fav4 < 0 || fav4 > 55)fav4 = 31;
  if (fav5 < 0 || fav5 > 55)fav5 = 24;
  if (fav6 < 0 || fav6 > 55)fav6 = 31;
  if (fav7 < 0 || fav7 > 55)fav7 = 24;
  if (fav8 < 0 || fav8 > 55)fav8 = 31;
}
#endif
////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef Furious
void scope() {
  display.clearDisplay();
  scp = 0;
  while (scp < 111) {
    scp++;
    display.drawBitmap(30, 0, flagy, 64, 64, 1);
    autocalib();
    display.fillRect(0, 62, 124, 2, WHITE);
    display.fillRect(1, 0, 1, 63, WHITE);
    display.fillRect(2, rssi2, 10, 10 , WHITE);
    display.fillRect(12, 0, 1, 63, WHITE);
    display.fillRect(112, 0, 1, 63, WHITE);
    display.fillRect(113, rssi3, 10, 10 , WHITE);
    display.fillRect(123, 0, 1, 63, WHITE);
    if (scp > 11 ) {
      display.fillRect(scp, rssi2, 1, 1 , WHITE);
      display.fillRect(scp, rssi3, 3, 1 , WHITE);
    }
    else if (scp > 112 ) {
      display.clearDisplay();
      scp = 0;
      return;
    }
    display.display();
    selector = 4;
    delay(5);
  }
}
#endif
#ifdef Realac
void scope() {
  display.clearDisplay();
  scp = 0;
  while (scp < 111) {
    scp++;
    display.drawBitmap(30, 0, flagy, 64, 64, 1);
    autocalib();
    display.fillRect(0, 62, 124, 2, WHITE);
    display.fillRect(1, 0, 1, 63, WHITE);
    display.fillRect(2, rssi2, 10, 10 , WHITE);
    display.fillRect(12, 0, 1, 63, WHITE);
    display.fillRect(112, 0, 1, 63, WHITE);
    display.fillRect(113, rssi3, 10, 10 , WHITE);
    display.fillRect(123, 0, 1, 63, WHITE);
    if (scp > 11 ) {
      display.fillRect(scp, rssi2, 1, 1 , WHITE);
      display.fillRect(scp, rssi3, 3, 1 , WHITE);
    }
    else if (scp > 112 ) {
      display.clearDisplay();
      scp = 0;
      return;
    }
    display.display();
    selector = 4;
    delay(5);
  }
}
#endif
#ifdef Realac
void search() {
  while (goat < 1) {
    buttonState0 = digitalRead(BUT1);
    buttonState1 = digitalRead(BUT2);
    buttonState2 = digitalRead(BUT3);
    autocalib();
    if (buttonState0 == LOW && buttonState2 == LOW) {
      display.clearDisplay();
      display.setCursor(34, 32);
      display.print("BACK MENU");
      display.display();
      selector = 4;
      goat = 0;
      return;
      delay (500);
    }
    if (rssi2 > 50 || rssi3 > 50)goat = 1;
    delay(20);
    display.setCursor(45, 53);
    display.print(rssi2);
    display.drawCircle(25, display.height() / 2, rssi2, WHITE);
    display.drawCircle(25, display.height() / 2, rssi2 / 2, WHITE);
    display.drawCircle(25, display.height() / 2, rssi2 / 5, WHITE);
    display.display();
    delay(15);
    display.clearDisplay();
    display.setCursor(45, 53);
    display.print(rssi2);
    display.drawCircle(102, display.height() / 2, rssi3, WHITE);
    display.drawCircle(102, display.height() / 2, rssi3 / 2, WHITE);
    display.drawCircle(102, display.height() / 2, rssi3 / 5, WHITE);
    display.display();
    delay(15);
    display.clearDisplay();
    display.setCursor(45, 53);
    // display.print("FINDER");
    display.print(rssi2);
    display.fillRect(23, rssi2 - rssi3, 5, 6, WHITE);
    display.fillRect(100, rssi3 - rssi2, 5, 6, WHITE);
    display.display();
    delay(15);
  }
  goat = 0;
}
#endif
#ifdef Furious
void search() {
  while (goat < 1) {
    buttonState0 = digitalRead(BUT1);
    buttonState1 = digitalRead(BUT2);
    buttonState2 = digitalRead(BUT3);
    autocalib();
    if (buttonState0 == LOW && buttonState2 == LOW) {
      display.clearDisplay();
      display.setCursor(34, 32);
      display.print("BACK MENU");
      display.display();
      selector = 4;
      goat = 0;
      return;
      delay (500);
    }
    if (rssi2 > 50 || rssi3 > 50)goat = 1;
    delay(20);
    display.setCursor(45, 53);
    display.print(rssi2);
    display.drawCircle(25, display.height() / 2, rssi2, WHITE);
    display.drawCircle(25, display.height() / 2, rssi2 / 2, WHITE);
    display.drawCircle(25, display.height() / 2, rssi2 / 5, WHITE);
    display.display();
    delay(15);
    display.clearDisplay();
    display.setCursor(45, 53);
    display.print(rssi2);
    display.drawCircle(102, display.height() / 2, rssi3, WHITE);
    display.drawCircle(102, display.height() / 2, rssi3 / 2, WHITE);
    display.drawCircle(102, display.height() / 2, rssi3 / 5, WHITE);
    display.display();
    delay(15);
    display.clearDisplay();
    display.setCursor(45, 53);
    // display.print("FINDER");
    display.print(rssi2);
    display.fillRect(23, rssi2 - rssi3, 5, 6, WHITE);
    display.fillRect(100, rssi3 - rssi2, 5, 6, WHITE);
    display.display();
    delay(15);
  }
  goat = 0;
}
#endif
#ifdef Buzz
void strong() {
  best = 0;
  delay(50);
  if (channel >= 40 && channel <= 47) {
    for (uint8_t i = 40; i <= 47; i++) {
      channel = i;
      delay (10);
      test();
      delay(100);
      rssi = (analogRead(A0));
      delay (50);
      if (rssi  - 10 > best + 20 ) {
        best = rssi - 5 ;
        digitalWrite(ledPin, HIGH);
        delay (50);
        memo = channel;
      }
      uint8_t ext = map(channel, 0, 48, 0, 128);
      rssi = map(rssi, 100, 300, 63, 40);
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(23, 20);
      display.print(">> SCANNING <<");
      display.setCursor(64, 40);
      display.print(channel - 39);
      display.fillRect(ext, rssi, 2, 14, WHITE);
      display.display();
      delay (100);
      digitalWrite(ledPin, LOW);
    }
    delay (50);
    channel = memo - 1;
    test();
    display.clearDisplay();
    display.setCursor(23, 20);
    display.print(">> STRONGEST <<");
    display.setTextSize(2);
    display.setCursor(20, 40);
    display.print(channel - 39);
    display.setTextSize(1);
    display.setCursor(72, 48);
    delay (50);
    memo = channel - 39;
    display.print("D/5.3");
    display.display();
    delay (1300);
    best = 0;
    return;
  }
  else if (channel >= 32 && channel <= 39 ) {
    for (uint8_t i = 32; i <= 39; i++) {
      channel = i;
      delay (10);
      test();
      delay(100);
      rssi = (analogRead(A0));
      delay (50);
      if (rssi  - 10 > best + 20 ) {
        best = rssi - 5 ;
        digitalWrite(ledPin, HIGH);
        delay (50);
        memo = channel;
      }
      uint8_t ext = map(channel, 0, 48, 0, 128);
      rssi = map(rssi, 100, 300, 63, 40);
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(23, 20);
      display.print(">> SCANNING <<");
      display.setCursor(64, 40);
      display.print(channel - 31);
      display.fillRect(ext, rssi, 2, 14, WHITE);
      display.display();
      delay (100);
      digitalWrite(ledPin, LOW);
    }
    delay (50);
    channel = memo - 1 ;
    test();
    display.clearDisplay();
    display.setCursor(23, 20);
    display.print(">> STRONGEST <<");
    display.setTextSize(2);
    display.setCursor(20, 40);
    display.print(channel - 31);
    display.setTextSize(1);
    display.setCursor(72, 48);
    delay (50);
    memo = channel - 31;
    display.print("C/Race");
    display.display();
    delay (1300);
    best = 0;
    return;
  }
  else if (channel >= 24 && channel <= 31) {
    best = 0;
    for (uint8_t i = 24; i <= 31; i++) {
      channel = i;
      delay (10);
      test();
      delay(100);
      rssi = (analogRead(A0));
      delay (50);
      if (rssi  - 10 > best + 20 ) {
        best = rssi - 5 ;
        digitalWrite(ledPin, HIGH);
        delay (50);
        memo = channel;
      }
      uint8_t ext = map(channel, 0, 48, 0, 128);
      rssi = map(rssi, 100, 300, 63, 40);
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(23, 20);
      display.print(">> SCANNING <<");
      display.setCursor(64, 40);
      display.print(channel - 23 );
      display.fillRect(ext, rssi, 2, 14, WHITE);
      display.display();
      delay (100);
      digitalWrite(ledPin, LOW);
    }
    delay (50);
    channel = memo - 1 ;
    test();
    display.clearDisplay();
    display.setCursor(23, 20);
    display.print(">> STRONGEST <<");
    display.setTextSize(2);
    display.setCursor(20, 40);
    display.print(channel - 23);
    display.setTextSize(1);
    display.setCursor(72, 48);
    delay (50);
    memo = channel - 23;
    display.print("F/Airwave");
    display.display();
    delay (1300);
    best = 0;
    return;
  }
  else if (channel >= 16 && channel <= 23) {
    for (uint8_t i = 16; i <= 23; i++) {
      channel = i;
      delay (10);
      test();
      delay(100);
      rssi = (analogRead(A0));
      delay (50);
      if (rssi  - 10 > best + 20 ) {
        best = rssi - 5 ;
        digitalWrite(ledPin, HIGH);
        delay (50);
        memo = channel;
      }
      uint8_t ext = map(channel, 0, 48, 0, 128);
      rssi = map(rssi, 100, 300, 63, 40);
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(23, 20);
      display.print(">> SCANNING <<");
      display.setCursor(64, 40);
      display.print(channel - 15);
      display.fillRect(ext, rssi, 2, 14, WHITE);
      display.display();
      delay (100);
      digitalWrite(ledPin, LOW);
    }
    delay (50);
    channel = memo - 1 ;
    test();
    display.clearDisplay();
    display.setCursor(23, 20);
    display.print(">> STRONGEST <<");
    display.setTextSize(2);
    display.setCursor(20, 40);
    display.print(channel - 15);
    display.setTextSize(1);
    display.setCursor(72, 48);
    delay (50);
    memo = channel - 15;
    display.print("E");
    display.display();
    delay (1300);
    best = 0;
    return;
  }
  else if (channel >= 8 && channel <= 15) {
    for (uint8_t i = 8; i <= 15; i++) {
      channel = i;
      delay (10);
      test();
      delay(100);
      rssi = (analogRead(A0));
      delay (50);
      if (rssi  - 10 > best + 20 ) {
        best = rssi - 5 ;
        digitalWrite(ledPin, HIGH);
        delay (50);
        memo = channel;
      }
      uint8_t ext = map(channel, 0, 48, 0, 128);
      rssi = map(rssi, 100, 300, 63, 40);
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(23, 20);
      display.print(">> SCANNING <<");
      display.setCursor(64, 40);
      display.print(channel - 7);
      display.fillRect(ext, rssi, 2, 14, WHITE);
      display.display();
      delay (100);
      digitalWrite(ledPin, LOW);
    }
    delay (50);
    channel = memo - 1;
    test();
    display.clearDisplay();
    display.setCursor(23, 20);
    display.print(">> STRONGEST <<");
    display.setTextSize(2);
    display.setCursor(20, 40);
    display.print(channel - 7);
    display.setTextSize(1);
    display.setCursor(72, 48);
    delay (50);
    memo = channel - 7;
    display.print("B");
    display.display();
    delay (1300);
    best = 0;
    return;
  }
  else if (channel <= 7 ) {
    for (uint8_t i = 0; i <= 7; i++) {
      channel = i;
      delay (10);
      test();
      delay(100);
      rssi = (analogRead(A0));
      delay (50);
      if (rssi  - 10 > best + 20 ) {
        best = rssi - 5 ;
        digitalWrite(ledPin, HIGH);
        delay (50);
        memo = channel;
      }
      uint8_t ext = map(channel, 0, 48, 0, 128);
      rssi = map(rssi, 100, 300, 63, 40);
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(23, 20);
      display.print(">> SCANNING <<");
      display.setCursor(64, 40);
      display.print(channel );
      display.fillRect(ext, rssi, 2, 14, WHITE);
      display.display();
      delay (100);
      digitalWrite(ledPin, LOW);
    }
    delay (50);
    channel = memo - 1;
    test();
    display.clearDisplay();
    display.setCursor(23, 20);
    display.print(">> STRONGEST <<");
    display.setTextSize(2);
    display.setCursor(20, 40);
    display.print(channel);
    display.setTextSize(1);
    display.setCursor(72, 48);
    delay (50);
    display.print("A");
    display.setCursor(72, 40);
    display.display();
    delay (1300);
    best = 0;
    return;
  }
}
#endif
//////////////////////////////////////////////////////////////////
#ifdef Buzz
void search() {
  while (goat < 1) {
    autocalib();
    if (rssi2 > 50 || rssi3 > 50)goat = 1;
    delay(20);
    display.setCursor(45, 53);
    display.print(rssi2);
    display.drawCircle(25, display.height() / 2, rssi2, WHITE);
    display.drawCircle(25, display.height() / 2, rssi2 / 2, WHITE);
    display.drawCircle(25, display.height() / 2, rssi2 / 5, WHITE);
    display.display();
    delay(15);
    display.clearDisplay();
    display.setCursor(45, 53);
    display.print(rssi2);
    display.drawCircle(102, display.height() / 2, rssi3, WHITE);
    display.drawCircle(102, display.height() / 2, rssi3 / 2, WHITE);
    display.drawCircle(102, display.height() / 2, rssi3 / 5, WHITE);
    display.display();
    delay(15);
    display.clearDisplay();
    display.setCursor(45, 53);
    // display.print("FINDER");
    display.print(rssi2);
    display.fillRect(23, rssi2 - rssi3, 5, 6, WHITE);
    display.fillRect(100, rssi3 - rssi2, 5, 6, WHITE);
    display.display();
    delay(15);
  }
  goat = 0;
}
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef Buzz
void scope() {
  scp = 0;
  while (scp < 111) {
    scp++;
    autocalib();
    display.fillRect(0, 62, 124, 2, WHITE);
    display.fillRect(1, 0, 1, 63, WHITE);
    display.fillRect(2, rssi2, 10, 10 , WHITE);
    display.fillRect(12, 0, 1, 63, WHITE);
    display.fillRect(112, 0, 1, 63, WHITE);
    display.fillRect(113, rssi3, 10, 10 , WHITE);
    display.fillRect(123, 0, 1, 63, WHITE);
    if (scp > 11 ) {
      display.fillRect(scp, rssi2, 1, 1 , WHITE);
      display.fillRect(scp, rssi3, 3, 1 , WHITE);
    }
    else if (scp > 112 ) {
      display.clearDisplay();
      scp = 0;
      return;
    }
    display.display();
    delay(5);
  }
}
#endif
//////////////////////////////////////////////////////////////////////////
#ifdef osd
void osd() {  // new section to send data 2 osd ,,
#ifdef Furious
  rssiosd1 = map(analogRead(A6), rssi1_MIN, rssi1_MAX, 100, 0);
  delay (30);
  rssiosd2 = map(analogRead(A7), rssi2_MIN, rssi2_MAX, 100, 0);
#endif
#ifdef Realac
  rssiosd1 = map(analogRead(A6), rssi1_MIN, rssi1_MAX, 100, 0);
  delay (30);
  rssiosd2 = map(analogRead(A7), rssi2_MIN, rssi2_MAX, 100, 0);
#endif
  delay (30);
  Serial.print(channel);
  Serial.print(",");
  delay (3);
  Serial.print(rssiosd1);
  Serial.print(",");
  delay (3);
  Serial.print(rssiosd2);
  Serial.print(",");
  delay (3);
  Serial.print(swt);
  Serial.print(",");
  delay (3);
  Serial.println(mnu);///  new for showing menu stuff ,,///
  mnu = 0;
  return;
}
#endif
void turbo() { // making the switching routine faster by dropping al other routines ,, !!
  turboswitch() ;
  display.clearDisplay();
  display.drawBitmap(30, 0, hand, 64, 64, 1);
  return;
}
