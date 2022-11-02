#include "UC.h"
#include "Class.h"
#include "Student.h"
#include "Aula.h"
#include <iostream>
#include <vector>

using namespace std;

void readClasses(vector<UC> UCs) {
    ifstream infile("data/classes.cvs");
    string line;

    while (getline(infile, line, ',')) {
        istringstream iss(line);
        string turma, cadeira, dia, tipo;
        float hora, duracao;
        line >> turma >> cadeira >> dia >> hora >> duracao >> tipo;
        int turmaN;
        std::istringstream(turma.substr(turma.length()-2,2)) >> turmaN;
        for (UC uc : UCs) {
            if (uc.getCode() == cadeira) {
                int len = uc.getClasses().size();
                Class cl = uc.getClasses()[len/2]
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
                Aula aula = new Aula(uc, dia, hora, duracao, tipo, cl);
                cl.addAula(aula);
                break;
            }
        }

    }
}

void readClassesPerUC(vector<UC> UCs) {
    ifstream infile("data/classes_per_uc.cvs");
    string line;
    while (getline(infile, line, ',')) {
        istringstream iss(line);
        string uccode, classcode;
        line >> uccode >> classcode;
        for (UC uc : UCs) {
            if (uc.getCode() == uccode) {
                Class cl = new Class(classcode, uc);
                uc.addClass(cl)
                break;
            }
            UC uc = new UC(uccode);
            Class cl = new Class(classcode, uc);
            uc.addClass(cl);
            UCs.push_back(u);
        }
    }
}

void readStudentsClasses(vector<UC> UCs, vector<Student> students) {
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
        if (!(student_exists)) { Student s = new Student(codigo, nome); }
        for(UC uc : UCs) {
            if (uc.getCode() == cadeira){
                int len = uc.getClasses().size();
                Class cl = uc.getClasses()[len/2];
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
}

int main() {


    ifstream infile("data/classes.cvs");
    string line;
    vector<UC> UCs;
    vector<Student> students;

    readClassesPerUC(UCs);
    readClasses(UCs);
    readStudentsClasses(UCs, students);
    /*
    for (UC uc : UCs) {
        for (Class c : uc.getClasses()) {
            cout << c.getCode();
        }
    }*/

    return;
}