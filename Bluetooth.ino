#include <SoftwareSerial.h>// import the serial library
#include <ArduinoJson.h>
#include <Servo.h>
#include <Adafruit_MotorShield.h>

// ******************************************* Serial port Bluetooth
SoftwareSerial Genotronex(10, 11); // RX, TX
String inputString = "";
int angle;
int speed;

// ******************************************* Motors and Servos
Adafruit_MotorShield motorShield;
Adafruit_DCMotor *motor;
const int motorPort = 1;
const int servoPort = 9;

void setup() {
  // put your setup code here, to run once:
  Genotronex.begin(9600);
  Serial.begin(9600);
  angle = 0;
  speed = 0;
  inputString.reserve(200);
}

void loop() {
  // put your main code here, to run repeatedly:
 getParams();
 printParams();
}
void getParams() {
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
void setServoAngle() {
  if(angle >=180) {
    angle = abs(180-angle);
  }
   
}
void printParams() {
  Serial.print(speed);
  Serial.print("  ");
  Serial.println(angle);
}
