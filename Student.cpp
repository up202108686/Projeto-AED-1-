//
// Created by nando on 02/11/2022.
//
#include "Student.h"
#include "Class.h"
#include "Class.cpp"

Student::Student() {}

//-------------------------------------------------------------------

//Constructor -------------------
Student::Student(int code, string name) {
    this.code = code;
    this.name = name;
}

//Getters --------------------
vector<Turma> Student::getClasses() {
    return this.classes;
}

int Student::getCode() {
    return this.code;
}

string Student::getName() {
    return this.name;
}

void Student::addClass(Turma t) {
    this.classes.push_back(t);
}