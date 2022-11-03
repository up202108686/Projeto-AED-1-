//
// Created by nando on 02/11/2022.
//
#include "Student.h"

Student::Student() {}

//-------------------------------------------------------------------

//Constructor -------------------
Student::Student(list<UcTurma> turmas, int code, string name) {
    this->code = code;
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

/*
void Student::addClass(Turma t) {
    this.classes.push_back(t);
}
 */