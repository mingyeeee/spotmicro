/*
  Morse.h - Library for coordinating SpotMicro's servo movements.
  Created by Mingye C 2021-02-10.
*/
#include "Arduino.h"
#include "spotmicro.h"

Limb::Limb (int angle_offset, int pin) : m_initial_offset(angle_offset), m_pin(pin) {
  m_center_position = 90 + m_initial_offset;
  // Set starting configuration
  m_current_position = m_center_position;

  m_servo.attach(m_pin);

  Serial.print("center position: ");
  Serial.print(m_center_position);
  Serial.print(" angle offset: ");
  Serial.print(m_initial_offset);
  Serial.print(" pin: ");
  Serial.println(m_pin);
}

Arm::Arm (int angle_offset, int pin) : Limb(angle_offset, pin)
{
  m_upperlimit = ((m_center_position + m_max_movement) > 180) ? 180 : (m_center_position + m_max_movement);
  m_lowerlimit = ((m_center_position - m_max_movement) < 0) ? 0 : (m_center_position - m_max_movement);

  Serial.print("Arm - current position: ");
  Serial.print(m_current_position);
  Serial.print(" lowerlimits: ");
  Serial.print(m_lowerlimit);
  Serial.print(" upperlimits: ");
  Serial.println(m_upperlimit);
}

Wrist::Wrist (int angle_offset, int pin) : Limb(angle_offset, pin)
{
  m_upperlimit = ((m_center_position + m_max_movement) > 180) ? 180 : (m_center_position + m_max_movement);
  m_lowerlimit = ((m_center_position - m_max_movement) < 0) ? 0 : (m_center_position - m_max_movement);

  Serial.print("Wrist - current position: ");
  Serial.print(m_current_position);
  Serial.print(" lowerlimits: ");
  Serial.print(m_lowerlimit);
  Serial.print(" upperlimits: ");
  Serial.println(m_upperlimit);
}

Shoulder::Shoulder (int angle_offset, int pin) : Limb(angle_offset, pin)
{
  m_upperlimit = ((m_center_position + m_max_movement) > 180) ? 180 : (m_center_position + m_max_movement);
  m_lowerlimit = ((m_center_position - m_max_movement) < 0) ? 0 : (m_center_position - m_max_movement);

  Serial.print("Shoulder - current position: ");
  Serial.print(m_current_position);
  Serial.print(" lowerlimits: ");
  Serial.print(m_lowerlimit);
  Serial.print(" upperlimits: ");
  Serial.println(m_upperlimit);
}
