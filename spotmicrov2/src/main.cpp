#include "spotmicro.h"
#include "controllerInput.h"

double angle[3];
int xlen = 0, ylen = 0, zlen = 0;

int prev=0;

// Remote Controller Setup
int channelValues[4];
Controller_Channel channels[4] = {Controller_Channel(23, 23), Controller_Channel(22, 22), Controller_Channel(21, 21), Controller_Channel(20, 20)};

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
  Serial.println("Serial initialized");

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
  Shoulder fl_shoulder(-4, 2, 180);
  Shoulder fr_shoulder(-5, 6, 0);
  Shoulder bl_shoulder(4, 9, 0);
  Shoulder br_shoulder(0, 13, 180);
}

void loop() {

  // Remote Controller values
  
  if(millis() - prev > 100){
    channelValues[0] = channels[0].checkValueUpdate();
    channelValues[2] = channels[2].checkValueUpdate();
    channelValues[1] = channels[1].checkValueUpdate();
      
    xlen = map(channelValues[0], 1000, 2000, -20, 20);
    ylen = map(channelValues[2], 1000, 2000, -20, 20);
    zlen = map(channelValues[1], 1000, 2000, 20, 200);

    IK_Model::calcAngles(zlen, ylen, xlen, angle);
    Serial.print("x: "); Serial.println(xlen);
    Serial.print("y: "); Serial.println(ylen);
    Serial.print("z: "); Serial.println(zlen);
    Serial.print("angle 0: "); Serial.println(angle[0]);
    Serial.print("angle 1: "); Serial.println(angle[1]);
    Serial.print("angle 2: "); Serial.println(angle[2]);
    prev = millis();
  }
}
