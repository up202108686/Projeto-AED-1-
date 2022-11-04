//
// Created by nando on 03/11/2022.
//

#ifndef SLOT_H
#define SLOT_H

#include <iostream>

using namespace std;

class Slot {
public:
    Slot();
    Slot(string weekday, float start_hour, float duration, string type);
    string getWeekday();
    float getStart_hour();
    float getDuration();
    string getType();
    bool operator<(const Slot & s);

private:
    string weekday;
    float start_hour;
    float duration;
    string type;
};


#endif
