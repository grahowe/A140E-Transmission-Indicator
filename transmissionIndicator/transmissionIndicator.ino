//Copyright (c)2023 Owen Graham - Distribution of this code for free is acceptable without any monetary gain.
//This code tells the driver when the automatic transmission shifts and locks up. It is helpful for diagnosing possible transaxle issues.
//CAUTION: This device works only on cars with the Aisin A140E 4-speed automatic transmission. This includes the 1992-1996 Camry. Toyota OBDI compliant.
//To connect, find the Tt pin on the Toyota DLC, either under the hood or under the dash. Place A0 in this pin socket and ground to E1.
//You MUST have a voltage divider on A0 or else this will blow up the Arduino board. I am not responsible. Arduinos handle up to 5V, and some handle 3.3V.
//I have engineered this to handle a max of 3.3V. Tt's output signal has a maximum of 8VDC.

#include <U8g2lib.h>
#include <Wire.h>

typedef U8G2_SSD1306_128X64_NONAME_F_SW_I2C oledScr; // This renames U8G2... to SeeedDisplay (Thanks C++!)

oledScr oled(U8G2_R0, SCL, SDA, U8X8_PIN_NONE);
//Define voltage divider resistor values
float R1 = 47000.0;
float R2 = 33000.0;
//This should convert 8VDC to 3.3VDC - perfect for any Arduino board

//Pin definitions for transmission
int firstGear = 2; //Blue LED, pin 1
int secondGear = 3; //Green LED, pin 2
int thirdGear = 4; //Yellow LED, pin 3
int fourthGear = 5; //Red LED, pin 4, Overdrive

void setup() {
  Serial.begin(9600); //When connected to a terminal output, this gives the voltage. Refer to the TurboNinjas manual p. AX1-47
  // put your setup code here, to run once:
  oled.begin();
  Serial.print("Diagnostics Started\n");
  pinMode(firstGear, OUTPUT);
  pinMode(secondGear, OUTPUT);
  pinMode(thirdGear, OUTPUT);
  pinMode(fourthGear, OUTPUT);
  oled.setFont(u8g2_font_freedoomr10_mu);
  oled.drawStr(40, 14, "TOYOTA");
  oled.sendBuffer();
  oled.drawStr(44, 28, "A140E");
  oled.sendBuffer();
  oled.drawStr(28, 42, "TRANSAXLE");
  oled.sendBuffer();
  oled.drawStr(36, 60, "(C)2023");
  oled.sendBuffer();
  delay(3000);
  oled.clearBuffer();
  oled.drawStr(14, 14, "TRANSMISSION");
  oled.drawStr(20, 30, "DIAGNOSTICS");
  oled.drawStr(12,60, "INITIALIZING...");
  oled.sendBuffer();
  delay(3000);
}

void loop(){
  driveTrainComputer();
}

void driveTrainComputer(){
  oled.clearBuffer();
  oled.setFont(u8g2_font_freedoomr10_mu);
  oled.drawStr(14, 64, "GEAR POSITION");
  oled.setFont(u8g2_font_timB24_tf);
  //Transmission function
  float voltValue = analogRead(A0);
  float gearVoltage = voltValue * (5.0/1023)*((R1 + R2)/R2); 
  //The value is 5.0 since this is the maximum value we can handle. 
  //Our out voltage is around 3.3V maximum after resistance division
  Serial.print("Voltage = ");
  Serial.println(gearVoltage);

  if(gearVoltage <= 1.5){ //1st Gear position
    digitalWrite(firstGear, HIGH);
    digitalWrite(secondGear, LOW);
    digitalWrite(thirdGear, LOW);
    digitalWrite(fourthGear, LOW);
    oled.drawStr(60, 32, "1");
    oled.sendBuffer();
    delay(25);
  }

  if(gearVoltage > 1.5 && gearVoltage < 2.6){ //2nd Gear shifting position
    digitalWrite(firstGear, HIGH);
    digitalWrite(secondGear, HIGH);
    digitalWrite(thirdGear, LOW);
    digitalWrite(fourthGear, LOW);
    oled.drawStr(20, 32, "SHIFT");
    oled.sendBuffer();
    delay(25);
  }

  if(gearVoltage > 2.5 && gearVoltage < 3.6){ //2nd Gear lock-up
    digitalWrite(firstGear, LOW);
    digitalWrite(secondGear, HIGH);
    digitalWrite(thirdGear, LOW);
    digitalWrite(fourthGear, LOW);
    oled.drawStr(60, 32, "2");
    oled.sendBuffer();
    delay(25);
  }

  if(gearVoltage > 3.5 && gearVoltage < 4.6){ //3rd gear shifting position
    digitalWrite(firstGear, LOW);
    digitalWrite(secondGear, HIGH);
    digitalWrite(thirdGear, HIGH);
    digitalWrite(fourthGear, LOW);
    oled.drawStr(20, 32, "SHIFT");
    oled.sendBuffer();
    delay(25);
  }

  if(gearVoltage > 4.5 && gearVoltage < 5.6){ //3rd gear lock-up
    digitalWrite(firstGear, LOW);
    digitalWrite(secondGear, LOW);
    digitalWrite(thirdGear, HIGH);
    digitalWrite(fourthGear, LOW);
    oled.drawStr(60, 32, "3");
    oled.sendBuffer();
    delay(25);
  }

  if(gearVoltage > 5.5 && gearVoltage < 6.6){ //OD shifting position
    digitalWrite(firstGear, LOW);
    digitalWrite(secondGear, LOW);
    digitalWrite(thirdGear, HIGH);
    digitalWrite(fourthGear, HIGH);
    oled.drawStr(20, 32, "SHIFT");
    oled.sendBuffer();
    delay(25);
  }

  if(gearVoltage > 6.5){ //OD lock-up
    digitalWrite(firstGear, LOW);
    digitalWrite(secondGear, LOW);
    digitalWrite(thirdGear, LOW);
    digitalWrite(fourthGear, HIGH);
    oled.drawStr(60, 32, "O/D");
    oled.sendBuffer();
    delay(25);
  }
}