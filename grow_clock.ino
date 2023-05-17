/*
 * Grow Clock 
 * James A Ware 
 * MAY-22
 * 
 */
 
#include "Wire.h"
#include "millisDelay.h"
#include "Servo.h"
#define DS3231_I2C_ADDRESS 0x68

//screen includes
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int BLED=11;
const int GLED=10;
const int RLED=6;
int ledMode = 0;
millisDelay ledDelay;

const int BUTTON=2;
boolean lastButton = LOW;
boolean currentButton = LOW;


int servo_pin = 9; //D9 on NANO board
Servo myservo;
int angle = 0;  


//RTC timer 
const long interval = 1000;  
unsigned long previousMillis = 0; 

// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val){
  return( (val/10*16) + (val%10) );
}

// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val){
  return( (val/16*10) + (val%16) );
}

void setup(){
  Serial.begin(115200);
  //screen init
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);

  //led init
  pinMode (BLED, OUTPUT);
  pinMode (GLED, OUTPUT);
  pinMode (RLED, OUTPUT);
  pinMode (BUTTON, INPUT); 
  
  Wire.begin();
  Serial.begin(9600);
//  ledDelay.start(10000);  // delay that holds the lights on 
//  ledintDelay.start(10000);  // delay that cycles through the colors

//servo init
{ 
  myservo.attach(servo_pin);
} 
  // set the time | seconds, minutes, hours, day, date, month, year
  setDS3231time(25,36,21,6,6,5,22);
}

  boolean debounce(boolean last){
    boolean current = digitalRead(BUTTON);
    if(last != current){
      delay(5);
      current = digitalRead(BUTTON);
    }
    return current;
  }

void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte
dayOfMonth, byte month, byte year){
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

void readDS3231time(byte *second,
byte *minute,
byte *hour,
byte *dayOfWeek,
byte *dayOfMonth,
byte *month,
byte *year){
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

void displayTime(){
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  // retrieve data from DS3231
  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month,
  &year);
  // send it to the serial monitor
  Serial.print(hour, DEC);
  // convert the byte variable to a decimal number when displayed
  Serial.print(":");
  if (minute<10){
    Serial.print("0");
  }
  Serial.print(minute, DEC);
  Serial.print(":");
  if (second<10){
    Serial.print("0");
  }
  Serial.print(second, DEC);
  Serial.print(" ");
  Serial.print(dayOfMonth, DEC);
  Serial.print("/");
  Serial.print(month, DEC);
  Serial.print("/");
  Serial.print(year, DEC);
  Serial.print(" Day of week: ");
  switch(dayOfWeek){
  case 1:
    Serial.println("Sunday");
    break;
  case 2:
    Serial.println("Monday");
    break;
  case 3:
    Serial.println("Tuesday");
    break;
  case 4:
    Serial.println("Wednesday");
    break;
  case 5:
    Serial.println("Thursday");
    break;
  case 6:
    Serial.println("Friday");
    break;
  case 7:
    Serial.println("Saturday");
    break;
  }
}

void displayTimeOLED(){
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  // retrieve data from DS3231
  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month,
  &year);
  // send it to the OLED
  display.setTextSize(3);
  display.setCursor(15,10);
  display.print(hour, DEC);

  display.setTextSize(3);
  display.setCursor(45,10);
  display.print(":");

  display.setTextSize(3);
  display.setCursor(60,10);
  display.print(minute, DEC);

  switch(dayOfWeek){
  case 1:
    display.setTextSize(2);
    display.setCursor(15,40);
    display.print("Sunday");
    break;
  case 2:
    display.setTextSize(2);
    display.setCursor(15,40);
    display.print("Monday");
    break;
  case 3:
    display.setTextSize(2);
    display.setCursor(15,40);
    display.print("Tuesday");
    break;
  case 4:
    display.print("Wednesday");
    break;
  case 5:
    display.setTextSize(2);
    display.setCursor(15,40);
    display.print("Thursday");
    break;
  case 6:
    display.setTextSize(2);
    display.setCursor(15,40);
    display.print("Friday");
    break;
  case 7:
    display.setTextSize(2);
    display.setCursor(15,40);
    display.print("Saturday");
    break;
  }

  display.display(); 
  
 }

void moveTehArm(){
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  // retrieve data from DS3231
  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
  if(hour > 7 && hour < 20) {
      myservo.write(0);
      Serial.println(hour);
      Serial.println("Sun up");
 
  } else {
    myservo.write(180);
    Serial.println(hour);
    Serial.println("Sun down");
  }
}

void setMode(int mode){
  if (mode == 1){
    digitalWrite(RLED, 64);
    digitalWrite(GLED, LOW);
    digitalWrite(BLED, LOW);
  }
  else if (mode == 2){
    digitalWrite(RLED, LOW);
    digitalWrite(GLED, 64);
    digitalWrite(BLED, LOW);
  }
  else if (mode == 3){
    digitalWrite(RLED, LOW);
    digitalWrite(GLED, LOW);
    digitalWrite(BLED, 64);
  }
  else if (mode ==4){
    digitalWrite(RLED, 32);
    digitalWrite(GLED, 0);
    digitalWrite(BLED, 32);
  }
  else if (mode == 5){
    digitalWrite(RLED, 0);
    digitalWrite(GLED, 32);
    digitalWrite(BLED, 32);
  }
  else if (mode ==6){
    digitalWrite(RLED, 32);
    digitalWrite(GLED, 32);
    digitalWrite(BLED, 0);
  }
  else{
    digitalWrite(RLED, 16);
    digitalWrite(GLED, 32);
    digitalWrite(BLED, 16);
  }
}

void checkTurnOnLed() { // the led task
  // check if delay has timed out
  if (ledDelay.isRunning()) { // only returns TRUE once.
    ledMode++;
    if (ledMode ==7) ledMode = 0;
    setMode(ledMode);
    Serial.println("Turned LED Off");
  }
}

void checkTurnOffLed() { // the led task
  // check if delay has timed out
  if (ledDelay.justFinished()) { // only returns TRUE once.
    digitalWrite(RLED, LOW);
    digitalWrite(GLED, LOW);
    digitalWrite(BLED, LOW);
    Serial.println("Turned LED Off");
  }
}

void loop(){
  
  displayTimeOLED();
  display.clearDisplay();
//  display.setTextSize(1);
//  display.setCursor(0,10);
//  display.print("The Time Today is");
//  display.display(); 
  unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      displayTime(); 
      moveTehArm();
      checkTurnOffLed();
//      displayTimeOLED();

    }
  currentButton = debounce(lastButton);
  if(lastButton == LOW && currentButton == HIGH) {
    ledDelay.start(360000);
    Serial.println("button pushed");
    checkTurnOnLed();
    }
  }
