#ifndef STUDENT_H_
#define STUDENT_H_

#include <vector>
#include <iostream>
#include "Class.h"

using namespace std;

class Student {
public:
    Student();
    Student(vector<Turma> classes, int code, string name);      //erro "Use of undeclared identifier 'Turma'"
    vector<Turma> getClasses();                                 //erro "Use of undeclared identifier 'Turma'"
    int getCode();
    string getName();
    void addClass(Turma t);

private:
    vector<Turma> classes;                                      //erro "Use of undeclared identifier 'Turma'"
    int code;
    string name;
};

#endif
