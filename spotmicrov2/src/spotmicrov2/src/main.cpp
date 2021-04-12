#include "spotmicro.h"
#include "controllerInput.h"
//#include "TeensyThreads.h"
double angle[3];

// Remote Controller Setup
int channelValues[4];
Controller_Channel channels[4] = {Controller_Channel(23, 23), Controller_Channel(22, 22), Controller_Channel(21, 21), Controller_Channel(20, 20)};

// Servo global initialization
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

void setup() {
  // Remote Controller ISR Setup
  attachInterrupt(channels[0].m_interruptPin, []() {
    channels[0].channelInput();
  }, CHANGE);
  attachInterrupt(channels[1].m_interruptPin, []() {
    channels[1].channelInput();
  }, CHANGE);
  attachInterrupt(channels[2].m_interruptPin, []() {
    channels[2].channelInput();
  }, CHANGE);
  attachInterrupt(channels[3].m_interruptPin, []() {
    channels[3].channelInput();
  }, CHANGE);

  Serial.begin(115200);
  br_arm.move_to_angle(br_arm.m_center_position);
  br_wrist.move_to_angle(br_wrist.m_center_position);
}

void loop() {

  // Remote Controller values
  /*
    for (int i = 0; i < 4; i++) {
    channelValues[i] = channels[i].checkValueUpdate();
    if(channelValues[i]){
      Serial.print(channelValues[i]);
      Serial.print("\t");
      if(i == 3) Serial.println(" ");
      }
    }*/
  for(int i = 0; i < 100; i++){
    br_wrist.move_to_angle(120.5 - i*0.25);
    delay(5);
  }
  for(int i = 0; i < 100; i++){
    br_wrist.move_to_angle(95.75 + i*0.25);
    delay(5);
  }

  
}