void floorCalibration()
{
    /* Place Robot On Floor (no line) */
    delay(2000);
    /* Wait until button is pressed to start robot */
    waitBtnPressed(LP_LEFT_BTN, RED_LED);

    delay(500);

    /* Set both motors direction forward */
    setMotorDirection(BOTH_MOTORS, MOTOR_DIR_FORWARD);
    /* Enable both motors */
    enableMotor(BOTH_MOTORS);
    /* Set both motors speed 10 */
    setMotorSpeed(BOTH_MOTORS, 10);

    /* Must be called prior to using getLinePosition() or readCalLineSensor() */
    calibrateLineSensor(lineColor);

    /* Disable both motors */
    disableMotor(BOTH_MOTORS);


}

void linefollowing()
{

    uint32_t linePos = getLinePosition();

    if ((linePos > 0) && (linePos < 4000)) {    // turn left
        setMotorSpeed(LEFT_MOTOR, normalSpeedforlinefollowing);
        setMotorSpeed(RIGHT_MOTOR, fastSpeedforlinefollowing);
    } else if (linePos > 5000) {                // turn right
        setMotorSpeed(LEFT_MOTOR, fastSpeedforlinefollowing);
        setMotorSpeed(RIGHT_MOTOR, normalSpeedforlinefollowing);
    } else {                                    // go straight
        setMotorSpeed(LEFT_MOTOR, normalSpeedforlinefollowing);
        setMotorSpeed(RIGHT_MOTOR, normalSpeedforlinefollowing);
    }
}
