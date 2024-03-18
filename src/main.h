#ifndef main_h_
#define main_h_

#include <M5Stack.h>
#include <ArduinoJson.h>
#include <TinyGPS++.h>
#include <WiFi.h>
#include "./Tasks/Tasks.h"



const String StringRoadType[] = {"Asphalt", "Kies", "Pflaster", "KopfsteinPflaster", "Feldweg", "Bodenwelle"};
extern u8_t currentRoadType;


#endif