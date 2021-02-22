/* Mingye Chen 2021-02-21
   to do:
   - inverse kinematic model
   - interpolation
*/
#include "spotmicro.h"
#include "controllerInput.h"
//#include "TeensyThreads.h"
double angle[2];

// Remote Controller Setup
int channelValues[4];
Controller_Channel channels[4] = {Controller_Channel(23,23), Controller_Channel(22,22), Controller_Channel(21,21), Controller_Channel(20,20)};

int prevtime = 0;

void setup() {
  // Remote Controller ISR Setup
  attachInterrupt(channels[0].m_interruptPin, [](){channels[0].channelInput();}, CHANGE);
  attachInterrupt(channels[1].m_interruptPin, [](){channels[1].channelInput();}, CHANGE);
  attachInterrupt(channels[2].m_interruptPin, [](){channels[2].channelInput();}, CHANGE);
  attachInterrupt(channels[3].m_interruptPin, [](){channels[3].channelInput();}, CHANGE);
  
  Serial.begin(115200);
  // Servo initialization
  // f - front | b - back
  // r - right | l - left
  Arm fr_arm(-1, 1, 0);
  Arm fl_arm(-3, 5, 180);
  Arm br_arm(3, 8, 0);
  Arm bl_arm(2, 11, 180);
  Wrist fr_wrist(-2, 3, 180);
  Wrist fl_wrist(1, 4, 0);
  Wrist br_wrist(7, 7, 180);
  Wrist bl_wrist(-11, 10, 0);
  Shoulder fr_shoulder(-4, 2, 180);
  Shoulder fl_shoulder(-5, 6, 0);
  Shoulder br_shoulder(4, 9, 0);
  Shoulder bl_shoulder(0, 12, 180);
}

void loop() {

  if(millis() - prevtime > 5000){
    IK_Model::get_leg_z_angles(150, angle);
    Serial.print("angle 1: "); Serial.println(angle[0]);
    Serial.print("angle 2: "); Serial.println(angle[1]);
    prevtime = millis();
  }

  // Remote Controller values
  for(int i = 0; i < 4; i++){
    channelValues[i] = channels[i].checkValueUpdate();
    if(channelValues[i]){
      Serial.print(channelValues[i]);
      Serial.print("\t");
      if(i == 3) Serial.println(" ");
    }
  }
}
