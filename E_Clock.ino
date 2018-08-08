 /*

 This code requires the following libraries:

   - RTClib https://github.com/adafruit/RTClib
   - DST_RTC https://github.com/andydoro/DST_RTC
   - Adafruit_GFX https://github.com/adafruit/Adafruit-GFX-Library
   - Adafruit_NeoPixel https://github.com/adafruit/Adafruit_NeoPixel
   - Adafruit_NeoMatrix https://github.com/adafruit/Adafruit_NeoMatrix
 
 Functions for Clock
 *  
 *  By: thelonelyprogrammer
 *  YouTube channel: https://www.youtube.com/channel/UCks-9JSnVb22dlqtMgPjrlg/videos


 
   grid pattern

    I T S H I S T H A L F B R T E N
    F L Q U A R T E R S T W E N T Y
    F I V E F E M I N U T E S S T O
    W P A S T C O N E S T H R E E W
    S T W O V F O U R G H E I G H T
    E L E V E N O T E N T I F I V E
    K N I N E R V S E V E N E S I X
    T W E L V E T S O R C L O C K S

*/

// include the library code:
#include <Wire.h>
#include <RTClib.h>
#include <DST_RTC.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

// define pins
#define NEOPIN 6  // connect to DIN on NeoMatrix 8x8 via a resistor
#define RTCGND A2 // use this as  ground 
#define RTCPWR A3 // use this as  power


RTC_DS1307 RTC; // Establish clock object
DST_RTC dst_rtc; // DST object

DateTime theTime; // Holds current clock time



// configure for 8x8 neopixel matrix
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, NEOPIN,
                            NEO_MATRIX_TOP  + NEO_MATRIX_LEFT +
                            NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
                            NEO_GRB         + NEO_KHZ800);
                            

