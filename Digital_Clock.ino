#include "LiquidCrystal.h"

// This defines the LCD wiring to the DIGITALpins
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// initial Time display is 12:59:45 PM
int h=12;
int m=59;
int s=45;
int flag=1; //PM

// Time Set Buttons
int button1;
int button2;

// Pins definition for Time Set Buttons
int hs=0;// pin 0 for Hours Setting
int ms=1;// pin 1 for Minutes Setting

// For accurate Time reading, use Arduino Real Time Clock and not just delay()
static uint32_t last_time, now = 0; // RTC

// the 8 arrays that form each segment of the custom numbers
byte bar1[8] = 
{
        B11100,
        B11110,
        B11110,
        B11110,
        B11110,
        B11110,
        B11110,
        B11100
};
byte bar2[8] =
{
        B00111,
        B01111,
        B01111,
        B01111,
        B01111,
        B01111,
        B01111,
        B00111
};
byte bar3[8] =
{
        B11111,
        B11111,
        B00000,
        B00000,
        B00000,
        B00000,
        B11111,
        B11111
};
byte bar4[8] =
{
        B11110,
        B11100,
        B00000,
        B00000,
        B00000,
        B00000,
        B11000,
        B11100
};
byte bar5[8] =
{
        B01111,
        B00111,
        B00000,
        B00000,
        B00000,
        B00000,
        B00011,
        B00111
};
byte bar6[8] =
{
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B11111,
        B11111
};
byte bar7[8] =
{
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00111,
        B01111
};
byte bar8[8] =
{
        B11111,
        B11111,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000
};


void setup()
{
  lcd.begin(16,2);
  pinMode(hs,INPUT_PULLUP);// avoid external Pullup resistors for Button 1
  pinMode(ms,INPUT_PULLUP);// and Button 2
  now=millis(); // read RTC initial value  
  
    // assignes each segment a write number
  lcd.createChar(1,bar1);
  lcd.createChar(2,bar2);
  lcd.createChar(3,bar3);
  lcd.createChar(4,bar4);
  lcd.createChar(5,bar5);
  lcd.createChar(6,bar6);
  lcd.createChar(7,bar7);
  lcd.createChar(8,bar8);
}

void custom0(int col)
{ // uses segments to build the number 0
  lcd.setCursor(col, 0); 
  lcd.write(2);  
  lcd.write(8); 
  lcd.write(1);
  lcd.setCursor(col, 1); 
  lcd.write(2);  
  lcd.write(6);  
  lcd.write(1);
}

