/*
  spotmicro.h - Library for coordinating SpotMicro's servo movements.
  Created by Mingye C, Thomas Z 2021-02-10.
*/
#ifndef spotmicro_h
#define spotmicro_h

#include "Arduino.h"
#include <Servo.h>
#include "math.h"
#include "spotmicro_util.h"

#define LEG_LENGTH 111.126
#define WRIST_LENGTH 118.5
#define HIP_LENGTH 60.5
// move servos every 10 ms
#define MOVEMENT_INTERVAL 10

class Limb {
  public:
    // tuning offsets
    int m_initial_offset;
    int m_pin;
    float m_current_position;
    // position to move to
    float m_target_position; 
    // starting angle with offsets
    int m_initial_position;
    // starting angle without offsets
    int m_center_position;
    // angle at most clockwise direction
    int m_cw_limit;
    // default movement speed to 1 deg per MOVEMENT_INTERVAL
    float m_movement_speed = 1;

    Servo m_servo;
    
    Limb (int angle_offset, int pin, int up_max_angle);
    //Limb ();
    void move_to_angle(float angle);
    //prints all public members for debugging purposes
    void mvar_debug();
};

class Arm : public Limb {
  public:
    Arm (int angle_offset, int pin, int up_maximum_angle);
    //Arm ();
    // 90 degrees is orgin, therefore full range is 180
    const int m_max_movement = 90;
    // angle offset caused by the structure of the arm limb
    const double m_structural_offset = 15.7;
    // does the calculations to determine the angle the servo must move relative to the initial position at ~90 deg
    float convertAngle(float angle);
    
};

class Wrist : public Limb {
  public:
    Wrist (int angle_offset, int pin, int up_maximum_angle);
    // 90 degrees is orgin, therefore full range is 180
    const int m_max_movement = 90;
    float convertAngle(float angle);
    
};

class Shoulder : public Limb {
  public:
    Shoulder (int angle_offset, int pin, int up_maximum_angle);
    // 90 degrees is orgin, Full range is 40 degrees
    const int m_max_movement = 20;
    float convertAngle(float angle);
};

class IK_Model{
  public:
    static void calcAngles(unsigned int z_length, int y_length, int x_length, double * angles);
};

#endif
