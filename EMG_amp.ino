#include <Servo.h>
Servo myservo1;
Servo myservo2;
Servo myservo3;
 
const int interval = 100;  // 取樣間隔時間
unsigned int sample1;   
unsigned int amplitude1;  // 訊號振幅
unsigned int sample2;   
unsigned int amplitude2;
unsigned int sample3;   
unsigned int amplitude3;


int servoAngle1=0;
int lastServoAngle1=0;
int servoAngle2=0;
int lastServoAngle2=0;
int servoAngle3=0;
int lastServoAngle3=0;

void setup() {
  Serial.begin(9600);
  analogReference(EXTERNAL);

  myservo1.attach(9,700,2300);
  myservo2.attach(10,700,2300);
  myservo3.attach(11,700,2300);
  
  myservo1.write(servoAngle1);
  myservo2.write(servoAngle2);
  myservo3.write(servoAngle3);
}

void loop() {
  unsigned int sigMax1 = 0;  // 最高峰值
  unsigned int sigMin1 = 1000;  // 最低峰值
  unsigned int sigMax2 = 0;
  unsigned int sigMin2 = 1000;
  unsigned int sigMax3 = 0;
  unsigned int sigMin3 = 1000;
  unsigned long now = millis(); // 當前時間

  while (millis() < now + interval) {
    sample1 = analogRead(A0);
    
    if (sample1 < sigMin1) {
      sigMin1 = sample1;
    } else if (sample1 > sigMax1) {
      sigMax1 = sample1;
    }

    sample2 = analogRead(A1);
    if (sample2 < sigMin2) {
      sigMin2 = sample2;
    } else if (sample2 > sigMax2) {
      sigMax2 = sample2;
    }

    sample3 = analogRead(A3);
    if (sample3 < sigMin3) {
      sigMin3 = sample3;
    } else if (sample3 > sigMax3) {
      sigMax3 = sample3;
    }

    //Serial.println(sample3);
    //Serial.print(",");
  }
  
  // 求取訊號振幅
  amplitude1 = sigMax1 - sigMin1;
  amplitude2 = sigMax2 - sigMin2;
  amplitude3 = sigMax3 - sigMin3;

  servoAngle1 = map(amplitude1,0,60,180,0);
  servoAngle2 = map(amplitude2,0,120,160,30);
  servoAngle3 = map(amplitude3,20,250,100,180);

  if(abs(lastServoAngle1-servoAngle1)>10)
    myservo1.write(servoAngle1);
    
  if(abs(lastServoAngle2-servoAngle2)>10)
    myservo2.write(servoAngle2);
    
  if(abs(lastServoAngle3-servoAngle3)>10)
    myservo3.write(servoAngle3);
 
  lastServoAngle1 = servoAngle1;
  lastServoAngle2 = servoAngle2;
  lastServoAngle3 = servoAngle3;

  Serial.print(amplitude1);
  Serial.print(",");
  Serial.print(amplitude2);
  Serial.print(",");
  Serial.println(amplitude3);
}
