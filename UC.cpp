//
// Created by nando on 02/11/2022.
//

#include "UC.h"

UC::UC() {}

//--------------------------------------------------------------------------------

//Constructor ---------------------------
UC::UC(vector<Turma> classes, std::string code) {
    this->classes = classes;                            //erro "no viable overloaded '='"
    this->code = code;                                  //Pode ser um erro de referência
}                                                       //de vetores
//Getters -------------------------------
vector<Turma> UC::getClasses() {
    return this->classes;
}

string UC::getCode() {
    return this->code;
}

