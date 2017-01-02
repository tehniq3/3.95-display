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
int hh1, mm1, yy1, ll1, dd1, zz1;

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

byte limburus = 0;  // 0 for english, 1 pt romana

#define meniu 23
#define minus 24
#define plus 25
byte nivel=20;  //
int maxday;



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


if (limburus == 0)
{
 tft.setTextSize(3);
            tft.setCursor(50, 20);
            tft.setTextColor(WHITE);
            tft.println("Clock with thermometer");
            tft.setCursor(80, 80);
            tft.setTextColor(RED);
            tft.println("on 3.95inch display");      
            tft.setCursor(90, 140);
            tft.setTextColor(GREEN);
            tft.println("original sketch by");   
            tft.setCursor(140, 200);
            tft.setTextColor(BLUE);
            tft.println("Nicu FLORICA");  
            tft.setCursor(180, 260);
            tft.setTextColor(BLUE);
            tft.println("(niq_ro)");    
    delay(3000);
    tft.fillScreen(BLACK);  // clear screen  
    tft.setTextColor(WHITE);
    tft.setCursor(30, 140);
    tft.println("in memory of Figo cat,");   
    tft.setCursor(0, 200);
    tft.println("member of my family..");   
}
else
{
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
    delay(3000);
    tft.setTextSize(3);
    tft.fillScreen(BLACK);  // clear screen  
    tft.setCursor(10, 140);
    tft.setTextColor(WHITE);
    tft.println("in memoria pisicului Figo,");
    tft.setCursor(30, 190);
    tft.println("membru al familiei...");   
   
}
   delay(5000);
    tft.fillScreen(BLACK);  // clear screen
 tft.setTextSize(3);    
pinMode(meniu, INPUT);   // MENU button
pinMode(plus, INPUT);   // + button
pinMode(minus, INPUT);   // + button
digitalWrite(meniu, HIGH);  
digitalWrite(plus, HIGH);  
digitalWrite(minus, HIGH);  
}

