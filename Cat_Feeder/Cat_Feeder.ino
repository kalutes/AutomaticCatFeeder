#include <DS3231.h>
#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);

DS3231 Clock;
bool h12;
bool PM;

int forward = 6;
int backward = 9;
int button = 13;

int dispenses;
int minute;
int lfMinute;
int lfHour;

void setup() 
{
  lcd.begin(16,2);
  Wire.begin();
  pinMode(button, INPUT);
  pinMode(forward, OUTPUT);
  pinMode(backward, OUTPUT);
}

void loop()
{
  if(minute != Clock.getMinute())
  {
    lcd.clear();
  }
  int hour = Clock.getHour(h12, PM);
  minute = Clock.getMinute();
  int second = Clock.getSecond();
  if(digitalRead(button) == HIGH)
  {
    feed(1);
  }
  else if(minute == 0 && second == 0 && (hour%2)==0)
  {
    feed(1);
  }
  else
  {
    printHome();
  }
}

void feed(int i)
{
  dispenses++;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Dispensing...");
  lfMinute = Clock.getMinute();
  lfHour = Clock.getHour(h12, PM);
  for(int x = 0; x < i; x++)
  {
    /* HERE IS THE ACTUAL FEED CODE CHANGE THIS TO CHANGE HOW MUCH IT DISPENSES */
    analogWrite(forward, 255); //set the forward direction to full speed (255)
    delay(1500);//run forward for 1.5 sec
    analogWrite(forward, 0); //set the forward direction to 0 speed
    analogWrite(backward, 150);//set the backward direction to around half speed
    delay(750);//run backward for .75 sec
    analogWrite(backward, 0);//set the backward direction to 0 speed
  }
  lcd.clear();
}

void printHome()
{
  lcd.noDisplay();
  lcd.display();
  lcd.setCursor(0,0);
  lcd.print(Clock.getHour(h12,PM));
  lcd.print(":");
  int minutep = Clock.getMinute();
  if(minutep < 10)
  {
    lcd.print("0");
  }
  lcd.print(minutep);
  lcd.print("   LF:");
  lcd.print(lfHour);
  lcd.print(":");
  if(lfMinute < 10)
  {
    lcd.print("0");
  }
  lcd.print(lfMinute);
  lcd.setCursor(0,1);
  lcd.print("Dispenses:");
  lcd.print(dispenses);
}
