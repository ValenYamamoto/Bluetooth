#include <SoftwareSerial.h>// import the serial library
#include <ArduinoJson.h>

SoftwareSerial Genotronex(10, 11); // RX, TX
String inputString = "";

void setup() {
  // put your setup code here, to run once:
  Genotronex.begin(9600);
  Serial.begin(9600);
  inputString.reserve(200);
}

void loop() {
  // put your main code here, to run repeatedly:
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

  // buffer for command
  StaticJsonBuffer<100> commandBuffer;

  // pointer to Json command object
  JsonObject& command = commandBuffer.parseObject(inputString);
  
  // get "cmd" value
  String cmd = command["cmd"];
  
  // depend on received command
  // perform actions
  if (cmd == "some_command_1") {
    // perform some actions as a result of receive some_command_1
  } else if (cmd == "some_command_2") {
    // perform some actions as a result of receive some_command_2
  } else if (cmd == "seek_bar_command") {
     // get seek bar value
     int value = command["params"]["value"];
     // actions ...
  } else if (cmd == "256") {
     int speed = command["params"]["speed"];
     int angle = command["params"]["angle"];
     Serial.print(speed);
     Serial.print("  ");
     Serial.println(angle);
  }

  // "some_command_1","some_command_2", "seek_bar_command" and "joystick_command" - strings that set
  //  in the field "command" during add widget in app.
}