void loop(void) {
  
  
if (nivel == 1)  // clock & thermometer
{
  
if (digitalRead(meniu) == LOW)
  {
  nivel = 2;
  tft.fillScreen(BLACK);  // clear screen
//  delay(500);
  }   
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
            tft.setTextColor(RED);
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
tft.setTextColor(YELLOW);
if (zz != zz0)
{
for (int i=0; i<9; i++){  
stergere(20+i*18,150,3);
}
zz0 = zz;
}
if (limburus == 1)
{
tft.setCursor(20, 150);
if ((zz == 0) || (zz == 7)) tft.print("Duminica"); 
if (zz == 1) tft.print("Luni");
if (zz == 2) tft.print("Marti");
if (zz == 3) tft.print("Miercuri");
if (zz == 4) tft.print("Joi");
if (zz == 5) tft.print("Vineri");
if (zz == 6) tft.print("Sambata");
}
else
{
tft.setCursor(20, 150);
if ((zz == 0) || (zz == 7)) tft.print("Sunday"); 
if (zz == 1) tft.print("Monday");
if (zz == 2) tft.print("Tuesday");
if (zz == 3) tft.print("Wednesday");
if (zz == 4) tft.print("Thursday");
if (zz == 5) tft.print("Friday");
if (zz == 6) tft.print("Saturday");
}
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
} // end level 1

if (nivel == 2)  // clear screen and enter to change hour
{
tft.fillScreen(BLACK);  // clear screen  
delay(500);
hh1 = hh;
tft.setTextSize(5);  
tft.setCursor(0, 0); 
if (limburus == 0)
{
tft.print("Hour adjus:");
}
else
tft.print("Reglaj ora:");
tft.setTextSize(15);  
nivel = 3;
}


if (nivel == 3)  // clear screen and enter to change hour
{
zh = hh1/10;
uh = hh1%10;
stergere(x+100,120,15); // hour
stergere(x+200,120,15);
            tft.setCursor(x+110, 120);
            tft.setTextColor(RED);
            tft.print(zh);
            tft.print(uh);
delay(10);
            tft.setCursor(x+110, 120);
            tft.setTextColor(BLUE);
            tft.print(zh);
            tft.print(uh);
delay(10);

if (digitalRead(meniu) == LOW)
  {
  nivel = 4;
  mm1 = mm;
  tft.fillScreen(BLACK);  // clear screen
//  delay(500);
  }   

if (digitalRead(plus) == LOW)
    {
    hh1 = hh1+1;
    delay(150);
    }
if (digitalRead(minus) == LOW)
    {
    hh1 = hh1-1;
    delay(150);
    }    
if (hh1 > 23) hh1 = 0;
if (hh1 < 0) hh1 = 23;  
}  

if (nivel == 4)  // clear screen and enter to change minutes
{
tft.fillScreen(BLACK);  // clear screen  
delay(500);
tft.setTextSize(5);  
tft.setCursor(0, 0); 
if (limburus == 0)
{
tft.print("Minute adjus:");
}
else
tft.print("Reglaj minute:");
tft.setTextSize(15);  
nivel = 5;
}


if (nivel == 5)  // clear screen and enter to change minute
{
zm = mm1/10;
um = mm1%10;
stergere(x+100,120,15); // hour
stergere(x+200,120,15);
            tft.setCursor(x+110, 120);
            tft.setTextColor(RED);
            tft.print(zm);
            tft.print(um);
delay(10);
            tft.setCursor(x+110, 120);
            tft.setTextColor(BLUE);
            tft.print(zm);
            tft.print(um);
delay(10);

if (digitalRead(meniu) == LOW)
  {
  nivel = 6;
  tft.fillScreen(BLACK);  // clear screen
//  delay(500);
  }   

if (digitalRead(plus) == LOW)
    {
    mm1 = mm1+1;
    delay(150);
    }
if (digitalRead(minus) == LOW)
    {
    mm1 = mm1-1;
    delay(150);
    }    
if (mm1 > 59) mm1 = 0;
if (mm1 < 0) mm1 = 59;  
}  

if (nivel == 6)  // clear screen and enter to change minutea
{
tft.fillScreen(BLACK);  // clear screen  
delay(500);
tft.setTextSize(5);  
tft.setCursor(0, 0);
yy1 = yy;
if (limburus == 0)
{
tft.print("Year adjus:");
}
else
tft.print("Reglaj an:");
tft.setTextSize(15);  
tft.setCursor(x+60, 120);
tft.print("20");
nivel = 7;
}

if (nivel == 7)  // clear screen and enter to change minute
{
zy = yy1/10;
uy = yy1%10;
stergere(x+240,120,15); // year
stergere(x+320,120,15);
            tft.setCursor(x+240, 120);
            tft.setTextColor(RED);
            tft.print(zy);
            tft.print(uy);
delay(10);
            tft.setCursor(x+240, 120);
            tft.setTextColor(BLUE);
            tft.print(zy);
            tft.print(uy);
delay(10);

if (digitalRead(meniu) == LOW)
  {
  nivel = 8;
  tft.fillScreen(BLACK);  // clear screen
  ll1 = ll;
//  delay(500);
  }   

if (digitalRead(plus) == LOW)
    {
    yy1 = yy1+1;
    delay(150);
    }
if (digitalRead(minus) == LOW)
    {
    yy1 = yy1-1;
    delay(150);
    }    
if (yy1 > 29) yy1 = 17;
if (yy1 < 17) yy1 = 29;  
}  

if (nivel == 8)  // clear screen and enter to change minutea
{
tft.fillScreen(BLACK);  // clear screen  
delay(500);
tft.setTextSize(5);  
tft.setCursor(0, 0);
ll1 = ll;
if (limburus == 0)
{
tft.print("Month adjus:");
}
else
tft.print("Reglaj luna:");
tft.setTextSize(15);  
nivel = 9;
}

if (nivel == 9)  // clear screen and enter to change month
{
zl = ll1/10;
ul = ll1%10;
stergere(x+100,120,15); // hour
stergere(x+200,120,15);
            tft.setCursor(x+110, 120);
            tft.setTextColor(RED);
            tft.print(zl);
            tft.print(ul);
delay(10);
            tft.setCursor(x+110, 120);
            tft.setTextColor(BLUE);
            tft.print(zl);
            tft.print(ul);
delay(10);

if (digitalRead(meniu) == LOW)
  {
  nivel = 10;
  tft.fillScreen(BLACK);  // clear screen
//  delay(500);
  }   

if (digitalRead(plus) == LOW)
    {
    ll1 = ll1+1;
    delay(150);
    }
if (digitalRead(minus) == LOW)
    {
    ll1 = ll1-1;
    delay(150);
    }    
if (ll1 > 12) ll1 = 1;
if (ll1 < 1) ll1 = 12;  
}  

if (nivel == 10)  // clear screen and enter to change day in month
{
tft.fillScreen(BLACK);  // clear screen  
delay(500);
tft.setTextSize(5);  
tft.setCursor(0, 0);
dd1 = dd;
if (limburus == 0)
{
tft.print("Day adjus:");
}
else
tft.print("Reglaj zi:");
tft.setTextSize(15); 
dd1 = dd;
nivel = 11;
}

if (nivel == 11)  // clear screen and enter to change day in month
{
zd = dd1/10;
ud = dd1%10;
stergere(x+100,120,15); // day
stergere(x+200,120,15);
            tft.setCursor(x+110, 120);
            tft.setTextColor(RED);
            tft.print(zd);
            tft.print(ud);
delay(10);
            tft.setCursor(x+110, 120);
            tft.setTextColor(BLUE);
            tft.print(zd);
            tft.print(ud);
delay(10);

if (digitalRead(meniu) == LOW)
  {
  nivel = 12;
  tft.fillScreen(BLACK);  // clear screen
//  delay(500);
  }   

if (digitalRead(plus) == LOW)
    {
    dd1 = dd1+1;
    delay(150);
    }
if (digitalRead(minus) == LOW)
    {
    dd1 = dd1-1;
    delay(150);
    }    
   
 // Dawn & Dusk controller. http://andydoz.blogspot.ro/2014_08_01_archive.html
 if (ll == 4 || ll == 5 || ll == 9 || ll == 11) { //30 days hath September, April June and November
    maxday = 30;
  }
  else {
  maxday = 31; //... all the others have 31
  }
  if (ll ==2 && yy % 4 ==0) { //... Except February alone, and that has 28 days clear, and 29 in a leap year.
    maxday = 29;
  }
  if (ll ==2 && ll % 4 !=0) {
    maxday = 28;
  }

if (dd1 > maxday) dd1 = 1;
if (dd1 < 1) dd1 = maxday;           
}  

if (nivel == 12)  // clear screen and enter to change day in week
{
tft.fillScreen(BLACK);  // clear screen  
delay(500);
tft.setTextSize(3);  
tft.setCursor(0, 0);
zz1 = zz;
if (limburus == 0)
{
tft.print("Day in week adjus:");
}
else
tft.print("Reglaj zi in saptamana:");
tft.setTextSize(15);  
nivel = 13;
}

if (nivel == 13)  // clear screen and enter to change month
{
stergere(x+100,120,15); // hour
            tft.setCursor(x+110, 120);
            tft.setTextColor(RED);
            tft.print(zz1);
delay(10);
            tft.setCursor(x+110, 120);
            tft.setTextColor(BLUE);
            tft.print(zz1);
delay(10);

if (digitalRead(meniu) == LOW)
  {
  nivel = 14;
  tft.fillScreen(BLACK);  // clear screen
//  delay(500);
  }   

if (digitalRead(plus) == LOW)
    {
    zz1 = zz1+1;
    delay(150);
    }
if (digitalRead(minus) == LOW)
    {
    zz1 = zz1-1;
    delay(150);
    }    
if (zz1 > 6) ll1 = 0;
if (ll1 < 0) ll1 = 7;  
}  

if (nivel == 14)  // clear screen and enter to change minutea
{
tft.fillScreen(BLACK);  // clear screen  
delay(500);
tft.setTextSize(5);  
tft.setCursor(0, 0);
yy1 = yy;
if (limburus == 0)
{
tft.print("Record data...");
}
else
tft.print("Memorez datele...");
tft.setTextSize(15);  
nivel = 19;
}

if (nivel == 19)  // clear screen and enter to change minutea
{
tft.fillScreen(BLACK);  // clear screen  
delay(500);
setDS3231time(0, mm1, hh1, zz1, dd1, ll1, yy1);
nivel = 20;
}

if (nivel == 20)
{
delay(500);
tft.fillScreen(BLACK);  // clear screen
nivel = 1;
}  
 
             
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

