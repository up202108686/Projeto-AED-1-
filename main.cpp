#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>

#include "UcTurma.cpp"
#include "Student.cpp"
#include "TurmaH.cpp"
#include "Slot.cpp"

using namespace std;

vector<UcTurma> readClasses(vector<UcTurma> UcTurmas) {
    ifstream infile("data/classes.cvs");
    string line;
    bool first = true;
    while (getline(infile, line)) {
        if (first) { first = false; }
        else {
            for (int i = 0; i < line.length(); ++i) {
                if (line[i] == ',') {
                    line[i] = ' ';
                }
            }
            istringstream iss(line);
            string turma, cadeira, dia, tipo;
            float hora, duracao;
            iss >> turma >> cadeira >> dia >> hora >> duracao >> tipo;
            Slot aula = Slot(dia, hora, duracao, tipo);
            for (int i = 0; i < UcTurmas.size(); i++) {
                if (UcTurmas[i].getTurmaCode() == turma && UcTurmas[i].getUcCode() == cadeira) {
                    UcTurmas[i].addSlot(aula);
                    break;
                }
            }
        }
    }
    return UcTurmas;
}

vector<UcTurma> readClassesPerUC(vector<UcTurma> UcTurmas) {
    ifstream infile("data/classes_per_uc.csv");
    string line;
    bool first = true;
    while (getline(infile, line)) {
        if (first) { first = false;}
        else {
            for (int i = 0; i < line.length(); ++i) {
                if (line[i] == ',') {
                    line[i] = ' ';
                }
            }
            istringstream iss(line);
            string UcCode, TurmaCode;
            iss >> UcCode >> TurmaCode;
            UcTurma ut = UcTurma(UcCode, TurmaCode);
            UcTurmas.push_back(ut);
        }
    }
    return UcTurmas;
}
/*
list<UcTurma>  readStudentsClasses(list<UcTurma> UcTurmas, list<Student> students) {
    ifstream infile("data/students_classes.csv");
    string line;
    while(getline(infile, line, ',')) {
        istringstream iss(line);
        string nome, cadeira, turma;
        int codigo;
        line >> codigo >> nome >> cadeira >> turma;
        int turmaN;
        std::istringstream(turma.substr(turma.length()-2,2)) >> turmaN;
        int mins = 0;
        int maxs = students.size();
        Student s = students[students.size()/2];
        bool student_exists = true;
        while (s.getCode() != codigo) {
            if (maxs - mins == 0) {
                student_exists = false;
                break;
            }
            if (s.getCode() > codigo) {
                maxs = (mins + maxs)/2;
            }
            else {
                mins = (mins + maxs)/2;
            }
        }
        if (!(student_exists)) { Student s = new Student(codigo, nome); students.push_back(s); sort(students.begin(), students.end()); }
        for(UcTurma uc : UCs) {
            if (uc.getCode() == cadeira){
                int len = uc.getClasses().size();
                Turma cl = uc.getClasses()[len/2];
                int min = 0; int max = len;
                while (cl.getN() != turmaN) {
                    if (cl.getN() > turmaN) {
                        max = (max + min)/2;
                    }
                    else {
                        min = (max + min)/2;
                    }
                    cl = uc.getClasses()[(max + min)/2];
                }
                s.addClass(cl);
                cl.addStudent(s);
            }
        }
    }
}*/


int main() {
    vector<UcTurma> UcTurmas;
    UcTurmas = readClassesPerUC(UcTurmas);
    UcTurmas = readClasses(UcTurmas);
    for(UcTurma ut: UcTurmas) {
        cout << ut.getUcCode() << ", " << ut.getTurmaCode() << "\n";
    }
}
