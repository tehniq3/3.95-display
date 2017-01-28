// All the mcufriend.com UNO shields have the same pinout.
// i.e. control pins A0-A4.  Data D2-D9.  microSD D10-D13.
// Touchscreens are normally A1, A2, D7, D6 but the order varies
// https://github.com/prenticedavid/MCUFRIEND_kbv
// This demo should work with most Adafruit TFT libraries
// If you are not using a shield,  use a full Adafruit constructor()

// e.g. Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
// Nicu FLORICA (niq_ro) clear the sketch for pust some text in portrait and landscape mode
// ver. 0 - just clear the sketch
// ver. 1 - put some info as dual thermostat with clock
// ver. 2 - put animates second points and valve
// ver. 3 - add random value for temperature and clock
// ver. 4 - add real DS18B20 sensor (3 units) ad D22 pin
// ver. 5 - add DS3231 RTC module for clock
// ver. 6 - add 3 button (contacts) for icons at D23, D24 & D25 pins
// ver. 7 - add menu for change clock (hours and data) and store set temperature and others in EEPROM from DS3231 RTC module

// from example MULTIPLE - DALLAS TEMPERATURE LIBRARY
#include <OneWire.h>
#include <DallasTemperature.h>

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

#define  BLACK   0x0000
#define RED     0x001F
#define BLUE    0xF800
#define GREEN   0x07E0
#define YELLOW  0x07FF
#define MAGENTA 0xF81F
#define CYAN    0xFFE0
#define WHITE   0xFFFF

uint16_t g_identifier;

byte hh, mm, ss;
byte yy, ll, dd, zz;
byte zh,uh,zm,um;
byte hh0 = 14;
byte mm0 = 35;

unsigned long ultimultimp;
unsigned long cattimp = 3000;
int stare = 0;

int text, tfl, tpart;
int text0 = 50;
int tfl0 = 50;
int tpart0 = 50;

// split part of temperature
// external temperature
int exts =1;
int extz =1;
int extu =2;

// floor (etaj)
int etajz = 2;
int etaju = 4;

// parterre (parter)
int partz = 2;
int partu = 2;

int bucla = 0;
int initial = 0;

// Data wire is plugged into port 22 on the Arduino
#define ONE_WIRE_BUS 22
#define TEMPERATURE_PRECISION 9
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
// arrays to hold device addresses
DeviceAddress senzor1, senzor2, senzor3;

#define robinet1 26
#define etaj 27
#define parter 28

byte limburus = 1;  // 0 for english, 1 pt romana
#define meniu 23
#define minus 24
#define plus 25
byte nivel=30;  // clear display anfd go to normal state
int maxday;

int hh1, mm1, yy1, ll1, dd1, zz1;
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

byte extra = 1;  // if 1 = display data and nane of day

int tt1 = 24;   // set temperature for s1st zone
int tt2 = 25;   // set temperature for 2nd zone
int dt = 5;     // x10 histeresys temperature
byte dtu = 0;
byte dts = 5;
int tmax = 27;
int tmin = 17;
int dtmin = 1;
int dtmax = 10;

#define disk1 0x57    //Address of 24LC256 eeprom chip

