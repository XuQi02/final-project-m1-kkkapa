#include "PS2X_lib.h"  // Include PS2 Controller Library
#include "SimpleRSLK.h" // Include RSLK library
#include <Servo.h>

// Define PS2 Controller Pins
#define PS2_DAT        14  // P1.7 <-> brown wire
#define PS2_CMD        15  // P1.6 <-> orange wire
#define PS2_SEL        34  // P2.3 <-> yellow wire (also called attention)
#define PS2_CLK        35  // P6.7 <-> blue wire
#define PS2X_DEBUG
#define PS2X_COM_DEBUG


// Define controller mode variables
#define pressures   false
#define rumble      false

// Create PS2 Controller Class instance
PS2X ps2x;
Servo myservo;
// Define error and type variables
int error = 0;
byte type = 0;
byte vibrate = 0;

void setup() {
  // Initialize Serial communication
  Serial.begin(57600);
  
  // Give time for the controller to be ready
  delayMicroseconds(500 * 1000);

  // Initialize the gamepad (check for error)
  error = 1;
  while(error) {
    error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);

    if(error == 0) {
      Serial.println("Found Controller, configured successfully");
      // ... additional successful setup messages ...
    } else {
      // Handle different types of errors
      // ... error handling messages ...
    }

    // Delay before trying again
    delayMicroseconds(1000 * 1000);
  }

  // Determine the type of controller
  type = ps2x.readType();

  // Initialize the RSLK library
  setupRSLK();


  // Enable both motors, setting their initial direction and speed
  enableMotor(BOTH_MOTORS);
  setMotorDirection(BOTH_MOTORS, MOTOR_DIR_FORWARD);
  setMotorSpeed(BOTH_MOTORS, 0); // Start with motors stopped

  // Additional RSLK-specific setup, if necessary
  myservo.attach(SRV_0);  // attaches the servo on Port 1, pin 5 to the servo object
}


void loop() {
  // Make sure we have a valid connection to the controller
  if(error == 1) {
    return; // Skip loop if no controller found
  }

  if(ps2x.Button(PSB_PAD_UP)) {
    myservo.write(140); // Open the gripper when PSB_R1 is pressed
  } else {
    myservo.write(40); // Close the gripper when PSB_R1 is not pressed
  }

  // Read the controller state
  ps2x.read_gamepad(false, vibrate);

  // Get the X and Y positions of the left joystick
  int joyX = ps2x.Analog(PSS_LX);
  int joyY = ps2x.Analog(PSS_LY);

  // Map the joystick values to motor speed ranges
  int motorSpeedY = map(joyY, 0, 255, 100, -100);
  int motorSpeedX = map(joyX, 0, 255, 100, -100);

  // Initialize motor speeds
  int leftMotorSpeed, rightMotorSpeed;

  // Determine motor speeds and directions based on joystick position
  if(abs(motorSpeedX) > abs(motorSpeedY)) { // Spin or turn
    if(motorSpeedX > 0) { // Turn right
      rightMotorSpeed = motorSpeedX;
      leftMotorSpeed = motorSpeedX / 2; // Right motor goes at half speed for a smooth turn
    } else { // Turn left
      leftMotorSpeed = -motorSpeedX;
      rightMotorSpeed = -motorSpeedX / 2; // Left motor goes at half speed for a smooth turn
    }
  } else { // Forward or reverse
    leftMotorSpeed = rightMotorSpeed = motorSpeedY;
  }
  if(ps2x.Button(PSB_PAD_LEFT)) { // Spin counterclockwise
    leftMotorSpeed = -100;
    rightMotorSpeed = 100;
  } else if(ps2x.Button(PSB_PAD_RIGHT)) { // Spin clockwise
    leftMotorSpeed = 100;
    rightMotorSpeed = -100;
  }

  setMotorSpeed(LEFT_MOTOR, abs(leftMotorSpeed));
  setMotorDirection(LEFT_MOTOR, leftMotorSpeed >= 0 ? MOTOR_DIR_FORWARD : MOTOR_DIR_BACKWARD);
  setMotorSpeed(RIGHT_MOTOR, abs(rightMotorSpeed));
  setMotorDirection(RIGHT_MOTOR, rightMotorSpeed >= 0 ? MOTOR_DIR_FORWARD : MOTOR_DIR_BACKWARD);
}


