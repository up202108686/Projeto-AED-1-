#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>

#include "UcTurma.cpp"
#include "Student.cpp"
#include "TurmaH.cpp"
#include "Slot.cpp"

using namespace std;

int main() {
    list<UcTurma> UcTurmas;
    ifstream infile("data/classes_per_uc.csv");
    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        string UcCode, TurmaCode;
        iss >> UcCode >> TurmaCode;
        UcTurma ut = UcTurma(UcCode, TurmaCode);
        UcTurmas.push_back(ut);
    }
    for(UcTurma ut: UcTurmas) {
        cout << ut.getUcCode() << ut.getTurmaCode() << "\n";
    }
}