int CheckForPassenger() { 
  leftIRVal = analogRead(leftIR);
  rightIRVal = analogRead(rightIR);
  // Check left side
  if (leftIRVal > leftIRValMax) {
    leftIRValMax = leftIRVal;
  } else if (leftIRVal < leftIRValMax - 10 && leftIRValMax > sideIRMin) {
    // Stop motors, reset maxima and pick up passenger
    motor.stop_all();
    leftIRValMax = -1;
    rightIRValMax = -1;
    return LEFT;
  }
  // Check right side
  if (rightIRVal > rightIRValMax) {
    rightIRValMax = rightIRVal;
  } else if (rightIRVal < rightIRValMax - 10 && rightIRValMax > sideIRMin) {
    // Stop motors, reset maxima and pick up passenger
    leftIRValMax = -1;
    rightIRValMax = -1;
    motor.stop_all();
    return RIGHT;
  }
  return 0;
}

int PickupPassenger(int side) { // side=-1 if on left, side=1 if on right
  int range = 80;
  int tripThresh = 800;
  int armDelay = 15;
  int maxIR = -1;
  int newIR = -1;
  int finalI = range - 1;
  side = side*-1;

  RCServo0.write(clawHome);
  RCServo1.write(armHome);

  LCD.clear(); LCD.print("Picking Up");

  // Position Arm
  for (int i = 0; i <= range; i++) {
    RCServo1.write(armHome + i * side);
    delay(armDelay);
    newIR = analogRead(ArmIRpin);
    if (newIR > maxIR) {
      maxIR = newIR;
    } else if (newIR < maxIR - 20 && maxIR > 300) {
      LCD.clear();
      LCD.print("Found Max"); LCD.setCursor(0,1);LCD.print(maxIR);
      delay(300);
      finalI = i;
      break;
    }
    LCD.clear(); LCD.print("IR:  "); LCD.print(newIR);
    LCD.setCursor(0, 1); LCD.print("Max: "); LCD.print(maxIR);
  }

  LCD.clear(); LCD.print("Closing Claw");
  // Position Claw
  motor.speed(2, 150);
  for (int i = 0; i < 2000; i++) { // Will need to change this
    if (!digitalRead(clawTrip)) {
      break;
    }
    delay(1);
  }
  motor.speed(2, 0);

  // Close Claw
  RCServo0.write(clawClose);
  delay(1000);

  // Retract Claw
  motor.speed(2, -150);
  delay(400);
  // Home Arm
  for (int i = 0; i <= finalI; i++) {
    RCServo1.write(armHome + (finalI - i)*side);
    delay(armDelay);
  }

  if (1600 - range * armDelay > 0) {
    delay(1600 - range * armDelay);
  }
  motor.speed(2, 0);

  // Home Claw
  //RCServo0.write(clawHome);
  //delay(1000);
  return 1;
}