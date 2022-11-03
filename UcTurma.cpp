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
