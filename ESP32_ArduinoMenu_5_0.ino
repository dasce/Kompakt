/********************
Board used:
Esp32 DevKit v1  https://github.com/espressif/arduino-esp32/issues/544

Arduino generic menu system
Arduino menu using clickEncoder and TFT_eSPI

Sep.2014 Rui Azevedo - ruihfazevedo(@rrob@)gmail.com
Feb.2018 Ken-Fitz - https://github.com/Ken-Fitz

ArduinoMenu library:
https://github.com/neu-rah/ArduinoMenu

ClickEncoder library:
https://github.com/0xPIT/encoder

TFT_eSPI library:
https://github.com/Bodmer/TFT_eSPI

U8G2 library:
https://github.com/olikraus/u8g2

FastLED library:
https://github.com/FastLED/FastLED

MIDI library:
https://github.com/FortySevenEffects/arduino_midi_library

ESPui (WiFi) library:
https://github.com/s00500/ESPUI

*/
#include <FS.h>
#include <SPIFFS.h>
#include <ESPUI.h>
#include <WiFi.h>
#include <FastLED.h>
#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <U8g2lib.h> 
#include <menu.h>
#include <menuIO/TFT_eSPIOut.h>
#include <ClickEncoder.h>
#include <menuIO/clickEncoderIn.h>
#include <menuIO/keyIn.h>
#include <menuIO/chainStream.h>
#include <menuIO/serialIO.h>
#include <menuIO/serialOut.h>
#include <menuIO/serialIn.h>
#include <MIDI.h>
#include <JPEGDecoder.h>

MIDI_CREATE_INSTANCE(HardwareSerial, Serial2, MIDI);

using namespace Menu;


// ----------------------------------------------------------------------------
// WiFi for ESPui
int millisLabelId;
int statusLabelId;
const char *ssid = "Dasce";
const char *password = "65CA07F1RJ";

long oldTime = 0;
bool switchi = false;

// ----------------------------------------------------------------------------
// Define FastLED strip
#define DATA_PIN 13
#define CLOCK_PIN 26
#define NUM_LEDS 101
#define COLOR_ORDER BGR
#define LED_TYPE    APA102
CRGB leds[NUM_LEDS];
// int BRIGHTNESS    =    35;
#define FRAMES_PER_SECOND  120

#define LEDPIN 2

File myFile;
		int BRIGHTNESS    =    35;
		int stLed1	;		int endLed1 = NUM_LEDS		;
		int red1		;		int green1	; 	int blue1 ;
		int stLed2	;		int endLed2	;
		int red2		;		int green2 	; 	int blue2 ;
		int stLed3	;		int endLed3	;
		int red3		;		int green3 	; 	int blue3 ;
		int stLed4	;		int endLed4 ;
		int red4 ;		int green4 ; 	int blue4 ;
		int stLed5	 ;		int endLed5		 ;
		int red5 ; 		int green5 ;	int blue5 ;
		int stLed6	 ;		int endLed6		 ;
		int red6 ; 		int green6 ;	int blue6 ;
		int stLed7	 ;		int endLed7		 ;
		int red7 ; 		int green7 ;	int blue7 ;
		int stLed8	 ;		int endLed8		 ;
		int red8 ; 		int green8 ;	int blue8 ;
		int stLed9	 ;		int endLed9		 ;
		int red9 ; 		int green9 ;	int blue9 ;
		int stLed10	  ;		int endLed10	 ;
		int red10 ; 	int green10	  ;	int blue10 ;
		int stLed11		;		int endLed11		  ;
		int red11 ; 	int green11  ;	int blue11 ;
		int stLed12		;		int endLed12		  ;
		int red12 ; 	int green12 	;	int blue12 ;
		int stLed13		;		int endLed13		  ;
		int red13 ; 	int green13 	;	int blue13 ;
		int stLed14		;		int endLed14		  ;
		int red14 ; 	int green14 	;	int blue14 ;
		int stLed15		;		int endLed15		  ;
		int red15 ; 	int green15 	;	int blue15 ;
		int stLed16		;		int endLed16		  ;
		int red16 ; 	int green16 	;	int blue16 ;
		
// Define LED colors /////////////////////////////////////////////
#define L_CRIMSON 			CRBG(220,  20,  60)
#define L_LIGHTCORAL 		CRBG(240, 128, 128)
#define L_DEEPPINK 			CRGB(255,  20, 147)
#define L_DARKORANGE 		CRGB(255, 140,   0)
#define L_SILVER 				CRGB(192, 192, 192)
#define L_GOLD 					CRGB(255, 215,   0)
#define L_GOLDENROD 		CRGB(218, 165,  32)
#define L_SADDLEBROWN 	CRGB(139,  69,  19)
#define L_MEDIUMORCHID 	CRGB(186,  85, 211)
#define L_PURPLE 				CRGB(128,   0, 128)
#define L_LAWNGREEN 		CRGB(124, 252,   0)
#define L_LIMEGREEN 		CRBG( 50, 205,  50)
#define L_YELLOWGREEN 	CRGB(154, 205,  50)
#define L_AQUA 					CRGB(  0, 255, 255)
#define L_DARKTURQUOISE CRGB(  0, 206, 209)
#define L_Dodgerblue 		CRBG( 30, 144, 255)
#define L_BLACK			 		CRBG(  0,   0,   0)
		

// ----------------------------------------------------------------------------
// Define displays
TFT_eSPI gfx;

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// define menu colors --------------------------------------------------------
//  {{disabled normal,disabled selected},{enabled normal,enabled selected, enabled editing}}
//monochromatic color table

#define Black RGB565(0,0,0)
#define Red  RGB565(255,0,0)
#define Green RGB565(0,255,0)
#define Blue RGB565(0,0,255)
#define Gray RGB565(128,128,128)
#define LighterRed RGB565(255,150,150)
#define LighterGreen RGB565(150,255,150)
#define LighterBlue RGB565(150,150,255)
#define DarkerRed RGB565(150,0,0)
#define DarkerGreen RGB565(0,150,0)
#define DarkerBlue RGB565(0,0,150)
#define Cyan RGB565(0,255,255)
#define Magenta RGB565(255,0,255)
#define Yellow RGB565(255,255,0)
#define White RGB565(255,255,255)


// ----------------------------------------------------------------------------
// Define clickEncoder
#define encA 33
#define encB 27
#define encBtn 14   //this encoder has a button here

ClickEncoder clickEncoder(encA,encB,encBtn,2);
ClickEncoderStream encStream(clickEncoder,1);

serialIn serial(Serial);
MENU_INPUTS(in,&encStream,&serial);

// -----------------------------------------------------------------------------
// MIDI Callbacks

void handleNoteOn(byte channel, byte pitch, byte velocity)
{
  if (pitch == 0x18)  {leds[0].maximizeBrightness();	FastLED.show();	u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "C   :On");}
  if (pitch == 0x19)  {leds[1].maximizeBrightness();	FastLED.show();	u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "C#  :On");}
  if (pitch == 0x1A)  {leds[2].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "D   :On");}
  if (pitch == 0x1B)  {leds[3].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "D#  :On");}
  if (pitch == 0x1C)  {leds[4].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "E   :On");}
  if (pitch == 0x1D)  {leds[5].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "F   :On");}
  if (pitch == 0x1E)  {leds[6].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "F#  :On");}
  if (pitch == 0x1F)  {leds[7].maximizeBrightness();	FastLED.show();	u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "G   :On");}
  if (pitch == 0x20)  {leds[8].maximizeBrightness();	FastLED.show();	u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "G#  :On");}
  if (pitch == 0x21)  {leds[9].maximizeBrightness();	FastLED.show();	u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "A   :On");}// ledTestStrip 10leds !!
  if (pitch == 0x22)  {leds[10].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "A#  :On");}
  if (pitch == 0x23)  {leds[22].maximizeBrightness();	FastLED.show();	u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "B   :On");}
  if (pitch == 0x24)  {leds[24].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "C1  :On");}
  if (pitch == 0x25)  {leds[26].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "C1# :On");}
  if (pitch == 0x26)  {leds[28].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "D1  :On");}
  if (pitch == 0x27)  {leds[30].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "D1# :On");}
  if (pitch == 0x28)  {leds[32].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "E1  :On");} 
  if (pitch == 0x29)  {leds[34].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "F1  :On");}
  if (pitch == 0x2A)  {leds[36].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "F1# :On");}
  if (pitch == 0x2B)  {leds[38].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "G1  :On");}
  if (pitch == 0x2C)  {leds[40].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "G1# :On");}
  if (pitch == 0x2D)  {leds[42].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "A1  :On");}
  if (pitch == 0x2E)  {leds[44].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "A1# :On");}
  if (pitch == 0x2F)  {leds[46].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "B1  :On");}
  if (pitch == 0x30)  {leds[48].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "C2  :On");}
  if (pitch == 0x31)  {leds[50].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "C2# :On");}
  if (pitch == 0x32)  {leds[52].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "D2  :On");}
  if (pitch == 0x33)  {leds[54].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "D2# :On");}
  if (pitch == 0x34)  {leds[56].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "E2  :On");}
  if (pitch == 0x35)  {leds[58].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "F2  :On");}
  if (pitch == 0x36)  {leds[60].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "F2# :On");}
  if (pitch == 0x37)  {leds[62].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "G2  :On");}
  if (pitch == 0x38)  {leds[64].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "G2# :On");}
  if (pitch == 0x39)  {leds[66].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "A2  :On");}
  if (pitch == 0x3A)  {leds[68].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "A2# :On");}
  if (pitch == 0x3B)  {leds[70].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "B2  :On");}
  if (pitch == 0x3C)  {leds[72].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "C3  :On");}
  if (pitch == 0x3D)  {leds[74].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "C3# :On");}
  if (pitch == 0x3E)  {leds[76].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "D3  :On");}
  if (pitch == 0x3F)  {leds[78].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "D3# :On");}
  if (pitch == 0x40)  {leds[80].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "E3  :On");}
  if (pitch == 0x41)  {leds[82].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "F3  :On");}
  if (pitch == 0x42)  {leds[84].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "F3# :On");}
  if (pitch == 0x43)  {leds[86].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "G3  :On");}
  if (pitch == 0x44)  {leds[88].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "G3# :On");}
  if (pitch == 0x45)  {leds[90].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "A3  :On");}
  if (pitch == 0x46)  {leds[92].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "A3# :On");}
  if (pitch == 0x47)  {leds[94].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "B3  :On");}
  if (pitch == 0x48)  {leds[96].maximizeBrightness();	FastLED.show(); u8g2.clearBuffer(); u8g2.drawStr( 0, 44, "C4  :On");}
  if (pitch == 0x49)  {leds[98].maximizeBrightness();	FastLED.show(); }
  if (pitch == 0x4A)  {leds[100].maximizeBrightness();	FastLED.show(); }
//  if (pitch == 0x4B)  {leds[102].maximizeBrightness();	FastLED.show(); /* tft.setCursor(280, 3); tft.setTextColor(WHITE, BLACK1); tft.println(F("E "));*/ }
//  if (pitch == 0x4C)  {leds[104].maximizeBrightness();	FastLED.show(); /* tft.setCursor(280, 3); tft.setTextColor(WHITE, BLACK1); tft.println(F("F "));*/ }
//  if (pitch == 0x4D)  {leds[106].maximizeBrightness();	FastLED.show(); /* tft.setCursor(280, 3); tft.setTextColor(WHITE, BLACK1); tft.println(F("F#"));*/ }
//  if (pitch == 0x4E)  {leds[108].maximizeBrightness();	FastLED.show(); /* tft.setCursor(280, 3); tft.setTextColor(WHITE, BLACK1); tft.println(F("G "));*/ }
//  if (pitch == 0x4F)  {leds[110].maximizeBrightness();	FastLED.show(); /* tft.setCursor(280, 3); tft.setTextColor(WHITE, BLACK1); tft.println(F("G#"));*/ }
//  if (pitch == 0x50)  {leds[112].maximizeBrightness();	FastLED.show(); /* tft.setCursor(280, 3); tft.setTextColor(WHITE, BLACK1); tft.println(F("A "));*/ }
//  if (pitch == 0x51)  {leds[114].maximizeBrightness();	FastLED.show(); /* tft.setCursor(280, 3); tft.setTextColor(WHITE, BLACK1); tft.println(F("Bb"));*/ }
//  if (pitch == 0x52)  {leds[116].maximizeBrightness();	FastLED.show(); /* tft.setCursor(280, 3); tft.setTextColor(WHITE, BLACK1); tft.println(F("B "));*/ }
//  if (pitch == 0x53)  {leds[118].maximizeBrightness();	FastLED.show(); /* tft.setCursor(280, 3); tft.setTextColor(WHITE, BLACK1); tft.println(F("C "));*/ }
//  if (pitch == 0x54)  {leds[120].maximizeBrightness();	FastLED.show(); /* tft.setCursor(280, 3); tft.setTextColor(WHITE, BLACK1); tft.println(F("C#"));*/ }
//  if (pitch == 0x55)  {leds[122].maximizeBrightness();	FastLED.show(); /* tft.setCursor(280, 3); tft.setTextColor(WHITE, BLACK1); tft.println(F("D "));*/ }
//  if (pitch == 0x56)  {leds[128].maximizeBrightness();	FastLED.show(); /* tft.setCursor(280, 3); tft.setTextColor(WHITE, BLACK1); tft.println(F("Eb"));*/ }
//  if (pitch == 0x57)  {leds[130].maximizeBrightness();	FastLED.show(); /* tft.setCursor(280, 3); tft.setTextColor(WHITE, BLACK1); tft.println(F("E "));*/ }
//  if (pitch == 0x58)  {leds[132].maximizeBrightness();	FastLED.show(); /* tft.setCursor(280, 3); tft.setTextColor(WHITE, BLACK1); tft.println(F("F "));*/ }
//  if (pitch == 0x59)  {leds[134].maximizeBrightness();	FastLED.show(); /* tft.setCursor(280, 3); tft.setTextColor(WHITE, BLACK1); tft.println(F("F#"));*/ }
//  if (pitch == 0x5A)  {leds[136].maximizeBrightness();	FastLED.show(); /* tft.setCursor(280, 3); tft.setTextColor(WHITE, BLACK1); tft.println(F("G "));*/ }
//  if (pitch == 0x5B)  {leds[138].maximizeBrightness();	FastLED.show(); /* tft.setCursor(280, 3); tft.setTextColor(WHITE, BLACK1); tft.println(F("G#"));*/ }
//  if (pitch == 0x5C)  {leds[140].maximizeBrightness();	FastLED.show(); /* tft.setCursor(280, 3); tft.setTextColor(WHITE, BLACK1); tft.println(F("A "));*/ } 

	Serial.print("\n");
  Serial.print(F("NoteOn  "));
  Serial.print(pitch);
  Serial.print(F("\tvelocity: "));
  Serial.println(velocity);
	
	u8g2.setFont(u8g2_font_courR18_tr);
	u8g2.drawStr(0, 16, "MIDI:"); u8g2.setCursor(88, 16); u8g2.print(pitch);
  u8g2.drawStr(0, 64, "Velo:");
  u8g2.setCursor(88, 64); u8g2.print(velocity);
	u8g2.sendBuffer(); 
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
  if (pitch == 0x18)  {leds[0].fadeLightBy( 150 );	FastLED.show();	u8g2.drawStr( 0, 44, "C   :Off");}
  if (pitch == 0x19)  {leds[1].fadeLightBy( 150 );	FastLED.show();	u8g2.drawStr( 0, 44, "C#  :Off");}
  if (pitch == 0x1A)  {leds[2].fadeLightBy( 150 );	FastLED.show(); u8g2.drawStr( 0, 44, "D   :Off");}
  if (pitch == 0x1B)  {leds[3].fadeLightBy( 150 );	FastLED.show();	u8g2.drawStr( 0, 44, "D#  :Off");}
  if (pitch == 0x1C)  {leds[4].fadeLightBy( 150 );	FastLED.show();	u8g2.drawStr( 0, 44, "E   :Off");}
  if (pitch == 0x1D)  {leds[5].fadeLightBy( 150 );	FastLED.show();	u8g2.drawStr( 0, 44, "F   :Off");}
  if (pitch == 0x1E)  {leds[6].fadeLightBy( 150 );	FastLED.show(); u8g2.drawStr( 0, 44, "F#  :Off");}
  if (pitch == 0x1F)  {leds[7].fadeLightBy( 150 );	FastLED.show();	u8g2.drawStr( 0, 44, "G   :Off");}
  if (pitch == 0x20)  {leds[8].fadeLightBy( 150 );	FastLED.show();	u8g2.drawStr( 0, 44, "G#  :Off");}
  if (pitch == 0x21)  {leds[9].fadeLightBy( 150 );	FastLED.show();	u8g2.drawStr( 0, 44, "A   :Off");}// ledTestStrip 10leds !!
  if (pitch == 0x22)  {leds[10].fadeLightBy( 250 );	FastLED.show(); u8g2.drawStr( 0, 44, "A#  :Off");}
  if (pitch == 0x23)  {leds[22].fadeLightBy( 250 );	FastLED.show(); u8g2.drawStr( 0, 44, "B   :Off");}
  if (pitch == 0x24)  {leds[24].fadeLightBy( 250 );	FastLED.show(); u8g2.drawStr( 0, 44, "C1  :Off");}
  if (pitch == 0x25)  {leds[26].fadeLightBy( 250 );	FastLED.show(); u8g2.drawStr( 0, 44, "C1# :Off");}
  if (pitch == 0x26)  {leds[28].fadeLightBy( 250 );	FastLED.show(); u8g2.drawStr( 0, 44, "D1  :Off");}
  if (pitch == 0x27)  {leds[30].fadeLightBy( 250 );	FastLED.show(); u8g2.drawStr( 0, 44, "D1# :Off");}
  if (pitch == 0x28)  {leds[32].fadeLightBy( 250 );	FastLED.show(); u8g2.drawStr( 0, 44, "E1  :Off");}
  if (pitch == 0x29)  {leds[34].fadeLightBy( 250 );	FastLED.show(); u8g2.drawStr( 0, 44, "F1  :Off");}
  if (pitch == 0x2A)  {leds[36].fadeLightBy( 250 );	FastLED.show(); u8g2.drawStr( 0, 44, "F1# :Off");}
  if (pitch == 0x2B)  {leds[38].fadeLightBy( 250 );	FastLED.show(); u8g2.drawStr( 0, 44, "G1  :Off");}
  if (pitch == 0x2C)  {leds[40].fadeLightBy( 250 );	FastLED.show(); u8g2.drawStr( 0, 44, "G1# :Off");}
  if (pitch == 0x2D)  {leds[42].fadeLightBy( 250 );	FastLED.show(); u8g2.drawStr( 0, 44, "A1  :Off");}
  if (pitch == 0x2E)  {leds[44].fadeLightBy( 250 );	FastLED.show(); u8g2.drawStr( 0, 44, "A1# :Off");}
  if (pitch == 0x2F)  {leds[46].fadeLightBy( 250 );	FastLED.show(); u8g2.drawStr( 0, 44, "B1  :Off");}
  if (pitch == 0x30)  {leds[48].fadeLightBy( 250 );	FastLED.show(); u8g2.drawStr( 0, 44, "C2  :Off");}
  if (pitch == 0x31)  {leds[50].fadeLightBy( 250 );	FastLED.show(); u8g2.drawStr( 0, 44, "C2# :Off");}
  if (pitch == 0x32)  {leds[52].fadeLightBy( 250 );	FastLED.show(); u8g2.drawStr( 0, 44, "D2  :Off");}
  if (pitch == 0x33)  {leds[54].fadeLightBy( 250 );	FastLED.show(); u8g2.drawStr( 0, 44, "D2# :Off");}
  if (pitch == 0x34)  {leds[56].fadeLightBy( 250 );	FastLED.show(); u8g2.drawStr( 0, 44, "E2  :Off");}
  if (pitch == 0x35)  {leds[58].fadeLightBy( 250 );	FastLED.show(); u8g2.drawStr( 0, 44, "F2  :Off");}
  if (pitch == 0x36)  {leds[60].fadeLightBy( 250 );	FastLED.show(); u8g2.drawStr( 0, 44, "F2# :Off");}
  if (pitch == 0x37)  {leds[62].fadeLightBy( 250 );	FastLED.show(); u8g2.drawStr( 0, 44, "G2  :Off");}
  if (pitch == 0x38)  {leds[64].fadeLightBy( 250 );	FastLED.show(); u8g2.drawStr( 0, 44, "G2# :Off");}
  if (pitch == 0x39)  {leds[66].fadeLightBy( 250 );	FastLED.show(); u8g2.drawStr( 0, 44, "A2  :Off");}
  if (pitch == 0x3A)  {leds[68].fadeLightBy( 250 );	FastLED.show(); u8g2.drawStr( 0, 44, "A2# :Off");}
  if (pitch == 0x3B)  {leds[70].fadeLightBy( 250 );	FastLED.show(); u8g2.drawStr( 0, 44, "B2  :Off");}
  if (pitch == 0x3C)  {leds[72].fadeLightBy( 250 );	FastLED.show(); u8g2.drawStr( 0, 44, "C3  :Off");}
  if (pitch == 0x3D)  {leds[74].fadeLightBy( 250 );	FastLED.show(); u8g2.drawStr( 0, 44, "C3# :Off");}
  if (pitch == 0x3E)  {leds[76].fadeLightBy( 250 );	FastLED.show(); u8g2.drawStr( 0, 44, "D3  :Off");}
  if (pitch == 0x3F)  {leds[78].fadeLightBy( 250 );	FastLED.show(); u8g2.drawStr( 0, 44, "D3# :Off");}
  if (pitch == 0x40)  {leds[80].fadeLightBy( 250 );	FastLED.show(); u8g2.drawStr( 0, 44, "E3  :Off");}
  if (pitch == 0x41)  {leds[82].fadeLightBy( 250 );	FastLED.show(); u8g2.drawStr( 0, 44, "F3  :Off");}
  if (pitch == 0x42)  {leds[84].fadeLightBy( 250 );	FastLED.show(); u8g2.drawStr( 0, 44, "F3# :Off");}
  if (pitch == 0x43)  {leds[86].fadeLightBy( 250 );	FastLED.show(); u8g2.drawStr( 0, 44, "G3  :Off");}
  if (pitch == 0x44)  {leds[88].fadeLightBy( 250 );	FastLED.show(); u8g2.drawStr( 0, 44, "G3# :Off");}
  if (pitch == 0x45)  {leds[90].fadeLightBy( 250 );	FastLED.show(); u8g2.drawStr( 0, 44, "A3  :Off");}
  if (pitch == 0x46)  {leds[92].fadeLightBy( 250 );	FastLED.show(); u8g2.drawStr( 0, 44, "A3# :Off");}
  if (pitch == 0x47)  {leds[94].fadeLightBy( 250 );	FastLED.show(); u8g2.drawStr( 0, 44, "B3  :Off");}
  if (pitch == 0x48)  {leds[96].fadeLightBy( 250 );	FastLED.show(); u8g2.drawStr( 0, 44, "C4  :Off");}
  if (pitch == 0x49)  {leds[98].fadeLightBy( 250 );	FastLED.show();  }
  if (pitch == 0x4A)  {leds[100].fadeLightBy( 250 );	FastLED.show();  }
