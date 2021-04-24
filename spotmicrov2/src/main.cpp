#include "spotmicro.h"
#include "controllerInput.h"
#include "math.h"

double angle[3];
int xlen = 0, ylen = 0, zlen = 0;

// Timer Variables
int prev = 0, servotimer = 0;

// Remote Controller Setup
int channelValues[4];
Controller_Channel channels[4] = {Controller_Channel(23, 23), Controller_Channel(22, 22), Controller_Channel(21, 21), Controller_Channel(20, 20)};

// global
/* 0 = front right limb
 * 1 = front left limb
 * 2 = back right limb
 * 3 = back left limb
 */
Arm arm[4]{{-1, 1, 0},{-3, 5, 180},{3, 8, 0},{2, 11, 180}};
Wrist wrist[4]{{-2, 3, 180},{1, 4, 0},{7, 7, 180},{-11, 10, 0}};
Shoulder shoulder[4]{{-4, 2, 180},{-5, 6, 0},{4, 9, 0},{0, 13, 180}};

// function prototype declaration 
void servo_movement();

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

  for(int i = 0; i < 4; i++){
    arm[i].mvar_debug();
  }
  for(int i = 0; i < 4; i++){
    wrist[i].mvar_debug();
  }
  for(int i = 0; i < 4; i++){
    shoulder[i].mvar_debug();
  }
}
bool state = true;
void loop() {
  // Remote Controller values
  // testing
  
  if(millis() - prev > 20){    
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

    Serial.print("converted arm: "); Serial.println(arm[0].convertAngle(angle[1]));
    Serial.print("converted wrist: "); Serial.println(wrist[0].convertAngle(angle[2]));
    Serial.print("converted shoulder: "); Serial.println(shoulder[0].convertAngle(angle[0]));

    for(int i = 0; i < 4; i++){
      arm[i].m_target_position = arm[i].convertAngle(angle[1]);
      wrist[i].m_target_position = wrist[i].convertAngle(angle[2]);
      shoulder[i].m_target_position = shoulder[i].convertAngle(angle[0]);
    }

    prev = millis();
    
   //prev = millis();
  }
  if(millis() - servotimer > MOVEMENT_INTERVAL){
    servo_movement();
    servotimer = millis();
  }
}

void servo_movement(){
  int directionOfMovement;
  for(int i = 0; i < 4; i++){
    // -----------------------------------------arm movement--------------------------------------------
    // checks if the current position is close enough to be equal to the target position
    if(fabs(arm[i].m_current_position - arm[i].m_target_position) < arm[i].m_movement_speed){
      arm[i].m_current_position = arm[i].m_target_position;
    }
    // move the servo towards the target angle
    else{
      directionOfMovement = 0;
      directionOfMovement = (arm[i].m_target_position > arm[i].m_current_position) ? 1 : -1;
      directionOfMovement = (arm[i].m_target_position == arm[i].m_current_position) ? 0 : directionOfMovement;
      arm[i].m_current_position += directionOfMovement * arm[i].m_movement_speed;
    }
    arm[i].move_to_angle(arm[i].m_current_position);
    //Serial.println(arm[i].m_current_position);
    // -----------------------------------------wrist movement--------------------------------------------
    // checks if the current position is close enough to be equal to the target position
    if(fabs(wrist[i].m_current_position - wrist[i].m_target_position) < wrist[i].m_movement_speed){
      wrist[i].m_current_position = wrist[i].m_target_position;
    }
    // move the servo towards the target angle
    else{
      directionOfMovement = 0;
      directionOfMovement = (wrist[i].m_target_position > wrist[i].m_current_position) ? 1 : -1;
      directionOfMovement = (wrist[i].m_target_position == wrist[i].m_current_position) ? 0 : directionOfMovement;
      wrist[i].m_current_position += directionOfMovement * wrist[i].m_movement_speed;
    }
    wrist[i].move_to_angle(wrist[i].m_current_position);
    //Serial.println(wrist[i].m_current_position);

    // -----------------------------------------shoulder movement--------------------------------------------
    // checks if the current position is close enough to be equal to the target position
    if(fabs(shoulder[i].m_current_position - shoulder[i].m_target_position) < shoulder[i].m_movement_speed){
      shoulder[i].m_current_position = shoulder[i].m_target_position;
    }
    // move the servo towards the target angle
    else{
      directionOfMovement = 0;
      directionOfMovement = (shoulder[i].m_target_position > shoulder[i].m_current_position) ? 1 : -1;
      directionOfMovement = (shoulder[i].m_target_position == shoulder[i].m_current_position) ? 0 : directionOfMovement;
      shoulder[i].m_current_position += directionOfMovement * shoulder[i].m_movement_speed;
    }
    shoulder[i].move_to_angle(shoulder[i].m_current_position);
    //Serial.println(shoulder[i].m_current_position);
;
    //Serial.println("----------------------------------------------");
  }
}
