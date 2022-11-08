#if !defined(CONTROLLER_H)
#define CONTROLLER_H

//#include <Arduino.h>
#include "CASleepController.h"
#include "CATransmissionController.h"

extern void mainFunctionallity();     //scope: Global (main)

class Controller: protected CASleepController, protected CATransmissionController
{
private:
  int mi_counter = 0; //debug
  int mi_upperThreshold = 0;
  int mi_lowerThreshold = 0;
  void m_disablePorts();
  friend void mainFunctionallity();   //scope: Global (main)
  bool m_ThresholdCheck();
  bool m_virtualSleep();	
  bool m_virtualTransmission(); 

protected:

public:
  Controller();
  void m_setData(int mi_data);
  int m_getData();
  void m_processController();

};

extern Controller controllerObj;
#endif // DEVICE_H


