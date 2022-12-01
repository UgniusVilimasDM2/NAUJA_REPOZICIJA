#include "libraries.h"
int main() {

    void NuskaitymasKLASE(vector<Studentas> &studentai, int studentuSkaicius, int namuDarbuSkaicius);

    void SkirstymasIGrupesKLASE(vector<Studentas> &studentai,
        vector<Studentas> &aukstesniojoLygio, vector<Studentas> &zemesniojoLygio);

    void SpausdinimasKLASE(int studentuSkaicius, const vector<Studentas> &aukstesniojoLygio,
        const vector<Studentas> &zemesniojoLygio);

    int namuDarbuSkaicius = 4;
    string pavadinimas;
    int studentuSkaiciai[2] = { 100000, 1000000 };

    vector<Studentas> studentai;
    vector<Studentas> aukstesniojoLygio;
    vector<Studentas> zemesniojoLygio;

    for (int i : studentuSkaiciai) {
        int studentuSkaicius = i;
        NuskaitymasKLASE(studentai, studentuSkaicius, namuDarbuSkaicius);
        SkirstymasIGrupesKLASE(studentai, aukstesniojoLygio, zemesniojoLygio);
        SpausdinimasKLASE(studentuSkaicius, aukstesniojoLygio, zemesniojoLygio);
        studentai.clear();
        aukstesniojoLygio.clear();
        zemesniojoLygio.clear();
    }

    return 0;
}

void NuskaitymasKLASE(vector<Studentas>& studentai, int studentuSkaicius, int namuDarbuSkaicius) {
    studentai.reserve(studentuSkaicius);
    ifstream fd;
    string pavadinimas = "Studentai" + to_string(studentuSkaicius) + ".txt";
    fd.open(pavadinimas);
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < studentuSkaicius; i++)
    {
        Studentas laikinas;
        laikinas.readStudentas(fd, namuDarbuSkaicius);
        studentai.push_back(laikinas);
    }
    fd.close();

    auto end = std::chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start;
    cout << to_string(studentuSkaicius) << " studentu duomenu nuskaitymas "
        "uztruko (naudojant CLASS): " << diff.count() << " s\n";

}


void SkirstymasIGrupesKLASE(vector<Studentas>& studentai,
    vector<Studentas>& aukstesniojoLygio, vector<Studentas>& zemesniojoLygio) {

    auto start = std::chrono::high_resolution_clock::now();
    for (auto& i : studentai) {
        if (i.getGalutinis() < 5.00) {
            zemesniojoLygio.push_back(i);
        }
        else {
            aukstesniojoLygio.push_back(i);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start;
    cout << "Studentu skirstymas i grupes uztruko (naudojant CLASS): " << diff.count() << " s\n";
}

void SpausdinimasKLASE(int studentuSkaicius, const vector<Studentas>& aukstesniojoLygio,
    const vector<Studentas>& zemesniojoLygio) {
    string zemesniujuPavadinimas = "ÞemesniojoLygioStudentai_klase" + to_string(studentuSkaicius) + ".txt";
    ofstream zem(zemesniujuPavadinimas);
    string aukstesniujuPavadinimas = "AukðtesniojoLygioStudentai_klase" + to_string(studentuSkaicius) + ".txt";
    ofstream aukst(aukstesniujuPavadinimas);

    for (Studentas elementas : zemesniojoLygio) {
        zem << elementas.getVardas() << " " << elementas.getPavarde() << " "
            << fixed << setprecision(2) << elementas.getGalutinis() << endl;
    }
    for (Studentas elementas : aukstesniojoLygio) {
        aukst << elementas.getVardas() << " " << elementas.getPavarde() << " " << fixed << setprecision(2) <<
            elementas.getGalutinis() << endl;
    }
    cout << "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << endl;
}

Studentas::Studentas(ifstream& fd, int namuDarbuSkaicius)
{
    readStudentas(fd, namuDarbuSkaicius);
}


double Studentas::getGalutinis() {
    double galutinis = 0.4 * (accumulate(this->namuDarbai.begin(), this->namuDarbai.end(), 0.0)
        / this->namuDarbai.size()) + 0.6 * this->egzaminas;
    return galutinis;
}

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

