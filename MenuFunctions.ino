void MainMenu()
{
  motor.stop_all();
  LCD.clear(); LCD.home();
  LCD.print("Entering Main Menu");
  delay(500);
  LCD.clear();
  int menuIndex = countMainMenu - knob(6) * (countMainMenu) / 1024 - 1;
  int topIndex;
  if (menuIndex < countMainMenu - 1) {
    topIndex = menuIndex;
  } else {
    topIndex = menuIndex - 1;
  }
  int cursorPosition = menuIndex - topIndex;
  LCD.print(mainMenuNames[topIndex]); LCD.setCursor(0, 1); LCD.print(mainMenuNames[topIndex + 1]);
  LCD.setCursor(0, cursorPosition);
  LCD.cursor();
  while (true)
  {
    menuIndex = countMainMenu - knob(6) * (countMainMenu) / 1024 - 1;
    if (cursorPosition != menuIndex - topIndex)
    {
      LCD.clear();
      if (menuIndex > topIndex + 1) {
        topIndex++;
      }
      if (menuIndex < topIndex) {
        topIndex--;
      }
      cursorPosition = menuIndex - topIndex;
      LCD.print(mainMenuNames[topIndex]); LCD.setCursor(0, 1); LCD.print(mainMenuNames[topIndex + 1]);
      LCD.setCursor(0, cursorPosition);
    }
    delay(100);
    if (startbutton())
    {
      delay(100);
      if (startbutton()) {
        LCD.noCursor();
        (*menuFunctions[menuIndex])();
        LCD.clear();
        LCD.print(mainMenuNames[topIndex]); LCD.setCursor(0, 1); LCD.print(mainMenuNames[topIndex + 1]);
        LCD.setCursor(0, cursorPosition);
        LCD.cursor();
      }
    }
    if (stopbutton())
    {
      delay(100);
      if (stopbutton())
      {
        LCD.clear(); LCD.home(); LCD.noCursor();
        LCD.print("Leaving menu");
        delay(500);
        return;
      }
    }
  }
}

void Menu()
{
  LCD.clear(); LCD.home();
  LCD.print("Entering menu");
  delay(500);

  while (true)
  {
    /* Show MenuItem value and knob value */
    int menuIndex = knob(6) * (MenuItem::MenuItemCount) / 1024;
    LCD.clear(); LCD.home();
    LCD.print(menuItems[menuIndex].Name); LCD.print(" "); LCD.print(menuItems[menuIndex].Value);
    LCD.setCursor(0, 1);
    LCD.print("Set to "); LCD.print(knob(7) / divisors[menuIndex]); LCD.print("?");
    delay(100);

    /* Press start button to save the new value */
    if (startbutton())
    {
      delay(200);
      if (startbutton())
      {
        menuItems[menuIndex].Value = knob(7) / divisors[menuIndex];
        menuItems[menuIndex].Save();
        delay(250);
      }
    }

    /* Press stop button to exit menu */
    if (stopbutton())
    {
      delay(100);
      if (stopbutton())
      {
        LCD.clear(); LCD.home();
        LCD.print("Leaving menu");
        g = menuItems[0].Value;
        kp = menuItems[1].Value;
        kd = menuItems[2].Value;
        vel = menuItems[3].Value;
        intGain = menuItems[4].Value;
        delay(500);

        return;
      }
    }
  }
}

void ViewDigital()
{
  LCD.clear(); LCD.print("Viewing Digital");
  delay(500);
  LCD.clear();
  while (true)
  {
    int index = knob(6) * 3 / 1024;
    if (index == 0)
    {
      LCD.print("D0:"); LCD.print(digitalRead(0)); LCD.print(" D1:"); LCD.print(digitalRead(1)); LCD.print(" D2:"); LCD.print(digitalRead(2));
      LCD.setCursor(0, 1);
      LCD.print("D3:"); LCD.print(digitalRead(3)); LCD.print(" D4:"); LCD.print(digitalRead(4)); LCD.print(" D5:"); LCD.print(digitalRead(5));


    } else if (index == 1)
    {
      LCD.print("D6:"); LCD.print(digitalRead(6)); LCD.print(" D7:"); LCD.print(digitalRead(7)); LCD.print(" D8:"); LCD.print(digitalRead(8));
      LCD.setCursor(0, 1);
      LCD.print("D9:"); LCD.print(digitalRead(9)); LCD.print(" D0:"); LCD.print(digitalRead(10)); LCD.print(" D1:"); LCD.print(digitalRead(11));
    } else if (index == 2)
    {
      LCD.print("D2:"); LCD.print(digitalRead(12)); LCD.print(" D3:"); LCD.print(digitalRead(13)); LCD.print(" D4:"); LCD.print(digitalRead(14));
      LCD.setCursor(0, 1);
      LCD.print("D5:"); LCD.print(digitalRead(15));
    }

    delay(100);
    LCD.clear();
    if (stopbutton())
    {
      LCD.clear(); LCD.home();
      LCD.print("Leaving menu");
      delay(500);
      return;
    }
  }
}