/*  if (pitch == 0x4B)  {leds[102].fadeLightBy( 250 );	FastLED.show();  }
  if (pitch == 0x4C)  {leds[104].fadeLightBy( 250 );	FastLED.show();  }
  if (pitch == 0x4D)  {leds[106].fadeLightBy( 250 );	FastLED.show();  }
  if (pitch == 0x4E)  {leds[108].fadeLightBy( 250 );	FastLED.show();  }
  if (pitch == 0x4F)  {leds[110].fadeLightBy( 250 );	FastLED.show();  }
  if (pitch == 0x50)  {leds[112].fadeLightBy( 250 );	FastLED.show();  }
  if (pitch == 0x51)  {leds[114].fadeLightBy( 250 );	FastLED.show();  }
  if (pitch == 0x52)  {leds[116].fadeLightBy( 250 );	FastLED.show();  }
  if (pitch == 0x53)  {leds[118].fadeLightBy( 250 );	FastLED.show();  }
  if (pitch == 0x54)  {leds[120].fadeLightBy( 250 );	FastLED.show();  }
  if (pitch == 0x55)  {leds[122].fadeLightBy( 250 );	FastLED.show();  }
  if (pitch == 0x56)  {leds[124].fadeLightBy( 250 );	FastLED.show();  }
  if (pitch == 0x57)  {leds[126].fadeLightBy( 250 );	FastLED.show();  }
  if (pitch == 0x58)  {leds[128].fadeLightBy( 250 );	FastLED.show();  }
  if (pitch == 0x59)  {leds[130].fadeLightBy( 250 );	FastLED.show();  }
  if (pitch == 0x5A)  {leds[132].fadeLightBy( 250 );	FastLED.show();  }
  if (pitch == 0x5B)  {leds[134].fadeLightBy( 250 );	FastLED.show();  }
  if (pitch == 0x5C)  {leds[136].fadeLightBy( 250 );	FastLED.show();  } */
	
	Serial.print("\n");
	Serial.print(F("NoteOff "));
	Serial.print(pitch);
//	Serial.print(F("\tvelocity: "));
//	Serial.println(velocity);
	 
	u8g2.setFont(u8g2_font_courR18_tr);	
//	u8g2.drawStr( 0, 14, "MIDI:"); u8g2.setCursor(98, 14); u8g2.print(pitch);
//  u8g2.drawStr(0, 64, "NoteOff");
//  u8g2.setCursor(90, 64); u8g2.print(pitch);
	u8g2.sendBuffer();
}

//#####################################################################################
// Draw a JPEG on the TFT pulled from SD Card
//#####################################################################################
// xpos, ypos is top left corner of plotted image
void drawFsJpeg(fs::FS &fs, const char *filename, int xpos, int ypos) {

  // Open the named file (the Jpeg decoder library will close it)
  File jpegFile = fs.open( filename, FILE_READ);  // or, file handle reference for SD library
 
  if ( !jpegFile ) {
    Serial.print("ERROR: File \""); Serial.print(filename); Serial.println ("\" not found!");
    return;
  }

  Serial.println("===========================");
  Serial.print("Drawing file: "); Serial.println(filename);
  Serial.println("===========================");

  // Use one of the following methods to initialise the decoder:
  boolean decoded = JpegDec.decodeSdFile(jpegFile);  // Pass the SD file handle to the decoder,
  //boolean decoded = JpegDec.decodeSdFile(filename);  // or pass the filename (String or character array)

  if (decoded) {
    // print information about the image to the serial port
    jpegInfo();
    // render the image onto the screen at given coordinates
    jpegRender(xpos, ypos);
  }
  else {
    Serial.println("Jpeg file format not supported!");
  }
}

//######################################################################################
// Draw a JPEG on the TFT, images will be cropped on the right/bottom sides if they do not fit
//######################################################################################
// This function assumes xpos,ypos is a valid screen coordinate. For convenience images that do not
// fit totally on the screen are cropped to the nearest MCU size and may leave right/bottom borders.
void jpegRender(int xpos, int ypos) {

  //jpegInfo(); // Print information from the JPEG file (could comment this line out)

  uint16_t *pImg;
  uint16_t mcu_w = JpegDec.MCUWidth;
  uint16_t mcu_h = JpegDec.MCUHeight;
  uint32_t max_x = JpegDec.width;
  uint32_t max_y = JpegDec.height;

  bool swapBytes = gfx.getSwapBytes();
  gfx.setSwapBytes(true);
  
  // Jpeg images are draw as a set of image block (tiles) called Minimum Coding Units (MCUs)
  // Typically these MCUs are 16x16 pixel blocks
  // Determine the width and height of the right and bottom edge image blocks
  uint32_t min_w = min(mcu_w, max_x % mcu_w);
  uint32_t min_h = min(mcu_h, max_y % mcu_h);

  // save the current image block size
  uint32_t win_w = mcu_w;
  uint32_t win_h = mcu_h;

  // record the current time so we can measure how long it takes to draw an image
  uint32_t drawTime = millis();

  // save the coordinate of the right and bottom edges to assist image cropping
  // to the screen size
  max_x += xpos;
  max_y += ypos;

  // Fetch data from the file, decode and display
  while (JpegDec.read()) {    // While there is more data in the file
    pImg = JpegDec.pImage ;   // Decode a MCU (Minimum Coding Unit, typically a 8x8 or 16x16 pixel block)

    // Calculate coordinates of top left corner of current MCU
    int mcu_x = JpegDec.MCUx * mcu_w + xpos;
    int mcu_y = JpegDec.MCUy * mcu_h + ypos;

    // check if the image block size needs to be changed for the right edge
    if (mcu_x + mcu_w <= max_x) win_w = mcu_w;
    else win_w = min_w;

    // check if the image block size needs to be changed for the bottom edge
    if (mcu_y + mcu_h <= max_y) win_h = mcu_h;
    else win_h = min_h;

    // copy pixels into a contiguous block
    if (win_w != mcu_w)
    {
      uint16_t *cImg;
      int p = 0;
      cImg = pImg + win_w;
      for (int h = 1; h < win_h; h++)
      {
        p += mcu_w;
        for (int w = 0; w < win_w; w++)
        {
          *cImg = *(pImg + w + p);
          cImg++;
        }
      }
    }

    // calculate how many pixels must be drawn
    uint32_t mcu_pixels = win_w * win_h;

    // draw image MCU block only if it will fit on the screen
    if (( mcu_x + win_w ) <= gfx.width() && ( mcu_y + win_h ) <= gfx.height())
      gfx.pushImage(mcu_x, mcu_y, win_w, win_h, pImg);
    else if ( (mcu_y + win_h) >= gfx.height())
      JpegDec.abort(); // Image has run off bottom of screen so abort decoding
  }

  gfx.setSwapBytes(swapBytes);

  showTime(millis() - drawTime); // These lines are for sketch testing only
}

//######################################################################################
// Print image information to the serial port (optional)
//######################################################################################
// JpegDec.decodeFile(...) or JpegDec.decodeArray(...) must be called before this info is available!
void jpegInfo() {

  // Print information extracted from the JPEG file
  Serial.print("\n");
  Serial.print("Width      :");
  Serial.println("===============");
  Serial.print("Width      :");
  Serial.println(JpegDec.width);
  Serial.print("Height     :");
  Serial.println(JpegDec.height);
  Serial.print("Components :");
  Serial.println(JpegDec.comps);
  Serial.print("MCU / row  :");
  Serial.println(JpegDec.MCUSPerRow);
  Serial.print("MCU / col  :");
  Serial.println(JpegDec.MCUSPerCol);
  Serial.print("Scan type  :");
  Serial.println(JpegDec.scanType);
  Serial.print("MCU width  :");
  Serial.println(JpegDec.MCUWidth);
  Serial.print("MCU height :");
  Serial.println(JpegDec.MCUHeight);
  Serial.println("===============");
  Serial.println("");
}

//######################################################################################
// Show the execution time (optional)
//######################################################################################
// WARNING: for UNO/AVR legacy reasons printing text to the screen with the Mega might not work for
// sketch sizes greater than ~70KBytes because 16 bit address pointers are used in some libraries.

// The Due will work fine with the HX8357_Due library.

void showTime(uint32_t msTime) {
  //tft.setCursor(0, 0);
  //tft.setTextFont(1);
  //tft.setTextSize(2);
  //tft.setTextColor(TFT_WHITE, TFT_BLACK);
  //tft.print(F(" JPEG drawn in "));
  //tft.print(msTime);
  //tft.println(F(" ms "));
  Serial.print(F("JPEG drawn in "));
  Serial.print(msTime);
  Serial.println(F(" ms "));
}


void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
    Serial.printf("\nListing directory: %s\r\n", dirname);

    File root = fs.open(dirname);
    if(!root){
        Serial.println("- failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        Serial.println(" - not a directory");
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if(levels){
                listDir(fs, file.name(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("\tSIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}


 void writeSDSettings(fs::FS &fs, const char * mName, const char * STARTled, int LEDst, const char * ENDled, int LEDend	, const char * REDled, int LEDred, const char * GREENled, int LEDgreen, const char * BLUEled, int LEDblue) {
		 // Delete the old one
		 fs.remove(mName);
		 // Create new one
		 myFile = fs.open(mName, FILE_WRITE);
		 // writing in the file works just like regular print()/println() function
myFile.print(F("["));myFile.print(STARTled);	myFile.print(F("="));		myFile.print(LEDst);	myFile.println(F("]"));
myFile.print(F("["));myFile.print(ENDled);		myFile.print(F("="));		myFile.print(LEDend);	myFile.println(F("]"));
myFile.print(F("["));myFile.print(REDled);		myFile.print(F("="));		myFile.print(LEDred);		myFile.println(F("]"));
myFile.print(F("["));myFile.print(GREENled);	myFile.print(F("="));		myFile.print(LEDgreen);	myFile.println(F("]"));
myFile.print(F("["));myFile.print(BLUEled);		myFile.print(F("="));		myFile.print(LEDblue);		myFile.println(F("]"));
		 // close the file:
		 myFile.close();
 }
 
 void applySetting(String settingName, String settingValue/*, const char * STARTled, const char * ENDled*/) {
		if(settingName == "stLed1") 	{		 stLed1=settingValue.toInt();		}
		if(settingName == "endLed1") 	{		 endLed1=settingValue.toInt();	}
		if(settingName == "red1") 		{		 red1=settingValue.toInt();			}
		if(settingName == "green1") 	{		 green1=settingValue.toInt();		}
		if(settingName == "blue1") 		{		 blue1=settingValue.toInt();		}
		if(settingName == "stLed2") 	{		 stLed2=settingValue.toInt();		}
		if(settingName == "endLed2") 	{		 endLed2=settingValue.toInt();	}
		if(settingName == "red2") 		{		 red2=settingValue.toInt();			}
		if(settingName == "green2") 	{		 green2=settingValue.toInt();		}
		if(settingName == "blue2") 		{		 blue2=settingValue.toInt();		}
		if(settingName == "stLed3") 	{		 stLed3=settingValue.toInt();		}
		if(settingName == "endLed3") 	{		 endLed3=settingValue.toInt();	}
		if(settingName == "red3") 		{		 red3=settingValue.toInt();			}
		if(settingName == "green3") 	{		 green3=settingValue.toInt();		}
		if(settingName == "blue3") 		{		 blue3=settingValue.toInt();		}
		if(settingName == "stLed4") 	{		 stLed4=settingValue.toInt();		}
		if(settingName == "endLed4") 	{		 endLed4=settingValue.toInt();	}
		if(settingName == "red4") 		{		 red4=settingValue.toInt();			}
		if(settingName == "green4") 	{		 green4=settingValue.toInt();		}
		if(settingName == "blue4") 		{		 blue4=settingValue.toInt();		}
		if(settingName == "stLed5") 	{		 stLed5=settingValue.toInt();		}
		if(settingName == "endLed5") 	{		 endLed5=settingValue.toInt();	}
		if(settingName == "red5") 		{		 red5=settingValue.toInt();			}
		if(settingName == "green5") 	{		 green5=settingValue.toInt();		}
		if(settingName == "blue5") 		{		 blue5=settingValue.toInt();		}
		if(settingName == "stLed6") 	{		 stLed6=settingValue.toInt();		}
		if(settingName == "endLed6") 	{		 endLed6=settingValue.toInt();	}
		if(settingName == "red6") 		{		 red6=settingValue.toInt();			}
		if(settingName == "green6") 	{		 green6=settingValue.toInt();		}
		if(settingName == "blue6") 		{		 blue6=settingValue.toInt();		}
		if(settingName == "stLed7") 	{		 stLed7=settingValue.toInt();		}
		if(settingName == "endLed7") 	{		 endLed7=settingValue.toInt();	}
		if(settingName == "red7") 		{		 red7=settingValue.toInt();			}
		if(settingName == "green7") 	{		 green7=settingValue.toInt();		}
		if(settingName == "blue7") 		{		 blue7=settingValue.toInt();		}
		if(settingName == "stLed8") 	{		 stLed8=settingValue.toInt();		}
		if(settingName == "endLed8") 	{		 endLed8=settingValue.toInt();	}
		if(settingName == "red8") 		{		 red8=settingValue.toInt();			}
		if(settingName == "green8") 	{		 green8=settingValue.toInt();		}
		if(settingName == "blue8") 		{		 blue8=settingValue.toInt();		}
		if(settingName == "stLed9") 	{		 stLed9=settingValue.toInt();		}
		if(settingName == "endLed9") 	{		 endLed9=settingValue.toInt();	}
		if(settingName == "red9") 		{		 red9=settingValue.toInt();			}
		if(settingName == "green9") 	{		 green9=settingValue.toInt();		}
		if(settingName == "blue9") 		{		 blue9=settingValue.toInt();		}
		if(settingName == "stLed10") 	{		 stLed10=settingValue.toInt();	}
		if(settingName == "endLed10") {		 endLed10=settingValue.toInt();	}
		if(settingName == "red10") 		{		 red10=settingValue.toInt();		}
		if(settingName == "green10") 	{		 green10=settingValue.toInt();	}
		if(settingName == "blue10") 	{		 blue10=settingValue.toInt();		}
		if(settingName == "stLed11") 	{	   stLed11=settingValue.toInt();	}
		if(settingName == "endLed11") {		 endLed11=settingValue.toInt();	}
		if(settingName == "red11") 		{		 red11=settingValue.toInt();		}
		if(settingName == "green11") 	{		 green11=settingValue.toInt();	}
		if(settingName == "blue11") 	{		 blue11=settingValue.toInt();		}
		if(settingName == "stLed12") 	{		 stLed12=settingValue.toInt();	}
		if(settingName == "endLed12") {		 endLed12=settingValue.toInt();	}
		if(settingName == "red12") 		{		 red12=settingValue.toInt();		}
		if(settingName == "green12") 	{		 green12=settingValue.toInt();	}
		if(settingName == "blue12") 	{		 blue12=settingValue.toInt();		}
		if(settingName == "stLed13") 	{		 stLed13=settingValue.toInt();	}
		if(settingName == "endLed13") {		 endLed13=settingValue.toInt();	}
		if(settingName == "red13") 		{		 red13=settingValue.toInt();		}
		if(settingName == "green13") 	{		 green13=settingValue.toInt();	}
		if(settingName == "blue13") 	{		 blue13=settingValue.toInt();		}
		if(settingName == "stLed14") 	{		 stLed14=settingValue.toInt();	}
		if(settingName == "endLed14") {		 endLed14=settingValue.toInt();	}
		if(settingName == "red14") 		{		 red14=settingValue.toInt();		}
		if(settingName == "green14") 	{		 green14=settingValue.toInt();	}
		if(settingName == "blue14") 	{		 blue14=settingValue.toInt();		}
		if(settingName == "stLed15") 	{		 stLed15=settingValue.toInt();	}
		if(settingName == "endLed15") {		 endLed15=settingValue.toInt();	}
		if(settingName == "red15") 		{		 red15=settingValue.toInt();		}
		if(settingName == "green15") 	{		 green15=settingValue.toInt();	}
		if(settingName == "blue15") 	{		 blue15=settingValue.toInt();		}
		if(settingName == "stLed16") 	{		 stLed16=settingValue.toInt();	}
		if(settingName == "endLed16")	{		 endLed16=settingValue.toInt();	}
		if(settingName == "red16") 		{		 red16=settingValue.toInt();		}
		if(settingName == "green16")	{		 green16=settingValue.toInt();	}
		if(settingName == "blue16") 	{		 blue16=settingValue.toInt();		}
	}
  
 void readSDSettings(fs::FS &fs, const char * mName/*, const char * STARTled, const char * ENDled*/){
		 char character;
		 String settingName;
		 String settingValue;
		 myFile = fs.open(mName);
		 if (myFile) {
		 while (myFile.available()) {
		 character = myFile.read();
		 while((myFile.available()) && (character != '[')){
		 character = myFile.read();
		 }
		 character = myFile.read();
		 while((myFile.available()) && (character != '=')){
		 settingName = settingName + character;
		 character = myFile.read();
		 }
		 character = myFile.read();
		 while((myFile.available()) && (character != ']')){
		 settingValue = settingValue + character;
		 character = myFile.read();
		 }
		 if(character == ']'){
		 
		 // Apply the value to the parameter
		 applySetting(settingName,settingValue);
		 // Reset Strings
		 settingName = "";
		 settingValue = "";
		 }
		 }
		 // close the file:
		 myFile.close();
		 } else {
		 // if the file didn't open, print an error:
		 Serial.println("\nError opening file!!");
		 }
 }
 
void OLED_init(void) {
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_courR18_tr);
	u8g2.drawStr( 36, 16, "OLED");
	u8g2.drawStr( 12, 44, "working");
  u8g2.sendBuffer();         // transfer internal memory to the display
}

void redLed(void) {
  int red = 255; int green = 0; int blue = 0;
	FastLED.clear();
	for(int colLed = 0;	colLed < NUM_LEDS;	colLed = colLed + 2){
		leds[colLed] = CRGB(red, green, blue);
//		FastLED.setBrightness(30);
		FastLED.show();
	}
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_courR18_tr);
	u8g2.drawStr( 0, 16, " LEDs:");
	u8g2.drawStr( 0, 44, "  Red");
  u8g2.sendBuffer();         // transfer internal memory to the display
}

void greenLed(void) {
	FastLED.clear();
	for(int colLed = 0;	colLed < NUM_LEDS;	colLed = colLed + 2){
		leds[colLed].setRGB( 0,   255,   0);
//		FastLED.setBrightness(15);
		FastLED.show();
	}
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_courR18_tr);
	u8g2.drawStr( 0, 16, " LEDs:");
	u8g2.drawStr( 0, 44, "  Green");
  u8g2.sendBuffer();         // transfer internal memory to the display
}	

void blueLed(void) {
	FastLED.clear();
	for(int colLed = 0;	colLed < NUM_LEDS;	colLed = colLed + 2){
		leds[colLed].setRGB( 0,   0,   255);
//		FastLED.setBrightness(15);
		FastLED.show();
	}
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_courR18_tr);
	u8g2.drawStr( 0, 16, " LEDs:");
	u8g2.drawStr( 0, 44, "  Blue");
  u8g2.sendBuffer();         // transfer internal memory to the display
}

void ledsOff(){
  // Turn the LEDstrip off
	for(int colLed = 0;	colLed < NUM_LEDS;	colLed = colLed + 2){
		leds[colLed] = 0x0000 ;
		FastLED.show();
	}	
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_courR18_tr);
	u8g2.drawStr( 0, 16, " LEDs:");
	u8g2.drawStr( 0, 44, "  Off");
  u8g2.sendBuffer();         // transfer internal memory to the display
	}

result doAlert(eventMask e, prompt &item);

result showEvent(eventMask e,navNode& nav,prompt& item) {
	Serial.print("\n");
  Serial.print("event: ");
  Serial.println(e);
  return proceed;
}

int test=55;

result action1(eventMask e,navNode& nav, prompt &item) {
  Serial.print("\n");
  Serial.print("action1 event: ");
  Serial.print(e);
  Serial.println(", proceed menu");
  Serial.flush();
  return proceed;
}

result action2(eventMask e,navNode& nav, prompt &item) {
  Serial.print("\n");
  Serial.print("action2 event: ");
  Serial.print(e);
  Serial.println(", quiting menu.");
  Serial.flush();
  return quit;
}

result action3(eventMask e,navNode& nav, prompt &item) {
	redLed();
  Serial.print("\n");
  Serial.print("action3 event: ");
  Serial.print(e);
  Serial.println(", proceed menu");
  Serial.flush();
  return proceed;
}

result action4(eventMask e,navNode& nav, prompt &item) {
	ledsOff();
  Serial.print("\n");
  Serial.print("action4 event: ");
  Serial.print(e);
  Serial.println(", proceed menu");
  Serial.flush();
  return proceed;
}

result action5(eventMask e,navNode& nav, prompt &item) {
	greenLed();
  Serial.print("\n");
  Serial.print("action5 event: ");
  Serial.print(e);
  Serial.println(", proceed menu");
  Serial.flush();
  return proceed;
}

result action6(eventMask e,navNode& nav, prompt &item) {
	blueLed();
  Serial.print("\n");
  Serial.print("action6 event: ");
  Serial.print(e);
  Serial.println(", proceed menu");
  Serial.flush();
  return proceed;
}

result reCall() {
  FastLED.clear();
	fsRead1();
	fsRead2();
	fsRead3();
	fsRead4();
	fsRead5();
	fsRead6();
	fsRead7();
	fsRead8();
	fsRead9();
	fsRead10();
	fsRead11();
	fsRead12();
	fsRead13();
	fsRead14();
	fsRead15();
	fsRead16();
  return proceed;
}

int ledCtrl=LOW;

result myLedOn() {
  ledCtrl=HIGH;
  return proceed;
}
result myLedOff() {
  ledCtrl=LOW;
  return proceed;
}

TOGGLE(ledCtrl,setLed,"Led: ",doNothing,noEvent,noStyle//,doExit,enterEvent,noStyle
  ,VALUE("On",HIGH,doNothing,noEvent)
  ,VALUE("Off",LOW,doNothing,noEvent)
);

result wifiOn() {
	Serial.println("** Starting WiFi");
	/////////////////////////////////////////////////////////
//ESPui/WiFi setup

	WiFi.begin(ssid, password);
	Serial.println("");
	// Wait for connection
	while (WiFi.status() != WL_CONNECTED) {
	delay(500);
	Serial.print(".");
	}
	Serial.println("");
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());

  statusLabelId = ESPUI.label("LEDs:", ControlColor::Turquoise, "Off");
  ESPUI.button("LEDs Off", &button3Example, ControlColor::Wetasphalt, "Push");
  ESPUI.button("LEDs Red", &buttonExample, ControlColor::Alizarin, "Push");
  ESPUI.button("LEDs Green", &button1Example, ControlColor::Emerald, "Push");
  ESPUI.button("LEDs Blue", &button2Example, ControlColor::Peterriver, "Push");
  millisLabelId = ESPUI.label("Millis:", ControlColor::Turquoise, "0");
  ESPUI.padWithCenter("Pad with center", &padExample, ControlColor::Sunflower);
  ESPUI.pad("Pad without center", &padExample, ControlColor::Carrot);
  ESPUI.switcher("Switch one", &switchExample, ControlColor::Wetasphalt, false);
  ESPUI.switcher("Switch two", &otherSwitchExample, ControlColor::None, true);
  ESPUI.slider("Slider one", &slider, ControlColor::Alizarin, 30);
  ESPUI.slider("Slider two", &slider, ControlColor::None, 100);
  ESPUI.text("Text Test:", &textCall, ControlColor::Alizarin, "a Text Field");
  ESPUI.number("Numbertest", &numberCall, ControlColor::Alizarin, 5, 0, 10);
	
  ESPUI.beginSPIFFS("Kompakt Control");

  return proceed;
}
result wifiOff() {
	Serial.println("** Stopping WiFi");
  WiFi.mode(WIFI_OFF);
  return proceed;
}