void setup(void) {
    Serial.begin(9600);
    g_identifier = 0x9481;// force ID
    tft.begin(g_identifier);
    tft.fillScreen(BLACK);  // clear screen
    
    ultimultimp = millis();
tft.setRotation(1);  // landscape
  
    Wire.begin();
    
http://www.hobbytronics.co.uk/arduino-external-eeprom
limburus = readEEPROM(disk1, 0), DEC;
if (limburus > 1) limburus = 1;
if (limburus < 0) limburus = 0;

tt1 = readEEPROM(disk1, 1), DEC;
if (tt1 > tmax) tt1 = tmax;
if (tt1 < tmin) tt1 = tmin;

tt2 = readEEPROM(disk1, 2), DEC;
if (tt2 > tmax) tt2 = tmax;
if (tt2 < tmin) tt2 = tmin;

dt = readEEPROM(disk1, 3), DEC;
if (dt > dtmax) dt = dtmax;
if (dt < dtmin) dt = dtmin;

if (limburus == 0)
{
 tft.setTextSize(3);
            tft.setCursor(20, 20);
            tft.setTextColor(WHITE);
            tft.println("Dual thermometer ver.7.0");
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
}
else
{
 tft.setTextSize(4);
            tft.setCursor(20, 20);
            tft.setTextColor(WHITE);
            tft.println("Termostat dublu 7.0");
            tft.setCursor(30, 80);
            tft.setTextColor(RED);
            tft.println("pe afisaj de 10cm");      
            tft.setCursor(40, 140);
            tft.setTextColor(GREEN);
            tft.println("program scris de");   
            tft.setCursor(90, 200);
            tft.setTextColor(BLUE);
            tft.println("Nicu FLORICA");  
            tft.setCursor(130, 260);
            tft.setTextColor(BLUE);
            tft.println("(niq_ro)");      
}
  delay(3000);

 
pinMode(robinet1, INPUT);  // valve button
pinMode(etaj, OUTPUT);   // floor relay
pinMode(parter, OUTPUT);   // ground relay
digitalWrite(robinet1, HIGH);  
digitalWrite(etaj, LOW);  
digitalWrite(parter, LOW);  

pinMode(meniu, INPUT);   // MENU button
pinMode(plus, INPUT);   // + button
pinMode(minus, INPUT);   // + button
digitalWrite(meniu, HIGH);  
digitalWrite(plus, HIGH);  
digitalWrite(minus, HIGH);  
 
  // Start up the library
  sensors.begin();

  // locate devices on the bus
  Serial.print("Locating devices...");
  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" devices.");

  // report parasite power requirements
  Serial.print("Parasite power is: "); 
  if (sensors.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");

  // assign address manually.  the addresses below will beed to be changed
  // to valid device addresses on your bus.  device address can be retrieved
  // by using either oneWire.search(deviceAddress) or individually via
  // sensors.getAddress(deviceAddress, index)
  //insideThermometer = { 0x28, 0x1D, 0x39, 0x31, 0x2, 0x0, 0x0, 0xF0 };
  //outsideThermometer   = { 0x28, 0x3F, 0x1C, 0x31, 0x2, 0x0, 0x0, 0x2 };

  // search for devices on the bus and assign based on an index.  ideally,
  // you would do this to initially discover addresses on the bus and then 
  // use those addresses and manually assign them (see above) once you know 
  // the devices on your bus (and assuming they don't change).
  // 
  // method 1: by index
  if (!sensors.getAddress(senzor1, 0)) Serial.println("Unable to find address for Device 0"); 
  if (!sensors.getAddress(senzor2, 1)) Serial.println("Unable to find address for Device 1");
  if (!sensors.getAddress(senzor3, 2)) Serial.println("Unable to find address for Device 2");

  // method 2: search()
  // search() looks for the next device. Returns 1 if a new address has been
  // returned. A zero might mean that the bus is shorted, there are no devices, 
  // or you have already retrieved all of them.  It might be a good idea to 
  // check the CRC to make sure you didn't get garbage.  The order is 
  // deterministic. You will always get the same devices in the same order
  //
  // Must be called before search()
  //oneWire.reset_search();
  // assigns the first address found to insideThermometer
  //if (!oneWire.search(insideThermometer)) Serial.println("Unable to find address for insideThermometer");
  // assigns the seconds address found to outsideThermometer
  //if (!oneWire.search(outsideThermometer)) Serial.println("Unable to find address for outsideThermometer");

  // show the addresses we found on the bus
  Serial.print("Device 0 Address: ");
  printAddress(senzor1);
  Serial.println();

  Serial.print("Device 1 Address: ");
  printAddress(senzor2);
  Serial.println();

  Serial.print("Device 2 Address: ");
  printAddress(senzor3);
  Serial.println();

  // set the resolution to 9 bit
  sensors.setResolution(senzor1, TEMPERATURE_PRECISION);
  sensors.setResolution(senzor2, TEMPERATURE_PRECISION);
  sensors.setResolution(senzor3, TEMPERATURE_PRECISION);
 

  Serial.print("Device 0 Resolution: ");
  Serial.print(sensors.getResolution(senzor1), DEC); 
  Serial.println();

  Serial.print("Device 1 Resolution: ");
  Serial.print(sensors.getResolution(senzor2), DEC); 
  Serial.println();

  Serial.print("Device 2 Resolution: ");
  Serial.print(sensors.getResolution(senzor3), DEC); 
  Serial.println();

 tft.fillScreen(BLACK);  // clear screen
 
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
            tft.setTextSize(6);
 readDS3231time(&ss, &mm, &hh, &zz, &dd, &ll,&yy);
if (mm != mm0)
{
stergere(118,20,6); // minute
stergere(154,20,6);  
}


if (hh != hh0)
{
stergere(10,20,6); // hour
stergere(46,20,6);  
}

zh = hh/10;
uh = hh%10;
zm = mm/10;
um = mm%10;
mm0 = mm;
hh0 = hh;

// first row - clock (primul rand  - ora)
            tft.setCursor(10, 20);
            tft.setTextColor(WHITE);
            tft.print(zh);
            tft.print(uh);
            if (millis()/1000%2) tft.print(":");
            else 
            {
            stergere(82,20,6);
            tft.print(" ");            
            }
            
            tft.print(zm);
            tft.print(um);

if (extra == 1)
{
tft.setTextSize(2);
tft.setTextColor(GREEN);
if (zz != zz0)
{
for (int i=0; i<9; i++){  
stergere(220+i*18,20,2);
}
zz0 = zz;
}
if (limburus == 1)
{
tft.setCursor(220, 20);
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
tft.setCursor(220, 20);
if ((zz == 0) || (zz == 7)) tft.print("Sunday"); 
if (zz == 1) tft.print("Monday");
if (zz == 2) tft.print("Tuesday");
if (zz == 3) tft.print("Wednesday");
if (zz == 4) tft.print("Thursday");
if (zz == 5) tft.print("Friday");
if (zz == 6) tft.print("Saturday");
}

//tft.setTextColor(GREEN);
tft.setCursor(220, 50);
if (dd != dd0)
{
for (int i=0; i<10; i++){  
stergere(220+i*18,50,2);
}
dd0 = dd;
}

zd = dd/10;
ud = dd%10;
zl = ll/10;
ul = ll%10;
zy = yy/10;
uy = yy%10;


tft.setCursor(220, 50);
tft.print(zd);
tft.print(ud);
tft.print("/");
tft.print(zl);
tft.print(ul);
tft.print("/20");
tft.print(zy);
tft.print(uy);
} // enf of extra


if ((bucla > 50) || (initial == 0))
{
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures();
  Serial.println("DONE");

  // print the device information
  printData(senzor1);
  printData(senzor2);  
  printData(senzor3);  
/*
float tempC1 = sensors.getTempC(senzor1);
float tempC2 = sensors.getTempC(senzor2);
float tempC3 = sensors.getTempC(senzor3);
*/
float tempC1 = sensors.getTempC(senzor1) +0.5;
float tempC2 = sensors.getTempC(senzor2) +0.5;
float tempC3 = sensors.getTempC(senzor3) +0.5;

if ((tempC1 < -100) || (tempC1 >100)) tempC1 = 0;
if ((tempC2 < -100) || (tempC2 >100)) tempC2 = 0;
if ((tempC3 < -100) || (tempC3 >100)) tempC3 = 0;

text = tempC3;
tfl = tempC1;
tpart = tempC2;

//text = random(-20, 30);  //  
//text = -12;
//text = -7;
//text =0;
//text = 4;
//text = 17;
//tfl = random (19,24);
//tfl =0;
//tfl = 4;
//tfl = 17;
//tpart = random (19,24);
//tpart =0;
//tpart = 4;
//tpart = 17;

  bucla = 0;
  initial = 1;
}
bucla = bucla +1;

// second row - external temperature (al doilea rand - temperatura exterioara)
if (text != text0)
{
if (text < 0)
{
 exts = -1;
 text = -text;
}
else exts = 1;

extz = text/10;
extu = text%10;
            tft.setCursor(10, 100);
            tft.setTextColor(YELLOW);
       if (limburus == 1)
       {
        tft.setTextSize(5);
        tft.print("EXT");
       }
       if (limburus == 0)
       {
        tft.setTextSize(4);
        tft.print("Outside");
       }
            tft.setTextSize(6);
//          tft.setCursor(204, 100);
//          tft.print("-12 C");
            stergere(204,100,6);
            stergere(240,100,6);
            stergere(276,100,6);
            if ((exts == -1) && (text > 10))         
            {
             tft.setCursor(204, 100); 
             tft.print("-");
             tft.print(extz);
             tft.print(extu);
            }
            if ((exts == -1) && (text < 10))         
            {
             tft.setCursor(240, 100); 
             tft.print("-");
             tft.print(extu);
            }
            if ((exts == 1) && (text < 10))        
            {
             tft.setCursor(276, 100); 
             tft.print(extu);
            }
            if ((exts == 1) && (text > 10))         
            {
             tft.setCursor(240, 100); 
             tft.print(extz);
             tft.print(extu);
            }
            if (text == 0)        
            {
             tft.setCursor(276, 100); 
             tft.print(text);
            }
            
            tft.setTextSize(3);
            tft.setCursor(320, 85);
            tft.print("o");
            tft.setTextSize(6);
            tft.setCursor(348, 100);
            tft.print("C");
text0 = exts*text;
}

// 3rd row - floor temperature (al treilea rand - temperatura etaj)
if (tfl != tfl0)
{
etajz = tfl/10;
etaju = tfl%10;
            tft.setCursor(10, 180);
            tft.setTextColor(CYAN);
            if (limburus == 1)
            {
            tft.setTextSize(5);
            tft.print("ETAJ");
            }
            if (limburus == 0)
            {
             tft.setTextSize(4);
            tft.print("1st zone");
            }
            stergere(240,180,6);
            stergere(276,180,6);
            tft.setTextSize(6);
            tft.setCursor(240, 180);
 //           tft.print("24 C");
            if (tfl < 10)
            {
             tft.print(" ");
            } 
            else tft.print(etajz); 
            tft.print(etaju);
            
            tft.setTextSize(3);
            tft.setCursor(320, 165);
            tft.print("o");
            tft.setTextSize(6);
            tft.setCursor(348, 180);
            tft.print("C");
tfl0 = tfl;
}

// al patrulea rand - temperatura parter            
if (tpart != tpart0)
{
partz = tpart/10;
partu = tpart%10;
            tft.setCursor(10, 260);
            tft.setTextColor(RED);
            if (limburus == 1)
            {
            tft.setTextSize(5);
            tft.print("PARTER");
            }
            if (limburus == 0)
            {
             tft.setTextSize(4);
            tft.print("2nd zone");
            }
            stergere(240,260,6);
            stergere(276,260,6);
            tft.setTextSize(6);
            tft.setCursor(240, 260);
 //           tft.print("22 C");
            if (tpart < 10)
            {
             tft.print(" ");
            } 
            else tft.print(partz); 
            tft.print(partu);

            tft.setTextSize(3);
            tft.setCursor(320, 245);
            tft.print("o");
            tft.setTextSize(6);
            tft.setCursor(348, 260);
            tft.print("C");

tpart0 = tpart;
}

if (digitalRead(robinet1) == LOW)
{
robinet (ics1, igrec1);
}
else
{
stergere1 (ics1, igrec1);
}
/*
if (digitalRead(etaj) == LOW)
{
triunghi(400, 170);
}
else
{
stergere1 (400, 170);
}

if (digitalRead(parter) == LOW)
{
triunghi(400, 250);
}
else
{
stergere1 (400, 250);
}
*/
if (tfl < tt1-dt/10)
{
triunghi(400, 170);
digitalWrite(etaj, HIGH);
}
if (tfl >= tt1)
{
stergere1 (400, 170);
digitalWrite(etaj, LOW);
}

if (tpart < tt2-dt/10){
triunghi(400, 250);
digitalWrite(parter, HIGH);
}
if (tpart >= tt2)
{
stergere1 (400, 250);
digitalWrite(parter, LOW);
}

} // end level 1


