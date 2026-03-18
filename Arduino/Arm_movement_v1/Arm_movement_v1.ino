#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

'''
Trying to move the servo from 0 degree to 90 degree using the adafruit controller
but it only does pwm
'''

// define the structure i.e.the dictionary / template.
struct ServoConfig {
  const char* name; // The "Key" (e.g., "base", "claw")
  const int pin;    // The hardware pin
  const int minPW;  // Minimum Pulse Width
  const int maxPW;  // Maximum Pulse Width
};

Adafruit_PWMServoDriver board1 = Adafruit_PWMServoDriver(0x40);

const ServoConfig myServos[] = {
  {"body",  0,  500,  2400},  //{motor 1 min, motor 1 max , motor 2 min, motor 2 max}
  {"armL",  1,  600,  2200},
  {"armR",  2,  750,  2000},
  {"leg",   3,  500,  2500}
};

void printServoDictionary() {
  Serial.println("--- Servo Configuration ---");
  Serial.println("Name\t\tPin\t\tMin\t\tMax"); // Header with tabs
  
  for (int i = 0; i < sizeof(myServos) / sizeof(myServos[0]); i++) {
    Serial.print(myServos[i].name);
    Serial.print("\t\t"); // Tab for spacing
    Serial.print(myServos[i].pin);
    Serial.print("\t\t");
    Serial.print(myServos[i].minPW);
    Serial.print("\t\t");
    Serial.println(myServos[i].maxPW);
  }
  Serial.println("---------------------------");
}

void moveServo(ServoConfig myServos, int startAngle, int stopAngle) {
  int minP = myServos.minPW;
  int maxP = myServos.maxPW;

  // Map the angle (0-180) to the pulse range (min-max)
  // map(value, fromLow, fromHigh, toLow, toHigh)
  int startPulse = map(startAngle, 0, 180, minP, maxP);
  int stopPulse = map(stopAngle, 0, 180, minP, maxP);

// Function to move a servo slowly to a specific angle (0-180)
  if (startPulse < endPulse) {
    for (int pulse = startPulse; pulse <= endPulse; pulse++) {
      pwm.setPWM(myServos.pin, 0, pulse);
      delay(1000); // Lower speedDelay = faster movement
    }
  } else {
    for (int pulse = startPulse; pulse >= endPulse; pulse--) {
      pwm.setPWM(myServos.pin, 0, pulse);
      delay(1000);
    }
  }

  //board1.setPWM(myServos.pin, 0, pulse);
  //board1.writeMicroseconds(myServos.pin ,pulse);
}

void setup() {
  Serial.begin(9600); // for future printing errors and stuff
  printServoDictionary();

  board1.begin();
  board1.setOscillatorFrequency(27000000); // sets the internal clock frequency to 27 MHz
  board1.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

}

void loop() {
  printServoDictionary();

  moveServo(myServos[0], 90);
  delay(1000);
  Serial.println(board1.getPWM(myServos[0].pin));

  moveServo(myServos[0], 0);
  delay(1000);
  Serial.println(board1.getPWM(myServos[0].pin));
}
