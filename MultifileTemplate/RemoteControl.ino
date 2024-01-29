
///srewfwef/


void RemoteControl() {

 // Read input from PlayStation controller
  ps2x.read_gamepad();

  // Operate the robot in remote control mode
  RemoteControlPlaystation();
}


void RemoteControlPlaystation() {
 if (ps2x.Button(PSB_PAD_UP)) {
      Serial.println("PAD UP button pushed ");
      forward();
    } else if (ps2x.Button(PSB_CROSS)) {
      Serial.println("CROSS button pushed");
      stop();
    } else if (ps2x.Button(PSB_PAD_DOWN)){
      Serial.println("PAD DOWN button pushed ");
      backward();
    } else if (ps2x.Button(PSB_PAD_LEFT)){
      Serial.println("PAD LEFT button pushed");
      turnleft();
    } else if (ps2x.Button(PSB_PAD_RIGHT)){
      Serial.println("PAD RIGHT button pushed");
      turnright();
    } else if (ps2x.Button(PSB_SQUARE)){
      Serial.println("SQUARE button pushed");
      spincounter();
    } else if (ps2x.Button(PSB_CIRCLE)){
      Serial.println("CIRCLE button pushed");
      spinclock();
    } else if (ps2x.Button(PSB_TRIANGLE)){
      Serial.println("TRIANGLE button pushed");
      myservo.write(130);
    }  else if (ps2x.Button(PSB_R1)){
      Serial.println("R1 button pushed");
      myservo.write(40);
    }  
}

