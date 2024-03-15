#include "main.h"

#define TICKS_TO_WAIT 5
TickType_t xLastWakeTime;
const TickType_t xFrequency = 10;

void IMUTask::setup(){
    
    xLastWakeTime = xTaskGetTickCount();
    xIMUDataQueue = xQueueCreate(250, sizeof(IMUData));

    M5.Imu.Init();


}

void IMUTask::loop(){

    vTaskDelayUntil(&xLastWakeTime, xFrequency);
    IMUData currentData;
    IMUData newData;


    M5.Imu.getAccelData(&currentData.accX, &currentData.accY, &currentData.accZ);
    M5.Imu.getGyroData(&currentData.gyrX, &currentData.gyrY, &currentData.gyrZ);
    M5.Imu.getAhrsData(&currentData.pitch, &currentData.roll, &currentData.yaw);


    //Example code to send data into a queue
    if(xQueueSend(xIMUDataQueue, &currentData, TICKS_TO_WAIT) != pdPASS){
        Serial.println("Error sending data to queue");
    }
}


String IMUData::toString(){
    String retStr = String(this->accX) + "," + String(this->accY) + "," + String(this->accZ) + "," + String(this->gyrX) + "," + String(this->gyrY) + "," + String(this->gyrZ) + "," + String(this->pitch) + "," + String(this->roll) + "," + String(this->yaw);
    
    return retStr;

}