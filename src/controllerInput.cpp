/*
  controllerInput.cpp - Library for controller input using interrupts inorder to create non blocking code.
  Alternative to pulseIn() function which is blocking code
  Created by Mingye C 2021-02-20.
*/
#include "Arduino.h"
#include "controllerInput.h"

Controller_Channel::Controller_Channel(int interruptPin, int digitalPin) : m_interruptPin(interruptPin), m_digitalPin(digitalPin){}

int Controller_Channel::checkValueUpdate(){
  if(m_newSignal){
    m_newSignal = false;
    return m_channelValue;
  }
  //no new value
  return 0;
}

void Controller_Channel::channelInput(){

  if(digitalRead(m_digitalPin) == HIGH)
  {
    // start recording pwm length
    m_startTime = micros();
  }
  else
  {
    if(m_startTime && !m_newSignal)
    {
      m_channelValue = (int)(micros() - m_startTime);
      m_startTime = 0;

      // will not update m_channelvalue until previous value is checked by main program
      m_newSignal = true;
    }
  }
}
