//Copyright (c)2023 Owen Graham - Distribution of this code for free is acceptable without any monetary gain.
//This code tells the driver when the automatic transmission shifts and locks up. It is helpful for diagnosing possible transaxle issues.
//CAUTION: This device works only on cars with the Aisin A140E 4-speed automatic transmission. This includes the 1992-1996 Camry. Toyota OBDI compliant.
//To connect, find the Tt pin on the Toyota DLC, either under the hood or under the dash. Place A0 in this pin socket and ground to E1.
//You MUST have a voltage divider on A0 or else this will blow up the Arduino board. I am not responsible. Arduinos handle up to 5V, and some handle 3.3V.
//I have engineered this to handle a max of 3.3V. Tt's output signal has a maximum of 8VDC.

float R1 = 47000.0;
float R2 = 33000.0;

int firstGear = 2;   // Blue LED, pin 1
int secondGear = 3;  // Green LED, pin 2
int thirdGear = 4;   // Yellow LED, pin 3
int fourthGear = 5;  // Red LED, pin 4, Overdrive

void setup() {
  Serial.begin(9600);
  
  pinMode(firstGear, OUTPUT);
  pinMode(secondGear, OUTPUT);
  pinMode(thirdGear, OUTPUT);
  pinMode(fourthGear, OUTPUT);
}

void loop() {
  float voltValue = analogRead(A0);
  float gearVoltage = voltValue * (8.0 / 1023) * ((R1 + R2) / R2);
  
  Serial.print("Voltage = ");
  Serial.println(gearVoltage);
  Serial.println("------------------");

  delay(1000);
}