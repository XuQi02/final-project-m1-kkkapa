uint8_t SensorPos = 1; // sets the sensor pin used


void LaserSensor() {
  //reads the distance as 14bit integer
  distValue = readSharpDist(SensorPos);

  //reads the distance in millimeters
  distMM = readSharpDistMM(SensorPos);

  //reads the distance in inches
  distIN = readSharpDistIN(SensorPos);

  Serial.println(distMM);
}