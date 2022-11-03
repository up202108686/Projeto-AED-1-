#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <algorithm>

#include "UcTurma.cpp"
#include "Student.cpp"
#include "Slot.cpp"

using namespace std;

vector<UcTurma> readClasses(vector<UcTurma> UcTurmas) {
    ifstream infile("data/classes.csv");
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

vector<Student>  readStudentsClasses(vector<UcTurma> UcTurmas, vector<Student> students) {
    ifstream infile("data/students_classes.csv");
    string line;
    bool first = true;
    while(getline(infile, line)) {
        if (first) { first = false;}
        else {
            for (int i = 0; i < line.length(); ++i) {
                if (line[i] == ',') {
                    line[i] = ' ';
                }
                else if (line[i] == ' ') {
                    line[i] = '_';
                }
            }
            sort(students.begin(), students.end());
            istringstream iss(line);
            string nome, cadeira, turma;
            int codigo;
            iss >> codigo >> nome >> cadeira >> turma;
            int mins = 0;
            int maxs = students.size();
            int si = students.size() / 2;
            bool student_exists = true;
            Student s;
            if (students.size() != 0) {
                s = students[si];
                int cancel = 0;
                while (s.getCode() != codigo) {
                    cancel += 1;
                    if (maxs - mins == 0 || cancel > students.size()) {
                        student_exists = false;
                        break;
                    }
                    else if (s.getCode() > codigo) {
                        maxs = (mins + maxs) / 2;
                    }
                    else {
                        mins = (mins + maxs) / 2;
                    }
                    si = (mins + maxs) / 2;
                    s = students[(mins + maxs) / 2];
                }
            }
            else { student_exists = false; }
            if (!(student_exists)) {
                list<UcTurma> t;
                s = Student(t, codigo, nome);
                students.push_back(s);
                si = students.size() - 1;
            }
            for (int i = 0; i < UcTurmas.size(); i++) {
                if (UcTurmas[i].getTurmaCode() == turma && UcTurmas[i].getUcCode() == cadeira) {
                    s.addUcTurma(UcTurmas[i]);
                    students[si] = s;
                    break;
                }
            }
        }
    }
    return students;
}


int main() {
    vector<UcTurma> UcTurmas;
    vector<Student> students;
    UcTurmas = readClassesPerUC(UcTurmas);
    UcTurmas = readClasses(UcTurmas);
    students = readStudentsClasses(UcTurmas, students);
    for(Student st: students) {
        cout << st.getCode() << "\n";
        for (UcTurma ut : st.getTurmas()){
            cout << ut.getUcCode() << ", " << ut.getTurmaCode() << "\n";
        }
        cout << "\n";
    }
}
