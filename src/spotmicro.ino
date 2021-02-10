/* Mingye Chen 2021-02-09
 * to do:
 * - inverse kinematic model
 * - interpolation
 */
#include <Servo.h>

class Limb{
    public:
        int m_initial_offset;
        int m_pin;
        int m_current_position;
        int m_initial_position;
        int m_center_position;
        int m_upperlimit;
        int m_lowerlimit;
        Servo m_servo;
        Limb (int angle_offset, int pin) : m_initial_offset(angle_offset), m_pin(pin) {
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
        
};

class Arm : public Limb{
    public:
        //using Limb::Limb;
        Arm (int angle_offset, int pin) : Limb(angle_offset, pin)
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
        // 90 degrees is orgin, therefore full range is 180
        const int m_max_movement = 90;

};

class Wrist : public Limb{
    public:
        Wrist (int angle_offset, int pin) : Limb(angle_offset, pin)
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
        // 90 degrees is orgin, therefore full range is 180
        const int m_max_movement = 90;
};

class Shoulder : public Limb{
    public:
        Shoulder (int angle_offset, int pin) : Limb(angle_offset, pin)
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
        // 90 degrees is orgin, therefore full range is 180
        const int m_max_movement = 20;
};


void setup() {
  Serial.begin(115200);
  // Servo initialization
  // f - front | b - back
  // r - right | l - left
  Arm fr_arm(-1,1);
  Arm fl_arm(-3,5);
  Arm br_arm(3,8);
  Arm bl_arm(2,11);
  Wrist fr_wrist(-2,3);
  Wrist fl_wrist(1,4);
  Wrist br_wrist(7,7);
  Wrist bl_wrist(-11,10);
  Shoulder fr_shoulder(-4,2);
  Shoulder fl_shoulder(-5,6);
  Shoulder br_shoulder(4,9);
  Shoulder bl_shoulder(0,12);
}

void loop() {
  // put your main code here, to run repeatedly:

}
