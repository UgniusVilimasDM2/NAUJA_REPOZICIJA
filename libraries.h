#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <numeric>
#include <fstream>
#include <chrono>
using namespace std;

class Studentas {
private:
    string vardas, pavarde;
    vector<int> namuDarbai;
    int egzaminas;
public:
    Studentas() : egzaminas(0) {}; // konstruktorius

    ~Studentas() // destruktorius
        = default;;

    Studentas(const Studentas& laikinas) // copy konstruktorius
    {
        vardas = laikinas.vardas;
        pavarde = laikinas.pavarde;
        namuDarbai = laikinas.namuDarbai;
        egzaminas = laikinas.egzaminas;
    }

    void swap(Studentas& kitas)
    {
        ::swap(vardas, kitas.vardas);
        ::swap(pavarde, kitas.pavarde);
        ::swap(namuDarbai, kitas.namuDarbai);
        ::swap(egzaminas, kitas.egzaminas);
    }

    // copy assignment konstruktorius
    Studentas& operator = (Studentas kitas) {
        swap(kitas);
        return *this;
    }

    Studentas(ifstream& fd, int namuDarbuSkaicius);
    void readStudentas(ifstream&, int);
    inline string getVardas() const { return vardas; }
    inline string getPavarde() const { return pavarde; }
    double getGalutinis();


};