if (nivel == 2)  // clear screen and enter to change temperature for 1st zone 
{
tft.fillScreen(BLACK);  // clear screen  
delay(500);
tft.setTextSize(3);  
tft.setCursor(0, 0); 
if (limburus == 0)
{
tft.print("1st zone temperature:");
}
else
tft.print("Reglaj temperatura etaj:");
tft.setTextSize(15);  
nivel = 3;
}

if (nivel == 3)  // clear screen and enter to change temperature in 1st zone
{
stergere(x+100,120,15); // 
stergere(x+190,120,15);
            tft.setCursor(x+110, 120);
            tft.setTextColor(RED);
            tft.print(tt1);
            delay(10);
            tft.setCursor(x+110, 120);
            tft.setTextColor(BLUE);
            tft.print(tt1);
delay(10);

if (digitalRead(meniu) == LOW)
  {
  nivel = 4;
  tft.fillScreen(BLACK);  // clear screen
//  delay(500);
  }   

if (digitalRead(plus) == LOW)
    {
    tt1 = tt1+1;
    delay(150);
    }
if (digitalRead(minus) == LOW)
    {
    tt1 = tt1-1;
    delay(150);
    }    
if (tt1 > tmax) tt1 = tmin;
if (tt1 < tmin) tt1 = tmax;  
}  

