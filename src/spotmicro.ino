/* Mingye Chen 2021-02-09
 * to do:
 * - inverse kinematic model
 * - interpolation
 */
#include "spotmicro.h"

void setup() {
  Serial.begin(115200);
  // Servo initialization
  // f - front | b - back
  // r - right | l - left
  Arm fr_arm(-1,1);
  Arm fl_arm(-3,5);
  Arm br_arm(3,8);
  Arm bl_arm(2,11);
  Wrist fr_wrist(-2,3);
  Wrist fl_wrist(1,4);
  Wrist br_wrist(7,7);
  Wrist bl_wrist(-11,10);
  Shoulder fr_shoulder(-4,2);
  Shoulder fl_shoulder(-5,6);
  Shoulder br_shoulder(4,9);
  Shoulder bl_shoulder(0,12);
}

void loop() {
  // put your main code here, to run repeatedly:

}
