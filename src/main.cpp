#include "main.h"

TinyGPSPlus gps;
HardwareSerial HWSerial2(2);

IMUTask* LocalIMUTask;
SDCardTask* LocalSDTask;

bool running = false; 

u8_t currentRoadType = 0;


void pausetasks(){
  LocalIMUTask->pauseTask();
  LocalSDTask->pauseTask();
  // xQueueReset(xIMUDataQueue);
}

void restartTasks(){
  LocalIMUTask->resumeTask();
  LocalSDTask->resumeTask();
  // xQueueReset(xIMUDataQueue);
}

void setup() {

  M5.begin(true, true, true, true);
  M5.Lcd.clearDisplay();

  delay(1000);


  LocalSDTask = new SDCardTask(4096, 10, NULL);
  delay(1);
  LocalIMUTask = new IMUTask(4096, 20, NULL);

  delay(10);

  pausetasks();

  M5.Lcd.setTextSize(2);
  M5.Lcd.drawString(StringRoadType[currentRoadType], 50, 20);
  M5.Lcd.drawString("Paused", 50, 50);
  
  

}

void loop() {
  if(M5.BtnA.wasPressed()){
    if(running){
      M5.Lcd.clearDisplay();
      M5.Lcd.drawString(StringRoadType[currentRoadType], 50, 20);
      M5.Lcd.drawString("Paused", 50, 50);
      running = false;

      pausetasks();
    }
    else{
      M5.Lcd.clearDisplay();
      M5.Lcd.drawString(StringRoadType[currentRoadType], 50, 20);
      M5.Lcd.drawString("Running", 50, 50);
      running = true;

      restartTasks();
    }
  }


  if(!running && M5.BtnB.wasPressed()){
    if(currentRoadType == 5){
      currentRoadType = 0;
    }
    else{
      currentRoadType +=1;
    }

    M5.Lcd.clearDisplay();
    M5.Lcd.drawString("Paused", 50, 50);
    M5.Lcd.drawString(StringRoadType[currentRoadType], 50, 20);

  }

  delay(10);
  M5.update();
}

