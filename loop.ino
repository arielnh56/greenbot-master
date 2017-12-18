void loop() {
  if (stopped && digitalRead(B_START) == LOW) {
    stopped = false;
    sonarLook(LOOK_RIGHT | LOOK_FRONT);
  }
  if (stopped) {
    rpm_l = 0;
    rpm_r = 0;
    checkRovertalk();
    return;
  }
  int maxD = 500;
#ifdef OCTOSONAR
  myOcto.doSonar();  // call every cycle, OctoSonar handles the spacing
  int backD = myOcto.read(5, maxD);
  int frontD = myOcto.read(6, maxD);
  int forwardD = min(myOcto.read(0, maxD), myOcto.read(7, maxD));
#else
  SonarI2C::doSonar();  // call every cycle, SonarI2C handles the spacing
  int backD = constrain(sonars[5].mm(), 0, maxD);
  int frontD = constrain(sonars[6].mm(), 0, maxD);
  int forwardD = min(sonars[0].mm(), sonars[7].mm());
#endif
  int rot = constrain((backD - frontD) / 4, -20, 20);
  int dist = min(backD, frontD);
  int distAdj = (dist < 500) ? constrain((min(backD, frontD) - 150) / 4, -20, 20) : 0;
  int avoid = constrain(200 - forwardD, 0, 50);
  int avoidTimer;
  double mult = 2.0;
  if (!(backD == frontD == maxD)) {
    if (avoid > 0 || avoidTimer > millis()) {
      if (avoid > 0) {
        avoidTimer = millis() + 2000;
      }
      rpm_l = -75;
      rpm_r = 75;
    } else {
      rpm_l = mult * (20 - rot + distAdj);
      rpm_r = mult * (20 + rot - distAdj);
    }
  }
  checkRovertalk();
  char buffer[20];
  if (last_print + 500 < millis()) {
    last_print = millis();
    sprintf(buffer, "0 %5d      %5d 7  ", myOcto.read(0), myOcto.read(7));
    lcd.setCursor(0, 0); lcd.print(buffer);
    sprintf(buffer, "1 %5d      %5d 6", myOcto.read(1), myOcto.read(6));
    lcd.setCursor(0, 1); lcd.print(buffer);
    sprintf(buffer, "2 %5d      %5d 5", myOcto.read(2), myOcto.read(5));
    lcd.setCursor(0, 2); lcd.print(buffer);
    sprintf(buffer, "3 %5d      %5d 4", myOcto.read(3), myOcto.read(4));
    lcd.setCursor(0, 3); lcd.print(buffer);
  }

}

