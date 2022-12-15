#include "libraries.h"

Studentas::Studentas(ifstream& fd, int namuDarbuSkaicius)
{
    readStudentas(fd, namuDarbuSkaicius);
}

double Studentas::getGalutinis() {
    /** skaiciuojama galutinis balas pagal surinktus namu darbu rezultatus ir egzamino pazymi*/
    double galutinis = 0.4 * (accumulate(this->namuDarbai.begin(), this->namuDarbai.end(), 0.0)
        / this->namuDarbai.size()) + 0.6 * this->egzaminas;
    return galutinis;
}

void Studentas::readStudentas(ifstream& fd, int namuDarbuSkaicius) {
    /** skaito vieno studento informacija*/
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