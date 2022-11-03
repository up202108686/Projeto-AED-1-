#ifndef UC_H_
#define UC_H_

#include <vector>
#include <iostream>

using namespace std;

class UcTurma {
public:
    UcTurma();
    UcTurma(string UcCode, string TurmaCode);
    string getUcCode();
    string getTurmaCode();
    /*
    void addClass(Turma t);
     */
private:
    string UcCode;
    string TurmaCode;
};

#endif