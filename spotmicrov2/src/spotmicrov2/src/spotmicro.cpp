/*
  spotmicro.cpp - Library for coordinating SpotMicro's servo movements.
  Created by Mingye C 2021-02-10.
*/
#include "Arduino.h"
#include "spotmicro.h"
#include "math.h"

Limb::Limb (int angle_offset, int pin, int cw_max) : m_initial_offset(angle_offset), m_pin(pin), m_cw_limit(cw_max) 
{
  m_center_position = 90 + m_initial_offset;
  // Set starting configuration
  m_current_position = m_center_position;

  m_servo.attach(m_pin);

  Serial.print("center position: ");
  Serial.print(m_center_position);
  Serial.print(" angle offset: ");
  Serial.print(m_initial_offset);
  Serial.print(" pin: ");
  Serial.print(m_pin);
  Serial.print(" cw limit: ");
  Serial.print(m_cw_limit);
}
void Limb::move_to_angle(float angle){
  int ms_angle = int(angle * ANGLE_TO_MS);
  m_servo.writeMicroseconds(ms_angle);
}

Arm::Arm (int angle_offset, int pin, int cw_max) : Limb(angle_offset, pin, cw_max)
{
  Serial.print("Arm - current position: ");
  Serial.print(m_current_position);
}


Wrist::Wrist (int angle_offset, int pin, int cw_max) : Limb(angle_offset, pin, cw_max)
{
  Serial.print("Wrist - current position: ");
  Serial.print(m_current_position);
}

Shoulder::Shoulder (int angle_offset, int pin, int cw_max) : Limb(angle_offset, pin, cw_max)
{
  Serial.print("Shoulder - current position: ");
  Serial.print(m_current_position);
}

// angle - Arm, Wrist, Shoulder angle values in that order
void IK_Model::calcAngles(int z_length, int y_length, int x_length, double * angles)
{
  //tilt 
  float hipOffset = y_length+HIP_LENGTH;
  float hipAngleWithY1 = atan((hipOffset)/z_length);
  float hipHyp = hipOffset/sin(hipAngleWithY1);

  float hipAngleWithY2 = acos(HIP_LENGTH/hipHyp);
  //hip angle
  angles[0] = ((hipAngleWithY2+hipAngleWithY1)*180)/PI;
  //length of leg with tilt
  float z2 = HIP_LENGTH*tan(hipAngleWithY2);

  //new angle for foot position
  double legAngleWithX = atan(x_length/z2)*180;
  double legAngleWithXDeg = (legAngleWithX*180)/PI;
  //length of leg with x
  double z3 = z2/cos(legAngleWithX);

  // leg angle
  angles[1] = (acos((pow(z3,2) + pow(111.1,2) - pow(118.5,2))/(2*z3*111.1)-atan(x_length/z3))*180)/M_PI;
  // wrist angle
  angles[2] = (acos((pow(111.1,2) + pow(118.5,2) - pow(z3,2))/(2*111.1*118.5))*180)/M_PI;

  
}