void jettPace(){
  LCD.clear();
  LCD.setCursor(0,0);
  LCD.print("JETT PACE!!");
  int lengthOfSilence = 150;
  int l = 450;
  int s = 150;
  int sequence[34] = {s,l,l,l,0,0,s,0,0,l,0,0,l,0,0,0,0,s,l,l,s,0,0,s,l,0,0,l,s,l,s,0,0,s};

  for(int i = 0; i < 34; i++){
    motor.speed(BUZZER_PIN,MAX_MOTOR_SPEED*2/3);
    delay(sequence[i]);
    motor.stop_all();
    delay(lengthOfSilence);
  }

}

void ViewAnalog()
{
  LCD.clear(); LCD.print("Viewing Analog");
  delay(500);
  LCD.clear();
  while (true)
  {
    int index = knob(6) * 2 / 1024;
    if (index == 0)
    {
      LCD.print("BL:"); LCD.print(analogRead(leftIR)); LCD.setCursor(8, 0); LCD.print("BR:"); LCD.print(analogRead(rightIR));
      LCD.setCursor(0, 1);
      LCD.print("k6:"); LCD.print(analogRead(6)); LCD.setCursor(8, 1); LCD.print("k7:"); LCD.print(analogRead(7));
    } else if (index == 1)
    {
      LCD.print("TB:"); LCD.print(analogRead(topIRBack)); LCD.setCursor(8, 0); LCD.print("AF:"); LCD.print(analogRead(ArmIRpin));
      LCD.setCursor(0, 1);
      LCD.print("TL:"); LCD.print(analogRead(topIRLeft)); LCD.setCursor(8, 1); LCD.print("TR:"); LCD.print(analogRead(topIRRight)) ;
    }

    delay(100);
    LCD.clear();
    if (stopbutton())
    {
      LCD.clear(); LCD.home();
      LCD.print("Leaving menu");
      delay(500);
      return;
    }
  }
}

void ControlArm()
{
  int armAngle = armHome;
  int clawAngle = 0;
  int spd = 0;
  int count = 0;
  LCD.clear(); LCD.print("Controlling Arm");
  delay(500);
  LCD.clear();
  LCD.print("Press Start to begin");
  while (true) {
    if (startbutton()) {
      break;
    }
  }
  while (true) {
    clawAngle = (int)(knob(7) * 110.0 / 1024.0);
    armAngle = (int)(knob(6) * 200.0 / 1024.0);
    spd =  -255 + (int)(knob(6) * 512.0 / 1024.0);

    RCServo0.write(clawAngle);

    if (!startbutton() && !stopbutton()) {
      motor.speed(GM7, 0);
      RCServo1.write((int)(armAngle));
    }

    else if (stopbutton()) {
      motor.speed(GM7, spd);
    }

    if (count == 2000) {
      count = 0;
      LCD.clear();
      LCD.print("Claw: "); LCD.print(clawAngle);
      LCD.setCursor(0, 1);
      LCD.print("Arm: "); LCD.print(armAngle); LCD.print(" Spd: "); LCD.print(spd);
    }


    if (stopbutton() && !startbutton())
    {
      RCServo0.write(clawOpen);
      RCServo1.write(armHome);
      LCD.clear(); LCD.home();
      LCD.print("Leaving Arm Control");
      delay(50);
      return;
    }
    count++;
  }
}

void PickupPassengerMain(){
  LCD.clear(); LCD.print("Press start");
  LCD.setCursor(0,1); LCD.print("Pickup on Right");
  delay(500);
    
  while(true){
    if(startbutton()){
      break;
    }
    delay(50);
  }
  PickupPassenger(-1);
  
  LCD.clear(); LCD.print("Press start");
  LCD.setCursor(0,1); LCD.print("Pickup on Left");
  delay(500);
    
  while(true){
    if(startbutton()){
      break;
    }
    delay(50);
  }
  PickupPassenger(1);
}

void altMotor(void){
  int altCount = 0;
  int motorSpeed = 0;
  while(true){
    altCount++;
    for(int i = 0; i < 100; i++){
      motorSpeed = knob(6)*255.0/1024.0;
      motor.speed(LEFT_MOTOR, motorSpeed);
      motor.speed(RIGHT_MOTOR, motorSpeed);
      LCD.clear(); LCD.print("Speed: "); LCD.print(motorSpeed);
      LCD.setCursor(0,1); LCD.print("L: "); LCD.print(leftCount); LCD.print(" R: "); LCD.print(rightCount);
      delay(50);
    }
  }
}

