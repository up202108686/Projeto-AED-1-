#ifndef CLASS_H_
#define CLASS_H_

#include <vector>
#include <iostream>
#include "Student.h"
#include "Aula.h"

using namespace std;

class Turma {
public:
    Turma();
    Turma(std::vector<Student> &students, string code, vector<Aula> &aulas, UC uc);
    vector<Student> getStudents();
    string getCode();
    vector<Aula> getAulas();
    UC getUc();

private:
    vector<Student> students;
    string code;
    vector<Aula> aulas;
    UC uc;
};

#endif