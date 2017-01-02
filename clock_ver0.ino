// All the mcufriend.com UNO shields have the same pinout.
// i.e. control pins A0-A4.  Data D2-D9.  microSD D10-D13.
// Touchscreens are normally A1, A2, D7, D6 but the order varies
// https://github.com/prenticedavid/MCUFRIEND_kbv
// This demo should work with most Adafruit TFT libraries
// If you are not using a shield,  use a full Adafruit constructor()
// e.g. Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
// Nicu FLORICA (niq_ro) clear the sketch for pust some text in portrait and landscape mode
// see more at http://www.tehnic.go.ro 
// & http://nicuflorica.blogspot.ro/
// ver. 0 - just clear the sketch
// ver.00c - put DS3231 clock and DS18B20 sensor


#include <OneWire.h>
#include <DallasTemperature.h>
// Data wire is plugged into port 22 on the Arduino Due
#define ONE_WIRE_BUS 22
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

#include <Wire.h>
#define DS3231_I2C_ADDRESS 104
byte tMSB, tLSB;

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
#define YELLOW  0x07FF
#define MAGENTA 0xF81F
#define CYAN    0xFFE0
#define WHITE   0xFFFF

uint16_t g_identifier;

byte hh, mm, ss;
byte yy, ll, dd, zz;
byte zh,uh,zm,um;
byte zd, ud, zl, ul, zy, uy; 
//byte hh0 = 14;
byte zh0 = 1;
byte uh0 = 4;
//byte mm0 = 35;
byte zm0 = 3;
byte um0 = 5;
int ics1 = 400;
int igrec1 = 20;
byte zz0 = 8;
byte dd0 = 32;
int x = 10;
float t;
float t0 = 23.5; 
int t1;
byte zt1;
byte ut1;
byte st1;

byte zt0 = 2;
byte ut0 = 3;
byte st0 = 5;

unsigned long citire;
unsigned long stau = 15000;
int semn = 1;
int te = 0;
byte zt, ut, st, rt;

void setup(void) {
    Serial.begin(9600);
    
  // Start up the library
  sensors.begin();    
    g_identifier = 0x9481;// force ID
    tft.begin(g_identifier);
    tft.fillScreen(BLACK);  // clear screen
    
tft.setRotation(1);  // landscape

Wire.begin(); 
// setDS3231time(second, minute, hour, dayOfWeek, dayOfMonth, month, year)
// setDS3231time(0, 00, 16, 6, 2, 1, 17);                  

citire = millis();
 sensors.requestTemperatures(); // Send the command to get temperatures
 t = sensors.getTempCByIndex(0); 
 Serial.println(sensors.getTempCByIndex(0));   

 tft.setTextSize(4);
            tft.setCursor(20, 20);
            tft.setTextColor(WHITE);
            tft.println("Ceas cu termometru");
            tft.setCursor(30, 80);
            tft.setTextColor(RED);
            tft.println("pe afisaj de 3.95");      
            tft.setCursor(40, 140);
            tft.setTextColor(GREEN);
            tft.println("program scris de");   
            tft.setCursor(90, 200);
            tft.setTextColor(BLUE);
            tft.println("Nicu FLORICA");  
            tft.setCursor(130, 260);
            tft.setTextColor(BLUE);
            tft.println("(niq_ro)");      
 
   delay(5000);
    tft.fillScreen(BLACK);  // clear screen
}

