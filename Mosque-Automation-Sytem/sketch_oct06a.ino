#include<Servo.h>
#include<Wire.h>
Servo doorMotor;
Servo sprayMotor;
Servo waterMotor;

int water = 0;

int doorSensor = 22;
int tempSensor = A15;

int tempRed = 31;
int tempGreen = 32;

int sonarRed = 30;
int sonarGreen = 29;


int triggerPin = 27 ;
int echoPin = 26;

int check = 0;
int second;
 int minute;
  int hour;

int buzzer = 25;
void setup() {

  Serial.begin(9600);
  doorMotor.attach(23);
  sprayMotor.attach(24);
  waterMotor.attach(28);
  
  pinMode(doorSensor, INPUT);
  pinMode(tempRed, OUTPUT);
  pinMode(tempGreen, OUTPUT);
  
  pinMode(echoPin, INPUT);
  pinMode(triggerPin, OUTPUT);

  
  pinMode(sonarGreen, OUTPUT);
  pinMode(sonarRed, OUTPUT);
   pinMode(buzzer, OUTPUT);
  Wire.begin();

}

void loop() {

  digitalWrite(triggerPin, LOW);

  int checkSensor = digitalRead(doorSensor);


  if (checkSensor == 0 && check == 1) {

    check = 0;
    int doorOpen = 0;
    for (doorOpen = 0; doorOpen <= 90; doorOpen++) {

      Serial.print("door = ");

      Serial.println(doorOpen);
      doorMotor.write(doorOpen);

    }
    int sprayOpen = 0;
    for (sprayOpen = 0; sprayOpen <= 90; sprayOpen++) {

      Serial.print("spray = ");

      Serial.println(sprayOpen);
      sprayMotor.write(sprayOpen);

    }
  }
  if (checkSensor == 1 && check == 0) {

    check = 1;
    int doorOpen = 0;
    for (doorOpen = 90; doorOpen >= 0; doorOpen--) {

      Serial.print("door = ");

      Serial.println(doorOpen);

      doorMotor.write(doorOpen);

    }
    int sprayOpen = 90;
    for (sprayOpen = 90; sprayOpen >= 0; sprayOpen--) {

      Serial.print("spray = ");

      Serial.println(sprayOpen);

      sprayMotor.write(sprayOpen);

    }
  }


  //Temp

  int value = analogRead(tempSensor);
  float currentTemp = ((value / 1024.0) * 5 * 1000) / 10;

  if (currentTemp <= 18) {

    digitalWrite(tempGreen , LOW);
    digitalWrite(tempRed , HIGH);
  }

  if (currentTemp >= 26) {

    digitalWrite(tempGreen , HIGH );
    digitalWrite(tempRed , LOW);
  }

  digitalWrite(triggerPin,HIGH);
  delay(10);
  digitalWrite(triggerPin,LOW);

  float distance = ((((pulseIn(echoPin,HIGH)*0.034)/2)-6)/1092)*100;
        Serial.println(distance);

  if(distance>=50){
    
    digitalWrite(sonarGreen , HIGH);
    digitalWrite(sonarRed ,  LOW);


    
    for (water = 0; water <= 90; water++) {


      waterMotor.write(water);

    }
    
  }

  if(distance < 3.0 ){
    
    digitalWrite(sonarGreen , LOW);
    digitalWrite(sonarRed ,  HIGH); 


  




      waterMotor.write(0);


    
  }


}
