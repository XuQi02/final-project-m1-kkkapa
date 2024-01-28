

void AutonomousControl() {
  // put your code here to run in Autonomous control mode

  unsigned long myTime;

  Serial.println("in the AutonomousControl function");

  // State machine loop
  while (AutoCurrentState != IDLE) {
    switch (AutoCurrentState) {
      case AUTO_TOWALL:

        //move forward then update sensor
        forward();  
        LaserSensor();
        // Check if the movement duration has passed
        if (distMM < 120) {
          stop();
          lastActionTime = millis();  // Record the time when the forward state started
          spincounter();
          if ((millis() - lastActionTime) > 500) {
            stop();
            AutoCurrentState = AUTO_LINEFOLLOW;
          }
          
        }
        
        break;

      case AUTO_LINEFOLLOW:
        // Add state instructions here
        delay(1000);  // Placeholder delay
        forward();
        linefollowing();
        if (distMM < 150) {
          AutoCurrentState = IDLE;  // Transition to next state
        }
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