if (nivel == 4)  // clear screen and enter to change temperature for 2nd zone 
{
tft.fillScreen(BLACK);  // clear screen  
delay(500);
tft.setTextSize(3);  
tft.setCursor(0, 0); 
if (limburus == 0)
{
tft.print("2nd zone temperature:");
}
else
tft.print("Reglaj temperatura parter:");
tft.setTextSize(15);  
nivel = 5;
}

if (nivel == 5)  // clear screen and enter to change temperature in 2nd zone
{
stergere(x+100,120,15); // 
stergere(x+190,120,15);
            tft.setCursor(x+110, 120);
            tft.setTextColor(RED);
            tft.print(tt2);
delay(10);
            tft.setCursor(x+110, 120);
            tft.setTextColor(BLUE);
            tft.print(tt2);
delay(10);

if (digitalRead(meniu) == LOW)
  {
  nivel = 6;
  tft.fillScreen(BLACK);  // clear screen
//  delay(500);
  }   

if (digitalRead(plus) == LOW)
    {
    tt2 = tt2+1;
    delay(150);
    }
if (digitalRead(minus) == LOW)
    {
    tt2 = tt2-1;
    delay(150);
    }    
if (tt2 > tmax) tt2 = tmin;
if (tt2 < tmin) tt2 = tmin;  
}  

