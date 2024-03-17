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
  M5.Lcd.clearDisplay();

  delay(1000);


  LocalSDTask = new SDCardTask(2048, 10, NULL);
  delay(1);
  LocalIMUTask = new IMUTask(2048, 20, NULL);

  pausetasks();

  M5.Lcd.drawString("Paused", 50, 50);
  
  

}

void loop() {
  if(M5.BtnA.wasPressed()){
    if(running){
      M5.Lcd.clearDisplay();
      M5.Lcd.drawString("Paused", 50, 50);
      running = !running;

      pausetasks();
    }
    else{
      M5.Lcd.clearDisplay();
      M5.Lcd.drawString("Running", 50, 50);
      running = !running;

      restartTasks();
    }

    

    
  }


  M5.update();
  
  
}

