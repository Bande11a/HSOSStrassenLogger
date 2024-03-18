#ifndef main_h_
#define main_h_

#include <M5Stack.h>
#include <ArduinoJson.h>
#include <TinyGPS++.h>
#include <WiFi.h>
#include "./Tasks/Tasks.h"


enum RoadType{
    Asphalt,
    Kies,
    Pflaster,
    KopfsteinPflaster,
    Feldweg,
    Bodenwelle
};

const String StringRoadType[] = {"Asphalt", "Kies", "Pflaster", "KopfsteinPflaster", "Feldweg", "Bodenwelle"};



#endif