//array to store if LEDs are lit or not
int ledMatrix[8][8] = {
  {1, 1, 1, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
  };

int ledCount = 64;  // the 8x8 grid of the Neomatrix

void setup() {
  // put your setup code here, to run once:


//Serial for debugging
  Serial.begin(9600);
// set pinmodes
  pinMode(NEOPIN, OUTPUT);
// start clock
  Wire.begin();  // Begin I2C
  RTC.begin();   // begin clock
  RTC.adjust(DateTime(__DATE__, __TIME__));
  matrix.begin();
  matrix.setBrightness(100);
  matrix.fillScreen(0); // Initialize all pixels to 'off'
  matrix.show();
}

void loop() {
  // get the time
  theTime = dst_rtc.calculateTime(RTC.now()); 
  // add 2.5 minutes to get better estimates
  theTime = theTime.unixtime() + 150;

  r_its();//write 'it is' everytime:

//Minutes
 
if ((theTime.minute() > 4) && (theTime.minute() < 10)) 
  {
  r_mfive();
  }
  
if ((theTime.minute() > 9) && (theTime.minute() < 15)) 
{
  r_mten();
}

if ((theTime.minute() > 14) && (theTime.minute() < 20)) 
{
  r_quarter();
}

if ((theTime.minute() > 19) && (theTime.minute() < 25)) 
{
 r_mtwenty();
}

if ((theTime.minute() > 24) && (theTime.minute() < 30)) 
{
 r_mtwenty_five();
}

if ((theTime.minute() > 29) && (theTime.minute() < 35)) 
{
 r_mhalf();
}

if ((theTime.minute() > 34) && (theTime.minute() < 40)) 
{
 r_mtwenty_five();
}
 
if ((theTime.minute() > 39) && (theTime.minute() < 45)) 
{
 r_mtwenty();
}

if ((theTime.minute() > 44) && (theTime.minute() < 50)) 
{
 r_quarter();
}
  
if ((theTime.minute() > 49) && (theTime.minute() < 55)) 
{
 r_mten();
}

if (theTime.minute() > 54) 
{
 r_mfive();
}


// Past or two
if ((theTime.minute() < 5)) {  }

else if ((theTime.minute() < 35) && (theTime.minute() > 4))
{
 r_past();  
}
else
{
 r_to();
}
  
// hours
if((theTime.hour() ==  1 ) || (theTime.hour() ==  13 )
{
 r_hone();
}

if((theTime.hour() ==  2 ) || (theTime.hour() ==  14 )
{
 r_htwo();
}

if((theTime.hour() ==  3 ) || (theTime.hour() ==  15 )
{
 r_hthree();
}

if((theTime.hour() ==  4 ) || (theTime.hour() ==  16 )
{
 r_hfour();
}

if((theTime.hour() ==  5 ) || (theTime.hour() ==  17 )
{
 r_hfive();
}

if((theTime.hour() ==  6 ) || (theTime.hour() ==  18 )
{
 r_hsix();
}

if((theTime.hour() ==  7 ) || (theTime.hour() ==  19 )
{
 r_hseven();
}

if((theTime.hour() ==  8 ) || (theTime.hour() ==  20 )
{
 r_height();
}

if((theTime.hour() ==  9 ) || (theTime.hour() ==  21 )
{
 r_hnine();
}


if((theTime.hour() ==  10 ) || (theTime.hour() ==  22 )
{
 r_hten();
}

if((theTime.hour() ==  11 ) || (theTime.hour() ==  23 )
{
 r_heleven();
}


if((theTime.hour() ==  12 ) || (theTime.hour() ==  0 )
{
 r_htwelve();
}

//it's show time....

for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {
      if (ledMatrix[i][j] == 1) {
        matrix.drawPixel(i, j, matrix.Color(255, 255, 0));
      }
      else {
        matrix.drawPixel(i, j, matrix.Color(0, 0, 0));
      }

    }
    Serial.println();
  }

//====================================================


displayTime();
checkArray();
matrix.show();
delay(5000);
resetArray();
}




void checkArray(){
  //print out the array to check it:
  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {
      Serial.print(ledMatrix[i][j]);
      Serial.print(",");
    }
    Serial.println();
  }
  Serial.println();
}


void resetArray(){
  //set all the array values to 0 (off):
  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {
      ledMatrix[i][j] = 0;
    }
  }
  Serial.print("Array reset (All LEDs switched set to off)");
  Serial.println();
  Serial.println();
}

void displayTime() {

  // get time from the RTC
  DateTime theTime = RTC.now();

  // serial print current time
  
  Serial.print(theTime.year(), DEC);
  Serial.print('/');
  Serial.print(theTime.month(), DEC);
  Serial.print('/');
  Serial.print(theTime.day(), DEC);
  Serial.print(' ');
  Serial.print(theTime.hour(), DEC);
  Serial.print(':');
  Serial.print(theTime.minute(), DEC);
  Serial.print(':');
  Serial.print(theTime.second(), DEC);
  Serial.println();
}

/***************** Functions***********************/
void r_its()
{
//write 'it is' everytime:
 ledMatrix[0][0] = 1;
 ledMatrix[0][1] = 1;
 ledMatrix[0][0] = 1;
}
void r_mfive()
{
  ledMatrix[2][0] = 1;
  ledMatrix[2][1] = 1;
  ledMatrix[2][2] = 1;
  ledMatrix[2][3] = 1;
  Serial.print("mfive ");
}

void r_mten()
{
 ledMatrix[0][13] = 1;
 ledMatrix[0][14] = 1;
 ledMatrix[0][15] = 1;
 Serial.print("mten ");
}

void r_quarter()
{
 ledMatrix[1][2] = 1;
 ledMatrix[1][3] = 1;
 ledMatrix[1][4] = 1;
 ledMatrix[1][5] = 1;
 ledMatrix[1][6] = 1;
 ledMatrix[1][7] = 1;
 ledMatrix[1][8] = 1;
 Serial.print("mquarter ");
}

void r_mtwenty ()
{
 ledMatrix[1][10] = 1;
 ledMatrix[1][11] = 1;
 ledMatrix[1][12] = 1;
 ledMatrix[1][13] = 1;
 ledMatrix[1][14] = 1;
 ledMatrix[1][15] = 1;
 Serial.print("mtwenty ");
}
 
void r_mtwenty_five()
{
 ledMatrix[1][10] = 1;
 ledMatrix[1][11] = 1;
 ledMatrix[1][12] = 1;
 ledMatrix[1][13] = 1;
 ledMatrix[1][14] = 1;
 ledMatrix[1][15] = 1;
 ledMatrix[2][0] = 1;
 ledMatrix[2][1] = 1;
 ledMatrix[2][2] = 1;
 ledMatrix[2][3] = 1;
 Serial.print("mtwenty five ");
}

void r_mhalf()
{
 ledMatrix[0][7] = 1;
 ledMatrix[0][8] = 1;
 ledMatrix[0][9] = 1;
 ledMatrix[0][10] = 1;
 Serial.print("mhalf ");
}

void r_hone()
{
 ledMatrix[3][6] = 1;
 ledMatrix[3][7] = 1;
 ledMatrix[3][8] = 1;
 Serial.print("hone ");
}

void r_htwo()
{
 ledMatrix[4][1] = 1;
 ledMatrix[4][2] = 1;
 ledMatrix[4][3] = 1;
 Serial.print("htwo ");
}

void r_hthree()
{
 ledMatrix[3][10] = 1;
 ledMatrix[3][11] = 1;
 ledMatrix[4][12] = 1;
 ledMatrix[3][13] = 1;
 ledMatrix[3][14] = 1;
 Serial.print("hthree ");
}

void r_hfour()
{
 ledMatrix[4][5] = 1;
 ledMatrix[4][6] = 1;
 ledMatrix[4][7] = 1;
 ledMatrix[4][8] = 1;
 Serial.print("hfour ");
}

void r_hfive()
{
 ledMatrix[5][12] = 1;
 ledMatrix[5][13] = 1;
 ledMatrix[5][14] = 1;
 ledMatrix[5][15] = 1;
 Serial.print("hfive ");
}

void r_hsix()
{
 ledMatrix[6][13] = 1;
 ledMatrix[6][14] = 1;
 ledMatrix[6][15] = 1;
 Serial.print("hsix ");
}

void r_hseven()
{
 ledMatrix[6][7] = 1;
 ledMatrix[6][8] = 1;
 ledMatrix[6][9] = 1;
 ledMatrix[6][10] = 1;
 ledMatrix[6][11] = 1;
 Serial.print("hseven ");
}

void r_height()
{
 ledMatrix[4][11] = 1;
 ledMatrix[4][12] = 1;
 ledMatrix[4][13] = 1;
 ledMatrix[4][14] = 1;
 ledMatrix[4][15] = 1;
 Serial.print("height");
}

void r_hnine()
{
 ledMatrix[6][1] = 1;
 ledMatrix[6][2] = 1;
 ledMatrix[6][3] = 1;
 ledMatrix[6][4] = 1;
 Serial.print("hnine ");
}

void r_hten()
{
 ledMatrix[5][7] = 1;
 ledMatrix[5][8] = 1;
 ledMatrix[5][9] = 1;
 Serial.print("hten");
}

void r_heleven()
{
 ledMatrix[5][0] = 1;
 ledMatrix[5][1] = 1;
 ledMatrix[5][2] = 1;
 ledMatrix[5][3] = 1;
 ledMatrix[5][4] = 1; 
 ledMatrix[5][5] = 1;
 Serial.print("heleven ");
}

void r_htwelve()
{
 ledMatrix[7][0] = 1;
 ledMatrix[7][1] = 1;
 ledMatrix[7][2] = 1;
 ledMatrix[7][3] = 1;
 ledMatrix[7][4] = 1; 
 ledMatrix[7][5] = 1;
 Serial.print("htwelve ");
}

void r_past()
{
 ledMatrix[3][1] = 1;
 ledMatrix[3][2] = 1;
 ledMatrix[3][2] = 1;
 ledMatrix[3][3] = 1;
 Serial.print("past");
}

void r_to()
{
 ledMatrix[2][14] = 1;
 ledMatrix[2][15] = 1;
 Serial.print("to ");
}