int wifiSw=2;
TOGGLE(wifiSw,wifiMenu,"WiFi : ",doNothing,noEvent,noStyle//,doExit,enterEvent,noStyle
  ,VALUE("On",1,wifiOn,noEvent)
  ,VALUE("Off",2,wifiOff,noEvent)
);

int selTest=-1;
SELECT(selTest,selMenu,"Leds",doNothing,noEvent,noStyle
  ,VALUE("Red",0,action3,enterEvent/*doNothing,noEvent*/)
  ,VALUE("Green",1,action5,enterEvent/*doNothing,noEvent*/)
  ,VALUE("Blue",2,action6,enterEvent/*doNothing,noEvent*/)
  ,VALUE("Off",3,action4,enterEvent/*doNothing,noEvent*/)
  ,VALUE("Cancel",-1,doNothing,noEvent)
);

int chooseTest=-1;
CHOOSE(chooseTest,chooseMenu,"Choose",doNothing,noEvent,noStyle
  ,VALUE("Red",0,action3,enterEvent/*doNothing,noEvent*/)
  ,VALUE("Green",1,action5,enterEvent/*doNothing,noEvent*/)
  ,VALUE("Blue",2,action6,enterEvent/*doNothing,noEvent*/)
  ,VALUE("Off",3,action4,enterEvent/*doNothing,noEvent*/)
  ,VALUE("Cancel",-1,doNothing,noEvent)
);

void setLedColpt1(){
  for(int colLed = stLed1; colLed < endLed1;  colLed = colLed + 2){
    leds[colLed] = CRGB( red1, green1, blue1) ;
  }
  FastLED.show();
	stLed2 = endLed1;
	endLed2 = NUM_LEDS;
}

result ledCol1Pt1() {
  red1 = 220; green1 = 20; blue1 = 60;
	setLedColpt1();
  return proceed;
}

result ledCol2Pt1() {
  red1 = 240; green1 = 128; blue1 = 128;
	setLedColpt1();
  return proceed;
}

result ledCol3Pt1() {
  red1 = 255; green1 = 20; blue1 = 147;
	setLedColpt1();
  return proceed;
}

result ledCol4Pt1() {
  red1 = 255; green1 = 140; blue1 = 0;
	setLedColpt1();
  return proceed;
}

result ledCol5Pt1() {
  red1 = 192; green1 = 192; blue1 = 192;
	setLedColpt1();
  return proceed;
}

result ledCol6Pt1() {
  red1 = 255; green1 = 215; blue1 = 0;
	setLedColpt1();
  return proceed;
}

result ledCol7Pt1() {
  red1 = 218; green1 = 165; blue1 = 32;
	setLedColpt1();
  return proceed;
}

result ledCol8Pt1() {
  red1 = 139; green1 = 69; blue1 = 19;
	setLedColpt1();
  return proceed;
}

result ledCol9Pt1() {
  red1 = 186; green1 = 85; blue1 = 211;
	setLedColpt1();
  return proceed;
}

result ledCol10Pt1() {
  red1 = 128; green1 = 0; blue1 = 128;
	setLedColpt1();
  return proceed;
}

result ledCol11Pt1() {
  red1 = 124; green1 = 252; blue1 = 0;
	setLedColpt1();
  return proceed;
}

result ledCol12Pt1() {
  red1 = 50; green1 = 205; blue1 = 50;
	setLedColpt1();
  return proceed;
}

result ledCol13Pt1() {
  red1 = 154; green1 = 205; blue1 = 50;
	setLedColpt1();
  return proceed;
}

result ledCol14Pt1() {
  red1 = 0; green1 = 255; blue1 = 255;
	setLedColpt1();
  return proceed;
}

result ledCol15Pt1() {
  red1 = 0; green1 = 206; blue1 = 209;
	setLedColpt1();
  return proceed;
}

result ledCol16Pt1() {
  red1 = 30; green1 = 144; blue1 = 255;
	setLedColpt1();
  return proceed;
}

result ledCol17Pt1() {
  red1 = 0; green1 = 0; blue1 = 0;
	setLedColpt1();
  return proceed;
}

int ledColSel1=-1;
CHOOSE(ledColSel1,ledColSelMenu1,"Cl",doNothing,noEvent,wrapStyle
  ,VALUE("Crimson"			,1,ledCol1Pt1,anyEvent)
//  ,VALUE("Light coral"	,2,ledCol2Pt1,anyEvent)
  ,VALUE("Dpink"				,3,ledCol3Pt1,anyEvent)
  ,VALUE("Dorange"			,4,ledCol4Pt1,anyEvent)
  ,VALUE("Silver"				,5,ledCol5Pt1,anyEvent)
  ,VALUE("Gold"					,6,ledCol6Pt1,anyEvent)
  ,VALUE("Goldenrod"		,7,ledCol7Pt1,anyEvent)
  ,VALUE("Sadbrown"			,8,ledCol8Pt1,anyEvent)
  ,VALUE("MedOrchid"		,9,ledCol9Pt1,anyEvent)
  ,VALUE("Purple"				,10,ledCol10Pt1,anyEvent)
  ,VALUE("Lawngreen"		,11,ledCol11Pt1,anyEvent)
  ,VALUE("Limegreen"		,12,ledCol12Pt1,anyEvent)
  ,VALUE("Yellgreen"		,13,ledCol13Pt1,anyEvent)
  ,VALUE("Aqua"					,14,ledCol14Pt1,anyEvent)
//  ,VALUE("Darkturquoise",15,ledCol15Pt1,anyEvent)
  ,VALUE("Dodgeblue"		,16,ledCol16Pt1,anyEvent)
  ,VALUE("Off"					,17,ledCol17Pt1,anyEvent)
  ,VALUE("Cancel"				,-1,doNothing,noEvent)
);

void setLedColpt2(){
  for(int colLed = stLed2; colLed < endLed2;  colLed = colLed + 2){
    leds[colLed] = CRGB( red2, green2, blue2) ;
  }
  FastLED.show();
	stLed3 = endLed2;
	endLed3 = NUM_LEDS;
}

result ledCol1Pt2() {
  red2 = 220; green2 = 20; blue2 = 60;
	setLedColpt2();
  return proceed;
}

result ledCol2Pt2() {
  red2 = 240; green2 = 128; blue2 = 128;
	setLedColpt2();
  return proceed;
}

result ledCol3Pt2() {
  red2 = 255; green2 = 20; blue2 = 147;
	setLedColpt2();
  return proceed;
}

result ledCol4Pt2() {
  red2 = 255; green2 = 140; blue2 = 0;
	setLedColpt2();
  return proceed;
}

result ledCol5Pt2() {
  red2 = 192; green2 = 192; blue2 = 192;
	setLedColpt2();
  return proceed;
}

result ledCol6Pt2() {
  red2 = 255; green2 = 215; blue2 = 0;
	setLedColpt2();
  return proceed;
}

result ledCol7Pt2() {
  red2 = 218; green2 = 165; blue2 = 32;
	setLedColpt2();
  return proceed;
}

result ledCol8Pt2() {
  red2 = 139; green2 = 69; blue2 = 19;
	setLedColpt2();
  return proceed;
}

result ledCol9Pt2() {
  red2 = 186; green2 = 85; blue2 = 211;
	setLedColpt2();
  return proceed;
}

result ledCol10Pt2() {
  red2 = 128; green2 = 0; blue2 = 128;
	setLedColpt2();
  return proceed;
}

result ledCol11Pt2() {
  red2 = 124; green2 = 252; blue2 = 0;
	setLedColpt2();
  return proceed;
}

result ledCol12Pt2() {
  red2 = 50; green2 = 205; blue2 = 50;
	setLedColpt2();
  return proceed;
}

result ledCol13Pt2() {
  red2 = 154; green2 = 205; blue2 = 50;
	setLedColpt2();
  return proceed;
}

result ledCol14Pt2() {
  red2 = 0; green2 = 255; blue2 = 255;
	setLedColpt2();
  return proceed;
}

result ledCol15Pt2() {
  red2 = 0; green2 = 206; blue2 = 209;
	setLedColpt2();
  return proceed;
}

result ledCol16Pt2() {
  red2 = 30; green2 = 144; blue2 = 255;
	setLedColpt2();
  return proceed;
}

result ledCol17Pt2() {
  red2 = 0; green2 = 0; blue2 = 0;
	setLedColpt2();
  return proceed;
}

int ledColSel2=-1;
CHOOSE(ledColSel2,ledColSelMenu2,"Cl",doNothing,noEvent,wrapStyle
  ,VALUE("Crimson"			,1,ledCol1Pt2,anyEvent)
//  ,VALUE("Light coral",2,ledCol2Pt2,enterEvent)
  ,VALUE("Dpink"				,3,ledCol3Pt2,anyEvent)
  ,VALUE("Dorange"			,4,ledCol4Pt2,anyEvent)
  ,VALUE("Silver"				,5,ledCol5Pt2,anyEvent)
  ,VALUE("Gold"					,6,ledCol6Pt2,anyEvent)
  ,VALUE("Goldenrod"		,7,ledCol7Pt2,anyEvent)
  ,VALUE("Sadbrown"			,8,ledCol8Pt2,anyEvent)
  ,VALUE("MedOrchid"		,9,ledCol9Pt2,anyEvent)
  ,VALUE("Purple"				,10,ledCol10Pt2,anyEvent)
  ,VALUE("Lawngreen"		,11,ledCol11Pt2,anyEvent)
  ,VALUE("Limegreen"		,12,ledCol12Pt2,anyEvent)
  ,VALUE("Yellgreen"		,13,ledCol13Pt2,anyEvent)
  ,VALUE("Aqua"					,14,ledCol14Pt2,anyEvent)
//  ,VALUE("Darkturquoise",15,ledCol15Pt2,anyEvent)
  ,VALUE("Dodgeblue"		,16,ledCol16Pt2,anyEvent)
  ,VALUE("Off"					,17,ledCol17Pt2,anyEvent)
  ,VALUE("Cancel"				,-1,doNothing,noEvent)
);

void setLedColpt3(){
  for(int colLed = stLed3; colLed < endLed3;  colLed = colLed + 2){
    leds[colLed] = CRGB( red3, green3, blue3) ;
  }
  FastLED.show();
	stLed4 = endLed3;
	endLed4 = NUM_LEDS;
}

result ledCol1Pt3() {
  red3 = 220; green3 = 20; blue3 = 60;
	setLedColpt3();
  return proceed;
}

result ledCol2Pt3() {
  red3 = 240; green3 = 128; blue3 = 128;
	setLedColpt3();
  return proceed;
}

result ledCol3Pt3() {
  red3 = 255; green3 = 20; blue3 = 147;
	setLedColpt3();
  return proceed;
}

result ledCol4Pt3() {
  red3 = 255; green3 = 140; blue3 = 0;
	setLedColpt3();
  return proceed;
}

result ledCol5Pt3() {
  red3 = 192; green3 = 192; blue3 = 192;
	setLedColpt3();
  return proceed;
}

result ledCol6Pt3() {
  red3 = 255; green3 = 215; blue3 = 0;
	setLedColpt3();
  return proceed;
}

result ledCol7Pt3() {
  red3 = 218; green3 = 165; blue3 = 32;
	setLedColpt3();
  return proceed;
}

result ledCol8Pt3() {
  red3 = 139; green3 = 69; blue3 = 19;
	setLedColpt3();
  return proceed;
}

result ledCol9Pt3() {
  red3 = 186; green3 = 85; blue3 = 211;
	setLedColpt3();
  return proceed;
}

result ledCol10Pt3() {
  red3 = 128; green3 = 0; blue3 = 128;
	setLedColpt3();
  return proceed;
}

result ledCol11Pt3() {
  red3 = 124; green3 = 252; blue3 = 0;
	setLedColpt3();
  return proceed;
}

result ledCol12Pt3() {
  red3 = 50; green3 = 205; blue3 = 50;
	setLedColpt3();
  return proceed;
}

result ledCol13Pt3() {
  red3 = 154; green3 = 205; blue3 = 50;
	setLedColpt3();
  return proceed;
}

result ledCol14Pt3() {
  red3 = 0; green3 = 255; blue3 = 255;
	setLedColpt3();
  return proceed;
}

result ledCol15Pt3() {
  red3 = 0; green3 = 206; blue3 = 209;
	setLedColpt3();
  return proceed;
}

result ledCol16Pt3() {
  red3 = 30; green3 = 144; blue3 = 255;
	setLedColpt3();
  return proceed;
}

result ledCol17Pt3() {
  red3 = 0; green3 = 0; blue3 = 0;
	setLedColpt3();
  return proceed;
}

int ledColSel3=-1;
CHOOSE(ledColSel3,ledColSelMenu3,"Col",doNothing,noEvent,wrapStyle
  ,VALUE("Crimson"			,1,ledCol1Pt3,anyEvent)
//  ,VALUE("Light coral",2,ledCol2Pt3,enterEvent)
  ,VALUE("Dpink"				,3,ledCol3Pt3,anyEvent)
  ,VALUE("Dorange"			,4,ledCol4Pt3,anyEvent)
  ,VALUE("Silver"				,5,ledCol5Pt3,anyEvent)
  ,VALUE("Gold"					,6,ledCol6Pt3,anyEvent)
  ,VALUE("Goldenrod"		,7,ledCol7Pt3,anyEvent)
  ,VALUE("Sadbrown"			,8,ledCol8Pt3,anyEvent)
  ,VALUE("MedOrchid"		,9,ledCol9Pt3,anyEvent)
  ,VALUE("Purple"				,10,ledCol10Pt3,anyEvent)
  ,VALUE("Lawngreen"		,11,ledCol11Pt3,anyEvent)
  ,VALUE("Limegreen"		,12,ledCol12Pt3,anyEvent)
  ,VALUE("Yellgreen"		,13,ledCol13Pt3,anyEvent)
  ,VALUE("Aqua"					,14,ledCol14Pt3,anyEvent)
//  ,VALUE("Darkturquoise",15,ledCol15Pt3,anyEvent)
  ,VALUE("Dodgeblue"		,16,ledCol16Pt3,anyEvent)
  ,VALUE("Off"					,17,ledCol17Pt3,anyEvent)
  ,VALUE("Cancel"				,-1,doNothing,noEvent)
);

//customizing a prompt look!
//by extending the prompt class
class altPrompt:public prompt {
public:
  altPrompt(constMEM promptShadow& p):prompt(p) {}
  Used printTo(navRoot &root,bool sel,menuOut& out, idx_t idx,idx_t len,idx_t) override {
    return out.printRaw(F("spec. prompt!"),len);;
  }
};

result LEDcoL1() { 
	for(int colLed = stLed1; colLed < endLed1;  colLed = colLed + 2){
    leds[colLed] = CRGB( red1, green1, blue1) ;
  }
  FastLED.show();
  return proceed;
};

result LEDcoL2() { 
	for(int colLed = stLed2; colLed < endLed2;  colLed = colLed + 2){
    leds[colLed] = CRGB( red2, green2, blue2) ;
  }
  FastLED.show();
  return proceed;
};

result LEDcoL3() { 
	for(int colLed = stLed3; colLed < endLed3;  colLed = colLed + 2){
    leds[colLed] = CRGB( red3, green3, blue3) ;
  }
  FastLED.show();
  return proceed;
};

result fsWrite1(eventMask e,navNode& nav, prompt &item) { 
	writeSDSettings(SPIFFS, "/Part1", "stLed1", stLed1, "endLed1", endLed1, "red1", red1, "green1", green1, "blue1", blue1);
  return proceed;
};