if (nivel == 6)  // clear screen and enter to change histeresys temperature
{
tft.fillScreen(BLACK);  // clear screen  
delay(500);
tft.setTextSize(3);  
tft.setCursor(0, 0); 
if (limburus == 0)
{
tft.print("histeresys temperature:");
}
else
tft.print("Histerezis temperatura:");
tft.setTextSize(15);  
nivel = 7;
}

if (nivel == 7)  // clear screen and enter to change histeresys temperature
{
dtu = dt/10;
dts = dt%10;
stergere(x+100,120,15); // 
stergere(x+190,120,15);
stergere(x+280,120,15);
            tft.setCursor(x+110, 120);
            tft.setTextColor(RED);
            tft.print(dtu);
            tft.print(".");
            tft.print(dts);
delay(10);
            tft.setCursor(x+110, 120);
            tft.setTextColor(BLUE);
            tft.print(dtu);
            tft.print(".");
            tft.print(dts);
delay(10);

if (digitalRead(meniu) == LOW)
  {
  nivel = 8;
  tft.fillScreen(BLACK);  // clear screen
//  delay(500);
  }   

if (digitalRead(plus) == LOW)
    {
    dt = dt+1;
    delay(150);
    }
if (digitalRead(minus) == LOW)
    {
    dt = dt-1;
    delay(150);
    }    
if (dt > dtmax) dt = dtmin;
if (dt < dtmin)  dt = dtmax;  
}  

