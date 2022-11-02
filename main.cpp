#include "UC.h"
#include "Class.h"
#include "Student.h"
#include "Aula.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ifstream infile("data/classes.cvs");
    string line;
    vector<UC> UCs;
    vector<Student> students;

    while (getline(infile, line, ',')) {
        istringstream iss(line);
        string turma, cadeira, dia, tipo;
        float hora, duracao;
        line >> turma >> cadeira >> dia >> hora >> duracao >> tipo;
        for (UC uc : UCs) {
            if (uc.getCode() == cadeira) {
                for (Class cl : uc.getClasses()) {
                    if (cl.getCode() == turma) {
                        Aula a = new Aula(uc, dia, hora, duracao, tipo, cl);
                        cl.addAula(a);
                        break;
                    }
                    Class c = new Class(turma, uc);
                    Aula a = new Aula(uc, dia, hora, duracao, tipo, cl);
                    c.addAula(a);
                    uc.addClass(c);
                }
                break;
            }
            UC u = new UC(cadeira);
            Class c = new Class(turma, uc);
            Aula a = new Aula(uc, dia, hora, duracao, tipo, cl);
            c.addAula(a);
            u.addClass(c);
            UCs.push_back(u);
        }
    }
    /*
    for (UC uc : UCs) {
        for (Class c : uc.getClasses()) {
            cout << c.getCode();
        }
    }*/

    return;
}