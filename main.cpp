#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <algorithm>

#include "UcTurma.cpp"
#include "Student.cpp"
#include "Slot.cpp"

using namespace std;

bool wouldBeBalanced(string uc_code, string turma_1, string turma_2, vector<Student> students, int limit) {
    vector<UcTurma> turmas;
    vector<int> students_per_turma;
    for (int i = 0; i < students.size(); i++) {
        for (UcTurma ut : students[i].getTurmas()) {
            if (ut.getUcCode() == uc_code) {
                bool turma_exists = false;
                for (int j = 0; j < turmas.size(); j++) {
                    if (ut.getTurmaCode() == turmas[j].getTurmaCode()) {
                        students_per_turma[j] += 1;
                        turma_exists = true;
                        break;
                    }
                }
                if (!(turma_exists)) {
                    turmas.push_back(ut);
                    students_per_turma.push_back(1);
                }
            }
        }
    }
    for (int j = 0; j < turmas.size(); j++) {
        if (turma_1 == turmas[j].getTurmaCode()) {
            students_per_turma[j] -= 1;
        }
       else if (turma_2 == turmas[j].getTurmaCode()) {
            students_per_turma[j] += 1;
        }
    }
    int turma_1_n = 0; int turma_2_n = 0;
    for (int i = 0; i < students_per_turma.size(); i++) {
        if (turmas[i].getTurmaCode() == turma_1) { turma_1_n = students_per_turma[i]; }
        else if (turmas[i].getTurmaCode() == turma_2) { turma_2_n = students_per_turma[i]; }
    }
    if (turma_2_n >= limit) { return false; }
    if (turma_1_n > turma_2_n) { return true; }
    int min = INT_MAX; int max = 0;
    for (int i = 0; i < students_per_turma.size(); i++) {
        if (students_per_turma[i] < min) { min = students_per_turma[i]; }
        else if (students_per_turma[i] > max) { max = students_per_turma[i]; }
    }
    if (max - min < 4) { return true; }
    return false;
}

