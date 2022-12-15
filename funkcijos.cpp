#include "libraries.h"

void NuskaitymasKLASE(vector<Studentas>& studentai, int studentuSkaicius, int namuDarbuSkaicius) {
    studentai.reserve(studentuSkaicius);
    ifstream fd;
    string pavadinimas = "Studentai" + to_string(studentuSkaicius) + ".txt";
    fd.open(pavadinimas);
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < studentuSkaicius; i++)
    {
        /** perskaito informacija apie kiekviena studenta ið duoto failo*/
        Studentas laikinas;
        laikinas.readStudentas(fd, namuDarbuSkaicius);
        studentai.push_back(laikinas);
    }
    fd.close();

    auto end = std::chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start;
    cout << to_string(studentuSkaicius) << " studentu duomenu nuskaitymas "
        "uztruko (naudojant CLASS) - " << diff.count() << " s\n";

}


void SkirstymasIGrupesKLASE(vector<Studentas>& studentai,
    vector<Studentas>& aukstesniojoLygio, vector<Studentas>& zemesniojoLygio) {

    auto start = std::chrono::high_resolution_clock::now();
    /** studentai yra suskirstomi á atskiras grupes pagal tai kokius pazymius gavo ir koks buvo galutinis ivertinimas*/
    for (auto& i : studentai) {
        /** jei studento galutinis pazymys buvo mazesnis nei 5, studentas buvo dedamas á zemesniojo lygio grupe*/
        if (i.getGalutinis() < 5.00) {
            zemesniojoLygio.push_back(i);
        }
        /** automatiðkai visi kiti, turëjo galutini pazymi didesni negu 5, todël dedami á aukðtesniojo lygio grupe*/
        else {
            aukstesniojoLygio.push_back(i);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start;
    cout << "Studentu skirstymas i grupes uztruko (naudojant CLASS) - " << diff.count() << " s\n";
}

void SpausdinimasKLASE(int studentuSkaicius, const vector<Studentas>& aukstesniojoLygio,
    const vector<Studentas>& zemesniojoLygio) {
    /** zemesniojo ir aukstesniojo lygio studentu failu kurimas*/
    string zemesniujuPavadinimas = "ÞemesniojoLygioStudentai_klase" + to_string(studentuSkaicius) + ".txt";
    ofstream zem(zemesniujuPavadinimas);
    string aukstesniujuPavadinimas = "AukðtesniojoLygioStudentai_klase" + to_string(studentuSkaicius) + ".txt";
    ofstream aukst(aukstesniujuPavadinimas);

    /** po sukurtu failu, jie yra pildomi suskaiciuotais galutiniais pazymiais*/
    for (Studentas elementas : zemesniojoLygio) {
        zem << elementas.getVardas() << " " << elementas.getPavarde() << " "
            << fixed << setprecision(2) << elementas.getGalutinis() << endl;
    }
    for (Studentas elementas : aukstesniojoLygio) {
        aukst << elementas.getVardas() << " " << elementas.getPavarde() << " " << fixed << setprecision(2) <<
            elementas.getGalutinis() << endl;
    }
    cout << "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << endl;
}