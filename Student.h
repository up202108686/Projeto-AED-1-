#ifndef STUDENT_H_
#define STUDENT_H_

#include <vector>
#include <iostream>
#include <list>
#include "UcTurma.h"


using namespace std;

class Student {
public:
    Student();
    Student(list<UcTurma> turmas, int code, string name);
    list<UcTurma> getTurmas();
    int getCode() const;
    string getName();
    void addUcTurma(UcTurma ut);
    bool operator< (const Student & a);


private:
    list<UcTurma> turmas;
    int code;
    string name;
};

#endif
