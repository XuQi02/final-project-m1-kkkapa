

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
        turnright();
        delay(1500);
        AutoCurrentState = AUTO_ACTION3;
       
        break;

      case AUTO_ACTION3:
        Serial.println("in Autonomous mode the current state: AUTO_ACTION3");
        // Add state instructions here
        
        forward();
         if (millis() - lastActionTime >= movementDuration2) {
          stop(); //stop the forward movement
          AutoCurrentState = AUTO_ACTION4;  // Transition to next state
          lastActionTime = millis();  // Record the time when the next state started
        }
        break;

      case AUTO_ACTION4:
        Serial.println("in Autonomous mode the current state: AUTO_ACTION4");
        // Add state instructions here
        linefollowing();
         if (millis() - lastActionTime >= movementDuration) {
          stop(); //stop the forward movement
          AutoCurrentState = AUTO_ACTION5;  // Transition to next state
          lastActionTime = millis();  // Record the time when the next state started
        }
        break;


      case AUTO_ACTION5:
        Serial.println("in Autonomous mode the current state: AUTO_ACTION6");
        
        myservo.write(40);
        delay(1000);
        AutoCurrentState = IDLE;
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
