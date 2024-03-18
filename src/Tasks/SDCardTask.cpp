#include "main.h"


TickType_t xIMULastWakeTime;
const TickType_t xFrequency = 1000;

File dataFile;


void SDCardTask::setup(){
    xIMULastWakeTime = xTaskGetTickCount();

}

void SDCardTask::loop(){
    vTaskDelayUntil(&xIMULastWakeTime, xFrequency);
    dataFile = SD.open("/data_" + StringRoadType[currentRoadType] +".csv", FILE_APPEND);
    if(!dataFile){
        Serial.println("Failed to open File");
    }
    else{
        IMUData currentData;
        while (xQueueReceive(xIMUDataQueue, &currentData, 2) == pdPASS)
        {
            dataFile.println(currentData.toString());
        }
        dataFile.close();
    }
}

