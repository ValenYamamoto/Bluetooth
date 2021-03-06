// ****************************************** Import libraries
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <Servo.h>
#include <Adafruit_MotorShield.h>
#include <Wire.h>

// ******************************************* Serial port Bluetooth
SoftwareSerial Genotronex(5, 6); // RX, TX
String inputString = "";
int angle;
int speed;

// ******************************************* Motors and Servos
Adafruit_MotorShield motorShield;
Adafruit_DCMotor *motor;
Servo servo;
const int motorPort = 1;
const int servoPort = 9;

void setup() {
  // put your setup code here, to run once:
  // ***************************************** Intializing Serial Comms
  Genotronex.begin(9600);
  Serial.begin(9600);
  
  // **************************************** Initializing motors and servos
  motorShield = Adafruit_MotorShield();
  servo.attach(servoPort);
  motor = motorShield.getMotor(motorPort);
  motorShield.begin();
  
  // **************************************** Intializing Variables
  angle = 0;
  speed = 0;
  inputString.reserve(200);
}

void loop() {  
  // put your main code here, to run repeatedly:

 getParams();

 setMotorPower(speed, angle);
 setServoAngle(angle);


   
  
}

void getParams() {
  // **************************************** calls parseCommand when all chars are in
  while (Genotronex.available()) {
    char inChar = (char)Genotronex.read();

    if (inChar == '\n') {
      parseCommand();
      inputString = "";
    } else {
      inputString += inChar;

    }
  }
}

void parseCommand() {
  // **************************************** Reading strings from Serial Comms
  StaticJsonBuffer<100> commandBuffer;
  JsonObject& command = commandBuffer.parseObject(inputString);
  String cmd = command["cmd"];

  if (cmd == "some_command_1") {
    // perform some actions as a result of receive some_command_1
  } else if (cmd == "some_command_2") {
    // perform some actions as a result of receive some_command_2
  } else if (cmd == "seek_bar_command") {
     // get seek bar value
     int value = command["params"]["value"];
     // actions ...
  } else if (cmd == "256") {
     speed = command["params"]["speed"];
     angle = command["params"]["angle"];
  }
}

void setServoAngle(int angle) {
  // **************************************** Set Servo Angle
//  angle = constrain(angle, 0, 180);
  angle = getAngle();
  if (speed < 15 && angle == 0) {
    angle = 90;
  }
   servo.write(angle);
}

int getAngle() {
  if(angle > 180) {
    angle = 360 - angle;
  }
  return angle;
}

void setMotorPower(int power, int angle) {
  // **************************************** Set Motor Speed
  if (angle > 180) {
    motor->run(BACKWARD); 
  } else {
    motor->run(FORWARD);
  }
//  power = constrain(power, -255, 255);
  motor->setSpeed(power);
}

void printParams() {
  // **************************************** Print parameters in Serial comms
  Serial.print(speed);
  Serial.print("  ");
  Serial.println(angle);
}
