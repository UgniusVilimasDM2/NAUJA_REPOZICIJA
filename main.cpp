#include "libraries.h"
int main() {

    void NuskaitymasKLASE(vector<Studentas> &studentai, int studentuSkaicius, int namuDarbuSkaicius);

    void SkirstymasIGrupesKLASE(vector<Studentas> &studentai,
        vector<Studentas> &aukstesniojoLygio, vector<Studentas> &zemesniojoLygio);

    void SpausdinimasKLASE(int studentuSkaicius, const vector<Studentas> &aukstesniojoLygio,
        const vector<Studentas> &zemesniojoLygio);

    void NuskaitymasIsFailo(vector<StudentasStruct> &studentai, int studentuSkaicius, int namuDarbuSkaicius);

    void SkirstymasIGrupes(vector<StudentasStruct> &studentai,
        vector<StudentasStruct> &aukstesniojoLygio, vector<StudentasStruct> &zemesniojoLygio);

    void Spausdinimas(int studentuSkaicius, const vector<StudentasStruct> &aukstesniojoLygio,
        const vector<StudentasStruct> &zemesniojoLygio);



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

    vector<StudentasStruct> studentaiStruct;
    vector<StudentasStruct> aukstesniojoLygioStruct;
    vector<StudentasStruct> zemesniojoLygioStruct;

    for (int i : studentuSkaiciai) {
        int studentuSkaicius = i;
        NuskaitymasIsFailo(studentaiStruct, studentuSkaicius, namuDarbuSkaicius);
        SkirstymasIGrupes(studentaiStruct, aukstesniojoLygioStruct, zemesniojoLygioStruct);
        Spausdinimas(studentuSkaicius, aukstesniojoLygioStruct, zemesniojoLygioStruct);
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
    cout << "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << endl;
}

double NamuDarbuVidurkioSkaiciavimas(StudentasStruct studentas) {
    double vidurkis =
        accumulate(studentas.namuDarbai.begin(), studentas.namuDarbai.end(), 0.0) / studentas.namuDarbai.size();
    return vidurkis;
}

void NuskaitymasIsFailo(vector<StudentasStruct>& studentai, int studentuSkaicius, int namuDarbuSkaicius) {
    int indeksas = 0;
    ifstream fd;
    string pavadinimas = "Studentai" + to_string(studentuSkaicius) + ".txt";
    fd.open(pavadinimas);
    auto start = std::chrono::high_resolution_clock::now();
    auto startas = start;
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
        studentai.at(indeksas).galutinis = NamuDarbuVidurkioSkaiciavimas(studentai.at(indeksas)) * 0.4
            + studentai.at(indeksas).egzaminas * 0.6;
        indeksas++;
    }
    auto end = std::chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start;
    cout << to_string(studentuSkaicius) << " studentu duomenu nuskaitymas "
        "uztruko (naudojant STRUCT): " << diff.count() << " s\n";
}

void SkirstymasIGrupes(vector<StudentasStruct>& studentai,
    vector<StudentasStruct>& aukstesniojoLygio, vector<StudentasStruct>& zemesniojoLygio) {

    auto start = std::chrono::high_resolution_clock::now();
    auto startas = start;
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
    cout << "Studentu skirstymas i grupes uztruko (naudojant STRUCT): " << diff.count() << " s\n";
}

void Spausdinimas(int studentuSkaicius, const vector<StudentasStruct>& aukstesniojoLygio,
    const vector<StudentasStruct>& zemesniojoLygio) {
    string zemesniujuPavadinimas = "ÞemesniojoLygioStudentai_struct" + to_string(studentuSkaicius) + ".txt";
    ofstream zem(zemesniujuPavadinimas);
    string aukstesniujuPavadinimas = "AukðtesniojoLygioStudentai_struct" + to_string(studentuSkaicius) + ".txt";
    ofstream aukst(aukstesniujuPavadinimas);

    for (const auto& elementas : zemesniojoLygio) {
        zem << elementas.vardas << " " << elementas.pavarde << " "
            << fixed << setprecision(2) << elementas.galutinis << endl;
    }
    for (const auto& elementas : aukstesniojoLygio) {
        aukst << elementas.vardas << " " << elementas.pavarde << " " << fixed << setprecision(2) <<
            elementas.galutinis << endl;
    }
    cout << "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << endl;
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

