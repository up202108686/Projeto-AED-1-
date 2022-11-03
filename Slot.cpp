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