//
// Created by nando on 03/11/2022.
//

#include "Slot.h"

Slot::Slot() {}

Slot::Slot(string weekday, float start_hour, float duration, string type) {
    this->weekday = weekday;
    this->start_hour = start_hour;
    this->duration = duration;
    this->type = type;
}

string Slot::getWeekday() {
    return this->weekday;
}

float Slot::getStart_hour() {
    return this->start_hour;
}

float Slot::getDuration() {
    return this->duration;
}

string Slot::getType() {
    return this->type;
}

bool Slot::operator<(const Slot & s) {
    int x;
    int y;
    if (this->weekday == s.weekday){
        if (this->start_hour < s.start_hour) return true;
    }
    if(this->weekday=="Monday") x=1;
    if(this->weekday=="Tuesday") x=2;
    if(this->weekday=="Wednesday") x=3;
    if(this->weekday=="Thursday") x=4;
    if(this->weekday=="Friday") x=5;
    if(s.weekday=="Monday") y=1;
    if(s.weekday=="Tuesday") y=2;
    if(s.weekday=="Wednesday") y=3;
    if(s.weekday=="Thursday") y=4;
    if(s.weekday=="Friday") y=5;
    if(x<y) return true;
    return false;
}