result fsWrite2(eventMask e,navNode& nav, prompt &item) { 
	writeSDSettings(SPIFFS, "/Part2", "stLed2", stLed2, "endLed2", endLed2, "red2", red2, "green2", green2, "blue2", blue2);
  return proceed;
};

result fsWrite3(eventMask e,navNode& nav, prompt &item) { 
	writeSDSettings(SPIFFS, "/Part3", "stLed3", stLed3, "endLed3", endLed3, "red3", red3, "green3", green3, "blue3", blue3);
  return proceed;
};

result fsRead1() { 
	readSDSettings(SPIFFS, "/Part1");
	LEDcoL1();
  return proceed;
};

result fsRead2() { 
	readSDSettings(SPIFFS, "/Part2");
	LEDcoL2();
  return proceed;
};

result fsRead3() { 
	readSDSettings(SPIFFS, "/Part3");
	LEDcoL3();
  return proceed;
};

result serDebug() { 
	serialDebug();
  return proceed;
};

result dirList() { 
	listDir(SPIFFS, "/", 0);
  return proceed;
};

MENU(ColorPt1,"RGB pt1",showEvent,anyEvent,noStyle
  ,FIELD(red1,"Red","",red1,255,1,0,LEDcoL1,enterEvent/*noEvent*/,wrapStyle)
  ,FIELD(green1,"Green","",green1,255,1,0,LEDcoL1,enterEvent/*noEvent*/,wrapStyle)
  ,FIELD(blue1,"Blue","",blue1,255,1,0,LEDcoL1,enterEvent/*noEvent*/,wrapStyle)
//  ,SUBMENU(ledColSelMenu)
  ,EXIT("<Back")
);

MENU(ColorPt2,"RGB pt2",showEvent,anyEvent,noStyle
  ,FIELD(red2,"Red","",red2,255,1,0,LEDcoL2,enterEvent/*noEvent*/,wrapStyle)
  ,FIELD(green2,"Green","",green2,255,1,0,LEDcoL2,enterEvent/*noEvent*/,wrapStyle)
  ,FIELD(blue2,"Blue","",blue2,255,1,0,LEDcoL2,enterEvent/*noEvent*/,wrapStyle)
//  ,SUBMENU(ledColSelMenu)
  ,EXIT("<Back")
);

MENU(ColorPt3,"RGB pt3",showEvent,anyEvent,noStyle
  ,FIELD(red3,"Red","",red3,255,1,0,LEDcoL3,enterEvent/*noEvent*/,wrapStyle)
  ,FIELD(green3,"Green","",green3,255,1,0,LEDcoL3,enterEvent/*noEvent*/,wrapStyle)
  ,FIELD(blue3,"Blue","",blue3,255,1,0,LEDcoL3,enterEvent/*noEvent*/,wrapStyle)
//  ,SUBMENU(ledColSelMenu)
  ,EXIT("<Back")
);

result ldPrst1() {
	readSDSettings(SPIFFS, "/Kompakt5");
	LEDcoL1();
	LEDcoL2();
	LEDcoL3();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_courR18_tr);
	u8g2.drawStr( 0, 16, "Massive:");
	u8g2.drawStr( 0, 44, " Piano");
  u8g2.sendBuffer();
//  gfx.setTextSize(1);
	gfx.fillRoundRect(0, 106, 160, 22, 2, White);
	gfx.setCursor(3, 108);
  gfx.setTextColor(Black,White);
  gfx.println("Massive:Piano");
//  gfx.setTextSize(2);
  return proceed;
}

result ldPrst2() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_courR18_tr);
	u8g2.drawStr( 0, 16, "Massive:");
	u8g2.drawStr( 0, 44, " Synth");
  u8g2.sendBuffer();
	gfx.fillRoundRect(0, 106, 160, 22, 2, White);
	gfx.setCursor(3, 108);
  gfx.setTextColor(Black,White);
  gfx.println("Massive:Synth");
  return proceed;
}

result ldPrst3() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_courR18_tr);
	u8g2.drawStr( 0, 16, "Massive:");
	u8g2.drawStr( 0, 44, " Drums");
  u8g2.sendBuffer();
	gfx.fillRoundRect(0, 106, 160, 22, 2, White);
	gfx.setCursor(3, 108);
  gfx.setTextColor(Black,White);
  gfx.println("Massive:Drums");
  return proceed;
}

result ldPrst4() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_courR18_tr);
	u8g2.drawStr( 0, 16, "Massive:");
	u8g2.drawStr( 0, 44, " Guitar");
  u8g2.sendBuffer();
	gfx.fillRoundRect(0, 106, 160, 22, 2, White);
	gfx.setCursor(3, 108);
  gfx.setTextColor(Black,White);
  gfx.println("Massive:Guitar");
  return proceed;
}

int selPrst=-1;
SELECT(selPrst,prstMenu,"Preset",doNothing,noEvent,noStyle
  ,VALUE(" 1",0,ldPrst1,anyEvent)
  ,VALUE(" 2",1,ldPrst2,anyEvent)
  ,VALUE(" 3",2,ldPrst3,anyEvent)
  ,VALUE(" 4",3,ldPrst4,anyEvent)
  ,VALUE("Cancel",-1,doNothing,noEvent)
);

MENU(subMenu,"Load preset1",showEvent,anyEvent,wrapStyle
  ,SUBMENU(prstMenu)
  ,EXIT("<Back")
);

MENU(sub1Menu,"LED pt1",showEvent,anyEvent,wrapStyle
  ,FIELD(stLed1,"Start","",0,NUM_LEDS,2,0,doNothing,enterEvent,wrapStyle)
  ,FIELD(endLed1,"End","",stLed1,NUM_LEDS,2,0,doNothing,enterEvent,wrapStyle)
  ,SUBMENU(ColorPt1)
  ,SUBMENU(ledColSelMenu1)
  ,OP("Save Part 1",fsWrite1,enterEvent)
  ,OP("Load Part 1",fsRead1,enterEvent)
  ,EXIT("<Back")
);

MENU(sub2Menu,"LED pt2",showEvent,anyEvent,wrapStyle
  ,FIELD(stLed2,"Start","",stLed2,NUM_LEDS,2,0,doNothing,enterEvent,wrapStyle)
  ,FIELD(endLed2,"End","",stLed2,NUM_LEDS,2,0,doNothing,enterEvent,wrapStyle)
  ,SUBMENU(ColorPt2)
  ,SUBMENU(ledColSelMenu2)
  ,OP("Save Part 2",fsWrite2,enterEvent)
  ,OP("Load Part 2",fsRead2,enterEvent)
  ,EXIT("<Back")
);

MENU(sub3Menu,"LED pt3",showEvent,anyEvent,wrapStyle
  ,FIELD(stLed3,"Start","",stLed3,NUM_LEDS,2,0,doNothing,enterEvent,wrapStyle)
  ,FIELD(endLed3,"End","",stLed3,NUM_LEDS,2,0,doNothing,enterEvent,wrapStyle)
  ,SUBMENU(ColorPt3)
  ,SUBMENU(ledColSelMenu3)
  ,OP("Save Part 3",fsWrite3,enterEvent)
  ,OP("Load Part 3",fsRead3,enterEvent)
  ,EXIT("<Back")
);

void setLedColpt4(){
  for(int colLed = stLed4; colLed < endLed4;  colLed = colLed + 2){
    leds[colLed] = CRGB( red4, green4, blue4) ;
  }
  FastLED.show();
	stLed5 = endLed4;
	endLed5 = NUM_LEDS;
}

result ledCol1Pt4() {
  red4 = 220; green4 = 20; blue4 = 60;
	setLedColpt4();
  return proceed;
}

result ledCol2Pt4() {
  red4 = 240; green4 = 128; blue4 = 128;
	setLedColpt4();
  return proceed;
}

result ledCol3Pt4() {
  red4 = 255; green4 = 20; blue4 = 147;
	setLedColpt4();
  return proceed;
}

result ledCol4Pt4() {
  red4 = 255; green4 = 140; blue4 = 0;
	setLedColpt4();
  return proceed;
}

result ledCol5Pt4() {
  red4 = 192; green4 = 192; blue4 = 192;
	setLedColpt4();
  return proceed;
}

result ledCol6Pt4() {
  red4 = 255; green4 = 215; blue4 = 0;
	setLedColpt4();
  return proceed;
}

result ledCol7Pt4() {
  red4 = 218; green4 = 165; blue4 = 32;
	setLedColpt4();
  return proceed;
}

result ledCol8Pt4() {
  red4 = 139; green4 = 69; blue4 = 19;
	setLedColpt4();
  return proceed;
}

result ledCol9Pt4() {
  red4 = 186; green4 = 85; blue4 = 211;
	setLedColpt4();
  return proceed;
}

result ledCol10Pt4() {
  red4 = 128; green4 = 0; blue4 = 128;
	setLedColpt4();
  return proceed;
}

result ledCol11Pt4() {
  red4 = 124; green4 = 252; blue4 = 0;
	setLedColpt4();
  return proceed;
}

result ledCol12Pt4() {
  red4 = 50; green4 = 205; blue4 = 50;
	setLedColpt4();
  return proceed;
}

result ledCol13Pt4() {
  red4 = 154; green4 = 205; blue4 = 50;
	setLedColpt4();
  return proceed;
}

result ledCol14Pt4() {
  red4 = 0; green4 = 255; blue4 = 255;
	setLedColpt4();
  return proceed;
}

result ledCol15Pt4() {
  red4 = 0; green4 = 206; blue4 = 209;
	setLedColpt4();
  return proceed;
}

result ledCol16Pt4() {
  red4 = 30; green4 = 144; blue4 = 255;
	setLedColpt4();
  return proceed;
}

result ledCol17Pt4() {
  red4 = 0; green4 = 0; blue4 = 0;
	setLedColpt4();
  return proceed;
}

int ledColSel4=-1;
CHOOSE(ledColSel4,ledColSelMenu4,"Col",doNothing,noEvent,wrapStyle
  ,VALUE("Crimson"			,1,ledCol1Pt4,anyEvent)
//  ,VALUE("Light coral",2,ledCol2Pt4,enterEvent)
  ,VALUE("Dpink"				,3,ledCol3Pt4,anyEvent)
  ,VALUE("Dorange"			,4,ledCol4Pt4,anyEvent)
  ,VALUE("Silver"				,5,ledCol5Pt4,anyEvent)
  ,VALUE("Gold"					,6,ledCol6Pt4,anyEvent)
  ,VALUE("Goldenrod"		,7,ledCol7Pt4,anyEvent)
  ,VALUE("Sadbrown"			,8,ledCol8Pt4,anyEvent)
  ,VALUE("MedOrchid"		,9,ledCol9Pt4,anyEvent)
  ,VALUE("Purple"				,10,ledCol10Pt4,anyEvent)
  ,VALUE("Lawngreen"		,11,ledCol11Pt4,anyEvent)
  ,VALUE("Limegreen"		,12,ledCol12Pt4,anyEvent)
  ,VALUE("Yellgreen"		,13,ledCol13Pt4,anyEvent)
  ,VALUE("Aqua"					,14,ledCol14Pt4,anyEvent)
//  ,VALUE("Darkturquoise",15,ledCol15Pt4,anyEvent)
  ,VALUE("Dodgeblue"		,16,ledCol16Pt4,anyEvent)
  ,VALUE("Off"					,17,ledCol17Pt4,anyEvent)
  ,VALUE("Cancel"				,-1,doNothing,noEvent)
);

result LEDcoL4() { 
	for(int colLed = stLed4; colLed < endLed4;  colLed = colLed + 2){
    leds[colLed] = CRGB( red4, green4, blue4) ;
  }
  FastLED.show();
  return proceed;
};

result fsWrite4(eventMask e,navNode& nav, prompt &item) { 
	writeSDSettings(SPIFFS, "/Part4", "stLed4", stLed4, "endLed4", endLed4, "red4", red4, "green4", green4, "blue4", blue4);
  return proceed;
};

result fsRead4() { 
	readSDSettings(SPIFFS, "/Part4");
	LEDcoL4();
  return proceed;
};

MENU(ColorPt4,"RGB pt4",showEvent,anyEvent,noStyle
  ,FIELD(red4,"Red","",red4,255,1,0,LEDcoL4,enterEvent/*noEvent*/,wrapStyle)
  ,FIELD(green4,"Green","",green4,255,1,0,LEDcoL4,enterEvent/*noEvent*/,wrapStyle)
  ,FIELD(blue4,"Blue","",blue4,255,1,0,LEDcoL4,enterEvent/*noEvent*/,wrapStyle)
//  ,SUBMENU(ledColSelMenu)
  ,EXIT("<Back")
);

MENU(sub4Menu,"LED pt4",showEvent,anyEvent,wrapStyle
  ,FIELD(stLed4,"Start","",stLed4,NUM_LEDS,1,0,doNothing,enterEvent,wrapStyle)
  ,FIELD(endLed4,"End","",stLed4,NUM_LEDS,1,0,doNothing,enterEvent,wrapStyle)
  ,SUBMENU(ColorPt4)
  ,SUBMENU(ledColSelMenu4)
  ,OP("Save Part 4",fsWrite4,enterEvent)
  ,OP("Load Part 4",fsRead4,enterEvent)
  ,EXIT("<Back")
);

void setLedColpt5(){
  for(int colLed = stLed5; colLed < endLed5;  colLed = colLed + 2){
    leds[colLed] = CRGB( red5, green5, blue5) ;
  }
  FastLED.show();
	stLed6 = endLed5;
	endLed6 = NUM_LEDS;
}

result ledCol1Pt5() {
  red5 = 220; green5 = 20; blue5 = 60;
	setLedColpt5();
  return proceed;
}

result ledCol2Pt5() {
  red5 = 240; green5 = 128; blue5 = 128;
	setLedColpt5();
  return proceed;
}

result ledCol3Pt5() {
  red5 = 255; green5 = 20; blue5 = 147;
	setLedColpt5();
  return proceed;
}

result ledCol4Pt5() {
  red5 = 255; green5 = 140; blue5 = 0;
	setLedColpt5();
  return proceed;
}

result ledCol5Pt5() {
  red5 = 192; green5 = 192; blue5 = 192;
	setLedColpt5();
  return proceed;
}

result ledCol6Pt5() {
  red5 = 255; green5 = 215; blue5 = 0;
	setLedColpt5();
  return proceed;
}

result ledCol7Pt5() {
  red5 = 218; green5 = 165; blue5 = 32;
	setLedColpt5();
  return proceed;
}

result ledCol8Pt5() {
  red5 = 139; green5 = 69; blue5 = 19;
	setLedColpt5();
  return proceed;
}

result ledCol9Pt5() {
  red5 = 186; green5 = 85; blue5 = 211;
	setLedColpt5();
  return proceed;
}

result ledCol10Pt5() {
  red5 = 128; green5 = 0; blue5 = 128;
	setLedColpt5();
  return proceed;
}

result ledCol11Pt5() {
  red5 = 124; green5 = 252; blue5 = 0;
	setLedColpt5();
  return proceed;
}

result ledCol12Pt5() {
  red5 = 50; green5 = 205; blue5 = 50;
	setLedColpt5();
  return proceed;
}

result ledCol13Pt5() {
  red5 = 154; green5 = 205; blue5 = 50;
	setLedColpt5();
  return proceed;
}

result ledCol14Pt5() {
  red5 = 0; green5 = 255; blue5 = 255;
	setLedColpt5();
  return proceed;
}

result ledCol15Pt5() {
  red5 = 0; green5 = 206; blue5 = 209;
	setLedColpt5();
  return proceed;
}

result ledCol16Pt5() {
  red5 = 30; green5 = 144; blue5 = 255;
	setLedColpt5();
  return proceed;
}

result ledCol17Pt5() {
  red5 = 0; green5 = 0; blue5 = 0;
	setLedColpt5();
  return proceed;
}

int ledColSel5=-1;
CHOOSE(ledColSel5,ledColSelMenu5,"Col",doNothing,noEvent,wrapStyle
  ,VALUE("Crimson"			,1,ledCol1Pt5,anyEvent)
//  ,VALUE("Light coral",2,ledCol2Pt5,enterEvent)
  ,VALUE("Dpink"				,3,ledCol3Pt5,anyEvent)
  ,VALUE("Dorange"			,4,ledCol4Pt5,anyEvent)
  ,VALUE("Silver"				,5,ledCol5Pt5,anyEvent)
  ,VALUE("Gold"					,6,ledCol6Pt5,anyEvent)
  ,VALUE("Goldenrod"		,7,ledCol7Pt5,anyEvent)
  ,VALUE("Sadbrown"			,8,ledCol8Pt5,anyEvent)
  ,VALUE("MedOrchid"		,9,ledCol9Pt5,anyEvent)
  ,VALUE("Purple"				,10,ledCol10Pt5,anyEvent)
  ,VALUE("Lawngreen"		,11,ledCol11Pt5,anyEvent)
  ,VALUE("Limegreen"		,12,ledCol12Pt5,anyEvent)
  ,VALUE("Yellgreen"		,13,ledCol13Pt5,anyEvent)
  ,VALUE("Aqua"					,14,ledCol14Pt5,anyEvent)
//  ,VALUE("Darkturquoise",15,ledCol15Pt5,anyEvent)
  ,VALUE("Dodgeblue"		,16,ledCol16Pt5,anyEvent)
  ,VALUE("Off"					,17,ledCol17Pt5,anyEvent)
  ,VALUE("Cancel"				,-1,doNothing,noEvent)
);

result LEDcoL5() { 
	for(int colLed = stLed5; colLed < endLed5;  colLed = colLed + 2){
    leds[colLed] = CRGB( red5, green5, blue5) ;
  }
  FastLED.show();
  return proceed;
};

result fsWrite5(eventMask e,navNode& nav, prompt &item) { 
	writeSDSettings(SPIFFS, "/Part5", "stLed5", stLed5, "endLed5", endLed5, "red5", red5, "green5", green5, "blue5", blue5);
  return proceed;
};

result fsRead5() { 
	readSDSettings(SPIFFS, "/Part5");
	LEDcoL5();
  return proceed;
};

MENU(ColorPt5,"RGB pt5",showEvent,anyEvent,noStyle
  ,FIELD(red5,"Red","",red5,255,1,0,LEDcoL5,enterEvent/*noEvent*/,wrapStyle)
  ,FIELD(green5,"Green","",green5,255,1,0,LEDcoL5,enterEvent/*noEvent*/,wrapStyle)
  ,FIELD(blue5,"Blue","",blue5,255,1,0,LEDcoL5,enterEvent/*noEvent*/,wrapStyle)
//  ,SUBMENU(ledColSelMenu)
  ,EXIT("<Back")
);

MENU(sub5Menu,"LED pt5",showEvent,anyEvent,wrapStyle
  ,FIELD(stLed5,"Start","",stLed5,NUM_LEDS,1,0,doNothing,enterEvent,wrapStyle)
  ,FIELD(endLed5,"End","",stLed5,NUM_LEDS,1,0,doNothing,enterEvent,wrapStyle)
  ,SUBMENU(ColorPt5)
  ,SUBMENU(ledColSelMenu5)
  ,OP("Save Part 5",fsWrite5,enterEvent)
  ,OP("Load Part 5",fsRead5,enterEvent)
  ,EXIT("<Back")
);

void setLedColpt6(){
  for(int colLed = stLed6; colLed < endLed6;  colLed = colLed + 2){
    leds[colLed] = CRGB( red6, green6, blue6) ;
  }
  FastLED.show();
	stLed7 = endLed6;
	endLed7 = NUM_LEDS;
}

result ledCol1Pt6() {
  red6 = 220; green6 = 20; blue6 = 60;
	setLedColpt6();
  return proceed;
}

result ledCol2Pt6() {
  red6 = 240; green6 = 128; blue6 = 128;
	setLedColpt6();
  return proceed;
}

result ledCol3Pt6() {
  red6 = 255; green6 = 20; blue6 = 147;
	setLedColpt6();
  return proceed;
}

result ledCol4Pt6() {
  red6 = 255; green6 = 140; blue6 = 0;
	setLedColpt6();
  return proceed;
}

result ledCol5Pt6() {
  red6 = 192; green6 = 192; blue6 = 192;
	setLedColpt6();
  return proceed;
}

result ledCol6Pt6() {
  red6 = 255; green6 = 215; blue6 = 0;
	setLedColpt6();
  return proceed;
}

result ledCol7Pt6() {
  red6 = 218; green6 = 165; blue6 = 32;
	setLedColpt6();
  return proceed;
}

result ledCol8Pt6() {
  red6 = 139; green6 = 69; blue6 = 19;
	setLedColpt6();
  return proceed;
}

result ledCol9Pt6() {
  red6 = 186; green6 = 85; blue6 = 211;
	setLedColpt6();
  return proceed;
}

result ledCol10Pt6() {
  red6 = 128; green6 = 0; blue6 = 128;
	setLedColpt6();
  return proceed;
}

