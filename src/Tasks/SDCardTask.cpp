#include "main.h"


TickType_t xLastWakeTime;
const TickType_t xFrequency = 1000;

File dataFile;


void SDCardTask::setup(){
    xLastWakeTime = xTaskGetTickCount();

}

void SDCardTask::loop(){
    vTaskDelayUntil(&xLastWakeTime, xFrequency);
    dataFile = SD.open("./data.csv");
    IMUData currentData;
    while (xQueueReceive(xIMUDataQueue, &currentData, 2) == pdPASS)
    {
        dataFile.println(currentData.toString());
    }
    dataFile.close();
}

