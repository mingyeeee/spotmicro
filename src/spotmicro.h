/*
  Morse.h - Library for coordinating SpotMicro's servo movements.
  Created by Mingye C 2021-02-10.
*/
#ifndef spotmicro_h
#define spotmicro_h

#include "Arduino.h"
#include <Servo.h>

class Limb {
  public:
    int m_initial_offset;
    int m_pin;
    int m_current_position;
    int m_initial_position;
    int m_center_position;
    int m_upperlimit;
    int m_lowerlimit;
    Servo m_servo;
    Limb (int angle_offset, int pin);
};

class Arm : public Limb {
  public:
    Arm (int angle_offset, int pin);
    // 90 degrees is orgin, therefore full range is 180
    const int m_max_movement = 90;
};

class Wrist : public Limb {
  public:
    Wrist (int angle_offset, int pin);
    // 90 degrees is orgin, therefore full range is 180
    const int m_max_movement = 90;
};

class Shoulder : public Limb {
  public:
    Shoulder (int angle_offset, int pin);
    // 90 degrees is orgin, Full range is 40 degrees
    const int m_max_movement = 20;
};

#endif
