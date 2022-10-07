#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <vector>
#include <sstream>
#include <numeric>
#include <fstream>

using namespace std;
ifstream fd("/Users/kaktu/Desktop/Objektinis programavimas/kursiokai.txt");

struct Studentas {
    string vardas, pavarde;
    int ndSkaicius = 0;
    vector<int> namuDarbai;
    double namuDarbuSuma = 0;
    int egzaminas;
    double galutinis;
    double galutinisMediana;
    double galutinisVidurkis;
};

void DuomenuIvedimasIrSaugojimas(vector<Studentas> studentai, int& studentuSkaicius);
void DuomenuSuvedimas(Studentas& studentas);
void NuskaitymasIsFailo(Studentas& studentas, int pazymiuSkaicius);
double PazymiuSkaiciavimasFaile(string const& str);
void PazymiaiRanka(Studentas& studentas);
void PazymiaiAtsitiktinai(Studentas& studentas);
double Vidurkis(Studentas studentas);
double Mediana(Studentas studentas);
double Galutinis(Studentas studentas);
void SpausdinimasIKonsole(Studentas studentas);
bool Lyginimas(const Studentas& pirmas, const Studentas& antras);
void SpausdinimasIRezultatuFaila(const vector<Studentas>& studentai);

int main() {
    int studentuSkaicius = 0;
    vector<Studentas> studentai;
    studentai.reserve(10000);
    DuomenuIvedimasIrSaugojimas(studentai, studentuSkaicius);
    return 0;
}

void DuomenuIvedimasIrSaugojimas(vector<Studentas> studentai, int& studentuSkaicius) {
    char duomenuIvedimoBudas;
    cout << "iveskite 'F' jeigu studentu informacija nuskaityti nuo failo arba iveskite 'P' jei norite vesti"
        " patys - ";

    while (true) {
        cin >> duomenuIvedimoBudas;
        if (duomenuIvedimoBudas != 'P' && duomenuIvedimoBudas != 'F') {
            cout << "pasirinkimai buvo 'P' arba 'F', bandyk is naujo";
        }
        else break;
    }
    if (duomenuIvedimoBudas == 'P') {
        cout << "studentu skaicius - ";
        cin >> studentuSkaicius;
        for (int i = 0; i < studentuSkaicius; i++) {
            Studentas laikinas;
            DuomenuSuvedimas(laikinas);
            laikinas.galutinis = Galutinis(laikinas);
            studentai.push_back(laikinas);
            laikinas.namuDarbai.clear();
        }
        for (const Studentas& st : studentai) {
            SpausdinimasIKonsole(st);
        }
    }
    else if (duomenuIvedimoBudas == 'F') {
        studentuSkaicius = 0;
        string pirmojiEilute;
        getline(fd, pirmojiEilute);
        double pazymiuSkaicius = PazymiuSkaiciavimasFaile(pirmojiEilute);
        while (!fd.eof()) {
            Studentas laikinas;
            NuskaitymasIsFailo(laikinas, pazymiuSkaicius);
            laikinas.galutinisVidurkis = 0.4 * Vidurkis(laikinas) + 0.6 * laikinas.egzaminas;
            laikinas.galutinisMediana = 0.4 * Mediana(laikinas) + 0.6 * laikinas.egzaminas;
            studentai.push_back(laikinas);
            ++studentuSkaicius;
        }
        sort(studentai.begin(), studentai.end(), Lyginimas);
        SpausdinimasIRezultatuFaila(studentai);

    }
}

void DuomenuSuvedimas(Studentas& studentas) {
    cout << "Vardas - ";
    cin >> studentas.vardas;
    cout << "pavarde - ";
    cin >> studentas.pavarde;
    char pasirinkimas;

    cout << "Jeigu pazymius norite vesti ranka, iveskite 'R', o jeigu norite atsitiktiniu pazymiu, "
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

void NuskaitymasIsFailo(Studentas& studentas, int pazymiuSkaicius) {
    studentas.namuDarbuSuma = 0;
    char vardas[14];
    char pavarde[24];
    fd.get(vardas, 14);
    studentas.vardas = vardas;
    fd.get(pavarde, 24);
    studentas.pavarde = pavarde;
    int ivestis;
    for (int i = 0; i < pazymiuSkaicius; i++) {
        fd >> ivestis;
        studentas.namuDarbai.push_back(ivestis);
        studentas.namuDarbuSuma += ivestis;
    }
    fd >> studentas.egzaminas;
    fd.clear();
    fd.ignore(256, '\n');
}

double PazymiuSkaiciavimasFaile(string const& stream) {
    stringstream streaming(stream);
    return distance(istream_iterator<string>(streaming), istream_iterator<string>()) - 3;
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

void PazymiaiAtsitiktinai(Studentas& studentas) {
    srand(time(NULL));
    cout << "irasykite kiek noretumet atsitiktiniu pazymiu - ";
    cin >> studentas.ndSkaicius;
    cout << "kompiuterio parinkti atsitiktiniai namu darbai - ";
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

void SpausdinimasIKonsole(Studentas studentas) {
    cout << setw(15) << left << "Vardas" << setw(25) << left << "Pavarde" << setw(15) << left <<
        "Galutinis balas" << endl;
    cout << fixed;
    cout << setw(15) << left << studentas.vardas << setw(25) << left << studentas.pavarde <<
        setw(25) << left << setprecision(2) << studentas.galutinis << endl;
}

bool Lyginimas(const Studentas& pirmas, const Studentas& antras) {
    return pirmas.pavarde < antras.pavarde;
}

void SpausdinimasIRezultatuFaila(const vector<Studentas>& studentai) {
    ofstream fr("/Users/kaktu/Desktop/Objektinis programavimas/kursiokai_rez.txt");
    fr << "Vardas          " << "Pavarde               " << "Galutinis(Med) " << "Galutinis(Vid)" << endl;
    for (const Studentas& st : studentai) {
        fr << st.vardas << " " << st.pavarde << " " << setprecision(3) << st.galutinisMediana
            << "            " << setprecision(3) << st.galutinisVidurkis << endl;
    }
}