bool classesDontOverlap(Student student, UcTurma ut) {
    for (UcTurma u : student.getTurmas()) {
        if (ut.getUcCode() != u.getUcCode()) {
            for (Slot s1: ut.getUcTurmaAulas()) {
                for (Slot s2 : u.getUcTurmaAulas()) {
                    if (s1.getWeekday() == s2.getWeekday() && (s1.getType() != "T" && s2.getType() != "T")) {
                        if ((s2.getStart_hour() <= s1.getStart_hour() <= s2.getStart_hour() + s2.getDuration()) || (s1.getStart_hour() <= s2.getStart_hour() <= s1.getStart_hour() + s1.getDuration())) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

void changeClass(int student_code, string uc_code, string turma_1, string turma_2, vector<Student> &students, vector<UcTurma> ucturmas, bool &throw_away) {
    int limit = 20;                                                                                                                                             //LIMITE MAXIMO DE ESTUDANTES NUMA TURMA
    throw_away = false;
    for (int i = 0; i < students.size(); i++) {
        if (students[i].getCode() == student_code) {
            UcTurma ut1; UcTurma ut2;
            for (int j = 0; j < ucturmas.size(); j++) {
                if (ucturmas[j].getUcCode() == uc_code && ucturmas[j].getTurmaCode() == turma_2) {
                    ut2 = ucturmas[j];
                }
                else if (ucturmas[j].getUcCode() == uc_code && ucturmas[j].getTurmaCode() == turma_1) {
                    ut1 = ucturmas[j];
                }
            }
            if (classesDontOverlap(students[i], ut2) && wouldBeBalanced(uc_code, turma_1, turma_2, students, limit)) {
                students[i].removeUcTurma(ut1);
                students[i].addUcTurma(ut2);
            }
            else { throw_away = true; }
        }
    }
}

void changeSeveralClass(int student_code, vector<string> uc_code, vector<string> turma_1, vector<string> turma_2, vector<Student> &students, vector<UcTurma> ucturmas, bool &throw_away) {
    int limit = 20;                                                                                                                                             //LIMITE MAXIMO DE ESTUDANTES NUMA TURMA
    throw_away = false;
    for (int i = 0; i < students.size(); i++) {
        if (students[i].getCode() == student_code) {
            int total_possible = 0;
            for (int j = 0; j < uc_code.size(); j++) {
                UcTurma ut;
                for (int k = 0; k < ucturmas.size(); k++) {
                    if (ucturmas[k].getUcCode() == uc_code[j] && ucturmas[k].getTurmaCode() == turma_2[j]) {
                        ut = ucturmas[k];
                    }
                }
                if (classesDontOverlap(students[i], ut) && wouldBeBalanced(uc_code[j], turma_1[j], turma_2[j], students, limit)) {
                    total_possible += 1;
                }
            }
            if (total_possible == uc_code.size()) {
                for (int j = 0; j < uc_code.size(); j++) {
                    UcTurma ut1; UcTurma ut2;
                    for (int k = 0; k < ucturmas.size(); k++) {
                        if (ucturmas[k].getUcCode() == uc_code[j] && ucturmas[k].getTurmaCode() == turma_2[j]) {
                            ut2 = ucturmas[k];
                        }
                        else if (ucturmas[k].getUcCode() == uc_code[j] && ucturmas[k].getTurmaCode() == turma_1[j]) {
                            ut1 = ucturmas[k];
                        }
                    }
                    students[i].removeUcTurma(ut1);
                    students[i].addUcTurma(ut2);
                }
            }
            else { throw_away = true; }
        }
    }
}

void removeUcFromStudent(vector<Student> &students, int s_code, string uc_code, string turma) {
    int mins = 0;
    int maxs = students.size();
    int si = students.size() / 2;
    Student s;
    s = students[si];
    while (s.getCode() != s_code) {
        if (s.getCode() > s_code) {
            maxs = (mins + maxs) / 2;
        }
        else {
            mins = (mins + maxs) / 2;
        }
        si = (mins + maxs) / 2;
        s = students[(mins + maxs) / 2];
    }
    for (UcTurma ut : s.getTurmas()) {
        if (ut.getUcCode() == uc_code && ut.getTurmaCode() == turma) {
            s.removeUcTurma(ut);
            break;
        }
    }
    students[si] = s;
}

void addUcToStudent(vector<Student> &students, vector<UcTurma> ucturmas, int s_code, string name, string uc_code, string turma) {
    int limit = 20;                                                                                                                                             //LIMITE MAXIMO DE ESTUDANTES NUMA TURMA
    int mins = 0;
    int maxs = students.size();
    int si = students.size() / 2;
    Student s;
    s = students[si];
    bool student_exists = true;
    int cancel = 0;
    while (s.getCode() != s_code) {
        cancel += 1;
        if (maxs - mins == 0 || cancel > students.size()) {
            student_exists = false;
            break;
        }
        else if (s.getCode() > s_code) {
            maxs = (mins + maxs) / 2;
        }
        else {
            mins = (mins + maxs) / 2;
        }
        si = (mins + maxs) / 2;
        s = students[(mins + maxs) / 2];
    }
    if (!(student_exists)) {
        list<UcTurma> l;
        s = Student(l, s_code, name);
        si = students.size();
        students.push_back(s);
    }
    UcTurma ut;
    for (int i = 0; i < ucturmas.size(); i++) {
        if (ucturmas[i].getUcCode() == uc_code && ucturmas[i].getTurmaCode() == turma) {
            ut = ucturmas[i];
        }
    }
    if (wouldBeBalanced(uc_code, "", turma, students, limit) && classesDontOverlap(s, ut)) {
        s.addUcTurma(ut);
    }
    students[si] = s;
    sort(students.begin(), students.end());
}

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
    sort(students.begin(), students.end());
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
