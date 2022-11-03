//
// Created by nando on 02/11/2022.
//
#include "TurmaH.h"

TurmaH::TurmaH() {}

//------------------------------------------------------------------------------------------------------

//Constructor ---------------
TurmaH::TurmaH(std::string UcCode, std::string TurmaCode, list<Slot> UcTurmaAulas) {
    this->UcCode = UcCode;
    this->TurmaCode = TurmaCode;
    this->UcTurmaAulas = UcTurmaAulas;
}

//Getters -------------------
string TurmaH::getUcCode() {
    return this->UcCode;
}

string TurmaH::getTurmaCode() {
    return this->TurmaCode;
}

list<Slot> TurmaH::getUcTurmaAulas() {
    return this->UcTurmaAulas;
}