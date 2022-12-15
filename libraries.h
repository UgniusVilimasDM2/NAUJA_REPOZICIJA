#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <numeric>
#include <fstream>
#include <chrono>
using namespace std;

class Zmogus {
protected:
    string vardas;
    string pavarde;
public:
    Zmogus() {};
    ~Zmogus() {};
    virtual string getVardas() const = 0;
    virtual string getPavarde() const = 0;
};

class Studentas : public Zmogus {
private:
    vector<int> namuDarbai;
    int egzaminas;
public:
    Studentas() : egzaminas(0) {};
    Studentas(ifstream& fd, int namuDarbuSkaicius);
    string getVardas() const { return vardas; }
    string getPavarde() const { return pavarde; }
    double getGalutinis();
    void readStudentas(ifstream&, int);

};