result ledCol11Pt6() {
  red6 = 124; green6 = 252; blue6 = 0;
	setLedColpt6();
  return proceed;
}

result ledCol12Pt6() {
  red6 = 50; green6 = 205; blue6 = 50;
	setLedColpt6();
  return proceed;
}

result ledCol13Pt6() {
  red6 = 154; green6 = 205; blue6 = 50;
	setLedColpt6();
  return proceed;
}

result ledCol14Pt6() {
  red6 = 0; green6 = 255; blue6 = 255;
	setLedColpt6();
  return proceed;
}

result ledCol15Pt6() {
  red6 = 0; green6 = 206; blue6 = 209;
	setLedColpt6();
  return proceed;
}

result ledCol16Pt6() {
  red6 = 30; green6 = 144; blue6 = 255;
	setLedColpt6();
  return proceed;
}

result ledCol17Pt6() {
  red6 = 0; green6 = 0; blue6 = 0;
	setLedColpt6();
  return proceed;
}

int ledColSel6=-1;
CHOOSE(ledColSel6,ledColSelMenu6,"Col",doNothing,noEvent,wrapStyle
  ,VALUE("Crimson"			,1,ledCol1Pt6,anyEvent)
//  ,VALUE("Light coral",2,ledCol2Pt6,enterEvent)
  ,VALUE("Dpink"				,3,ledCol3Pt6,anyEvent)
  ,VALUE("Dorange"			,4,ledCol4Pt6,anyEvent)
  ,VALUE("Silver"				,5,ledCol5Pt6,anyEvent)
  ,VALUE("Gold"					,6,ledCol6Pt6,anyEvent)
  ,VALUE("Goldenrod"		,7,ledCol7Pt6,anyEvent)
  ,VALUE("Sadbrown"			,8,ledCol8Pt6,anyEvent)
  ,VALUE("MedOrchid"		,9,ledCol9Pt6,anyEvent)
  ,VALUE("Purple"				,10,ledCol10Pt6,anyEvent)
  ,VALUE("Lawngreen"		,11,ledCol11Pt6,anyEvent)
  ,VALUE("Limegreen"		,12,ledCol12Pt6,anyEvent)
  ,VALUE("Yellgreen"		,13,ledCol13Pt6,anyEvent)
  ,VALUE("Aqua"					,14,ledCol14Pt6,anyEvent)
//  ,VALUE("Darkturquoise",15,ledCol15Pt6,anyEvent)
  ,VALUE("Dodgeblue"		,16,ledCol16Pt6,anyEvent)
  ,VALUE("Off"					,17,ledCol17Pt6,anyEvent)
  ,VALUE("Cancel"				,-1,doNothing,noEvent)
);

result LEDcoL6() { 
	for(int colLed = stLed6; colLed < endLed6;  colLed = colLed + 2){
    leds[colLed] = CRGB( red6, green6, blue6) ;
  }
  FastLED.show();
  return proceed;
};

result fsWrite6(eventMask e,navNode& nav, prompt &item) { 
	writeSDSettings(SPIFFS, "/Part6", "stLed6", stLed6, "endLed6", endLed6, "red6", red6, "green6", green6, "blue6", blue6);
  return proceed;
};

result fsRead6() { 
	readSDSettings(SPIFFS, "/Part6");
	LEDcoL6();
  return proceed;
};

MENU(ColorPt6,"RGB pt6",showEvent,anyEvent,noStyle
  ,FIELD(red6,"Red","",red6,255,1,0,LEDcoL6,enterEvent/*noEvent*/,wrapStyle)
  ,FIELD(green6,"Green","",green6,255,1,0,LEDcoL6,enterEvent/*noEvent*/,wrapStyle)
  ,FIELD(blue6,"Blue","",blue6,255,1,0,LEDcoL6,enterEvent/*noEvent*/,wrapStyle)
//  ,SUBMENU(ledColSelMenu)
  ,EXIT("<Back")
);

MENU(sub6Menu,"LED pt6",showEvent,anyEvent,wrapStyle
  ,FIELD(stLed6,"Start","",stLed6,NUM_LEDS,1,0,doNothing,enterEvent,wrapStyle)
  ,FIELD(endLed6,"End","",stLed6,NUM_LEDS,1,0,doNothing,enterEvent,wrapStyle)
  ,SUBMENU(ColorPt6)
  ,SUBMENU(ledColSelMenu6)
  ,OP("Save Part 6",fsWrite6,enterEvent)
  ,OP("Load Part 6",fsRead6,enterEvent)
  ,EXIT("<Back")
);

void setLedColpt7(){
  for(int colLed = stLed7; colLed < endLed7;  colLed = colLed + 2){
    leds[colLed] = CRGB( red7, green7, blue7) ;
  }
  FastLED.show();
	stLed8 = endLed7;
	endLed8 = NUM_LEDS;
}

result ledCol1Pt7() {
  red7 = 220; green7 = 20; blue7 = 60;
	setLedColpt7();
  return proceed;
}

result ledCol2Pt7() {
  red7 = 240; green7 = 128; blue7 = 128;
	setLedColpt7();
  return proceed;
}

result ledCol3Pt7() {
  red7 = 255; green7 = 20; blue7 = 147;
	setLedColpt7();
  return proceed;
}

result ledCol4Pt7() {
  red7 = 255; green7 = 140; blue7 = 0;
	setLedColpt7();
  return proceed;
}

result ledCol5Pt7() {
  red7 = 192; green7 = 192; blue7 = 192;
	setLedColpt7();
  return proceed;
}

result ledCol6Pt7() {
  red7 = 255; green7 = 215; blue7 = 0;
	setLedColpt7();
  return proceed;
}

result ledCol7Pt7() {
  red7 = 218; green7 = 165; blue7 = 32;
	setLedColpt7();
  return proceed;
}

result ledCol8Pt7() {
  red7 = 139; green7 = 69; blue7 = 19;
	setLedColpt7();
  return proceed;
}

result ledCol9Pt7() {
  red7 = 186; green7 = 85; blue7 = 211;
	setLedColpt7();
  return proceed;
}

result ledCol10Pt7() {
  red7 = 128; green7 = 0; blue7 = 128;
	setLedColpt7();
  return proceed;
}

result ledCol11Pt7() {
  red7 = 124; green7 = 252; blue7 = 0;
	setLedColpt7();
  return proceed;
}

result ledCol12Pt7() {
  red7 = 50; green7 = 205; blue7 = 50;
	setLedColpt7();
  return proceed;
}

result ledCol13Pt7() {
  red7 = 154; green7 = 205; blue7 = 50;
	setLedColpt7();
  return proceed;
}

result ledCol14Pt7() {
  red7 = 0; green7 = 255; blue7 = 255;
	setLedColpt7();
  return proceed;
}

result ledCol15Pt7() {
  red7 = 0; green7 = 206; blue7 = 209;
	setLedColpt7();
  return proceed;
}

result ledCol16Pt7() {
  red7 = 30; green7 = 144; blue7 = 255;
	setLedColpt7();
  return proceed;
}

result ledCol17Pt7() {
  red7 = 0; green7 = 0; blue7 = 0;
	setLedColpt7();
  return proceed;
}

int ledColSel7=-1;
CHOOSE(ledColSel7,ledColSelMenu7,"Col",doNothing,noEvent,wrapStyle
  ,VALUE("Crimson"			,1,ledCol1Pt7,anyEvent)
//  ,VALUE("Light coral",2,ledCol2Pt7,enterEvent)
  ,VALUE("Dpink"				,3,ledCol3Pt7,anyEvent)
  ,VALUE("Dorange"			,4,ledCol4Pt7,anyEvent)
  ,VALUE("Silver"				,5,ledCol5Pt7,anyEvent)
  ,VALUE("Gold"					,6,ledCol6Pt7,anyEvent)
  ,VALUE("Goldenrod"		,7,ledCol7Pt7,anyEvent)
  ,VALUE("Sadbrown"			,8,ledCol8Pt7,anyEvent)
  ,VALUE("MedOrchid"		,9,ledCol9Pt7,anyEvent)
  ,VALUE("Purple"				,10,ledCol10Pt7,anyEvent)
  ,VALUE("Lawngreen"		,11,ledCol11Pt7,anyEvent)
  ,VALUE("Limegreen"		,12,ledCol12Pt7,anyEvent)
  ,VALUE("Yellgreen"		,13,ledCol13Pt7,anyEvent)
  ,VALUE("Aqua"					,14,ledCol14Pt7,anyEvent)
//  ,VALUE("Darkturquoise",15,ledCol15Pt7,anyEvent)
  ,VALUE("Dodgeblue"		,16,ledCol16Pt7,anyEvent)
  ,VALUE("Off"					,17,ledCol17Pt7,anyEvent)
  ,VALUE("Cancel"				,-1,doNothing,noEvent)
);

result LEDcoL7() { 
	for(int colLed = stLed7; colLed < endLed7;  colLed = colLed + 2){
    leds[colLed] = CRGB( red7, green7, blue7) ;
  }
  FastLED.show();
  return proceed;
};

result fsWrite7(eventMask e,navNode& nav, prompt &item) { 
	writeSDSettings(SPIFFS, "/Part7", "stLed7", stLed7, "endLed7", endLed7, "red7", red7, "green7", green7, "blue7", blue7);
  return proceed;
};

result fsRead7() { 
	readSDSettings(SPIFFS, "/Part7");
	LEDcoL7();
  return proceed;
};

MENU(ColorPt7,"RGB pt7",showEvent,anyEvent,noStyle
  ,FIELD(red7,"Red","",red7,255,1,0,LEDcoL7,enterEvent/*noEvent*/,wrapStyle)
  ,FIELD(green7,"Green","",green7,255,1,0,LEDcoL7,enterEvent/*noEvent*/,wrapStyle)
  ,FIELD(blue7,"Blue","",blue7,255,1,0,LEDcoL7,enterEvent/*noEvent*/,wrapStyle)
//  ,SUBMENU(ledColSelMenu)
  ,EXIT("<Back")
);

MENU(sub7Menu,"LED pt7",showEvent,anyEvent,wrapStyle
  ,FIELD(stLed7,"Start","",stLed7,NUM_LEDS,1,0,doNothing,enterEvent,wrapStyle)
  ,FIELD(endLed7,"End","",stLed7,NUM_LEDS,1,0,doNothing,enterEvent,wrapStyle)
  ,SUBMENU(ColorPt7)
  ,SUBMENU(ledColSelMenu7)
  ,OP("Save Part 7",fsWrite7,enterEvent)
  ,OP("Load Part 7",fsRead7,enterEvent)
  ,EXIT("<Back")
);

void setLedColpt8(){
  for(int colLed = stLed8; colLed < endLed8;  colLed = colLed + 2){
    leds[colLed] = CRGB( red8, green8, blue8) ;
  }
  FastLED.show();
	stLed9 = endLed8;
	endLed9 = NUM_LEDS;
}

result ledCol1Pt8() {
  red8 = 220; green8 = 20; blue8 = 60;
	setLedColpt8();
  return proceed;
}

result ledCol2Pt8() {
  red8 = 240; green8 = 128; blue8 = 128;
	setLedColpt8();
  return proceed;
}

result ledCol3Pt8() {
  red8 = 255; green8 = 20; blue8 = 147;
	setLedColpt8();
  return proceed;
}

result ledCol4Pt8() {
  red8 = 255; green8 = 140; blue8 = 0;
	setLedColpt8();
  return proceed;
}

result ledCol5Pt8() {
  red8 = 192; green8 = 192; blue8 = 192;
	setLedColpt8();
  return proceed;
}

result ledCol6Pt8() {
  red8 = 255; green8 = 215; blue8 = 0;
	setLedColpt8();
  return proceed;
}

result ledCol7Pt8() {
  red8 = 218; green8 = 165; blue8 = 32;
	setLedColpt8();
  return proceed;
}

result ledCol8Pt8() {
  red8 = 139; green8 = 69; blue8 = 19;
	setLedColpt8();
  return proceed;
}

result ledCol9Pt8() {
  red8 = 186; green8 = 85; blue8 = 211;
	setLedColpt8();
  return proceed;
}

result ledCol10Pt8() {
  red8 = 128; green8 = 0; blue8 = 128;
	setLedColpt8();
  return proceed;
}

result ledCol11Pt8() {
  red8 = 124; green8 = 252; blue8 = 0;
	setLedColpt8();
  return proceed;
}

result ledCol12Pt8() {
  red8 = 50; green8 = 205; blue8 = 50;
	setLedColpt8();
  return proceed;
}

result ledCol13Pt8() {
  red8 = 154; green8 = 205; blue8 = 50;
	setLedColpt8();
  return proceed;
}

result ledCol14Pt8() {
  red8 = 0; green8 = 255; blue8 = 255;
	setLedColpt8();
  return proceed;
}

result ledCol15Pt8() {
  red8 = 0; green8 = 206; blue8 = 209;
	setLedColpt8();
  return proceed;
}

result ledCol16Pt8() {
  red8 = 30; green8 = 144; blue8 = 255;
	setLedColpt8();
  return proceed;
}

result ledCol17Pt8() {
  red8 = 0; green8 = 0; blue8 = 0;
	setLedColpt8();
  return proceed;
}

int ledColSel8=-1;
CHOOSE(ledColSel8,ledColSelMenu8,"Col",doNothing,noEvent,wrapStyle
  ,VALUE("Crimson"			,1,ledCol1Pt8,anyEvent)
//  ,VALUE("Light coral",2,ledCol2Pt8,enterEvent)
  ,VALUE("Dpink"				,3,ledCol3Pt8,anyEvent)
  ,VALUE("Dorange"			,4,ledCol4Pt8,anyEvent)
  ,VALUE("Silver"				,5,ledCol5Pt8,anyEvent)
  ,VALUE("Gold"					,6,ledCol6Pt8,anyEvent)
  ,VALUE("Goldenrod"		,7,ledCol7Pt8,anyEvent)
  ,VALUE("Sadbrown"			,8,ledCol8Pt8,anyEvent)
  ,VALUE("MedOrchid"		,9,ledCol9Pt8,anyEvent)
  ,VALUE("Purple"				,10,ledCol10Pt8,anyEvent)
  ,VALUE("Lawngreen"		,11,ledCol11Pt8,anyEvent)
  ,VALUE("Limegreen"		,12,ledCol12Pt8,anyEvent)
  ,VALUE("Yellgreen"		,13,ledCol13Pt8,anyEvent)
  ,VALUE("Aqua"					,14,ledCol14Pt8,anyEvent)
//  ,VALUE("Darkturquoise",15,ledCol15Pt8,anyEvent)
  ,VALUE("Dodgeblue"		,16,ledCol16Pt8,anyEvent)
  ,VALUE("Off"					,17,ledCol17Pt8,anyEvent)
  ,VALUE("Cancel"				,-1,doNothing,noEvent)
);

result LEDcoL8() { 
	for(int colLed = stLed8; colLed < endLed8;  colLed = colLed + 2){
    leds[colLed] = CRGB( red8, green8, blue8) ;
  }
  FastLED.show();
  return proceed;
};

result fsWrite8(eventMask e,navNode& nav, prompt &item) { 
	writeSDSettings(SPIFFS, "/Part8", "stLed8", stLed8, "endLed8", endLed8, "red8", red8, "green8", green8, "blue8", blue8);
  return proceed;
};

result fsRead8() { 
	readSDSettings(SPIFFS, "/Part8");
	LEDcoL8();
  return proceed;
};

MENU(ColorPt8,"RGB pt8",showEvent,anyEvent,noStyle
  ,FIELD(red8,"Red","",red8,255,1,0,LEDcoL8,enterEvent/*noEvent*/,wrapStyle)
  ,FIELD(green8,"Green","",green8,255,1,0,LEDcoL8,enterEvent/*noEvent*/,wrapStyle)
  ,FIELD(blue8,"Blue","",blue8,255,1,0,LEDcoL8,enterEvent/*noEvent*/,wrapStyle)
//  ,SUBMENU(ledColSelMenu)
  ,EXIT("<Back")
);

MENU(sub8Menu,"LED pt8",showEvent,anyEvent,wrapStyle
  ,FIELD(stLed8,"Start","",stLed8,NUM_LEDS,1,0,doNothing,enterEvent,wrapStyle)
  ,FIELD(endLed8,"End","",stLed8,NUM_LEDS,1,0,doNothing,enterEvent,wrapStyle)
  ,SUBMENU(ColorPt8)
  ,SUBMENU(ledColSelMenu8)
  ,OP("Save Part 8",fsWrite8,enterEvent)
  ,OP("Load Part 8",fsRead8,enterEvent)
  ,EXIT("<Back")
);

void setLedColpt9(){
  for(int colLed = stLed9; colLed < endLed9;  colLed = colLed + 2){
    leds[colLed] = CRGB( red9, green9, blue9) ;
  }
  FastLED.show();
	stLed10 = endLed9;
	endLed10 = NUM_LEDS;
}

result ledCol1Pt9() {
  red9 = 220; green9 = 20; blue9 = 60;
	setLedColpt9();
  return proceed;
}

result ledCol2Pt9() {
  red9 = 240; green9 = 128; blue9 = 128;
	setLedColpt9();
  return proceed;
}

result ledCol3Pt9() {
  red9 = 255; green9 = 20; blue9 = 147;
	setLedColpt9();
  return proceed;
}

result ledCol4Pt9() {
  red9 = 255; green9 = 140; blue9 = 0;
	setLedColpt9();
  return proceed;
}

result ledCol5Pt9() {
  red9 = 192; green9 = 192; blue9 = 192;
	setLedColpt9();
  return proceed;
}

result ledCol6Pt9() {
  red9 = 255; green9 = 215; blue9 = 0;
	setLedColpt9();
  return proceed;
}

result ledCol7Pt9() {
  red9 = 218; green9 = 165; blue9 = 32;
	setLedColpt9();
  return proceed;
}

result ledCol8Pt9() {
  red9 = 139; green9 = 69; blue9 = 19;
	setLedColpt9();
  return proceed;
}

result ledCol9Pt9() {
  red9 = 186; green9 = 85; blue9 = 211;
	setLedColpt9();
  return proceed;
}

result ledCol10Pt9() {
  red9 = 128; green9 = 0; blue9 = 128;
	setLedColpt9();
  return proceed;
}

result ledCol11Pt9() {
  red9 = 124; green9 = 252; blue9 = 0;
	setLedColpt9();
  return proceed;
}

result ledCol12Pt9() {
  red9 = 50; green9 = 205; blue9 = 50;
	setLedColpt9();
  return proceed;
}

result ledCol13Pt9() {
  red9 = 154; green9 = 205; blue9 = 50;
	setLedColpt9();
  return proceed;
}

result ledCol14Pt9() {
  red9 = 0; green9 = 255; blue9 = 255;
	setLedColpt9();
  return proceed;
}

result ledCol15Pt9() {
  red9 = 0; green9 = 206; blue9 = 209;
	setLedColpt9();
  return proceed;
}

result ledCol16Pt9() {
  red9 = 30; green9 = 144; blue9 = 255;
	setLedColpt9();
  return proceed;
}

result ledCol17Pt9() {
  red9 = 0; green9 = 0; blue9 = 0;
	setLedColpt9();
  return proceed;
}

int ledColSel9=-1;
CHOOSE(ledColSel9,ledColSelMenu9,"Col",doNothing,noEvent,wrapStyle
  ,VALUE("Crimson"			,1,ledCol1Pt9,anyEvent)
//  ,VALUE("Light coral",2,ledCol2Pt9,enterEvent)
  ,VALUE("Dpink"				,3,ledCol3Pt9,anyEvent)
  ,VALUE("Dorange"			,4,ledCol4Pt9,anyEvent)
  ,VALUE("Silver"				,5,ledCol5Pt9,anyEvent)
  ,VALUE("Gold"					,6,ledCol6Pt9,anyEvent)
  ,VALUE("Goldenrod"		,7,ledCol7Pt9,anyEvent)
  ,VALUE("Sadbrown"			,8,ledCol8Pt9,anyEvent)
  ,VALUE("MedOrchid"		,9,ledCol9Pt9,anyEvent)
  ,VALUE("Purple"				,10,ledCol10Pt9,anyEvent)
  ,VALUE("Lawngreen"		,11,ledCol11Pt9,anyEvent)
  ,VALUE("Limegreen"		,12,ledCol12Pt9,anyEvent)
  ,VALUE("Yellgreen"		,13,ledCol13Pt9,anyEvent)
  ,VALUE("Aqua"					,14,ledCol14Pt9,anyEvent)
//  ,VALUE("Darkturquoise",15,ledCol15Pt9,anyEvent)
  ,VALUE("Dodgeblue"		,16,ledCol16Pt9,anyEvent)
  ,VALUE("Off"					,17,ledCol17Pt9,anyEvent)
  ,VALUE("Cancel"				,-1,doNothing,noEvent)
);

