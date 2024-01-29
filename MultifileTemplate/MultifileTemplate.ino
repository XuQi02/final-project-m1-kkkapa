/*A multifile project code template
  A template for the Milestone 1 project code that uses multiple files
  for modularity. The compiler first loads the principal file 
  (the one with the same name as the folder) and then loads 
  the others in alphabetical order. Variables defined in an 
  earlier file will be visible to code in a file that is loaded 
  later, but not vice-versa. 

  Calls functions in files:
  MotorFunctions.ino

  written for the MSP432401 board
  Author: Chengyang Ye; Ian Morton; Tom Cai
  Last revised: 1/21/2024

***** Hardware Connections: *****
     start button       P3.0
     playstation connections
     brown wire         P1.7 
     orange wire        P1.6 
     yellow wire        P2.3
     blue wire          P6.7
*/

// Load libraries used
#include "SimpleRSLK.h"
#include <Servo.h>
#include "PS2X_lib.h"
#include <TinyIRremote.h>

// Define pin numbers for the button on the PlayStation controller
#define PS2_DAT 14  //P1.7 <-> brown wire
#define PS2_CMD 15  //P1.6 <-> orange wire
#define PS2_SEL 34  //P2.3 <-> yellow wire (also called attention)
#define PS2_CLK 35  //P6.7 <-> blue wire
#define START_BUTTON 18  //P3.0 a push button on top of the breadboard
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#define IR_RCV_PIN      33
#define IR_LED 6  //P4.3 <-> white wire
IRreceiver irRX(IR_RCV_PIN);
IRData IRresults;
// Create an instance of the playstation controller object
PS2X ps2x;
// Define remote mode either playstation controller or IR remote controller

Servo myservo;

enum AutoState {
  START,
  AUTO_ACTION1,
  AUTO_ACTION2,
  AUTO_ACTION3,
  AUTO_ACTION4,
  AUTO_ACTION5,
  AUTO_ACTION6,
  IDLE
};

AutoState AutoCurrentState = START;

uint16_t distValue; 
uint16_t distMM; 
float distIN;

enum RobotState {
  MANUAL,
  AUTONOMOUS,
  INITIALIZE,
};


RobotState RobotCurrentState = MANUAL;

// Global Variables
unsigned long lastActionTime = 0;  // Variable to store the last time an action was taken
const uint8_t lineColor = LIGHT_LINE;
const uint16_t normalSpeedforlinefollowing = 10;
const uint16_t fastSpeedforlinefollowing = 20;

// Tuning Parameters
const uint16_t slowSpeed = 15;
const uint16_t fastSpeed = 30;
const unsigned long movementDuration = 2000;  // Duration for movement forward autonomously in milliseconds

void setup() {
  Serial.begin(57600);
  Serial.print("Starting up Robot code...... ");
  setupRSLK();
  setupWaitBtn(LP_LEFT_BTN);
  setupLed(RED_LED);
  myservo.attach(SRV_0);
  // attaches the servo on Port 1, pin 5 to the servo object

  // Run setup code

    // using the playstation controller
    Serial.println("Using playstation controller, make sure it is paired first ");

    // Initialize PlayStation controller
    delayMicroseconds(500 * 1000);  //added delay to give wireless ps2 module some time to startup, before configuring it
    // declare variables for playstation control
    bool pressures = false;
    bool rumble = false;
    int error = 1;

    while (error) {
      error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);

      if (error == 0)
        Serial.println("Found Controller, configured successful ");

      else if (error == 1)
        Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

      else if (error == 2)
        Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

      else if (error == 3)
        Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
      delayMicroseconds(1000 * 1000);
    }
    enableRXLEDFeedback(BLUE_LED);
}

void loop() {
  // Read input from PlayStation controller
  ps2x.read_gamepad();

  // Update state machine based on button input
  updateStateMachine();

  // Perform actions based on the current state
  executeStateActions();
}


void updateStateMachine() {
  switch (RobotCurrentState) {
    case INITIALIZE:
      if (digitalRead(START_BUTTON) == 0) {
        Serial.print("start button has been pressed going to manual");
        //go to Manual state when start button pushed
        RobotCurrentState = MANUAL;
      }
      break;

    case MANUAL:
      Serial.print("in manual state........");
      if (ps2x.Button(PSB_SELECT)) {
        // go to Autonomous state when circle button pushed
        RobotCurrentState = AUTONOMOUS;
      }
      break;

    case AUTONOMOUS:
      Serial.print("in autonomous state........");
      if (ps2x.Button(PSB_START)) {
        // go to manual state when square button pushed
        RobotCurrentState = MANUAL;
        // reset autonomous state to start state for the next time
        AutoCurrentState = START; 
      }
      break;
  }
}

void executeStateActions() {
  switch (RobotCurrentState) {
    case INITIALIZE:
      // Perform actions for the initialize state
      Serial.println("Initializing...");
      // Add any additional actions for the initialize state
      break;

    case AUTONOMOUS:
      // Perform actions for the autonomous state
      Serial.println("Autonomous Mode");
      AutonomousControl();
      // Add any additional actions for the autonomous state
      break;

    case MANUAL:
      // Perform actions for the manual state
      Serial.println("Manual Mode");
      
      RemoteControl();
      // Add any additional actions for the manual state
      break;
  }
}





