#define OCTOSONAR
#ifdef OCTOSONAR
#include "OctoSonar.h"
#define SONAR_ADDR 0x38
#define SONAR_INT 2
#define ACTIVE_SONARS 0x00FF
OctoSonar myOcto(SONAR_ADDR);
#else // SonarI2C
#include "SonarI2C.h"
SonarI2C sonars[] = {
  SonarI2C (I2C_SONAR_ADDRESS, 0, 4000),
  SonarI2C (I2C_SONAR_ADDRESS, 1, 4000),
  SonarI2C (I2C_SONAR_ADDRESS, 2, 4000),
  SonarI2C (I2C_SONAR_ADDRESS, 3, 4000),
  SonarI2C (I2C_SONAR_ADDRESS, 4, 4000),
  SonarI2C (I2C_SONAR_ADDRESS, 5, 4000),
  SonarI2C (I2C_SONAR_ADDRESS, 6, 4000),
  SonarI2C (I2C_SONAR_ADDRESS, 7, 4000)
};
#endif

/* sonar placements on build

        0   7
       1|---|6
        | ^ |
        | ^ |
       2|---|5
        3   4
*/
// use bitmap to grab sensors. sometimes.
#define S_FRONT 1
#define S_SIDE 2
#define S_RIGHT 4

uint8_t sonarMap[8] = { 3, // 0 !front, !side, !right = back left
                        0, // 1  front, !side, !right = front left
                        2, // 2 !front,  side, !right = back left side
                        1, // 3  front,  side, !right = front left side
                        4, // 4 !front, !side,  right = back right
                        7, // 5  front, !side,  right = front right
                        5, // 6 !front,  side,  right = back right side
                        6  // 7  front,  side,  right = front right side
                      };
uint8_t numsonars = 8;

// Look directions
#define LOOK_RIGHT 1
#define LOOK_LEFT  2
#define LOOK_FRONT 4
#define LOOK_BACK  8

void setupSonar() {
#ifdef OCTOSONAR
  myOcto.begin(SONAR_INT, ACTIVE_SONARS);   // initialize bus, pins etc
#else
  SonarI2C::begin();   // initialize bus, pins etc
  for (uint8_t i = 0; i < numsonars; i++) {
    sonars[i].init();
    sonars[i].enable(false);
  }
#endif
}

void sonarLook(uint8_t mask) {
#ifdef OCTOSONAR
  for (uint8_t i = 0; i < numsonars; i++) {
    boolean look = false;
    if ((mask & LOOK_RIGHT)    &&  (i & S_SIDE) &&  (i & S_RIGHT))  look = true;
    if ((mask & LOOK_LEFT)     &&  (i & S_SIDE) && !(i & S_RIGHT))  look = true;
    if ((mask & LOOK_FRONT)    && !(i & S_SIDE) &&  (i & S_FRONT))  look = true;
    if ((mask & LOOK_BACK)     && !(i & S_SIDE) && !(i & S_FRONT))  look = true;
    if (look) {
      myOcto.active |= (1 << sonarMap[i]);
    } else {
      myOcto.active &= ~(1 << sonarMap[i]);
    }
  }
#else
  for (uint8_t i = 0; i < numsonars; i++) {
    boolean look = false;
    if ((mask & LOOK_RIGHT)    &&  (i & S_SIDE) &&  (i & S_RIGHT))  look = true;
    if ((mask & LOOK_LEFT)     &&  (i & S_SIDE) && !(i & S_RIGHT))  look = true;
    if ((mask & LOOK_FRONT)    && !(i & S_SIDE) &&  (i & S_FRONT))  look = true;
    if ((mask & LOOK_BACK)     && !(i & S_SIDE) && !(i & S_FRONT))  look = true;
    sonars[sonarMap[i]].enable(look);
  }
#endif
}

