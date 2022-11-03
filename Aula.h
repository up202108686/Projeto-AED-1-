#ifndef AULA_H_
#define AULA_H_

#include <vector>
#include <iostream>
#include "Class.h"
#include "UC.h"

using namespace std;

class Aula {
public:
    Aula();
    Aula(UC uc, string weekday, float start_hour, float duration, string type, Turma turma);    //erro "unknown type name 'UC'"
    UC getUc();                                                                                 //erro "unknown type name 'UC'"
    string getWeekday();
    float getStart_hour();
    float getDuration();
    string getType();
    Turma getTurma();                                                                           //erro "unknown type name 'Turma'"

private:
    UC uc;                                                                                      //erro "unknown type name 'UC'"
    string weekday;
    float start_hour;
    float duration;
    string type;
    Turma turma;                                                                                //erro "unknown type name 'UC'"
};

#endif