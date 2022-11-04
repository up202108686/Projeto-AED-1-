#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <algorithm>

#include "UcTurma.cpp"
#include "Student.cpp"
#include "Slot.cpp"

using namespace std;

class NameCompare
{
public:
    bool operator() (Student s1, Student s2 )
    {
        return s1.getName()< s2.getName();
    }
};

void EstudantesComMaisUcTurmas(vector<Student> students, int n, bool alfa){
    if(alfa) sort(students.begin(),students.end(),NameCompare());
    for(Student st : students){
        if(st.getTurmas().size()>=n){
            cout << st.getCode() << " | " << st.getName() << " | No de UCs: " << st.getTurmas().size() <<"\n";
        }
    }
}

void displayOcupacaoUcTurmas(vector <UcTurma> &UcTurmas, vector<Student> &Students,  bool Crescente) {
    vector<UcTurma> OcupacaoUcTurmas;
    for (UcTurma uct: UcTurmas) {
        OcupacaoUcTurmas.push_back(uct);
    }

    string Ordenacao = "crescente";
    sort(OcupacaoUcTurmas.begin(), OcupacaoUcTurmas.end());
    if(!Crescente) {
        sort(OcupacaoUcTurmas.rbegin(), OcupacaoUcTurmas.rend());
        Ordenacao = "decrescente";
    }
    cout << "Ordenacao da Ocupacao de UC e Turmas por ordem " << Ordenacao << "\n";
    cout << "\n" << " UcCode   -" << "  ClassCode -" << " Occupation" << "\n";
    for (UcTurma uct2: OcupacaoUcTurmas) {
        cout << ' ' << uct2.getUcCode() << " -  " << uct2.getTurmaCode() << "   - " << uct2.getNumberOfStudents() << "\n";
    }
}

void displayEstudantesEmUcTurma(UcTurma uct, vector<Student> students){
    for (Student st : students){
        for(UcTurma ut : st.getTurmas()){
            if (ut.getUcCode()==uct.getUcCode() && ut.getTurmaCode()==uct.getTurmaCode()){
                cout << st.getCode() << " | " << st.getName() << "\n";
            }
        }
    }
}

void displayHorarioEstudante(int code, vector<Student> students){
    int low = 0;
    int high = students.size()-1;
    while(low!=high){
        int mid = (low+high)/2;
        if (low==mid) break;
        if(students[mid].getCode()==code){
            cout << students[mid].getName() << "\n";
            list<Slot> sl;
            for(UcTurma ut : students[mid].getTurmas()) {
                for (Slot s : ut.getUcTurmaAulas()) sl.push_back(s);
            }
            sl.sort();
            for (Slot s: sl) {
                cout << s.getWeekday() << "," << s.getStart_hour() << "," << s.getDuration() << "," << s.getType()
                     << "\n";
            }
            cout << '\n';
            return;
        }

        if(students[mid].getCode()<code){
            low = mid;
            continue;
        }
        if(students[mid].getCode()>code){
            high = mid;
            continue;
        }
    }
    cout << "O aluno não existe\n";
}

/*void countStudentsPerTurma(vector<UcTurma> &ucturmas, vector<Student> students){
    for (int i = 0; i < ucturmas.size(); i++){
        ucturmas[i].setNStudents(0);
    }
    for (int i = 0; i < students.size(); i++) {
        for (UcTurma ut : students[i].getTurmas()) {
            ut.addNStudents(1);
        }
    }
}*/

