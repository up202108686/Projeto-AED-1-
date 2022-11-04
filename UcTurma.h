#ifndef UC_H_
#define UC_H_

#include <vector>
#include <iostream>
#include "Slot.h"

using namespace std;

class UcTurma {
public:
    UcTurma();
    UcTurma(string UcCode, string TurmaCode);
    string getUcCode();
    string getTurmaCode();
    list<Slot> getUcTurmaAulas();
    void addSlot(Slot aula);
    void addNStudents(int n);
    void setNStudents(int n);
    int getNumberOfStudents();


private:
    string UcCode;
    string TurmaCode;
    list<Slot> UcTurmaAulas;
    int number_of_students;
};

#endif