if (nivel == 8)  // clear screen and enter to change language
{
tft.fillScreen(BLACK);  // clear screen  
delay(500);
tft.setTextSize(3);  
tft.setCursor(0, 0); 
if (limburus == 0)
{
tft.print("language adjust:");
tft.setCursor(10, 20); 
tft.print("0) english");
tft.setCursor(10, 40); 
tft.print("1) romanian");
}
else
{
tft.print("Selectie limba:");
tft.setCursor(10, 20); 
tft.print("0) engleza");
tft.setCursor(10, 40); 
tft.print("1) romana");
}
tft.setTextSize(15);  
nivel = 9;
}

if (nivel == 9)  // clear screen and enter to change language
{
stergere(x+100,120,15); // 
//stergere(x+200,120,15);
            tft.setCursor(x+110, 120);
            tft.setTextColor(RED);
            tft.print(limburus);
            delay(10);
            tft.setCursor(x+110, 120);
            tft.setTextColor(BLUE);
            tft.print(limburus);
delay(10);

if (digitalRead(meniu) == LOW)
  {
  nivel = 10;
  hh1 = hh;
  tft.fillScreen(BLACK);  // clear screen
//  delay(500);
  }   

if (digitalRead(plus) == LOW)
    {
    limburus = limburus + 1;
    delay(150);
    }
if (digitalRead(minus) == LOW)
    {
    limburus = limburus -1;
    delay(150);
    }    
if (limburus > 1) limburus = 0;
if (limburus < 0) limburus = 1;  
}  


if (nivel == 10)  // clear screen and enter to change hour
{
tft.fillScreen(BLACK);  // clear screen  
delay(500);
tft.setTextColor(RED);
//tt1 = ;
tft.setTextSize(5);  
tft.setCursor(0, 0); 
if (limburus == 0)
{
tft.print("Hour adjust:");
}
else
tft.print("Reglaj ora:");
tft.setTextSize(15);  
nivel = 11;
}


