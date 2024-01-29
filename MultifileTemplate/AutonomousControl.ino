

void AutonomousControl() {
  // put your code here to run in Autonomous control mode

  unsigned long myTime;

Serial.println("in the AutonomousControl function");

  // State machine loop
  while (AutoCurrentState != IDLE) {
    switch (AutoCurrentState) {
      case START:
        Serial.println("in Autonomous mode the current state: START");
        // Add START state instructions here
        AutoCurrentState = AUTO_ACTION1;  // Transition to next state
        lastActionTime = millis();  // Record the time when the forward state started
        break;

      case AUTO_ACTION1:
        Serial.println("in Autonomous mode the current state: AUTO_ACTION1");
        //move forward for a time, then stop, and transition to the next state
        forward();  
        // Check if the movement duration has passed
        if (millis() - lastActionTime >= movementDuration) {
          stop(); //stop the forward movement
          AutoCurrentState = AUTO_ACTION2;  // Transition to next state
          lastActionTime = millis();  // Record the time when the next state started
        }
        break;

      case AUTO_ACTION2:
        Serial.println("in Autonomous mode the current state: AUTO_ACTION2");
        // Add state instructions here
        
        if (distMM < 30) {
          stop();
        } else {
          forward();
        }
        delay(1000);  // Placeholder delay
        AutoCurrentState = AUTO_ACTION3;  // Transition to next state
        break;

      case AUTO_ACTION3:
        Serial.println("in Autonomous mode the current state: AUTO_ACTION3");
        // Add state instructions here
         if (millis() - lastActionTime >= movementDuration) {
          spinclock();
        delay(1000);  // Placeholder delay
        AutoCurrentState = AUTO_ACTION4;  // Transition to next state
        break;

      case AUTO_ACTION4:
        Serial.println("in Autonomous mode the current state: AUTO_ACTION4");
        // Add state instructions here
        stop();
        delay(1000);
        floorCalibration();
        delay(1000);  // Placeholder delay
        AutoCurrentState = AUTO_ACTION5;  // Transition to next state
        break;



      case AUTO_ACTION5:
        Serial.println("in Autonomous mode the current state: AUTO_ACTION5");
        linefollowing();
        delay(1000);
        AutoCurrentState = AUTO_ACTION6;
        break;

      case AUTO_ACTION6:
        Serial.println("in Autonomous mode the current state: AUTO_ACTION6");
         if (distMM < 200) {
          stop();
         }
         delay(1000);
         myservo.write(40);
         AutoCurrentState = AUTO_ACTION6;
         break; 

      default:
        // Handle unknown state, if needed
        break;
    }
  }
  // The code will exit the while loop when IDLE state is reached
  Serial.println("State: IDLE");
  // Add IDLE state instructions here

}