result LEDcoL9() { 
	for(int colLed = stLed9; colLed < endLed9;  colLed = colLed + 2){
    leds[colLed] = CRGB( red9, green9, blue9) ;
  }
  FastLED.show();
  return proceed;
};

result fsWrite9(eventMask e,navNode& nav, prompt &item) { 
	writeSDSettings(SPIFFS, "/Part9", "stLed9", stLed9, "endLed9", endLed9, "red9", red9, "green9", green9, "blue9", blue9);
  return proceed;
};

result fsRead9() { 
	readSDSettings(SPIFFS, "/Part9");
	LEDcoL9();
  return proceed;
};

MENU(ColorPt9,"RGB pt9",showEvent,anyEvent,noStyle
  ,FIELD(red9,"Red","",red9,255,1,0,LEDcoL9,enterEvent/*noEvent*/,wrapStyle)
  ,FIELD(green9,"Green","",green9,255,1,0,LEDcoL9,enterEvent/*noEvent*/,wrapStyle)
  ,FIELD(blue9,"Blue","",blue9,255,1,0,LEDcoL9,enterEvent/*noEvent*/,wrapStyle)
//  ,SUBMENU(ledColSelMenu)
  ,EXIT("<Back")
);

MENU(sub9Menu,"LED pt9",showEvent,anyEvent,wrapStyle
  ,FIELD(stLed9,"Start","",stLed9,NUM_LEDS,1,0,doNothing,enterEvent,wrapStyle)
  ,FIELD(endLed9,"End","",stLed9,NUM_LEDS,1,0,doNothing,enterEvent,wrapStyle)
  ,SUBMENU(ColorPt9)
  ,SUBMENU(ledColSelMenu9)
  ,OP("Save Part 9",fsWrite9,enterEvent)
  ,OP("Load Part 9",fsRead9,enterEvent)
  ,EXIT("<Back")
);

void setLedColpt10(){
  for(int colLed = stLed10; colLed < endLed10;  colLed = colLed + 2){
    leds[colLed] = CRGB( red10, green10, blue10) ;
  }
  FastLED.show();
	stLed11 = endLed10;
	endLed11 = NUM_LEDS;
}

result ledCol1Pt10() {
  red10 = 220; green10 = 20; blue10 = 60;
	setLedColpt10();
  return proceed;
}

result ledCol2Pt10() {
  red10 = 240; green10 = 128; blue10 = 128;
	setLedColpt10();
  return proceed;
}

result ledCol3Pt10() {
  red10 = 255; green10 = 20; blue10 = 147;
	setLedColpt10();
  return proceed;
}

result ledCol4Pt10() {
  red10 = 255; green10 = 140; blue10 = 0;
	setLedColpt10();
  return proceed;
}

result ledCol5Pt10() {
  red10 = 192; green10 = 192; blue10 = 192;
	setLedColpt10();
  return proceed;
}

result ledCol6Pt10() {
  red10 = 255; green10 = 215; blue10 = 0;
	setLedColpt10();
  return proceed;
}

result ledCol7Pt10() {
  red10 = 218; green10 = 165; blue10 = 32;
	setLedColpt10();
  return proceed;
}

result ledCol8Pt10() {
  red10 = 139; green10 = 69; blue10 = 19;
	setLedColpt10();
  return proceed;
}

result ledCol9Pt10() {
  red10 = 186; green10 = 85; blue10 = 211;
	setLedColpt10();
  return proceed;
}

result ledCol10Pt10() {
  red10 = 128; green10 = 0; blue10 = 128;
	setLedColpt10();
  return proceed;
}

result ledCol11Pt10() {
  red10 = 124; green10 = 252; blue10 = 0;
	setLedColpt10();
  return proceed;
}

result ledCol12Pt10() {
  red10 = 50; green10 = 205; blue10 = 50;
	setLedColpt10();
  return proceed;
}

result ledCol13Pt10() {
  red10 = 154; green10 = 205; blue10 = 50;
	setLedColpt10();
  return proceed;
}

result ledCol14Pt10() {
  red10 = 0; green10 = 255; blue10 = 255;
	setLedColpt10();
  return proceed;
}

result ledCol15Pt10() {
  red10 = 0; green10 = 206; blue10 = 209;
	setLedColpt10();
  return proceed;
}

result ledCol16Pt10() {
  red10 = 30; green10 = 144; blue10 = 255;
	setLedColpt10();
  return proceed;
}

result ledCol17Pt10() {
  red10 = 0; green10 = 0; blue10 = 0;
	setLedColpt10();
  return proceed;
}

int ledColSel10=-1;
CHOOSE(ledColSel10,ledColSelMenu10,"Col",doNothing,noEvent,wrapStyle
  ,VALUE("Crimson"			,1,ledCol1Pt10,anyEvent)
//  ,VALUE("Light coral",2,ledCol2Pt10,enterEvent)
  ,VALUE("Dpink"				,3,ledCol3Pt10,anyEvent)
  ,VALUE("Dorange"			,4,ledCol4Pt10,anyEvent)
  ,VALUE("Silver"				,5,ledCol5Pt10,anyEvent)
  ,VALUE("Gold"					,6,ledCol6Pt10,anyEvent)
  ,VALUE("Goldenrod"		,7,ledCol7Pt10,anyEvent)
  ,VALUE("Sadbrown"			,8,ledCol8Pt10,anyEvent)
  ,VALUE("MedOrchid"		,9,ledCol9Pt10,anyEvent)
  ,VALUE("Purple"				,10,ledCol10Pt10,anyEvent)
  ,VALUE("Lawngreen"		,11,ledCol11Pt10,anyEvent)
  ,VALUE("Limegreen"		,12,ledCol12Pt10,anyEvent)
  ,VALUE("Yellgreen"		,13,ledCol13Pt10,anyEvent)
  ,VALUE("Aqua"					,14,ledCol14Pt10,anyEvent)
//  ,VALUE("Darkturquoise",15,ledCol15Pt10,anyEvent)
  ,VALUE("Dodgeblue"		,16,ledCol16Pt10,anyEvent)
  ,VALUE("Off"					,17,ledCol17Pt10,anyEvent)
  ,VALUE("Cancel"				,-1,doNothing,noEvent)
);

result LEDcoL10() { 
	for(int colLed = stLed10; colLed < endLed10;  colLed = colLed + 2){
    leds[colLed] = CRGB( red10, green10, blue10) ;
  }
  FastLED.show();
  return proceed;
};

result fsWrite10(eventMask e,navNode& nav, prompt &item) { 
	writeSDSettings(SPIFFS, "/Part10", "stLed10", stLed10, "endLed10", endLed10, "red10", red10, "green10", green10, "blue10", blue10);
  return proceed;
};

result fsRead10() { 
	readSDSettings(SPIFFS, "/Part10");
	LEDcoL10();
  return proceed;
};

MENU(ColorPt10,"RGB pt10",showEvent,anyEvent,noStyle
  ,FIELD(red10,"Red","",red10,255,1,0,LEDcoL10,enterEvent/*noEvent*/,wrapStyle)
  ,FIELD(green10,"Green","",green10,255,1,0,LEDcoL10,enterEvent/*noEvent*/,wrapStyle)
  ,FIELD(blue10,"Blue","",blue10,255,1,0,LEDcoL10,enterEvent/*noEvent*/,wrapStyle)
//  ,SUBMENU(ledColSelMenu)
  ,EXIT("<Back")
);

MENU(sub10Menu,"LED pt10",showEvent,anyEvent,wrapStyle
  ,FIELD(stLed10,"Start","",stLed10,NUM_LEDS,1,0,doNothing,enterEvent,wrapStyle)
  ,FIELD(endLed10,"End","",stLed10,NUM_LEDS,1,0,doNothing,enterEvent,wrapStyle)
  ,SUBMENU(ColorPt10)
  ,SUBMENU(ledColSelMenu10)
  ,OP("Save Part 10",fsWrite10,enterEvent)
  ,OP("Load Part 10",fsRead10,enterEvent)
  ,EXIT("<Back")
);

void setLedColpt11(){
  for(int colLed = stLed11; colLed < endLed11;  colLed = colLed + 2){
    leds[colLed] = CRGB( red11, green11, blue11) ;
  }
  FastLED.show();
	stLed12 = endLed11;
	endLed12 = NUM_LEDS;
}

result ledCol1Pt11() {
  red11 = 220; green11 = 20; blue11 = 60;
	setLedColpt11();
  return proceed;
}

result ledCol2Pt11() {
  red11 = 240; green11 = 128; blue11 = 128;
	setLedColpt11();
  return proceed;
}

result ledCol3Pt11() {
  red11 = 255; green11 = 20; blue11 = 147;
	setLedColpt11();
  return proceed;
}

result ledCol4Pt11() {
  red11 = 255; green11 = 140; blue11 = 0;
	setLedColpt11();
  return proceed;
}

result ledCol5Pt11() {
  red11 = 192; green11 = 192; blue11 = 192;
	setLedColpt11();
  return proceed;
}

result ledCol6Pt11() {
  red11 = 255; green11 = 215; blue11 = 0;
	setLedColpt11();
  return proceed;
}

result ledCol7Pt11() {
  red11 = 218; green11 = 165; blue11 = 32;
	setLedColpt11();
  return proceed;
}

result ledCol8Pt11() {
  red11 = 139; green11 = 69; blue11 = 19;
	setLedColpt11();
  return proceed;
}

result ledCol9Pt11() {
  red11 = 186; green11 = 85; blue11 = 211;
	setLedColpt11();
  return proceed;
}

result ledCol10Pt11() {
  red11 = 128; green11 = 0; blue11 = 128;
	setLedColpt11();
  return proceed;
}

result ledCol11Pt11() {
  red11 = 124; green11 = 252; blue11 = 0;
	setLedColpt11();
  return proceed;
}

result ledCol12Pt11() {
  red11 = 50; green11 = 205; blue11 = 50;
	setLedColpt11();
  return proceed;
}

result ledCol13Pt11() {
  red11 = 154; green11 = 205; blue11 = 50;
	setLedColpt11();
  return proceed;
}

result ledCol14Pt11() {
  red11 = 0; green11 = 255; blue11 = 255;
	setLedColpt11();
  return proceed;
}

result ledCol15Pt11() {
  red11 = 0; green11 = 206; blue11 = 209;
	setLedColpt11();
  return proceed;
}

result ledCol16Pt11() {
  red11 = 30; green11 = 144; blue11 = 255;
	setLedColpt11();
  return proceed;
}

result ledCol17Pt11() {
  red11 = 0; green11 = 0; blue11 = 0;
	setLedColpt11();
  return proceed;
}

int ledColSel11=-1;
CHOOSE(ledColSel11,ledColSelMenu11,"Col",doNothing,noEvent,wrapStyle
  ,VALUE("Crimson"			,1,ledCol1Pt11,anyEvent)
//  ,VALUE("Light coral",2,ledCol2Pt11,enterEvent)
  ,VALUE("Dpink"				,3,ledCol3Pt11,anyEvent)
  ,VALUE("Dorange"			,4,ledCol4Pt11,anyEvent)
  ,VALUE("Silver"				,5,ledCol5Pt11,anyEvent)
  ,VALUE("Gold"					,6,ledCol6Pt11,anyEvent)
  ,VALUE("Goldenrod"		,7,ledCol7Pt11,anyEvent)
  ,VALUE("Sadbrown"			,8,ledCol8Pt11,anyEvent)
  ,VALUE("MedOrchid"		,9,ledCol9Pt11,anyEvent)
  ,VALUE("Purple"				,10,ledCol10Pt11,anyEvent)
  ,VALUE("Lawngreen"		,11,ledCol11Pt11,anyEvent)
  ,VALUE("Limegreen"		,12,ledCol12Pt11,anyEvent)
  ,VALUE("Yellgreen"		,13,ledCol13Pt11,anyEvent)
  ,VALUE("Aqua"					,14,ledCol14Pt11,anyEvent)
//  ,VALUE("Darkturquoise",15,ledCol15Pt11,anyEvent)
  ,VALUE("Dodgeblue"		,16,ledCol16Pt11,anyEvent)
  ,VALUE("Off"					,17,ledCol17Pt11,anyEvent)
  ,VALUE("Cancel"				,-1,doNothing,noEvent)
);

result LEDcoL11() { 
	for(int colLed = stLed11; colLed < endLed11;  colLed = colLed + 2){
    leds[colLed] = CRGB( red11, green11, blue11) ;
  }
  FastLED.show();
  return proceed;
};

result fsWrite11(eventMask e,navNode& nav, prompt &item) { 
	writeSDSettings(SPIFFS, "/Part11", "stLed11", stLed11, "endLed11", endLed11, "red11", red11, "green11", green11, "blue11", blue11);
  return proceed;
};

result fsRead11() { 
	readSDSettings(SPIFFS, "/Part11");
	LEDcoL11();
  return proceed;
};

MENU(ColorPt11,"RGB pt11",showEvent,anyEvent,noStyle
  ,FIELD(red11,"Red","",red11,255,1,0,LEDcoL11,enterEvent/*noEvent*/,wrapStyle)
  ,FIELD(green11,"Green","",green11,255,1,0,LEDcoL11,enterEvent/*noEvent*/,wrapStyle)
  ,FIELD(blue11,"Blue","",blue11,255,1,0,LEDcoL11,enterEvent/*noEvent*/,wrapStyle)
//  ,SUBMENU(ledColSelMenu)
  ,EXIT("<Back")
);

MENU(sub11Menu,"LED pt11",showEvent,anyEvent,wrapStyle
  ,FIELD(stLed11,"Start","",stLed11,NUM_LEDS,1,0,doNothing,enterEvent,wrapStyle)
  ,FIELD(endLed11,"End","",stLed11,NUM_LEDS,1,0,doNothing,enterEvent,wrapStyle)
  ,SUBMENU(ColorPt11)
  ,SUBMENU(ledColSelMenu11)
  ,OP("Save Part 11",fsWrite11,enterEvent)
  ,OP("Load Part 11",fsRead11,enterEvent)
  ,EXIT("<Back")
);

void setLedColpt12(){
  for(int colLed = stLed12; colLed < endLed12;  colLed = colLed + 2){
    leds[colLed] = CRGB( red12, green12, blue12) ;
  }
  FastLED.show();
	stLed13 = endLed12;
	endLed13 = NUM_LEDS;
}

result ledCol1Pt12() {
  red12 = 220; green12 = 20; blue12 = 60;
	setLedColpt12();
  return proceed;
}

result ledCol2Pt12() {
  red12 = 240; green12 = 128; blue12 = 128;
	setLedColpt12();
  return proceed;
}

result ledCol3Pt12() {
  red12 = 255; green12 = 20; blue12 = 147;
	setLedColpt12();
  return proceed;
}

result ledCol4Pt12() {
  red12 = 255; green12 = 140; blue12 = 0;
	setLedColpt12();
  return proceed;
}

result ledCol5Pt12() {
  red12 = 192; green12 = 192; blue12 = 192;
	setLedColpt12();
  return proceed;
}

result ledCol6Pt12() {
  red12 = 255; green12 = 215; blue12 = 0;
	setLedColpt12();
  return proceed;
}

result ledCol7Pt12() {
  red12 = 218; green12 = 165; blue12 = 32;
	setLedColpt12();
  return proceed;
}

result ledCol8Pt12() {
  red12 = 139; green12 = 69; blue12 = 19;
	setLedColpt12();
  return proceed;
}

result ledCol9Pt12() {
  red12 = 186; green12 = 85; blue12 = 211;
	setLedColpt12();
  return proceed;
}

result ledCol10Pt12() {
  red12 = 128; green12 = 0; blue12 = 128;
	setLedColpt12();
  return proceed;
}

result ledCol11Pt12() {
  red12 = 124; green12 = 252; blue12 = 0;
	setLedColpt12();
  return proceed;
}

result ledCol12Pt12() {
  red12 = 50; green12 = 205; blue12 = 50;
	setLedColpt12();
  return proceed;
}

result ledCol13Pt12() {
  red12 = 154; green12 = 205; blue12 = 50;
	setLedColpt12();
  return proceed;
}

result ledCol14Pt12() {
  red12 = 0; green12 = 255; blue12 = 255;
	setLedColpt12();
  return proceed;
}

result ledCol15Pt12() {
  red12 = 0; green12 = 206; blue12 = 209;
	setLedColpt12();
  return proceed;
}

result ledCol16Pt12() {
  red12 = 30; green12 = 144; blue12 = 255;
	setLedColpt12();
  return proceed;
}

result ledCol17Pt12() {
  red12 = 0; green12 = 0; blue12 = 0;
	setLedColpt12();
  return proceed;
}

int ledColSel12=-1;
CHOOSE(ledColSel12,ledColSelMenu12,"Col",doNothing,noEvent,wrapStyle
  ,VALUE("Crimson"			,1,ledCol1Pt12,anyEvent)
//  ,VALUE("Light coral",2,ledCol2Pt12,enterEvent)
  ,VALUE("Dpink"				,3,ledCol3Pt12,anyEvent)
  ,VALUE("Dorange"			,4,ledCol4Pt12,anyEvent)
  ,VALUE("Silver"				,5,ledCol5Pt12,anyEvent)
  ,VALUE("Gold"					,6,ledCol6Pt12,anyEvent)
  ,VALUE("Goldenrod"		,7,ledCol7Pt12,anyEvent)
  ,VALUE("Sadbrown"			,8,ledCol8Pt12,anyEvent)
  ,VALUE("MedOrchid"		,9,ledCol9Pt12,anyEvent)
  ,VALUE("Purple"				,10,ledCol10Pt12,anyEvent)
  ,VALUE("Lawngreen"		,11,ledCol11Pt12,anyEvent)
  ,VALUE("Limegreen"		,12,ledCol12Pt12,anyEvent)
  ,VALUE("Yellgreen"		,13,ledCol13Pt12,anyEvent)
  ,VALUE("Aqua"					,14,ledCol14Pt12,anyEvent)
//  ,VALUE("Darkturquoise",15,ledCol15Pt12,anyEvent)
  ,VALUE("Dodgeblue"		,16,ledCol16Pt12,anyEvent)
  ,VALUE("Off"					,17,ledCol17Pt12,anyEvent)
  ,VALUE("Cancel"				,-1,doNothing,noEvent)
);

result LEDcoL12() { 
	for(int colLed = stLed12; colLed < endLed12;  colLed = colLed + 2){
    leds[colLed] = CRGB( red12, green12, blue12) ;
  }
  FastLED.show();
  return proceed;
};

result fsWrite12(eventMask e,navNode& nav, prompt &item) { 
	writeSDSettings(SPIFFS, "/Part12", "stLed12", stLed12, "endLed12", endLed12, "red12", red12, "green12", green12, "blue12", blue12);
  return proceed;
};

result fsRead12() { 
	readSDSettings(SPIFFS, "/Part12");
	LEDcoL12();
  return proceed;
};

MENU(ColorPt12,"RGB pt12",showEvent,anyEvent,noStyle
  ,FIELD(red12,"Red","",red12,255,1,0,LEDcoL12,enterEvent/*noEvent*/,wrapStyle)
  ,FIELD(green12,"Green","",green12,255,1,0,LEDcoL12,enterEvent/*noEvent*/,wrapStyle)
  ,FIELD(blue12,"Blue","",blue12,255,1,0,LEDcoL12,enterEvent/*noEvent*/,wrapStyle)
//  ,SUBMENU(ledColSelMenu)
  ,EXIT("<Back")
);

MENU(sub12Menu,"LED pt12",showEvent,anyEvent,wrapStyle
  ,FIELD(stLed12,"Start","",stLed12,NUM_LEDS,1,0,doNothing,enterEvent,wrapStyle)
  ,FIELD(endLed12,"End","",stLed12,NUM_LEDS,1,0,doNothing,enterEvent,wrapStyle)
  ,SUBMENU(ColorPt12)
  ,SUBMENU(ledColSelMenu12)
  ,OP("Save Part 12",fsWrite12,enterEvent)
  ,OP("Load Part 12",fsRead12,enterEvent)
  ,EXIT("<Back")
);

void setLedColpt13(){
  for(int colLed = stLed13; colLed < endLed13;  colLed = colLed + 2){
    leds[colLed] = CRGB( red13, green13, blue13) ;
  }
  FastLED.show();
	stLed14 = endLed13;
	endLed14 = NUM_LEDS;
}

result ledCol1Pt13() {
  red13 = 220; green13 = 20; blue13 = 60;
	setLedColpt13();
  return proceed;
}

result ledCol2Pt13() {
  red13 = 240; green13 = 128; blue13 = 128;
	setLedColpt13();
  return proceed;
}

result ledCol3Pt13() {
  red13 = 255; green13 = 20; blue13 = 147;
	setLedColpt13();
  return proceed;
}

result ledCol4Pt13() {
  red13 = 255; green13 = 140; blue13 = 0;
	setLedColpt13();
  return proceed;
}

result ledCol5Pt13() {
  red13 = 192; green13 = 192; blue13 = 192;
	setLedColpt13();
  return proceed;
}

