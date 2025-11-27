
#include <Wire.h>

#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver board1 = Adafruit_PWMServoDriver(0x40);
// Adafruit_PWMServoDriver board2 = Adafruit_PWMServoDriver(0x41);

// Depending on your servo make, the pulse width min and max may vary
#define SERVOMIN  125 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  575 // this is the 'maximum' pulse length count (out of 4096)

void setup() {
  Serial.begin(9600);
  Serial.println("32 channel Servo test!");

  board1.begin();
  // board2.begin();  
  board1.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  // board2.setPWMFreq(60);
  //yield();
}

void loop() {

    for( int angle =0; angle<181; angle +=10){
      for(int i=0; i<16; i++)
        {      
            // board2.setPWM(i, 0, angleToPulse(angle) );
            board1.setPWM(i, 0, angleToPulse(angle) );
        }
    }
// PCA9865 16 channel Servo control
  delay(100);
}

int angleToPulse(int ang){
   int pulse = map(ang,0, 180, SERVOMIN,SERVOMAX);// map angle of 0 to 180 to Servo min and Servo max 
   Serial.print("Angle: ");Serial.print(ang);
   Serial.print(" pulse: ");Serial.println(pulse);
   return pulse;
}
