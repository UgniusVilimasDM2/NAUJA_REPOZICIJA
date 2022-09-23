// Visi tekstai buvo rasomi be lietuvisku raidziu, nes programa vietoj ypatingu raidziu spausdina visokius zenklus
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <numeric>

using std::cout;
using std::string;
using std::cin;
using std::vector;
using std::endl;

using namespace std;

struct Studentas {
    string var;
    string pav;
    int ndSkaicius = 0;
    vector<int> namuDarbai;
    double namuDarbuSuma = 0;
    int egzaminas;
    double galutinis;
};

void Duomenys(Studentas& studentas);
void PazymiaiRanka(Studentas& studentas);
void PazymiaiAtsitiktinai(Studentas& studentas);
double Vidurkis(Studentas studentas);
double Mediana(Studentas studentas);
double Galutinis(Studentas studentas);
void Spausdinimas(Studentas studentas);

int main() {
    int studSkaicius;
    cout << "Studentu skaicius- ";
    cin >> studSkaicius;
    vector<Studentas> stud;
    Studentas S;
    stud.reserve(studSkaicius);

    for (int i = 0; i < studSkaicius; i++) {
        Duomenys(S);
        S.galutinis = Galutinis(S);
        stud.push_back(S);
        S.namuDarbai.clear();
    }

    cout << setw(15) << left << "Vardas" << setw(25) << left << "Pavarde" << setw(15) << left <<
        "Galutinis balas" << endl;
    cout << "--------------------------------------------------------" << endl;
    for (const Studentas& st : stud) {
        Spausdinimas(st);
    }
    return 0;
}

void Duomenys(Studentas& studentas) {
    cout << "vardas - ";
    cin >> studentas.var;
    cout << "pavarde - ";
    cin >> studentas.pav;
    char pasirinkimas;

    cout << "Jeigu pazymius norite vesti ranka, iveskite 'R', o jeigu norite atsitiktiniu pazymiu,"
        " iveskite 'A' - ";
    while (true) {
        cin >> pasirinkimas;
        if (pasirinkimas != 'A' && pasirinkimas != 'R') {
            cout << "jusu ivestis neteisinga, prasome perskaityti instrukcija dar karta ir bandyti vel - ";
        }
        else break;
    }
    if (pasirinkimas == 'A') {
        PazymiaiAtsitiktinai(studentas);
    }
    else if (pasirinkimas == 'R') {
        PazymiaiRanka(studentas);
    }
}

void PazymiaiRanka(Studentas& studentas) {
    cout << "Iveskite Namu darbu rezultatus, pabaige juos rasyti iveskite skaiciu 0 ir spauskite enter - ";
    int ivestis;
    while (cin >> ivestis) {
        if (ivestis != 0) {
            studentas.namuDarbai.push_back(ivestis);
            ++studentas.ndSkaicius;
            studentas.namuDarbuSuma = studentas.namuDarbuSuma + ivestis;
        }
        else break;
    }
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "Egzamino ivertinimas - ";
    cin >> studentas.egzaminas;
    }
}

void PazymiaiAtsitiktinai(Studentas& studentas) {
    srand(time(NULL));
    cout << "irasykite kiek noretumet atsitiktiniu pazymiu - ";
    cin >> studentas.ndSkaicius;
    cout << "kompiuterio parinkti atsitiktiniai namu darbai -  ";
    for (int i = 0; i < studentas.ndSkaicius; i++) {
        studentas.namuDarbai.push_back(rand() % 10 + 1);
        cout << studentas.namuDarbai.at(i) << " ";
    }
    cout << endl;
    studentas.egzaminas = rand() % 10 + 1;
    cout << "Egzamino ivertinimas - " << studentas.egzaminas << endl;
}

double Vidurkis(Studentas studentas) {
    double vidurkis =
        accumulate(studentas.namuDarbai.begin(), studentas.namuDarbai.end(), 0.0) / studentas.namuDarbai.size();
    return vidurkis;
}

double Mediana(Studentas studentas) {
    double mediana;
    sort(studentas.namuDarbai.begin(), studentas.namuDarbai.end());
    int vidurinisElementas = studentas.namuDarbai.size() / 2;
    if (studentas.namuDarbai.size() / 2 == 0) {
        mediana = (studentas.namuDarbai[vidurinisElementas - 1] + studentas.namuDarbai[vidurinisElementas]) / 2.;
    }
    else {
        mediana = studentas.namuDarbai[vidurinisElementas];
    }
    return mediana;
}

double Galutinis(Studentas studentas) {
    char skaiciavimoBudas;
    double vidurkis = Vidurkis(studentas);
    double mediana = Mediana(studentas);
    cout << "iveskite atitinkamai 'V'(vidurkis) arba 'M'(mediana) pagal tai kaip norite"
        " kad butu suskaiciuotas galutinis balas - ";
    double galutinis;

    while (true) {
        cin >> skaiciavimoBudas;
        if (skaiciavimoBudas != 'V' && skaiciavimoBudas != 'M') {
            cout << "Nera tokio pasirinkimo, iveskite is naujo - ";
        }
        else break;
    }
    if (skaiciavimoBudas == 'V') {
        galutinis = vidurkis * 0.4 + studentas.egzaminas * 0.6;
    }
    else if (skaiciavimoBudas == 'M') {
        galutinis = mediana * 0.4 + studentas.egzaminas * 0.6;
    }
    return galutinis;
}

void Spausdinimas(Studentas studentas) {
    cout << fixed;
    cout << setw(15) << left << studentas.var << setw(25) << left << studentas.pav <<
        setw(15) << left << setprecision(2) << studentas.galutinis << endl;
}
