#ifndef TURMAH_H_
#define TURMAH_H_

#include <list>
#include <iostream>
#include "Slot.h"

using namespace std;

class TurmaH {
public:
    TurmaH();
    TurmaH(string UcCode, string TurmaCode, list<Slot> UcTurmaAulas);
    string getUcCode();
    string getTurmaCode();
    list<Slot> getUcTurmaAulas();

private:
    string UcCode;
    string TurmaCode;
    list<Slot> UcTurmaAulas;
};

#endif