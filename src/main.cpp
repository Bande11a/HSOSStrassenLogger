#include "main.h"

TinyGPSPlus gps;
HardwareSerial HWSerial2(2);

IMUTask* LocalIMUTask;
SDCardTask* LocalSDTask;


void pausetasks(){
  LocalIMUTask->pauseTask();
  LocalSDTask->pauseTask();
  xQueueReset(xIMUDataQueue);
}

void restartTasks(){
  LocalIMUTask->resumeTask();
  LocalSDTask->resumeTask();
  xQueueReset(xIMUDataQueue);
}

void setup() {

  M5.begin(true, true, true, true);
  HWSerial2.begin(9600);
  M5.Lcd.clearDisplay();


  LocalSDTask = new SDCardTask(128, 10, NULL);
  delay(1);
  LocalIMUTask = new IMUTask(128, 20, NULL);

  pausetasks();
  
  

}

void loop() {
  if(M5.BtnA.wasPressed()){
    
  }


  M5.update();
  
  
}

