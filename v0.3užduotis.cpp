#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <numeric>
#include <fstream>
#include <chrono>

using namespace std;
struct Studentas {
    string vardas, pavarde;
    vector<int> namuDarbai;
    int egzaminas;
    double galutinis;
};

double Vidurkis(Studentas studentas);
void AtsitiktinisGeneravimas(int& studentuSkaicius, int& namuDarbuSkaicius);
void FailoNustkaitymas(vector<Studentas>& studentai, int studentuSkaicius, int namuDarbuSkaicius);
void SkirstymasIGrupes(int studentuSkaicius, vector<Studentas>& studentai,
    vector<Studentas>& aukstesniojoLygio, vector<Studentas>& zemesniojoLygio);
void Spausdinimas(int studentuSkaicius, const vector<Studentas>& aukstesniojoLygio,
    const vector<Studentas>& zemesniojoLygio);

int main() {

    int namuDarbuSkaicius = 4;
    string pavadinimas;
    int studentuSkaiciai[4] = { 1000, 10000, 100000, 1000000 };
    vector<Studentas> studentai;
    vector<Studentas> aukstesniojoLygio;
    vector<Studentas> zemesniojoLygio;
   
    for (int i : studentuSkaiciai)
    {
        int studentuSkaicius = i;
        AtsitiktinisGeneravimas(studentuSkaicius, namuDarbuSkaicius);
        FailoNustkaitymas(studentai, studentuSkaicius, namuDarbuSkaicius);
        SkirstymasIGrupes(studentuSkaicius, studentai,
            aukstesniojoLygio, zemesniojoLygio);
        Spausdinimas(studentuSkaicius, aukstesniojoLygio, zemesniojoLygio);
    }

    return 0;
}


double Vidurkis(Studentas studentas) {
    double vidurkis =
        accumulate(studentas.namuDarbai.begin(), studentas.namuDarbai.end(), 0.0) / studentas.namuDarbai.size();
    return vidurkis;
}

void AtsitiktinisGeneravimas(int& studentuSkaicius, int& namuDarbuSkaicius) {
    string pavadinimas = "Studentai" + to_string(studentuSkaicius) + ".txt";
    ofstream stud(pavadinimas);
    srand(time(NULL));
    auto start = std::chrono::high_resolution_clock::now(); auto startas = start;
    for (int i = 0; i < studentuSkaicius; i++) {
        stud << "Vardas" + to_string(i + 1) << " " << "Pavarde" + to_string(i + 1) << " ";
        for (int j = 0; j < namuDarbuSkaicius + 1; j++) { 
            stud << rand() % 10 + 1 << " ";
        }
        stud << endl;
    }
    auto end = std::chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start; 
    cout << to_string(studentuSkaicius) << " laikas studentu duomenu generavimo - " << diff.count() << " s\n";
}


void FailoNustkaitymas(vector<Studentas>& studentai, int studentuSkaicius, int namuDarbuSkaicius) {
    int indeksas = 0;
    ifstream fd;
    string pavadinimas = "Studentai" + to_string(studentuSkaicius) + ".txt";
    fd.open(pavadinimas);
    auto start = std::chrono::high_resolution_clock::now(); auto startas = start;
    while (indeksas < studentuSkaicius) {
        studentai.resize(studentai.size() + 1);
        fd >> studentai.at(indeksas).vardas;
        fd >> studentai.at(indeksas).pavarde;
        int ivestis;
        for (int i = 0; i < namuDarbuSkaicius; i++) {
            fd >> ivestis;
            studentai.at(indeksas).namuDarbai.push_back(ivestis);
        }
        fd >> studentai.at(indeksas).egzaminas;
        indeksas++;
    }
    auto end = std::chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start;
    cout << to_string(studentuSkaicius) << " laikas studentu duomenu nuskaitymo - " << diff.count() << " s\n";

}

void SkirstymasIGrupes(int studentuSkaicius, vector<Studentas>& studentai,
    vector<Studentas>& aukstesniojoLygio, vector<Studentas>& zemesniojoLygio) {
    
    for (int i = 0; i < studentuSkaicius; i++) {
        studentai.at(i).galutinis = Vidurkis(studentai.at(i)) * 0.4
            + studentai.at(i).egzaminas * 0.6;
    }
    auto start = std::chrono::high_resolution_clock::now(); auto startas = start;
    for (auto& i : studentai) {
        if (i.galutinis < 5.00) {
            zemesniojoLygio.push_back(i);
        }
        else {
            aukstesniojoLygio.push_back(i);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start;
    cout << "Laikas Studentu skirstymo i grupes - " << diff.count() << " s\n";
}

void Spausdinimas(int studentuSkaicius, const vector<Studentas>& aukstesniojoLygio,
    const vector<Studentas>& zemesniojoLygio) {
    string zemesniujuPavadinimas = "Lûzeriai" + to_string(studentuSkaicius) + ".txt";
    ofstream zem(zemesniujuPavadinimas);
    string aukstesniujuPavadinimas = "moksliukai" + to_string(studentuSkaicius) + ".txt";
    ofstream aukst(aukstesniujuPavadinimas);

    auto start = std::chrono::high_resolution_clock::now(); auto startas = start;
    for (const auto& elementas : zemesniojoLygio) {
        zem << elementas.vardas << " " << elementas.pavarde << " "
            << fixed << setprecision(2) << elementas.galutinis << endl;
    }
    for (const auto& elementas : aukstesniojoLygio) {
        aukst << elementas.vardas << " " << elementas.pavarde << " " << fixed << setprecision(2) <<
            elementas.galutinis << endl;
    }
    auto end = std::chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start;
    cout << "Laikas studentu spausdinimo i failus pagal grupes - " << diff.count() << " s\n";
    cout << "- + - + - + - + - + - + - + - + - + - + - + - + - + - + - + - + - + - + -" << endl;
}
