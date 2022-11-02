//
// Created by nando on 02/11/2022.
//
#include "Aula.h"
#include "UC.h"
#include "UC.cpp"
#include "Class.h"
#include "Class.cpp"

Aula::Aula() {}

//------------------------------------------------------------------------------------------------------

//Constructor ---------------
Aula::Aula(UC uc, string weekday, float start_hour, float duration, string type, Turma turma) {
    this.uc = uc;
    this.weekday = weekday;
    this.start_hour = start_hour;
    this.duration = duration;
    this.type = type;
    this.turma = turma;
}

//Getters -------------------
UC Aula::getUc() {
    return this.uc;
}

float Aula::getDuration() {
    return this.duration;
}

float Aula::getStart_hour() {
    return this.start_hour;
}

Turma Aula::getTurma() {
    return this.turma;
}

string Aula::getType() {
    return this.type;
}

string Aula::getWeekday() {
    return this.weekday;
}