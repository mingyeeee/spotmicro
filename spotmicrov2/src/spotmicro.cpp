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
  /*int z1 = z_length;
  int x1 = x_length;

  // calculate position to account for X axis
  int z2 = sqrt(pow(z1,2), pow(x1,2));
  int armXangle = atan(x1/z1);
  */

  int z2 = z_length;
  // leg angle
  angles[0] = (acos((pow(z2,2) + pow(111.1,2) - pow(118.5,2))/(2*z2*111.1))*180)/PI;
  // wrist angle
  angles[1] = 180 - angles[0]-(acos((pow(z2,2) + pow(118.5,2) - pow(111.1,2))/(2*z2*118.5))*180)/PI;
}
