#include <Wire.h>

//define i2c addresses
#define I2C_MASTER_ADDRESS 9
#define I2C_ROVER_ADDRESS 10
#define I2C_LCD_ADDRESS 0x27
#define I2C_SONAR_ADDRESS 0x20

// safety
volatile boolean stopped = true;
// desired rpm
double rpm_l = 0;
double rpm_r = 0;

// lcd debug
uint32_t last_print = 0;