result ledCol6Pt13() {
  red13 = 255; green13 = 215; blue13 = 0;
	setLedColpt13();
  return proceed;
}

result ledCol7Pt13() {
  red13 = 218; green13 = 165; blue13 = 32;
	setLedColpt13();
  return proceed;
}

result ledCol8Pt13() {
  red13 = 139; green13 = 69; blue13 = 19;
	setLedColpt13();
  return proceed;
}

result ledCol9Pt13() {
  red13 = 186; green13 = 85; blue13 = 211;
	setLedColpt13();
  return proceed;
}

result ledCol10Pt13() {
  red13 = 128; green13 = 0; blue13 = 128;
	setLedColpt13();
  return proceed;
}

result ledCol11Pt13() {
  red13 = 124; green13 = 252; blue13 = 0;
	setLedColpt13();
  return proceed;
}

result ledCol12Pt13() {
  red13 = 50; green13 = 205; blue13 = 50;
	setLedColpt13();
  return proceed;
}

result ledCol13Pt13() {
  red13 = 154; green13 = 205; blue13 = 50;
	setLedColpt13();
  return proceed;
}

result ledCol14Pt13() {
  red13 = 0; green13 = 255; blue13 = 255;
	setLedColpt13();
  return proceed;
}

result ledCol15Pt13() {
  red13 = 0; green13 = 206; blue13 = 209;
	setLedColpt13();
  return proceed;
}

result ledCol16Pt13() {
  red13 = 30; green13 = 144; blue13 = 255;
	setLedColpt13();
  return proceed;
}

result ledCol17Pt13() {
  red13 = 0; green13 = 0; blue13 = 0;
	setLedColpt13();
  return proceed;
}

int ledColSel13=-1;
CHOOSE(ledColSel13,ledColSelMenu13,"Col",doNothing,noEvent,wrapStyle
  ,VALUE("Crimson"			,1,ledCol1Pt13,anyEvent)
//  ,VALUE("Light coral",2,ledCol2Pt13,enterEvent)
  ,VALUE("Dpink"				,3,ledCol3Pt13,anyEvent)
  ,VALUE("Dorange"			,4,ledCol4Pt13,anyEvent)
  ,VALUE("Silver"				,5,ledCol5Pt13,anyEvent)
  ,VALUE("Gold"					,6,ledCol6Pt13,anyEvent)
  ,VALUE("Goldenrod"		,7,ledCol7Pt13,anyEvent)
  ,VALUE("Sadbrown"			,8,ledCol8Pt13,anyEvent)
  ,VALUE("MedOrchid"		,9,ledCol9Pt13,anyEvent)
  ,VALUE("Purple"				,10,ledCol10Pt13,anyEvent)
  ,VALUE("Lawngreen"		,11,ledCol11Pt13,anyEvent)
  ,VALUE("Limegreen"		,12,ledCol12Pt13,anyEvent)
  ,VALUE("Yellgreen"		,13,ledCol13Pt13,anyEvent)
  ,VALUE("Aqua"					,14,ledCol14Pt13,anyEvent)
//  ,VALUE("Darkturquoise",15,ledCol15Pt13,anyEvent)
  ,VALUE("Dodgeblue"		,16,ledCol16Pt13,anyEvent)
  ,VALUE("Off"					,17,ledCol17Pt13,anyEvent)
  ,VALUE("Cancel"				,-1,doNothing,noEvent)
);

result LEDcoL13() { 
	for(int colLed = stLed13; colLed < endLed13;  colLed = colLed + 2){
    leds[colLed] = CRGB( red13, green13, blue13) ;
  }
  FastLED.show();
  return proceed;
};

result fsWrite13(eventMask e,navNode& nav, prompt &item) { 
	writeSDSettings(SPIFFS, "/Part13", "stLed13", stLed13, "endLed13", endLed13, "red13", red13, "green13", green13, "blue13", blue13);
  return proceed;
};

result fsRead13() { 
	readSDSettings(SPIFFS, "/Part13");
	LEDcoL13();
  return proceed;
};

MENU(ColorPt13,"RGB pt13",showEvent,anyEvent,noStyle
  ,FIELD(red13,"Red","",red13,255,1,0,LEDcoL13,enterEvent/*noEvent*/,wrapStyle)
  ,FIELD(green13,"Green","",green13,255,1,0,LEDcoL13,enterEvent/*noEvent*/,wrapStyle)
  ,FIELD(blue13,"Blue","",blue13,255,1,0,LEDcoL13,enterEvent/*noEvent*/,wrapStyle)
//  ,SUBMENU(ledColSelMenu)
  ,EXIT("<Back")
);

MENU(sub13Menu,"LED pt13",showEvent,anyEvent,wrapStyle
  ,FIELD(stLed13,"Start","",stLed13,NUM_LEDS,1,0,doNothing,enterEvent,wrapStyle)
  ,FIELD(endLed13,"End","",stLed13,NUM_LEDS,1,0,doNothing,enterEvent,wrapStyle)
  ,SUBMENU(ColorPt13)
  ,SUBMENU(ledColSelMenu13)
  ,OP("Save Part 13",fsWrite13,enterEvent)
  ,OP("Load Part 13",fsRead13,enterEvent)
  ,EXIT("<Back")
);

void setLedColpt14(){
  for(int colLed = stLed14; colLed < endLed14;  colLed = colLed + 2){
    leds[colLed] = CRGB( red14, green14, blue14) ;
  }
  FastLED.show();
	stLed15 = endLed14;
	endLed15 = NUM_LEDS;
}

result ledCol1Pt14() {
  red14 = 220; green14 = 20; blue14 = 60;
	setLedColpt14();
  return proceed;
}

result ledCol2Pt14() {
  red14 = 240; green14 = 128; blue14 = 128;
	setLedColpt14();
  return proceed;
}

result ledCol3Pt14() {
  red14 = 255; green14 = 20; blue14 = 147;
	setLedColpt14();
  return proceed;
}

result ledCol4Pt14() {
  red14 = 255; green14 = 140; blue14 = 0;
	setLedColpt14();
  return proceed;
}

result ledCol5Pt14() {
  red14 = 192; green14 = 192; blue14 = 192;
	setLedColpt14();
  return proceed;
}

result ledCol6Pt14() {
  red14 = 255; green14 = 215; blue14 = 0;
	setLedColpt14();
  return proceed;
}

result ledCol7Pt14() {
  red14 = 218; green14 = 165; blue14 = 32;
	setLedColpt14();
  return proceed;
}

result ledCol8Pt14() {
  red14 = 139; green14 = 69; blue14 = 19;
	setLedColpt14();
  return proceed;
}

result ledCol9Pt14() {
  red14 = 186; green14 = 85; blue14 = 211;
	setLedColpt14();
  return proceed;
}

result ledCol10Pt14() {
  red14 = 128; green14 = 0; blue14 = 128;
	setLedColpt14();
  return proceed;
}

result ledCol11Pt14() {
  red14 = 124; green14 = 252; blue14 = 0;
	setLedColpt14();
  return proceed;
}

result ledCol12Pt14() {
  red14 = 50; green14 = 205; blue14 = 50;
	setLedColpt14();
  return proceed;
}

result ledCol13Pt14() {
  red14 = 154; green14 = 205; blue14 = 50;
	setLedColpt14();
  return proceed;
}

result ledCol14Pt14() {
  red14 = 0; green14 = 255; blue14 = 255;
	setLedColpt14();
  return proceed;
}

result ledCol15Pt14() {
  red14 = 0; green14 = 206; blue14 = 209;
	setLedColpt14();
  return proceed;
}

result ledCol16Pt14() {
  red14 = 30; green14 = 144; blue14 = 255;
	setLedColpt14();
  return proceed;
}

result ledCol17Pt14() {
  red14 = 0; green14 = 0; blue14 = 0;
	setLedColpt14();
  return proceed;
}

int ledColSel14=-1;
CHOOSE(ledColSel14,ledColSelMenu14,"Col",doNothing,noEvent,wrapStyle
  ,VALUE("Crimson"			,1,ledCol1Pt14,anyEvent)
//  ,VALUE("Light coral",2,ledCol2Pt14,enterEvent)
  ,VALUE("Dpink"				,3,ledCol3Pt14,anyEvent)
  ,VALUE("Dorange"			,4,ledCol4Pt14,anyEvent)
  ,VALUE("Silver"				,5,ledCol5Pt14,anyEvent)
  ,VALUE("Gold"					,6,ledCol6Pt14,anyEvent)
  ,VALUE("Goldenrod"		,7,ledCol7Pt14,anyEvent)
  ,VALUE("Sadbrown"			,8,ledCol8Pt14,anyEvent)
  ,VALUE("MedOrchid"		,9,ledCol9Pt14,anyEvent)
  ,VALUE("Purple"				,10,ledCol10Pt14,anyEvent)
  ,VALUE("Lawngreen"		,11,ledCol11Pt14,anyEvent)
  ,VALUE("Limegreen"		,12,ledCol12Pt14,anyEvent)
  ,VALUE("Yellgreen"		,13,ledCol13Pt14,anyEvent)
  ,VALUE("Aqua"					,14,ledCol14Pt14,anyEvent)
//  ,VALUE("Darkturquoise",15,ledCol15Pt14,anyEvent)
  ,VALUE("Dodgeblue"		,16,ledCol16Pt14,anyEvent)
  ,VALUE("Off"					,17,ledCol17Pt14,anyEvent)
  ,VALUE("Cancel"				,-1,doNothing,noEvent)
);

result LEDcoL14() { 
	for(int colLed = stLed14; colLed < endLed14;  colLed = colLed + 2){
    leds[colLed] = CRGB( red14, green14, blue14) ;
  }
  FastLED.show();
  return proceed;
};

result fsWrite14(eventMask e,navNode& nav, prompt &item) { 
	writeSDSettings(SPIFFS, "/Part14", "stLed14", stLed14, "endLed14", endLed14, "red14", red14, "green14", green14, "blue14", blue14);
  return proceed;
};

result fsRead14() { 
	readSDSettings(SPIFFS, "/Part14");
	LEDcoL14();
  return proceed;
};

MENU(ColorPt14,"RGB pt14",showEvent,anyEvent,noStyle
  ,FIELD(red14,"Red","",red14,255,1,0,LEDcoL14,enterEvent/*noEvent*/,wrapStyle)
  ,FIELD(green14,"Green","",green14,255,1,0,LEDcoL14,enterEvent/*noEvent*/,wrapStyle)
  ,FIELD(blue14,"Blue","",blue14,255,1,0,LEDcoL14,enterEvent/*noEvent*/,wrapStyle)
//  ,SUBMENU(ledColSelMenu)
  ,EXIT("<Back")
);

MENU(sub14Menu,"LED pt14",showEvent,anyEvent,wrapStyle
  ,FIELD(stLed14,"Start","",stLed14,NUM_LEDS,1,0,doNothing,enterEvent,wrapStyle)
  ,FIELD(endLed14,"End","",stLed14,NUM_LEDS,1,0,doNothing,enterEvent,wrapStyle)
  ,SUBMENU(ColorPt14)
  ,SUBMENU(ledColSelMenu14)
  ,OP("Save Part 14",fsWrite14,enterEvent)
  ,OP("Load Part 14",fsRead14,enterEvent)
  ,EXIT("<Back")
);

void setLedColpt15(){
  for(int colLed = stLed15; colLed < endLed15;  colLed = colLed + 2){
    leds[colLed] = CRGB( red15, green15, blue15) ;
  }
  FastLED.show();
	stLed16 = endLed15;
	endLed16 = NUM_LEDS;
}

result ledCol1Pt15() {
  red15 = 220; green15 = 20; blue15 = 60;
	setLedColpt15();
  return proceed;
}

result ledCol2Pt15() {
  red15 = 240; green15 = 128; blue15 = 128;
	setLedColpt15();
  return proceed;
}

result ledCol3Pt15() {
  red15 = 255; green15 = 20; blue15 = 147;
	setLedColpt15();
  return proceed;
}

result ledCol4Pt15() {
  red15 = 255; green15 = 140; blue15 = 0;
	setLedColpt15();
  return proceed;
}

result ledCol5Pt15() {
  red15 = 192; green15 = 192; blue15 = 192;
	setLedColpt15();
  return proceed;
}

result ledCol6Pt15() {
  red15 = 255; green15 = 215; blue15 = 0;
	setLedColpt15();
  return proceed;
}

result ledCol7Pt15() {
  red15 = 218; green15 = 165; blue15 = 32;
	setLedColpt15();
  return proceed;
}

result ledCol8Pt15() {
  red15 = 139; green15 = 69; blue15 = 19;
	setLedColpt15();
  return proceed;
}

result ledCol9Pt15() {
  red15 = 186; green15 = 85; blue15 = 211;
	setLedColpt15();
  return proceed;
}

result ledCol10Pt15() {
  red15 = 128; green15 = 0; blue15 = 128;
	setLedColpt15();
  return proceed;
}

result ledCol11Pt15() {
  red15 = 124; green15 = 252; blue15 = 0;
	setLedColpt15();
  return proceed;
}

result ledCol12Pt15() {
  red15 = 50; green15 = 205; blue15 = 50;
	setLedColpt15();
  return proceed;
}

result ledCol13Pt15() {
  red15 = 154; green15 = 205; blue15 = 50;
	setLedColpt15();
  return proceed;
}

result ledCol14Pt15() {
  red15 = 0; green15 = 255; blue15 = 255;
	setLedColpt15();
  return proceed;
}

result ledCol15Pt15() {
  red15 = 0; green15 = 206; blue15 = 209;
	setLedColpt15();
  return proceed;
}

result ledCol16Pt15() {
  red15 = 30; green15 = 144; blue15 = 255;
	setLedColpt15();
  return proceed;
}

result ledCol17Pt15() {
  red15 = 0; green15 = 0; blue15 = 0;
	setLedColpt15();
  return proceed;
}

int ledColSel15=-1;
CHOOSE(ledColSel15,ledColSelMenu15,"Col",doNothing,noEvent,wrapStyle
  ,VALUE("Crimson"			,1,ledCol1Pt15,anyEvent)
//  ,VALUE("Light coral",2,ledCol2Pt15,enterEvent)
  ,VALUE("Dpink"				,3,ledCol3Pt15,anyEvent)
  ,VALUE("Dorange"			,4,ledCol4Pt15,anyEvent)
  ,VALUE("Silver"				,5,ledCol5Pt15,anyEvent)
  ,VALUE("Gold"					,6,ledCol6Pt15,anyEvent)
  ,VALUE("Goldenrod"		,7,ledCol7Pt15,anyEvent)
  ,VALUE("Sadbrown"			,8,ledCol8Pt15,anyEvent)
  ,VALUE("MedOrchid"		,9,ledCol9Pt15,anyEvent)
  ,VALUE("Purple"				,10,ledCol10Pt15,anyEvent)
  ,VALUE("Lawngreen"		,11,ledCol11Pt15,anyEvent)
  ,VALUE("Limegreen"		,12,ledCol12Pt15,anyEvent)
  ,VALUE("Yellgreen"		,13,ledCol13Pt15,anyEvent)
  ,VALUE("Aqua"					,14,ledCol14Pt15,anyEvent)
//  ,VALUE("Darkturquoise",15,ledCol15Pt15,anyEvent)
  ,VALUE("Dodgeblue"		,16,ledCol16Pt15,anyEvent)
  ,VALUE("Off"					,17,ledCol17Pt15,anyEvent)
  ,VALUE("Cancel"				,-1,doNothing,noEvent)
);

result LEDcoL15() { 
	for(int colLed = stLed15; colLed < endLed15;  colLed = colLed + 2){
    leds[colLed] = CRGB( red15, green15, blue15) ;
  }
  FastLED.show();
  return proceed;
};

result fsWrite15(eventMask e,navNode& nav, prompt &item) { 
	writeSDSettings(SPIFFS, "/Part15", "stLed15", stLed15, "endLed15", endLed15, "red15", red15, "green15", green15, "blue15", blue15);
  return proceed;
};

result fsRead15() { 
	readSDSettings(SPIFFS, "/Part15");
	LEDcoL15();
  return proceed;
};

MENU(ColorPt15,"RGB pt15",showEvent,anyEvent,noStyle
  ,FIELD(red15,"Red","",red15,255,1,0,LEDcoL15,enterEvent/*noEvent*/,wrapStyle)
  ,FIELD(green15,"Green","",green15,255,1,0,LEDcoL15,enterEvent/*noEvent*/,wrapStyle)
  ,FIELD(blue15,"Blue","",blue15,255,1,0,LEDcoL15,enterEvent/*noEvent*/,wrapStyle)
//  ,SUBMENU(ledColSelMenu)
  ,EXIT("<Back")
);

MENU(sub15Menu,"LED pt15",showEvent,anyEvent,wrapStyle
  ,FIELD(stLed15,"Start","",stLed15,NUM_LEDS,1,0,doNothing,enterEvent,wrapStyle)
  ,FIELD(endLed15,"End","",stLed15,NUM_LEDS,1,0,doNothing,enterEvent,wrapStyle)
  ,SUBMENU(ColorPt15)
  ,SUBMENU(ledColSelMenu15)
  ,OP("Save Part 15",fsWrite15,enterEvent)
  ,OP("Load Part 15",fsRead15,enterEvent)
  ,EXIT("<Back")
);

void setLedColpt16(){
  for(int colLed = stLed16; colLed < endLed16;  colLed = colLed + 2){
    leds[colLed] = CRGB( red16, green16, blue16) ;
  }
  FastLED.show();
//	stLed17 = endLed16;
}

result ledCol1Pt16() {
  red16 = 220; green16 = 20; blue16 = 60;
	setLedColpt16();
  return proceed;
}

result ledCol2Pt16() {
  red16 = 240; green16 = 128; blue16 = 128;
	setLedColpt16();
  return proceed;
}

result ledCol3Pt16() {
  red16 = 255; green16 = 20; blue16 = 147;
	setLedColpt16();
  return proceed;
}

result ledCol4Pt16() {
  red16 = 255; green16 = 140; blue16 = 0;
	setLedColpt16();
  return proceed;
}

result ledCol5Pt16() {
  red16 = 192; green16 = 192; blue16 = 192;
	setLedColpt16();
  return proceed;
}

result ledCol6Pt16() {
  red16 = 255; green16 = 215; blue16 = 0;
	setLedColpt16();
  return proceed;
}

result ledCol7Pt16() {
  red16 = 218; green16 = 165; blue16 = 32;
	setLedColpt16();
  return proceed;
}

result ledCol8Pt16() {
  red16 = 139; green16 = 69; blue16 = 19;
	setLedColpt16();
  return proceed;
}

result ledCol9Pt16() {
  red16 = 186; green16 = 85; blue16 = 211;
	setLedColpt16();
  return proceed;
}

result ledCol10Pt16() {
  red16 = 128; green16 = 0; blue16 = 128;
	setLedColpt16();
  return proceed;
}

result ledCol11Pt16() {
  red16 = 124; green16 = 252; blue16 = 0;
	setLedColpt16();
  return proceed;
}

result ledCol12Pt16() {
  red16 = 50; green16 = 205; blue16 = 50;
	setLedColpt16();
  return proceed;
}

result ledCol13Pt16() {
  red16 = 154; green16 = 205; blue16 = 50;
	setLedColpt16();
  return proceed;
}

result ledCol14Pt16() {
  red16 = 0; green16 = 255; blue16 = 255;
	setLedColpt16();
  return proceed;
}

result ledCol15Pt16() {
  red16 = 0; green16 = 206; blue16 = 209;
	setLedColpt16();
  return proceed;
}

result ledCol16Pt16() {
  red16 = 30; green16 = 144; blue16 = 255;
	setLedColpt16();
  return proceed;
}

result ledCol17Pt16() {
  red16 = 0; green16 = 0; blue16 = 0;
	setLedColpt16();
  return proceed;
}

int ledColSel16=-1;
CHOOSE(ledColSel16,ledColSelMenu16,"Col",doNothing,noEvent,wrapStyle
  ,VALUE("Crimson"			,1,ledCol1Pt16,anyEvent)
//  ,VALUE("Light coral",2,ledCol2Pt16,enterEvent)
  ,VALUE("Dpink"				,3,ledCol3Pt16,anyEvent)
  ,VALUE("Dorange"			,4,ledCol4Pt16,anyEvent)
  ,VALUE("Silver"				,5,ledCol5Pt16,anyEvent)
  ,VALUE("Gold"					,6,ledCol6Pt16,anyEvent)
  ,VALUE("Goldenrod"		,7,ledCol7Pt16,anyEvent)
  ,VALUE("Sadbrown"			,8,ledCol8Pt16,anyEvent)
  ,VALUE("MedOrchid"		,9,ledCol9Pt16,anyEvent)
  ,VALUE("Purple"				,10,ledCol10Pt16,anyEvent)
  ,VALUE("Lawngreen"		,11,ledCol11Pt16,anyEvent)
  ,VALUE("Limegreen"		,12,ledCol12Pt16,anyEvent)
  ,VALUE("Yellgreen"		,13,ledCol13Pt16,anyEvent)
  ,VALUE("Aqua"					,14,ledCol14Pt16,anyEvent)
//  ,VALUE("Darkturquoise",15,ledCol15Pt16,anyEvent)
  ,VALUE("Dodgeblue"		,16,ledCol16Pt16,anyEvent)
  ,VALUE("Off"					,17,ledCol17Pt16,anyEvent)
  ,VALUE("Cancel"				,-1,doNothing,noEvent)
);

