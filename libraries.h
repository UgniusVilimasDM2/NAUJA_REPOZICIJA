#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <numeric>
#include <fstream>
#include <chrono>
using namespace std;
/** klasë "studentas" yra naudojama funkciju nuskaitymui, pazymiu skaiciavimui ir t.t.*/

/** abstrakti klase "zmogus"*/
class Zmogus {
protected:
    string vardas;
    string pavarde;
public:
    /** construktorius*/
    Zmogus() {};
    /** destruktorius*/
    ~Zmogus() {};
    /** virtual funkcijos*/
    virtual string getVardas() const = 0;
    virtual string getPavarde() const = 0;
};

/** iðveda klasæ ið klasës "zmogus"*/
class Studentas : public Zmogus {
private:
    vector<int> namuDarbai;
    int egzaminas;
public:
    /** construktorius*/
    Studentas() : egzaminas(0) {};
    Studentas(ifstream& fd, int namuDarbuSkaicius);
    string getVardas() const { return vardas; }
    string getPavarde() const { return pavarde; }
    double getGalutinis();
    void readStudentas(ifstream&, int);

};
