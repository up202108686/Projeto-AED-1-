#ifndef UC_H_
#define UC_H_

#include <vector>
#include <iostream>
#include "Class.h"

using namespace std;

class UC {
public:
    UC();
    UC(vector<Turma> classes, string code);
    vector<Turma> getClasses();
    string getCode();
private:
    vector<Turma> classes;
    string code;
};

#endif