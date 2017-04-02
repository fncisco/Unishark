#define Realac  // Realac // Furious// Buzz     // for Ubad = LaForge select Realac !
//#define v3  //v1//v3  define one if used for furious
#define osdoff // osd // osdoff for Minimosd mod !!
#define white // color // white  // oled white or 2 color versions 
////////////////////////////////////////////////////////////////////////////////////////////////
uint8_t NOBLACK = 10; // stil Beta Value !!
uint8_t HISFILT = 10; // setting set in menu
#define SIG_ALARM 20 // signal alarm treshold ,, between 0-50  // works onley on PIEZO enabled Modules ,, 
#define screentime 100
/////////////////////////////////////////////////////////////////
#ifdef Furious
#define ledPin 13
#define DIV1_PIN  6
#define DIV2_PIN  5
#define spiDataPin A3
#define slaveSelectPin A2
#define spiClockPin A1
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

#define spiDataPin 10
#define slaveSelectPin 11
#define spiClockPin 12
#define ledPin 13
#define DIV1_PIN  14
#define DIV2_PIN  15
#define PIEZO  6

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
#define ledPin 13
#define spiDataPin 10
#define slaveSelectPin 11
#define spiClockPin 12
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////

// DO Not TOuCH BelOw If not Knowing what you are doing !!




