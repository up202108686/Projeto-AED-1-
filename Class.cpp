//
// Created by nando on 02/11/2022.
//

#include "Class.h"
#include "UC.h"
#include "UC.cpp"
#include "Student.h"
#include "Student.cpp"
#include "Aula.h"
#include "Aula.cpp"

Turma::Turma() {}

//----------------------------------------------------------------------------------------------

//Constructor ---------------
Turma::Turma(std::string code, UC uc) {
    this.code = code;
    this.uc = uc;
}

//Getters -------------------
vector<Student> Turma::getStudents() {
    return this.students;
}

string Turma::getCode() {
    return this.code;
}

vector<Aula> Turma::getAulas() {
    return this.aulas;
}

UC Turma::getUc() {
    return this.uc;
}

void Turma::addStudent(Student s) {
    this.students.push_back(s);
}

void Turma::addAula(Aula a) {
    this.aulas.push_back(a);
}

int Turma::getN() {
    int n;
    std::istringstream(this.code.substr(this.code.length()-2,2)) >> n;
    return n;
}