if (nivel == 11)  // clear screen and enter to change hour
{
zh = hh1/10;
uh = hh1%10;
stergere(x+100,120,15); // hour
stergere(x+190,120,15);
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
  nivel = 12;
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

if (nivel == 12)  // clear screen and enter to change minutes
{
tft.fillScreen(BLACK);  // clear screen  
delay(500);
tft.setTextSize(5);  
tft.setCursor(0, 0); 
if (limburus == 0)
{
tft.print("Minute adjust:");
}
else
tft.print("Reglaj minute:");
tft.setTextSize(15);  
nivel = 13;
}


if (nivel == 13)  // clear screen and enter to change minute
{
zm = mm1/10;
um = mm1%10;
stergere(x+100,120,15); // hour
stergere(x+190,120,15);
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
  nivel = 14;
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

if (nivel == 14)  // clear screen and enter to change minutea
{
tft.fillScreen(BLACK);  // clear screen  
delay(500);
tft.setTextSize(5);  
tft.setCursor(0, 0);
yy1 = yy;
if (limburus == 0)
{
tft.print("Year adjust:");
}
else
tft.print("Reglaj an:");
tft.setTextSize(15);  
tft.setCursor(x+60, 120);
tft.print("20");
nivel = 15;
}

if (nivel == 15)  // clear screen and enter to change minute
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
  nivel = 16;
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

if (nivel == 16)  // clear screen and enter to change minutea
{
tft.fillScreen(BLACK);  // clear screen  
delay(500);
tft.setTextSize(5);  
tft.setCursor(0, 0);
ll1 = ll;
if (limburus == 0)
{
tft.print("Month adjust:");
}
else
tft.print("Reglaj luna:");
tft.setTextSize(15);  
nivel = 17;
}

if (nivel == 17)  // clear screen and enter to change month
{
zl = ll1/10;
ul = ll1%10;
stergere(x+100,120,15); // hour
stergere(x+190,120,15);
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
  nivel = 18;
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

if (nivel == 18)  // clear screen and enter to change day in month
{
tft.fillScreen(BLACK);  // clear screen  
delay(500);
tft.setTextSize(5);  
tft.setCursor(0, 0);
dd1 = dd;
if (limburus == 0)
{
tft.print("Day adjust:");
}
else
tft.print("Reglaj zi:");
tft.setTextSize(15); 
dd1 = dd;
nivel = 19;
}

if (nivel == 19)  // clear screen and enter to change day in month
{
zd = dd1/10;
ud = dd1%10;
stergere(x+100,120,15); // day
stergere(x+190,120,15);
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
  nivel = 20;
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

if (nivel == 20)  // clear screen and enter to change day in week
{
tft.fillScreen(BLACK);  // clear screen  
delay(500);
tft.setTextSize(3);  
tft.setCursor(0, 0);
zz1 = zz;
if (limburus == 0)
{
tft.print("Day in week adjust:");
}
else
tft.print("Reglaj zi in saptamana:");
tft.setTextSize(15);  
nivel = 21;
}

if (nivel == 21)  // clear screen and enter to change month
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
  nivel = 22;
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
if (zz1 > 6) zz1 = 0;
if (ll1 < 0) zz1 = 7;  
}  

if (nivel == 22)  // clear screen and enter to change minutea
{
tft.fillScreen(BLACK);  // clear screen  
delay(500);
tft.setTextSize(5);  
tft.setCursor(0, 0);
if (limburus == 0)
{
tft.print("Record data...");
}
else
tft.print("Memorez datele...");
tft.setTextSize(15);  
nivel = 29;
}

if (nivel == 29)  // clear screen and enter to change minutea
{
tft.fillScreen(BLACK);  // clear screen  
delay(500);

setDS3231time(0, mm1, hh1, zz1, dd1, ll1, yy1);
/*
EEPROM.write(0,limburus);
EEPROM.write(1,tt1);
EEPROM.write(2,tt2);
EEPROM.write(3,dt);
*/
writeEEPROM(disk1, 0, limburus);
writeEEPROM(disk1, 1, tt1);
writeEEPROM(disk1, 2, tt2);
writeEEPROM(disk1, 3, dt);

nivel = 30;
}

if (nivel == 30)
{
delay(500);
tft.fillScreen(BLACK);  // clear screen
nivel = 1;
initial = 0;
hh0 = 14;
mm0 = 35;
text0 = 50;
tfl0 = 50;
tpart0 = 50;
}  

}  // end

void robinet(int ics, int igrec)
{
tft.drawLine(ics+24, igrec+0, ics+44, igrec+0, BLUE);
tft.drawLine(ics+24, igrec+1, ics+44, igrec+1, BLUE);
tft.drawLine(ics+24, igrec+2, ics+44, igrec+2, BLUE);
tft.drawLine(ics+24, igrec+3, ics+44, igrec+3, BLUE);

tft.drawLine(ics+24, igrec+4, ics+44, igrec+4, BLUE);
tft.drawLine(ics+24, igrec+5, ics+44, igrec+5, BLUE);
tft.drawLine(ics+24, igrec+6, ics+44, igrec+6, BLUE);
tft.drawLine(ics+24, igrec+7, ics+44, igrec+7, BLUE);

tft.drawLine(ics+32, igrec+8, ics+36, igrec+8, BLUE);
tft.drawLine(ics+32, igrec+9, ics+36, igrec+9, BLUE);
tft.drawLine(ics+32, igrec+10, ics+36, igrec+10, BLUE);
tft.drawLine(ics+32, igrec+11, ics+36, igrec+11, BLUE);

tft.drawLine(ics+32, igrec+12, ics+36, igrec+12, BLUE);
tft.drawLine(ics+32, igrec+13, ics+36, igrec+13, BLUE);
tft.drawLine(ics+32, igrec+14, ics+36, igrec+14, BLUE);
tft.drawLine(ics+32, igrec+15, ics+36, igrec+15, BLUE);

tft.drawLine(ics+20, igrec+16, ics+52, igrec+16, BLUE);
tft.drawLine(ics+21, igrec+17, ics+52, igrec+17, BLUE);
tft.drawLine(ics+22, igrec+18, ics+52, igrec+18, BLUE);
tft.drawLine(ics+23, igrec+19, ics+52, igrec+19, BLUE);

tft.drawLine(ics+12, igrec+20, ics+52, igrec+20, BLUE);
tft.drawLine(ics+12, igrec+21, ics+52, igrec+21, BLUE);
tft.drawLine(ics+12, igrec+22, ics+52, igrec+22, BLUE);
tft.drawLine(ics+12, igrec+23, ics+52, igrec+23, BLUE);

tft.drawLine(ics+12, igrec+24, ics+52, igrec+24, BLUE);
tft.drawLine(ics+12, igrec+25, ics+52, igrec+25, BLUE);
tft.drawLine(ics+12, igrec+26, ics+52, igrec+26, BLUE);
tft.drawLine(ics+12, igrec+27, ics+52, igrec+27, BLUE);

tft.drawLine(ics+12, igrec+28, ics+16, igrec+28, BLUE);
tft.drawLine(ics+12, igrec+29, ics+16, igrec+29, BLUE);
tft.drawLine(ics+12, igrec+30, ics+16, igrec+30, BLUE);
tft.drawLine(ics+12, igrec+31, ics+16, igrec+31, BLUE);

tft.drawLine(ics+12, igrec+32, ics+16, igrec+32, BLUE);
tft.drawLine(ics+12, igrec+33, ics+16, igrec+33, BLUE);
tft.drawLine(ics+12, igrec+34, ics+16, igrec+34, BLUE);
tft.drawLine(ics+12, igrec+35, ics+16, igrec+35, BLUE);

tft.drawLine(ics+12, igrec+36, ics+16, igrec+36, RED);
tft.drawLine(ics+12, igrec+37, ics+16, igrec+37, RED);
tft.drawLine(ics+12, igrec+38, ics+16, igrec+38, RED);
tft.drawLine(ics+12, igrec+39, ics+16, igrec+39, RED);

tft.drawLine(ics+12, igrec+40, ics+16, igrec+40, RED);
tft.drawLine(ics+12, igrec+41, ics+16, igrec+41, RED);
tft.drawLine(ics+12, igrec+42, ics+16, igrec+42, RED);
tft.drawLine(ics+12, igrec+43, ics+16, igrec+43, RED);

tft.drawPixel(ics+12, igrec+44, RED);
tft.drawPixel(ics+12, igrec+45, RED);
tft.drawPixel(ics+12, igrec+46, RED);
tft.drawPixel(ics+12, igrec+47, RED);
}  

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
}
}

// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // zero pad the address if necessary
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

// function to print the temperature for a device
void printTemperature(DeviceAddress deviceAddress)
{
  float tempC = sensors.getTempC(deviceAddress);
  Serial.print("Temp C: ");
  Serial.print(tempC);
  Serial.print(" Temp F: ");
  Serial.print(DallasTemperature::toFahrenheit(tempC));
}

// function to print a device's resolution
void printResolution(DeviceAddress deviceAddress)
{
  Serial.print("Resolution: ");
  Serial.print(sensors.getResolution(deviceAddress));
  Serial.println();    
}

// main function to print information about a device
void printData(DeviceAddress deviceAddress)
{
  Serial.print("Device Address: ");
  printAddress(deviceAddress);
  Serial.print(" ");
  printTemperature(deviceAddress);
  Serial.println();
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

void writeEEPROM(int deviceaddress, unsigned int eeaddress, byte data ) 
{
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));   // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.write(data);
  Wire.endTransmission();
 
  delay(5);
}
 
byte readEEPROM(int deviceaddress, unsigned int eeaddress ) 
{
  byte rdata = 0xFF;
 
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));   // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.endTransmission();
 
  Wire.requestFrom(deviceaddress,1);
 
  if (Wire.available()) rdata = Wire.read();
 
  return rdata;
}

void triunghi(int ics, int igrec)
{
tft.fillTriangle(ics+10, igrec+50, ics+30, igrec+10,ics+50, igrec+50,RED);
tft.fillTriangle(ics+17, igrec+45, ics+30, igrec+20,ics+43, igrec+45,YELLOW);
}
