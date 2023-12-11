#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#define sensorDigital A0
#define relay 8
#define buzzer 7
#define sensorAnalog A0

LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial GSM(3, 2);
Servo s1;
char phone_no[]="91+8669022407";

int data = 0;

int Red = 6;
int Green = 7;

void setup() {
  s1.attach(9);
  randomSeed(analogRead(0));
  pinMode(sensorDigital, INPUT);

    pinMode(relay, OUTPUT);

      pinMode(buzzer, OUTPUT);
            
  GSM.begin(9600);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  
   data=analogRead(sensorDigital);
  
  lcd.print(" Gas Leakage Detector");
  Serial.println("Init...");
  initModule("AT","OK",1000);
  delay(3000);
  lcd.clear();
}

void loop() {
bool digital = digitalRead(sensorDigital);

            int analog = analogRead(sensorAnalog);
            
             if (digital == 0) 
             {

    lcd.setCursor(0, 0);
    lcd.print("Gas Level Normal");

      digitalWrite(relay, LOW);

       digitalWrite(buzzer, HIGH);

        delay(5000);

        digitalWrite(buzzer, LOW);

            } 
    else {
           
    lcd.setCursor(0, 0);
    lcd.print("Gas Level high");
    lcd.setCursor(0, 1);

    callUp(phone_no);
   
    lcd.print(" Calling..");
    delay(1000);
            lcd.clear();
                digitalWrite(relay, HIGH);
                    digitalWrite(buzzer, LOW);
  
       }
  lcd.clear();
}

void callUp(char *number){
  GSM.print("ATD+"); GSM.print(number); GSM.println(";");
  delay(15000);
  GSM.println("ATH");
  delay(100);
}

void initModule(String cmd,char* res,int t){
  while(1){
    Serial.println(cmd);
    GSM.println(cmd);
    delay(1000);
    while(GSM.available()>0){
      if(GSM.find(res)){
        Serial.println((res));
        delay(t);
        return;
      }
      else{
        Serial.println("Error");
      }
    }
    delay(t);
      }
}