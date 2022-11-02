//
// Created by nando on 02/11/2022.
//

#include "Class.h"

Turma::Turma() {}

//----------------------------------------------------------------------------------------------

//Constructor ---------------
Turma::Turma(std::vector<Student> &students, std::string code, vector<Aula> &aulas, UC uc) {
    this->students = students;                                                                  //erro "no viable overloaded '='"
    this->code = code;
    this->aulas = aulas;                                                                        //erro "no viable overloaded '='"
    this->uc = uc;
}

//Getters -------------------
vector<Student> Turma::getStudents() {
    return this->students;
}

string Turma::getCode() {
    return this->code;
}

vector<Aula> Turma::getAulas() {
    return this->aulas;
}

UC Turma::getUc() {
    return this->uc;
}