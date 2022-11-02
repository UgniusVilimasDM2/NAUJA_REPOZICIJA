#include "libraries.h"

double NamuDarbuVidurkioSkaiciavimasLIST(Studentas studentas);

void NuskaitymasIsFailoLIST(list<Studentas>& studentai, int studentuSkaicius, int namuDarbuSkaicius);

void SkirstymasIGrupesLIST(list<Studentas>& studentai, list<Studentas>& aukstesniojoLygio,
    list<Studentas>& zemesniojoLygio);

void SpausdinimasLIST(int studentuSkaicius, list<Studentas>& aukstesniojoLygio,
    list<Studentas>& zemesniojoLygio);

double NamuDarbuVidurkioSkaiciavimasVECTOR(Studentas studentas);

void NuskaitymasIsFailoVECTOR(vector<Studentas>& studentai, int studentuSkaicius, int namuDarbuSkaicius);

void SkirstymasIGrupesVECTOR(vector<Studentas>& studentai,
    vector<Studentas>& aukstesniojoLygio, vector<Studentas>& zemesniojoLygio);

void SpausdinimasVECTOR(int studentuSkaicius, const vector<Studentas>& aukstesniojoLygio,
    const vector<Studentas>& zemesniojoLygio);


int main() {

    int namuDarbuSkaicius = 4;
    string pavadinimas;
    int studentuSkaiciai[4] = { 1000, 10000, 100000, 1000000};

    list<Studentas> studentaiLIST;
    list<Studentas> aukstesniojoLygioLIST;
    list<Studentas> zemesniojoLygioLIST;

    vector<Studentas> studentaiVECTOR;
    vector<Studentas> aukstesniojoLygioVECTOR;
    vector<Studentas> zemesniojoLygioVECTOR;

    for (int i : studentuSkaiciai) {
        int studentuSkaicius = i;
        cout << to_string(studentuSkaicius) << " studentu skaicius" << endl;
        NuskaitymasIsFailoLIST(studentaiLIST, studentuSkaicius, namuDarbuSkaicius);
        NuskaitymasIsFailoVECTOR(studentaiVECTOR, studentuSkaicius, namuDarbuSkaicius);
        SkirstymasIGrupesLIST(studentaiLIST, aukstesniojoLygioLIST, zemesniojoLygioLIST);
        SkirstymasIGrupesVECTOR(studentaiVECTOR, aukstesniojoLygioVECTOR, zemesniojoLygioVECTOR);
        SpausdinimasLIST(studentuSkaicius, aukstesniojoLygioLIST, zemesniojoLygioLIST);
        SpausdinimasVECTOR(studentuSkaicius, aukstesniojoLygioVECTOR, zemesniojoLygioVECTOR);
        studentaiLIST.clear();
        aukstesniojoLygioLIST.clear();
        zemesniojoLygioLIST.clear();
        studentaiVECTOR.clear();
        aukstesniojoLygioVECTOR.clear();
        zemesniojoLygioVECTOR.clear();
    }
}
    double NamuDarbuVidurkioSkaiciavimasLIST(Studentas studentas) {
        double vidurkis =
            accumulate(studentas.namuDarbai.begin(), studentas.namuDarbai.end(), 0.0) / studentas.namuDarbai.size();
        return vidurkis;
    }


    void NuskaitymasIsFailoLIST(list<Studentas>&studentai, int studentuSkaicius, int namuDarbuSkaicius) {
        int indeksas = 0;
        ifstream fd;
        string pavadinimas = "Studentai" + to_string(studentuSkaicius) + ".txt";
        fd.open(pavadinimas);
        auto start = std::chrono::high_resolution_clock::now();
        auto startas = start;
        while (indeksas < studentuSkaicius) {
            Studentas studentas;
            fd >> studentas.vardas;
            fd >> studentas.pavarde;
            int ivestis;
            for (int i = 0; i < namuDarbuSkaicius; i++) {
                fd >> ivestis;
                studentas.namuDarbai.push_back(ivestis);
            }
            fd >> studentas.egzaminas;
            studentas.galutinis = NamuDarbuVidurkioSkaiciavimasLIST(studentas) * 0.4
                + studentas.egzaminas * 0.6;
            studentai.push_back(studentas);
            indeksas++;
        }
        auto end = std::chrono::high_resolution_clock::now();
        chrono::duration<double> diff = end - start;
        cout << "Duomenu nuskaitymas uztruko (list) - " << diff.count() << " s\n";

    }

    void SkirstymasIGrupesLIST(list<Studentas>&studentai, list<Studentas>&aukstesniojoLygio,
        list<Studentas>&zemesniojoLygio) {

        list<Studentas>::iterator it;

        auto start = std::chrono::high_resolution_clock::now();
        auto startas = start;

        for (it = studentai.begin(); it != studentai.end(); ++it) {
            if (it->galutinis < 5.00) {
                Studentas zemesnis;
                zemesnis.vardas = it->vardas;
                zemesnis.pavarde = it->pavarde;
                zemesnis.galutinis = it->galutinis;
                zemesniojoLygio.push_back(zemesnis);

            }
            else {
                Studentas aukstesnis;
                aukstesnis.vardas = it->vardas;
                aukstesnis.pavarde = it->pavarde;
                aukstesnis.galutinis = it->galutinis;
                aukstesniojoLygio.push_back(aukstesnis);

            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        chrono::duration<double> diff = end - start;
        cout << "Skirstymas i grupes uztruko (list) - " << diff.count() << " s\n";
    }

    void SpausdinimasLIST(int studentuSkaicius, list<Studentas>&aukstesniojoLygio,
        list<Studentas>&zemesniojoLygio) {
        string zemesniujuPavadinimas = "luzeriai" + to_string(studentuSkaicius) + ".txt";
        ofstream zem(zemesniujuPavadinimas);
        string aukstesniujuPavadinimas = "moksliukai" + to_string(studentuSkaicius) + ".txt";
        ofstream aukst(aukstesniujuPavadinimas);

        for (Studentas zemesnis : zemesniojoLygio) {
            zem << zemesnis.vardas << " " <<
                zemesnis.pavarde << " " << fixed << setprecision(2) <<
                zemesnis.galutinis << endl;
        }
        for (Studentas aukstesnis : aukstesniojoLygio) {
            aukst << aukstesnis.vardas << " " <<
                aukstesnis.pavarde << " " << fixed << setprecision(2) <<
                aukstesnis.galutinis << endl;
        }
        zemesniojoLygio.clear();
        aukstesniojoLygio.clear();
        cout << "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << endl;
    }

    double NamuDarbuVidurkioSkaiciavimasVECTOR(Studentas studentas) {
        double vidurkis =
            accumulate(studentas.namuDarbai.begin(), studentas.namuDarbai.end(), 0.0) / studentas.namuDarbai.size();
        return vidurkis;
    }


    void NuskaitymasIsFailoVECTOR(vector<Studentas>& studentai, int studentuSkaicius, int namuDarbuSkaicius) {
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
            studentai.at(indeksas).galutinis = NamuDarbuVidurkioSkaiciavimasVECTOR(studentai.at(indeksas)) * 0.4
                + studentai.at(indeksas).egzaminas * 0.6;
            indeksas++;
        }
        auto end = std::chrono::high_resolution_clock::now();
        chrono::duration<double> diff = end - start;
        cout << "Duomenu nuskaitymas uztruko (vector) - " << diff.count() << " s\n";
    };

    void SkirstymasIGrupesVECTOR(vector<Studentas>& studentai,
        vector<Studentas>& aukstesniojoLygio, vector<Studentas>& zemesniojoLygio) {

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
        cout << "Skirstymas i grupes uztruko (vector) - " << diff.count() << " s\n";
    }

    void SpausdinimasVECTOR(int studentuSkaicius, const vector<Studentas>& aukstesniojoLygio,
        const vector<Studentas>& zemesniojoLygio) {
        string zemesniujuPavadinimas = "luzeriai" + to_string(studentuSkaicius) + ".txt";
        ofstream zem(zemesniujuPavadinimas);
        string aukstesniujuPavadinimas = "moksliukai" + to_string(studentuSkaicius) + ".txt";
        ofstream aukst(aukstesniujuPavadinimas);

        for (const auto& elementas : zemesniojoLygio) {
            zem << elementas.vardas << " " << elementas.pavarde << " "
                << fixed << setprecision(2) << elementas.galutinis << endl;
        }
        for (const auto& elementas : aukstesniojoLygio) {
            aukst << elementas.vardas << " " << elementas.pavarde << " " << fixed << setprecision(2) <<
                elementas.galutinis << endl;
        }
    }
