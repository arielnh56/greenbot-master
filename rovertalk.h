#include <EasyTransferI2C.h>

//EasyTransfer
EasyTransferI2C ETdown;

struct DOWN_DATA_STRUCTURE {
  //put your variable definitions here for the data you want to send
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  double rpm_r;
  double rpm_l;
};

//give a name to the group of data
DOWN_DATA_STRUCTURE downdata;

void setupRovertalk() {
  ETdown.begin(details(downdata), &Wire);
}

unsigned long int last_rover_send = 0;

void checkRovertalk() {
  downdata.rpm_l = rpm_l;
  downdata.rpm_r = rpm_r;
  ETdown.sendData(I2C_ROVER_ADDRESS);
}

