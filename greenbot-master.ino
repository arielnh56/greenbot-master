/*
   master code for green bot
*/

#include "setup.h"
#include "rovertalk.h"
#include "sonar.h"
#include "control.h"

void setup() {
  Wire.begin(I2C_MASTER_ADDRESS);
  setupControl();
  setupSonar();
  setupRovertalk();
}


