//
// Created by nando on 02/11/2022.
//
#include "Student.h"

Student::Student() {}

//-------------------------------------------------------------------

//Constructor -------------------
Student::Student(vector<Turma> classes, int code, string name) {
    this->classes = classes;                                                //erro "no viable overloaded '='"
    this->code = code;
    this->name = name;
}

//Getters --------------------
vector<Turma> Student::getClasses() {
    return this->classes;
}

int Student::getCode() {
    return this->code;
}

string Student::getName() {
    return this->name;
}