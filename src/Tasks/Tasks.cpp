#include "main.h"

void taskFunc(void *pvParameters){
    TaskTemplate *currentObj = (TaskTemplate *) pvParameters;

    currentObj->setup();
    for(;;){
        currentObj->loop();
    }

    
}

TaskTemplate::TaskTemplate(uint32_t stackDepth, UBaseType_t Priority, void *pvParameters){


    //As each task needs a unique name im just taking the current millis time and allocating it to the heap.
    unsigned long currentTime = millis();
    int size = snprintf(NULL, 0, "%lu", currentTime) + 1;
    this->taskName = (char*)malloc(size);
    snprintf(this->taskName, size, "%lu", currentTime);

    this->taskParams = pvParameters;

    //Creating the task
    xTaskCreate(taskFunc, this->taskName, stackDepth, this, Priority, &(this->localTask));
}

TaskTemplate::~TaskTemplate(){
    vTaskDelete(this->localTask);

    //Deletes the task name;
    free(this->taskName);
}





QueueHandle_t xIMUDataQueue;