result LEDcoL16() { 
	for(int colLed = stLed16; colLed < endLed16;  colLed = colLed + 2){
    leds[colLed] = CRGB( red16, green16, blue16) ;
  }
  FastLED.show();
  return proceed;
};

result fsWrite16(eventMask e,navNode& nav, prompt &item) { 
	writeSDSettings(SPIFFS, "/Part16", "stLed16", stLed16, "endLed16", endLed16, "red16", red16, "green16", green16, "blue16", blue16);
  return proceed;
};

result fsRead16() { 
	readSDSettings(SPIFFS, "/Part16");
	LEDcoL16();
  return proceed;
};

MENU(ColorPt16,"RGB pt16",showEvent,anyEvent,noStyle
  ,FIELD(red16,"Red","",red16,255,1,0,LEDcoL16,enterEvent/*noEvent*/,wrapStyle)
  ,FIELD(green16,"Green","",green16,255,1,0,LEDcoL16,enterEvent/*noEvent*/,wrapStyle)
  ,FIELD(blue16,"Blue","",blue16,255,1,0,LEDcoL16,enterEvent/*noEvent*/,wrapStyle)
//  ,SUBMENU(ledColSelMenu)
  ,EXIT("<Back")
);

MENU(sub16Menu,"LED pt16",showEvent,anyEvent,wrapStyle
  ,FIELD(stLed16,"Start","",stLed16,NUM_LEDS,1,0,doNothing,enterEvent,wrapStyle)
  ,FIELD(endLed16,"End","",stLed16,NUM_LEDS,1,0,doNothing,enterEvent,wrapStyle)
  ,SUBMENU(ColorPt16)
  ,SUBMENU(ledColSelMenu16)
  ,OP("Save Part 16",fsWrite16,enterEvent)
  ,OP("Load Part 16",fsRead16,enterEvent)
  ,EXIT("<Back")
);

MENU(ledPtMenu1,"LED Prt 1-8",showEvent,anyEvent,wrapStyle
  ,SUBMENU(sub1Menu)
  ,SUBMENU(sub2Menu)
  ,SUBMENU(sub3Menu)
  ,SUBMENU(sub4Menu)
  ,SUBMENU(sub5Menu)
  ,SUBMENU(sub6Menu)
  ,SUBMENU(sub7Menu)
  ,SUBMENU(sub8Menu)
  ,EXIT("<Back")
);

MENU(ledPtMenu2,"LED Prt 9-16",showEvent,anyEvent,wrapStyle
  ,SUBMENU(sub9Menu)
  ,SUBMENU(sub10Menu)
  ,SUBMENU(sub11Menu)
  ,SUBMENU(sub12Menu)
  ,SUBMENU(sub13Menu)
  ,SUBMENU(sub14Menu)
  ,SUBMENU(sub15Menu)
  ,SUBMENU(sub16Menu)
  ,EXIT("<Back")
);

result writeBrite() {
		// Delete the old one
		SPIFFS.remove("/BRITENES");
		// Create new one
		myFile = SPIFFS.open("/BRITENES", FILE_WRITE);
		// writing in the file works just like regular print()/println() function
		myFile.print(F("["))		; myFile.print(F("BRIGHTNESS")); myFile.print(F("="));
		myFile.print(BRIGHTNESS);	myFile.println(F("]"));
		myFile.close();
 }

result setBriteness() {
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.show();
	writeBrite();
  return proceed;
}

result readFSBriteness() {
  readSDSettings(SPIFFS, "/BRITENES");
//  FastLED.show();
  return proceed;
}
		
/*extern menu mainMenu;
TOGGLE((mainMenu[1].enabled),togOp,"Op 2:",doNothing,noEvent,noStyle
  ,VALUE("Enabled",enabledStatus,doNothing,noEvent)
  ,VALUE("disabled",disabledStatus,doNothing,noEvent)
);*/

char* constMEM hexDigit MEMMODE="0123456789ABCDEF";
char* constMEM hexNr[] MEMMODE={"0","x",hexDigit,hexDigit};
char buf1[]="0x11";

MENU(mainMenu,"    Menu",doNothing,noEvent,wrapStyle
//  ,OP("Leds Red",action3,enterEvent)
//  ,OP("Leds Green",action5,enterEvent)
//  ,OP("Leds Blue",action6,enterEvent)
	,SUBMENU(wifiMenu)
  ,OP("FS Dir list",dirList,enterEvent)
  ,OP("Read memory",serDebug,enterEvent)
  ,OP("Recall",reCall,enterEvent)
  ,OP("Leds Off",action4,enterEvent)
  ,SUBMENU(chooseMenu)
  ,FIELD(BRIGHTNESS,"Bright","",0,180,10,1,setBriteness,enterEvent/*noEvent*/,wrapStyle)
  ,SUBMENU(prstMenu)
  ,SUBMENU(ledPtMenu1)
  ,SUBMENU(ledPtMenu2)
//  ,OP("SDtest",action7,enterEvent)
//  ,OP("SDjpeg",action8,enterEvent)
//  ,OP("OpA",action1,anyEvent)
//  ,OP("OpB",action2,enterEvent)
//  ,SUBMENU(togOp)
//  ,SUBMENU(selMenu)
//  ,SUBMENU(wifiMenu)
//  ,SUBMENU(setLed)
//  ,OP("LED On",myLedOn,enterEvent)
//  ,OP("LED Off",myLedOff,enterEvent)
//  ,OP("Alert test",doAlert,enterEvent)
//  ,EDIT("Hex",buf1,hexNr,doNothing,noEvent,noStyle)
  ,EXIT("<Back")
);

const colorDef<uint16_t> colors[] MEMMODE={
  {{(uint16_t)Black,(uint16_t)Black}, {(uint16_t)Black, (uint16_t)White,  (uint16_t)White}},//bgColor
  {{(uint16_t)Gray, (uint16_t)Gray},  {(uint16_t)White, (uint16_t)Black, (uint16_t)Black}},//fgColor
  {{(uint16_t)White,(uint16_t)Black}, {(uint16_t)Yellow,(uint16_t)Blue,(uint16_t)Red}},//valColor
  {{(uint16_t)White,(uint16_t)Black}, {(uint16_t)White, (uint16_t)Blue,(uint16_t)Yellow}},//unitColor
  {{(uint16_t)White,(uint16_t)Gray},  {(uint16_t)Black, (uint16_t)White,  (uint16_t)White}},//cursorColor
  {{(uint16_t)White,(uint16_t)Yellow},{(uint16_t)LighterBlue,  (uint16_t)White,   (uint16_t)Red}},//titleColor
};

#define MAX_DEPTH 4

//define serial output device
idx_t serialTops[MAX_DEPTH]={0};
serialOut outSerial(Serial,serialTops);

// Here is used a ST7735 160x128 SPI display module
// Configured in the library ..\libraries\TFT_eSPI\User_Setups\Setup2_ST7735.h
#define GFX_WIDTH 160
#define GFX_HEIGHT 109
#define fontW 10
#define fontH 16

constMEM panel panels[] MEMMODE = {{0, 0, GFX_WIDTH / fontW, GFX_HEIGHT / fontH}};
navNode* nodes[sizeof(panels) / sizeof(panel)]; //navNodes to store navigation status
panelsList pList(panels, nodes, 1); //a list of panels and nodes
idx_t eSpiTops[MAX_DEPTH]={0};
TFT_eSPIOut eSpiOut(gfx,colors,eSpiTops,pList,fontW,fontH+1);
menuOut* constMEM outputs[] MEMMODE={&outSerial,&eSpiOut};//list of output devices
outputsList out(outputs,sizeof(outputs)/sizeof(menuOut*));//outputs list controller

NAVROOT(nav,mainMenu,MAX_DEPTH,in,out);//the navigation root object

result alert(menuOut& o,idleEvent e) {
  if (e==idling) {
    o.setCursor(0,0);
    o.print("alert test");
    o.setCursor(0,1);
    o.print("[select] to continue...");
  }
  return proceed;
}

result doAlert(eventMask e, prompt &item) {
  nav.idleOn(alert);
  return proceed;
}

result idle(menuOut& o,idleEvent e) {
  switch(e) {
    case idleStart:o.print("suspending menu!");break;
    case idling:o.print("suspended...");break;
    case idleEnd:o.print("resuming menu.");break;
  }
  return proceed;
}

///////////////////////////////////////////////////////////////////////////////
//ESPui

void numberCall(Control *sender, int type) { Serial.println(sender->value); }

void textCall(Control *sender, int type) { Serial.println(sender->value); }

void slider(Control *sender, int type) { Serial.println(sender->value); }

void buttonCallback(Control *sender, int type) {
  switch (type) {
    case B_DOWN:
			ledsOff();
      Serial.println("Button DOWN");
      break;
    case B_UP:
      Serial.println("Button UP");
      break;
  }
}

void buttonExample(Control *sender, int type) {
  switch (type) {
    case B_DOWN:
			redLed();
      Serial.println("LEDs: Red");
      ESPUI.print(0, "LEDs: Red");
      break;
    case B_UP:
      Serial.println("LEDs: Red");
      ESPUI.print(0, "LEDs: Red");
      break;
  }
}

void button1Example(Control *sender, int type) {
  switch (type) {
    case B_DOWN:
			greenLed();
      Serial.println("LEDs: Green");
      ESPUI.print(0, "LEDs: Green");
      break;
    case B_UP:
      Serial.println("LEDs: Green");
      ESPUI.print(0, "LEDs: Green");
      break;
  }
}

void button2Example(Control *sender, int type) {
  switch (type) {
    case B_DOWN:
			blueLed();
      Serial.println("LEDs: Blue");
      ESPUI.print(0, "LEDs: Blue");
      break;
    case B_UP:
      Serial.println("LEDs: Blue");
      ESPUI.print(0, "LEDs: Blue");
      break;
  }
}

void button3Example(Control *sender, int type) {
  switch (type) {
    case B_DOWN:
			ledsOff();
      Serial.println("LEDs: Off");
      ESPUI.print(0, "LEDs: Off");
      break;
    case B_UP:
      Serial.println("LEDs: Off");
      ESPUI.print(0, "LEDs: Off");
      break;
  }
}

void padExample(Control *sender, int value) {
  switch (value) {
    case P_LEFT_DOWN:
      Serial.print("left down");
      break;
    case P_LEFT_UP:
      Serial.print("left up");
      break;
    case P_RIGHT_DOWN:
      Serial.print("right down");
      break;
    case P_RIGHT_UP:
      Serial.print("right up");
      break;
    case P_FOR_DOWN:
      Serial.print("for down");
      break;
    case P_FOR_UP:
      Serial.print("for up");
      break;
    case P_BACK_DOWN:
      Serial.print("back down");
      break;
    case P_BACK_UP:
      Serial.print("back up");
      break;
    case P_CENTER_DOWN:
      Serial.print("center down");
      break;
    case P_CENTER_UP:
      Serial.print("center up");
      break;
  }
  Serial.print(" ");
  Serial.println(sender->id);
}

void switchExample(Control *sender, int value) {
  switch (value) {
    case S_ACTIVE:
      Serial.print("Active:");
      break;
    case S_INACTIVE:
      Serial.print("Inactive");
      break;
  }
  Serial.print(" ");
  Serial.println(sender->id);
}

void otherSwitchExample(Control *sender, int value) {
  switch (value) {
    case S_ACTIVE:
      Serial.print("Active:");
      break;
    case S_INACTIVE:
      Serial.print("Inactive");
      break;
  }
  Serial.print(" ");
  Serial.println(sender->id);
}

void setup() {
/////////////////////////////////////////////////////////
//Oled SD1306 setup
  u8g2.begin();
	OLED_init();
	
//	gfx.print("Connecting to ");
//	gfx.println(ssid);
//	gfx.print("IP address: ");
//	gfx.println(WiFi.localIP());
	
  SPIFFS.begin();
	
  pinMode(21, OUTPUT);
  pinMode(22, OUTPUT);
  digitalWrite(21, 0);
  digitalWrite(22, 0);
  pinMode(encBtn,INPUT_PULLUP);
  pinMode(LEDPIN,OUTPUT);
  digitalWrite(LEDPIN,ledCtrl);
  Serial.begin(115200);
  while(!Serial);
  Serial.flush();
  nav.idleTask=idle;//point a function to be used when menu is suspended
  //mainMenu[2].disable();
  //outGfx.usePreview=true;//reserve one panel for preview?
  //nav.showTitle=false;//show menu title?
	
	// MIDI setup
	// Connect the handleNoteOn function to the library,
	// so it is called upon reception of a NoteOn.
	MIDI.setHandleNoteOn(handleNoteOn);  // Put only the name of the function
	// Do the same for NoteOffs
	MIDI.setHandleNoteOff(handleNoteOff);
	// Initiate MIDI communications, listen to all channels
	MIDI.begin(MIDI_CHANNEL_OMNI);

/////////////////////////////////////////////////////////
//TFT ST7735 setup
  SPI.begin();
  gfx.init();
  gfx.setRotation(3);
  // gfx.setTextSize(textScale);//test scalling
  // gfx.setTextFont(3);
  gfx.setTextSize(2);
  gfx.fillScreen(Black);
  gfx.setTextColor(Red,Black);
  gfx.println("ArduinoMenu\n\n        4.x\n\n\n by\n\n  Rui Azevedo");
  delay(1800);
	drawFsJpeg(SPIFFS, "/160x128_menu_bgr.jpg", 0, 0);
  delay(3400);
  gfx.fillScreen(Black);
	gfx.fillRoundRect(0, 106, 160, 22, 2, White); 
	
	// ----------------------------------------------------------------------------
	// LED setup
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,CLOCK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
	// set master brightness control
	readFSBriteness();
  FastLED.setBrightness(BRIGHTNESS);
	// clear LED strip
	ledsOff();
}

void loop() {

	// Call MIDI.read the fastest you can for real-time performance.
	MIDI.read();

  //Call clickEncoder.service in loop becasue using timer interrupts may affect ESP8266 WIFI
  //however call no more than 1 time per millisecond to reduce encoder bounce
  static uint32_t lastService = 0;
  if (lastService + 1000 < micros()) {
    lastService = micros();                
    clickEncoder.service();  
  }
  nav.poll();
  digitalWrite(LEDPIN, ledCtrl);
  // delay(100); // simulate a delay as if other tasks are running
	
//ESPui
  if (millis() - oldTime > 5000) {
    ESPUI.print(millisLabelId, String(millis()));
    //switchi = !switchi;
    //ESPUI.updateSwitcher("Switch one", switchi);
    oldTime = millis();
  }
  
//  FastLED.setBrightness(BRIGHTNESS);
//  FastLED.show();
}

void serialDebug(){
	 //Serial debug output 
		Serial.print("\n");
		Serial.println(F("In RAM Memory"));
		Serial.print(F("stLed1="))		;	Serial.println(stLed1)		;	Serial.print(F("endLed1="))		;	Serial.println(endLed1)	;
		Serial.print(F("red1="))			;	Serial.println(red1)			;	Serial.print(F("green1="))		;	Serial.println(green1)	;	Serial.print(F("blue1="))	;	Serial.println(blue1)	;
		Serial.print(F("stLed2="))		;	Serial.println(stLed2)		; Serial.print(F("endLed2="))		;	Serial.println(endLed2)	;
		Serial.print(F("red2="))			;	Serial.println(red2)			; Serial.print(F("green2="))		;	Serial.println(green2)	;	Serial.print(F("blue2="))	;	Serial.println(blue2)	;
		Serial.print(F("stLed3="))		;	Serial.println(stLed3)		; Serial.print(F("endLed3="))		;	Serial.println(endLed3)	;
		Serial.print(F("red3="))			;	Serial.println(red3)			; Serial.print(F("green3="))		;	Serial.println(green3)	;	Serial.print(F("blue3="))	;	Serial.println(blue3)	;
		Serial.print(F("stLed4="))		;	Serial.println(stLed4)		; Serial.print(F("endLed4="))		;	Serial.println(endLed4)	;
		Serial.print(F("red4="))			;	Serial.println(red4)			; Serial.print(F("green4="))		;	Serial.println(green4)	;	Serial.print(F("blue4="))	;	Serial.println(blue4)	;
		Serial.print(F("stLed5="))		;	Serial.println(stLed5)		; Serial.print(F("endLed5="))		;	Serial.println(endLed5)	;
		Serial.print(F("red5="))			;	Serial.println(red5)			; Serial.print(F("green5="))		;	Serial.println(green5)	;	Serial.print(F("blue5="))	;	Serial.println(blue5)	;
		Serial.print(F("stLed6="))		;	Serial.println(stLed6)		; Serial.print(F("endLed6="))		;	Serial.println(endLed6)	;
		Serial.print(F("red6="))			;	Serial.println(red6)			; Serial.print(F("green6="))		;	Serial.println(green6)	;	Serial.print(F("blue6="))	;	Serial.println(blue6)	;
		Serial.print(F("stLed7="))		;	Serial.println(stLed7)		; Serial.print(F("endLed7="))		;	Serial.println(endLed7)	;
		Serial.print(F("red7="))			;	Serial.println(red7)			; Serial.print(F("green7="))		;	Serial.println(green7)	;	Serial.print(F("blue7="))	;	Serial.println(blue7)	;
		Serial.print(F("stLed8="))		;	Serial.println(stLed8)		; Serial.print(F("endLed8="))		;	Serial.println(endLed8)	;
		Serial.print(F("red8="))			;	Serial.println(red8)			; Serial.print(F("green8="))		;	Serial.println(green8)	;	Serial.print(F("blue8="))	;	Serial.println(blue8)	;
		Serial.print(F("stLed9="))		;	Serial.println(stLed9)		; Serial.print(F("endLed9="))		;	Serial.println(endLed9)	;
		Serial.print(F("red9="))			;	Serial.println(red9)			; Serial.print(F("green9="))		;	Serial.println(green9)	;	Serial.print(F("blue9="))	;	Serial.println(blue9)	;
		Serial.print(F("stLed10="))		;	Serial.println(stLed10)		; Serial.print(F("endLed10="))	;	Serial.println(endLed10);
		Serial.print(F("red10="))			;	Serial.println(red10)			; Serial.print(F("green10="))		;	Serial.println(green10)	;	Serial.print(F("blue10="));	Serial.println(blue10);
		Serial.print(F("stLed11="))		;	Serial.println(stLed11)		; Serial.print(F("endLed11="))	;	Serial.println(endLed11);
		Serial.print(F("red11="))			;	Serial.println(red11)			; Serial.print(F("green11="))		;	Serial.println(green11)	;	Serial.print(F("blue11="));	Serial.println(blue11);
		Serial.print(F("stLed12="))		;	Serial.println(stLed12)		; Serial.print(F("endLed12="))	;	Serial.println(endLed12);
		Serial.print(F("red12="))			;	Serial.println(red12)			; Serial.print(F("green12="))		;	Serial.println(green12)	;	Serial.print(F("blue12="));	Serial.println(blue12);
		Serial.print(F("stLed13="))		;	Serial.println(stLed13)		; Serial.print(F("endLed13="))	;	Serial.println(endLed13);
		Serial.print(F("red13="))			;	Serial.println(red13)			; Serial.print(F("green13="))		;	Serial.println(green13)	;	Serial.print(F("blue13="));	Serial.println(blue13);
		Serial.print(F("stLed14="))		;	Serial.println(stLed14)		; Serial.print(F("endLed14="))	;	Serial.println(endLed14);
		Serial.print(F("red14="))			;	Serial.println(red14)			; Serial.print(F("green14="))		;	Serial.println(green14)	;	Serial.print(F("blue14="));	Serial.println(blue14);
		Serial.print(F("stLed15="))		;	Serial.println(stLed15)		; Serial.print(F("endLed15="))	;	Serial.println(endLed15);
		Serial.print(F("red15="))			;	Serial.println(red15)			; Serial.print(F("green15="))		;	Serial.println(green15)	;	Serial.print(F("blue15="));	Serial.println(blue15);
		Serial.print(F("stLed16="))			;	Serial.println(stLed16)			; Serial.print(F("endLed16="))		;	Serial.println(endLed16)	;
		Serial.print(F("red16="))				;	Serial.println(red16)				; Serial.print(F("green16="))			;	Serial.println(green16)		;	Serial.print(F("blue16="))	;	Serial.println(blue16)	;
		Serial.print("\n");
	}