void loop(void) {
// tft.fillScreen(BLACK);  // clear screen
tft.setTextSize(15);
 readDS3231time(&ss, &mm, &hh, &zz, &dd, &ll,&yy);
/* 
 Serial.print(hh);
 Serial.print(" : ");
 Serial.println(ss);
*/
zh = hh/10;
uh = hh%10;
zm = mm/10;
um = mm%10;
/*
if (mm != mm0)
{
stergere(x+270,20,15); // minute
stergere(x+360,20,15);  
}
*/
if (zm != zm0)
{
stergere(x+270,20,15); // minute
}
if (um != um0)
{
stergere(x+360,20,15);  
}
/*
if (hh != hh0)
{
stergere(x+10,20,15); // hour
stergere(x+100,20,15);  
}
*/
if (zh != zh0)
{
stergere(x+10,20,15); // hour
}
if (uh != uh0)
{
stergere(x+100,20,15);  
}

zm0 = zm;
um0 = um;
zh0 = zh;
uh0 = uh;
//mm0 = mm;
//hh0 = hh;

// first row - clock (primul rand  - ora)
            tft.setCursor(x+10, 20);
            tft.setTextColor(YELLOW);
            tft.print(zh);
            tft.print(uh);
            if (millis()/1000%2) tft.print(":");
            else 
            {
            stergere(x+190,20,15);
            tft.print(" ");            
            }           
            tft.print(zm);
            tft.print(um);


tft.setTextSize(3);
tft.setTextColor(RED);
if (zz != zz0)
{
for (int i=0; i<9; i++){  
stergere(20+i*18,150,3);
}
zz0 = zz;
}
tft.setCursor(20, 150);
if ((zz == 0) || (zz == 7)) tft.print("Duminica"); 
if (zz == 1) tft.print("Luni");
if (zz == 2) tft.print("Marti");
if (zz == 3) tft.print("Miercuri");
if (zz == 4) tft.print("Joi");
if (zz == 5) tft.print("Vineri");
if (zz == 6) tft.print("Sambata");

tft.setTextColor(GREEN);
tft.setCursor(280, 150);
if (dd != dd0)
{
for (int i=0; i<10; i++){  
stergere(280+i*18,150,3);
}
dd0 = dd;
}

zd = dd/10;
ud = dd%10;
zl = ll/10;
ul = ll%10;
zy = yy/10;
uy = yy%10;


tft.setCursor(280, 150);
tft.print(zd);
tft.print(ud);
tft.print("/");
tft.print(zl);
tft.print(ul);
tft.print("/20");
tft.print(zy);
tft.print(uy);


if (millis() - citire > stau)
{
// call sensors.requestTemperatures() to issue a global temperature 
  sensors.setResolution(12);
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  
  Serial.print("Temperature for the device 1 (index 0) is: ");
  t = sensors.getTempCByIndex(0);
  Serial.println(t);
    
 citire = millis(); 
}

if (t != t0)
{
for (int i=0; i<7; i++){  
stergere(30+i*60,200,10);
}

te = 10*t;
zt = te/100;
rt = te%100;
ut = rt/10;
st = rt%10;

if (t < 0)
{
 semn = -1;
 t = -t;
}
else semn = 1;
}

t0 = semn*t;


tft.setTextSize(10);
tft.setTextColor(BLUE);
//tft.setCursor(30, 200);
//tft.print("-20.5 C");

if ((semn == -1) && (t >= 10.0))         
            {
             tft.setCursor(30, 200); 
             tft.print("-");
             tft.print(zt);
             tft.print(ut);
            }
            if ((semn == -1) && (t < 10.0))         
            {
             tft.setCursor(120, 200); 
             tft.print("-");
             tft.print(ut);
            }
            if ((semn == 1) && (t < 10.0))        
            {
             tft.setCursor(180, 200); 
             tft.print(ut);
            }
            if ((semn == 1) && (t >= 10.0))         
            {
             tft.setCursor(90, 200); 
             tft.print(zt);
             tft.print(ut);
            }
             tft.setCursor(195, 200); 
             tft.print(",");
             tft.print(st);
             tft.print(" C");
          tft.setTextSize(5);
             tft.setCursor(330, 200); 
             tft.print("O");
 
             
}  // end

void stergere1(int ics, int igrec)
{
for (int i=0; i < 64; i++){
tft.drawLine(ics, igrec+i, ics+64, igrec+i, BLACK);
}
}

void stergere(int ics, int igrec, int zum)
{
for (int i=0; i < 8*zum; i++){
tft.drawLine(ics, igrec+i, ics+6*zum, igrec+i, BLACK);
//tft.drawLine(ics, igrec+i, ics+6*zum, igrec+i, BLUE);
}
}

// http://forum.arduino.cc/index.php?topic=398891.0
void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte
                   dayOfMonth, byte month, byte year)
{
    // sets time and date data to DS3231
    Wire.beginTransmission(DS3231_I2C_ADDRESS);
    Wire.write(0); // set next input to start at the seconds register
    Wire.write(decToBcd(second)); // set seconds
    Wire.write(decToBcd(minute)); // set minutes
    Wire.write(decToBcd(hour)); // set hours
    Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
    Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
    Wire.write(decToBcd(month)); // set month
    Wire.write(decToBcd(year)); // set year (0 to 99)
    Wire.endTransmission();
}

// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
    return ( (val / 16 * 10) + (val % 16) );
}

// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val)
{
    return ( (val / 10 * 16) + (val % 10) );
}

void readDS3231time(byte *second,
                    byte *minute,
                    byte *hour,
                    byte *dayOfWeek,
                    byte *dayOfMonth,
                    byte *month,
                    byte *year)
{
    Wire.beginTransmission(DS3231_I2C_ADDRESS);
    Wire.write(0); // set DS3231 register pointer to 00h
    Wire.endTransmission();
    Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
    // request seven bytes of data from DS3231 starting from register 00h
    *second = bcdToDec(Wire.read() & 0x7f);
    *minute = bcdToDec(Wire.read());
    *hour = bcdToDec(Wire.read() & 0x3f);
    *dayOfWeek = bcdToDec(Wire.read());
    *dayOfMonth = bcdToDec(Wire.read());
    *month = bcdToDec(Wire.read());
    *year = bcdToDec(Wire.read());
}

