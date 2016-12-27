// All the mcufriend.com UNO shields have the same pinout.
// i.e. control pins A0-A4.  Data D2-D9.  microSD D10-D13.
// Touchscreens are normally A1, A2, D7, D6 but the order varies
// https://github.com/prenticedavid/MCUFRIEND_kbv
// This demo should work with most Adafruit TFT libraries
// If you are not using a shield,  use a full Adafruit constructor()
// e.g. Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
// Nicu FLORICA (niq_ro) clear the sketch for pust some text in portrait and landscape mode


#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

#include <SPI.h>          // f.k. for Arduino-1.5.2
#include "Adafruit_GFX.h"// Hardware-specific library
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
//#include <Adafruit_TFTLCD.h>
//Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	RED     0x001F
#define	BLUE    0xF800
#define	GREEN   0x07E0
#define MAGENTA 0x07FF
#define CYAN    0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

uint16_t g_identifier;

void setup(void) {
    Serial.begin(9600);
    g_identifier = 0x9481;// force ID
    tft.begin(g_identifier);
}

void loop(void) {
 tft.fillScreen(BLACK);  // clear screen
            tft.setRotation(1);  // landscape
            tft.setTextSize(4);
            tft.setCursor(10, 20);
            tft.setTextColor(WHITE);
            tft.println("Sarbatori fericite!");
            tft.setCursor(0, 80);
            tft.setTextColor(CYAN);
            tft.println("  Happy Hollidays!");      
            tft.setCursor(0, 140);
            tft.setTextColor(YELLOW);
            tft.println("  Frohe Feiertage!");   
            tft.setCursor(0, 200);
            tft.setTextColor(MAGENTA);
            tft.println("  Joyeuses fetes!");    
delay(3000);
tft.fillScreen(BLACK);  // clear screen
            tft.setRotation(2); // portrait
            tft.setTextSize(5);
            tft.setCursor(10, 20);
            tft.setTextColor(WHITE);
            tft.println("Sarbatori fericite !");
            tft.setCursor(0, 120);
            tft.setTextColor(RED);
            tft.println("  Happy   Hollidays!"); 
            tft.setCursor(0, 220);
            tft.setTextColor(GREEN);
            tft.println("  Frohe   Feiertage!");   
            tft.setCursor(0, 320);
            tft.setTextColor(BLUE);
            tft.println(" Joyeuses   fetes!");   
delay(3000);

}  // end
