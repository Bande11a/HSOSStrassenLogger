#ifndef Tasks_h_
#define Tasks_h_

#include "./main.h"


class TaskTemplate{

private:
    TaskHandle_t localTask;
    char* taskName;
    
public:

    ~TaskTemplate();
    TaskTemplate(uint32_t stackDepth, UBaseType_t Priority, void *pvParameters);
    TaskTemplate(uint32_t stackDepth, UBaseType_t Priority, void *pvParameters, String taskName);


    void pauseTask(){vTaskSuspend(localTask);}
    void resumeTask(){vTaskResume(localTask);}


    void *taskParams;
    virtual void setup(){}
    virtual void loop(){}

};


class  IMUTask: public TaskTemplate{
public:
    using TaskTemplate::TaskTemplate;
    void setup() override;
    void loop() override;    
};

class  SDCardTask: public TaskTemplate{
public:
    using TaskTemplate::TaskTemplate;
    void setup() override;
    void loop() override;    
};


struct IMUData{
public:
    float accX;
    float accY;
    float accZ;

    float gyrX;
    float gyrY;
    float gyrZ;

    float pitch;
    float roll;
    float yaw;

    String toString();
};


extern QueueHandle_t xIMUDataQueue;

#endif