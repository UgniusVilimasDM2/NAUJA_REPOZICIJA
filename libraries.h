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
    Studentas() : egzaminas(0) {};
    Studentas(ifstream& fd, int namuDarbuSkaicius);
    inline string getVardas() const { return vardas; }
    inline string getPavarde() const { return pavarde; }
    double getGalutinis();
    void readStudentas(ifstream&, int);

};

struct StudentasStruct {
    string vardas, pavarde;
    vector<int> namuDarbai;
    int egzaminas;
    double galutinis;
};

void Studentas::readStudentas(ifstream& fd, int namuDarbuSkaicius) {
    fd >> this->vardas >> this->pavarde;
    this->namuDarbai.reserve(namuDarbuSkaicius);
    for (int i = 0; i < namuDarbuSkaicius; i++)
    {
        int ivestis;
        fd >> ivestis;
        this->namuDarbai.push_back(ivestis);
    }
    fd >> this->egzaminas;
}
