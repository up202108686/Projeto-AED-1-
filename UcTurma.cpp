//
// Created by nando on 02/11/2022.
//

#include <list>
#include "UcTurma.h"

UcTurma::UcTurma() {}

//--------------------------------------------------------------------------------

//Constructor ---------------------------
UcTurma::UcTurma(std::string UcCode, std::string TurmaCode) {
         this->TurmaCode = TurmaCode;
         this->UcCode = UcCode;
         this->number_of_students = 0;
}
//Getters -------------------------------
string UcTurma::getTurmaCode() {
    return this->TurmaCode;
}

string UcTurma::getUcCode() {
    return this->UcCode;
}

void UcTurma::addSlot(Slot aula) {
    this->UcTurmaAulas.push_back(aula);
}

list<Slot> UcTurma::getUcTurmaAulas() {
    return this->UcTurmaAulas;
}

void UcTurma::addNStudents(int n) {
    this->number_of_students += n;
}
void UcTurma::setNStudents(int n) {
    this->number_of_students = n;
}
int UcTurma::getNumberOfStudents() {
    return this->number_of_students;
}

bool UcTurma::operator==(const UcTurma & ut) {
    if (this->UcCode == ut.UcCode && this->TurmaCode == ut.TurmaCode) { return true; }
    return false;
}