bool wouldBeBalanced(string uc_code, string turma_1, string turma_2, vector<Student> students, vector<UcTurma> ucturmas, int limit) {
    //countStudentsPerTurma(ucturmas, students);
    vector<UcTurma> turmas;
    vector<int> students_per_turma;
    for (int i = 0; i < ucturmas.size(); i++) {
        if (ucturmas[i].getUcCode() == uc_code) {
            turmas.push_back(ucturmas[i]);
            students_per_turma.push_back(ucturmas[i].getNumberOfStudents());
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
                        if (((s2.getStart_hour() <= s1.getStart_hour()) && (s1.getStart_hour() < s2.getStart_hour() + s2.getDuration())) || ((s1.getStart_hour() <= s2.getStart_hour()) && (s2.getStart_hour() < s1.getStart_hour() + s1.getDuration()))) {
                            cout << s2.getWeekday() << ", " << s2.getStart_hour() << ", " << s2.getDuration() << '\n';
                            cout << s1.getWeekday() << ", " << s1.getStart_hour() << ", " << s1.getDuration() << '\n';
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
    sort(students.begin(), students.end());
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
            if (classesDontOverlap(students[i], ut2) && wouldBeBalanced(uc_code, turma_1, turma_2, students, ucturmas, limit)) {
                students[i].removeUcTurma(ut1);
                ut1.addNStudents(-1);
                students[i].addUcTurma(ut2);
                ut2.addNStudents(1);
            }
            else { throw_away = true; }
        }
    }
}

void changeSeveralClass(int student_code, vector<string> uc_code, vector<string> turma_1, vector<string> turma_2, vector<Student> &students, vector<UcTurma> ucturmas, bool &throw_away) {
    sort(students.begin(), students.end());
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
                if (classesDontOverlap(students[i], ut) && wouldBeBalanced(uc_code[j], turma_1[j], turma_2[j], students, ucturmas, limit)) {
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
                    ut1.addNStudents(-1);
                    students[i].addUcTurma(ut2);
                    ut2.addNStudents(1);
                }
            }
            else { throw_away = true; }
        }
    }
}

void removeUcFromStudent(vector<Student> &students, int s_code, string uc_code, string turma) {
    sort(students.begin(), students.end());
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
            ut.addNStudents(-1);
            break;
        }
    }
    students[si] = s;
}

void addUcToStudent(vector<Student> &students, vector<UcTurma> ucturmas, int s_code, string name, string uc_code, string turma, bool &is_rejected) {
    sort(students.begin(), students.end());
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
    if (wouldBeBalanced(uc_code, "", turma, students, ucturmas, limit) && classesDontOverlap(s, ut)) {
        s.addUcTurma(ut);
        ut.addNStudents(1);
    }
    else { is_rejected = true; }
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

vector<Student>  readStudentsClasses(vector<UcTurma> &UcTurmas, vector<Student> students) {
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
                    UcTurmas[i].addNStudents(1);
                    students[si] = s;
                    break;
                }
            }
        }
    }
    sort(students.begin(), students.end());
    return students;
}

void processPedido(string pedido, vector<Student> &students, vector<UcTurma> &ucturmas, vector<string> &pedidos_rejeitados) {
    vector<string> p;
    string current;
    bool is_rejected = false;
    for (int i = 0; i < pedido.length(); i++) {
        if (pedido[i] == ' ') {
            p.push_back(current);
            current = "";
        }
        else { current += pedido[i]; }
    }
    p.push_back(current);
    if (p[1] == "RemoverTurma") {
        int s_code = stoi(p[2]);
        string uc_code = p[3];
        string turma = p[4];
        removeUcFromStudent(students, s_code, uc_code, turma);
    }
    else if (p[1] == "AdicionarTurma") {
        int s_code = stoi(p[2]);
        string name = p[5];
        string uc_code = p[3];
        string turma = p[4];
        for (int i = 6; i < p.size(); i++) { name += p[i]; }
        addUcToStudent(students, ucturmas, s_code, name, uc_code, turma, is_rejected);
    }
    else if (p[1] == "TrocarTurma") {
        int s_code = stoi(p[2]);
        string uc_code = p[3];
        string turma_1 = p[4];
        string turma_2 = p[5];
        changeClass(s_code, uc_code, turma_1, turma_2, students, ucturmas, is_rejected);
    }
    else if (p[1] == "TrocarVariasTurmas") {
        int s_code = stoi(p[2]);
        vector<string> uc_codes;
        vector<string> turmas_1;
        vector<string> turmas_2;
        for (int i = 3; i < p.size(); i += 3) {
            uc_codes.push_back(p[i]);
            turmas_1.push_back(p[i+1]);
            turmas_2.push_back(p[i+2]);
        }
        changeSeveralClass(s_code, uc_codes, turmas_1, turmas_2, students, ucturmas, is_rejected);
    }
    if (is_rejected) { pedidos_rejeitados.push_back(pedido); }
}

