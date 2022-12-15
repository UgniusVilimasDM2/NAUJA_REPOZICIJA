#include "libraries.h"

void NuskaitymasKLASE(vector<Studentas>& studentai, int studentuSkaicius, int namuDarbuSkaicius);

void SkirstymasIGrupesKLASE(vector<Studentas>& studentai,
    vector<Studentas>& aukstesniojoLygio, vector<Studentas>& zemesniojoLygio);

void SpausdinimasKLASE(int studentuSkaicius, const vector<Studentas>& aukstesniojoLygio,
    const vector<Studentas>& zemesniojoLygio);

int main() {

    int namuDarbuSkaicius = 4;
    string pavadinimas;
    /** yra nustatoma kiek bus studentu ir failu*/
    int studentuSkaiciai[2] = { 10000, 100000 };

    vector<Studentas> studentai;
    vector<Studentas> aukstesniojoLygio;
    vector<Studentas> zemesniojoLygio;

    for (int i : studentuSkaiciai) {
        /** funkcijos yra naudojamos failams, kurie buvo duoti atskirai*/
        int studentuSkaicius = i;
        NuskaitymasKLASE(studentai, studentuSkaicius, namuDarbuSkaicius);
        SkirstymasIGrupesKLASE(studentai, aukstesniojoLygio, zemesniojoLygio);
        SpausdinimasKLASE(studentuSkaicius, aukstesniojoLygio, zemesniojoLygio);
        studentai.clear();
        aukstesniojoLygio.clear();
        zemesniojoLygio.clear();
    }
}