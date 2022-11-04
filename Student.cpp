//
// Created by nando on 02/11/2022.
//
#include "Student.h"

Student::Student() {}

//-------------------------------------------------------------------

//Constructor -------------------
Student::Student(list<UcTurma> turmas, int code, string name) {
    this->code = code;
    for (int i = 0; i < name.length(); ++i) {
        if (name[i] == '_') {
            name[i] = ' ';
        }
    }
    this->name = name;
}

//Getters --------------------
list<UcTurma> Student::getTurmas() {
    return this->turmas;
}

int Student::getCode() const {
    return this->code;
}

string Student::getName() {
    return this->name;
}

void Student::addUcTurma(UcTurma ut) {
    this->turmas.push_back(ut);
}

void Student::removeUcTurma(UcTurma ut) {
    this->turmas.remove(ut);
}

bool Student::operator< (const Student & a) {
    if (this->code < a.getCode()) { return true; }
    return false;
}