void custom1(int col)
{
  lcd.setCursor(col,0);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
  lcd.setCursor(col,1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
}

void custom2(int col)
{
  lcd.setCursor(col,0);
  lcd.write(5);
  lcd.write(3);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(2);
  lcd.write(6);
  lcd.write(6);
}

void custom3(int col)
{
  lcd.setCursor(col,0);
  lcd.write(5);
  lcd.write(3);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(7);
  lcd.write(6);
  lcd.write(1); 
}

void custom4(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(6);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
}

void custom5(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(3);
  lcd.write(4);
  lcd.setCursor(col, 1);
  lcd.write(7);
  lcd.write(6);
  lcd.write(1);
}

void custom6(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(3);
  lcd.write(4);
  lcd.setCursor(col, 1);
  lcd.write(2);
  lcd.write(6);
  lcd.write(1);
}

void custom7(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(8);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
}

void custom8(int col)
{
  lcd.setCursor(col, 0); 
  lcd.write(2);  
  lcd.write(3); 
  lcd.write(1);
  lcd.setCursor(col, 1); 
  lcd.write(2);  
  lcd.write(6);  
  lcd.write(1);
}

void custom9(int col)
{
  lcd.setCursor(col, 0); 
  lcd.write(2);  
  lcd.write(3); 
  lcd.write(1);
  lcd.setCursor(col, 1); 
  lcd.write(7);  
  lcd.write(6);  
  lcd.write(1);
}

void printNumber(int value, int col) {
  if (value == 0) {
    custom0(col);
  } if (value == 1) {
    custom1(col);
  } if (value == 2) {
    custom2(col);
  } if (value == 3) {
    custom3(col);
  } if (value == 4) {
    custom4(col);
  } if (value == 5) {
    custom5(col);
  } if (value == 6) {
    custom6(col);
  } if (value == 7) {
    custom7(col);
  } if (value == 8) {
    custom8(col);
  } if (value == 9) {
    custom9(col);
  }      
}  

void loop()
{ 
  Serial.begin(9600);
  lcd.begin(16,2);// every second
// Update LCD Display
// Print TIME in Hour, Min, Sec + AM/PM
 /*lcd.setCursor(0,0);
 if(h<10)lcd.print("0");// always 2 digits
 lcd.print(h);
 lcd.print(":");
 if(m<10)lcd.print("0");
 lcd.print(m);
 lcd.print(":");
 if(s<10)lcd.print("0");
 lcd.print(s);*/
  if(h < 10){
    printNumber(h%10, 2);
    Serial.print("h is :");
    Serial.print(h);
    Serial.println();
    Serial.print("h%10 is :");
    Serial.print(h%10);
    Serial.println();
    Serial.print("h/10 is :");
    Serial.print(h/10);
    Serial.println();
  }
  /*else{
    printNumber(h/10, 0);
    printNumber(h%10, 3);
  }
  lcd.setCursor(6, 0);
  lcd.print(".");
  lcd.setCursor(6, 1);
  lcd.print(".");
  printNumber(m/10, 7);
  printNumber(m%10, 10);
 

 if(flag==0) lcd.print(" AM");
 if(flag==1) lcd.print(" PM");
  delay(500);*/
// improved replacement of delay(1000) 
// Much better accuracy, no more dependant of loop execution time

for ( int i=0 ;i<5 ;i++)// make 5 time 200ms loop, for faster Button response
{

  while ((now-last_time)<200) //delay200ms
  { 
    now=millis();
  }
 // inner 200ms loop
 last_time=now; // prepare for next loop 

 // read Setting Buttons
 button1=digitalRead(hs);// Read Buttons
 button2=digitalRead(ms);


 if(button1==0){
  m=0;
  h=h+1;
 }

 if(button2==0){
  s=0;
  m=m+1;

  }

/* ---- manage seconds, minutes, hours am/pm overflow ----*/
 if(s==60){
  s=0;
  m=m+1;
 }
 if(m==60)
 {
  m=0;
  h=h+1;
 }
 if(h==13)
 {
  h=1;
  flag=flag+1;
  if(flag==2)flag=0;
 }


 if((button1==0)|(button2==0))// Update display if time set button pressed
 {
  // Update LCD Display
  // Print TIME in Hour, Min, Sec + AM/PM
  /*lcd.setCursor(0,0);
  if(h<10)lcd.print("0");// always 2 digits
  lcd.print(h);
  lcd.print(":");
  if(m<10)lcd.print("0");
  lcd.print(m);
  lcd.print(":");
  if(s<10)lcd.print("0");
  lcd.print(s);*/
  if(h < 10){
    printNumber(h%10, 2);
    Serial.print("h is :");
    Serial.print(h);
    Serial.println();
    Serial.print("h%10 is :");
    Serial.print(h%10);
    Serial.println();
    Serial.print("h/10 is :");
    Serial.print(h/10);
    Serial.println();
  }
 /* else{
    printNumber(h/10, 0);
    printNumber(h%10, 3);
  }
  lcd.setCursor(6, 0);
  lcd.print(".");
  lcd.setCursor(6, 1);
  lcd.print(".");
  printNumber(m/10, 7);
  printNumber(m%10, 10);

  if(flag==0) lcd.print(" AM");
  if(flag==1) lcd.print(" PM");
    delay(500);*/
 }// end if
 } // end for

// outer 1000ms loop

 s=s+1; //increment sec. counting
    
    
// ---- manage seconds, minutes, hours am/pm overflow ----
 if(s==60){
  s=0;
  m=m+1;
 }
 if(m==60)
 {
  m=0;
  h=h+1;
 }
 if(h==13)
 {
  h=1;
  flag=flag+1;
  if(flag==2)flag=0;
 } 
// Loop end
}


