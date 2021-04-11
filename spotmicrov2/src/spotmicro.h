/*
  Morse.h - Library for coordinating SpotMicro's servo movements.
  Created by Mingye C 2021-02-10.
*/
#ifndef spotmicro_h
#define spotmicro_h

#include "Arduino.h"
#include <Servo.h>
#include "math.h"

#define ANGLE_TO_MS 10.25

class Limb {
  public:
    // tuning offsets
    int m_initial_offset;
    int m_pin;
    int m_current_position;
    // starting angle with offsets
    int m_initial_position;
    // starting angle without offsets
    int m_center_position;
    // angle at most clockwise direction
    int m_cw_limit;
    Servo m_servo;
    
    Limb (int angle_offset, int pin, int up_max_angle);
    void move_to_angle(float angle);
};

class Arm : public Limb {
  public:
    Arm (int angle_offset, int pin, int up_maximum_angle);
    // 90 degrees is orgin, therefore full range is 180
    const int m_max_movement = 90;
    // angle offset caused by the structure of the arm limb
    const double m_structural_offset = 15.7;
    // does the calculations to determine the angle the servo must move relative to the initial position at ~90 deg
    
};

class Wrist : public Limb {
  public:
    Wrist (int angle_offset, int pin, int up_maximum_angle);
    // 90 degrees is orgin, therefore full range is 180
    const int m_max_movement = 90;
    
};

class Shoulder : public Limb {
  public:
    Shoulder (int angle_offset, int pin, int up_maximum_angle);
    // 90 degrees is orgin, Full range is 40 degrees
    const int m_max_movement = 20;
};

class IK_Model{
  public:
    static void calcAngles(int z_length, int y_length, int x_length, double * angles);
};

#endif
