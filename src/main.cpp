#include "main.h"

TinyGPSPlus gps;
HardwareSerial HWSerial2(2);

IMUTask* LocalIMUTask;
SDCardTask* LocalSDTask;

bool running = false; 


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
  SD.begin();

  delay(1000);


  LocalSDTask = new SDCardTask(128, 10, NULL);
  delay(1);
  LocalIMUTask = new IMUTask(128, 20, NULL);

  pausetasks();

  M5.Lcd.drawString("Paused", 50, 50);
  
  

}

void loop() {
  if(M5.BtnA.wasPressed()){
    if(running){
      M5.Lcd.clearDisplay();
      M5.Lcd.drawString("Paused", 50, 50);

      pausetasks();
    }
    else{
      M5.Lcd.clearDisplay();
      M5.Lcd.drawString("Running", 50, 50);
      restartTasks();
    }

    

    
  }


  M5.update();
  
  
}

