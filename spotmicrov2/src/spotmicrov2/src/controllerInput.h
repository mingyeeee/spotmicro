/*
  controllerInput.cpp - Library for controller input using interrupts inorder to create non blocking code.
  Alternative to pulseIn() function which is blocking code
  Created by Mingye C 2021-02-20.
*/
#ifndef controllerInput_h
#define controllerInput_h

#include "Arduino.h"

class Controller_Channel {
  public:
    Controller_Channel(int interruptPin, int digitalPin);
    int m_digitalPin;
    int m_interruptPin;
    
    int checkValueUpdate();
    void channelInput();
  private:
    
    volatile int m_channelValue;
    volatile unsigned long m_startTime = 0;
    volatile bool m_newSignal = false;
    
};

#endif