void displayMenu() {
    cout << '\n' << "Menu:\nhelp\n\nPedidos:\n";
    cout << "pedido RemoverTurma <student code> <uc> <turma>\n";
    cout << "pedido AdicionarTurma <student code> <uc> <turma> <student name>\n";
    cout << "pedido TrocarTurma <student code> <uc> <turma a deixar> <turma a juntar>\n";
    cout << "pedido TrocarVariasTurmas <student code> <uc1> <turma a deixar1> <turma a juntar1> ... <ucn> <turma a deixarn> <turma a juntarn>\n";
    cout << "processPedidos\npedidosRejeitados\n\n";
    cout << "Listagens:\n";
    cout << "horario <student code>\n";
    cout << "estudantesComMaisUcs <min> <ordem alfabetica? s/n>\n";
    cout << "ocupacaoTurmas <crescente/decrescente>\n";
    cout << "estudantesEmTurma <uc> <turma>\n\n";
    cout << "Terminar programa:\nclose\n";
}

void processInput(string input, vector<UcTurma> &ucturmas, vector<Student> &students, vector<string> &pedidos, vector<string> &pedidos_rejeitados) {
    cout << '\n';
    vector<string> p;
    string current;
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == ' ') {
            p.push_back(current);
            current = "";
        }
        else { current += input[i]; }
    }
    p.push_back(current);
    if (p[0] == "pedido") {
        pedidos.push_back(input);
    }
    else if (p[0] == "processPedidos") {
        for (int i = 0; i < pedidos.size(); i++) {
            processPedido(pedidos[i], students, ucturmas, pedidos_rejeitados);
        }
    }
    else if (p[0] == "pedidosRejeitados") {
        for (int i = 0; i < pedidos_rejeitados.size(); i++) {
            cout << pedidos_rejeitados[i] << "\n";
        }
    }
    else if (p[0] == "horario") {
        int s_code = stoi(p[1]);
        displayHorarioEstudante(s_code, students);
    }
    else if (p[0] == "estudantesComMaisUcs") {
        int n = stoi(p[1]);
        bool alfa = false;
        if (p[2] == "s") { alfa = true; }
        EstudantesComMaisUcTurmas(students, n, alfa);
    }
    else if (p[0] == "ocupacaoTurmas") {
        bool crescente = false;
        if (p[1] == "crescente") { crescente = true; }
        displayOcupacaoUcTurmas(ucturmas, students, crescente);
    }
    else if (p[0] == "estudantesEmTurma") {
        string uc_code = p[1]; string turma = p[2];
        UcTurma ut;
        for (int i = 0; i < ucturmas.size(); i++) {
            if (ucturmas[i].getTurmaCode() == turma && ucturmas[i].getUcCode() == uc_code) {
                ut = ucturmas[i];
                break;
            }
        }
        displayEstudantesEmUcTurma(ut, students);
    }
    else if (p[0] == "help") {
        displayMenu();
    }
}


void createNewStudentsFile(vector<Student> students) {
    ofstream ofs ("data/students_classes.csv");
    ofs << "StudentCode,StudentName,UcCode,ClassCode" << "\n";
    for (auto& st: students) {
        list<UcTurma> lut = st.getTurmas();
        for (auto& uct:  lut) {
            ofs << ',' << st.getCode() << ',' << st.getName() << ',' << uct.getUcCode() << ',' << uct.getTurmaCode() << "\n";
        }
    }
}

int main() {
    vector<UcTurma> UcTurmas;
    vector<Student> students;
    UcTurmas = readClassesPerUC(UcTurmas);
    UcTurmas = readClasses(UcTurmas);
    students = readStudentsClasses(UcTurmas, students);
    vector<string> pedidos;
    vector<string> pedidos_rejeitados;
    string input;
    displayMenu();
    cout << '\n';
    while (input != "close") {
        cout << "Enter input:\n";
        getline(std::cin, input);
        processInput(input, UcTurmas, students, pedidos, pedidos_rejeitados);
    }
    createNewStudentsFile(students);
    return 0;
}
