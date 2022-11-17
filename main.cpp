#include "libraries.h"
//1 STRATEGIJA LIST
double LISTNamuDarbuVidurkioSkaiciavimas(Studentas studentas);
void LISTAtsitiktiniuStudentuDuomenuGeneravimas(int& studentuSkaicius, int& namuDarbuSkaicius);
void LISTNuskaitymasIsFailo(list<Studentas>& studentai, int studentuSkaicius, int namuDarbuSkaicius);
void LISTSkirstymasIGrupes(list<Studentas> studentai, list<Studentas>& aukstesniojoLygio,
    list<Studentas>& zemesniojoLygio, int& zemesnioL, int& aukstesnioL);
void LISTSpausdinimas(int studentuSkaicius, list<Studentas>& aukstesniojoLygio,
    list<Studentas>& zemesniojoLygio, int zemesnioL, int aukstesnioL);

double LISTNamuDarbuVidurkioSkaiciavimas(Studentas studentas) {
    double vidurkis =
        accumulate(studentas.namuDarbai.begin(), studentas.namuDarbai.end(), 0.0) / studentas.namuDarbai.size();
    return vidurkis;
}

void LISTAtsitiktiniuStudentuDuomenuGeneravimas(int& studentuSkaicius, int& namuDarbuSkaicius) {
    string pavadinimas = "StudentaiLIST" + to_string(studentuSkaicius) + ".txt";
    ofstream stud(pavadinimas);
    srand(time(NULL));

    for (int i = 0; i < studentuSkaicius; i++) {
        stud << "Vardas" + to_string(i + 1) << " " << "Pavarde" + to_string(i + 1) << " ";
        for (int j = 0; j < namuDarbuSkaicius + 1; j++) { 
            stud << rand() % 10 + 1 << " ";
        }
        stud << endl;
    }
}

void LISTNuskaitymasIsFailo(list<Studentas>& studentai, int studentuSkaicius, int namuDarbuSkaicius) {
    int indeksas = 0;
    ifstream fd;
    string pavadinimas = "StudentaiLIST" + to_string(studentuSkaicius) + ".txt";
    fd.open(pavadinimas);

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
        studentas.galutinis = LISTNamuDarbuVidurkioSkaiciavimas(studentas) * 0.4
            + studentas.egzaminas * 0.6;
        studentai.push_back(studentas);
        indeksas++;
    }
}

void LISTSkirstymasIGrupes(list<Studentas> studentai, list<Studentas>& aukstesniojoLygio,
    list<Studentas>& zemesniojoLygio, int& zemesnioL, int& aukstesnioL) {

    list<Studentas>::iterator it;

    for (it = studentai.begin(); it != studentai.end(); ++it) {
        if (it->galutinis < 5.00) {
            Studentas zemesnis;
            zemesnis.vardas = it->vardas;
            zemesnis.pavarde = it->pavarde;
            zemesnis.galutinis = it->galutinis;
            zemesniojoLygio.push_back(zemesnis);
            zemesnioL++;
        }
        else {
            Studentas aukstesnis;
            aukstesnis.vardas = it->vardas;
            aukstesnis.pavarde = it->pavarde;
            aukstesnis.galutinis = it->galutinis;
            aukstesniojoLygio.push_back(aukstesnis);
            aukstesnioL++;
        }
    }
}

void LISTSpausdinimas(int studentuSkaicius, list<Studentas>& aukstesniojoLygio,
    list<Studentas>& zemesniojoLygio, int zemesnioL, int aukstesnioL) {
    string zemesniujuPavadinimas = "ÞemesniojoLygioStudentaiLIST" + to_string(studentuSkaicius) + ".txt";
    ofstream zem(zemesniujuPavadinimas);
    string aukstesniujuPavadinimas = "AukðtesniojoLygioStudentaiLIST" + to_string(studentuSkaicius) + ".txt";
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
}
// 1 STRATEGIJA VECTOR
double VECTORNamuDarbuVidurkioSkaiciavimas(Studentas studentas);
void VECTORAtsitiktiniuStudentuDuomenuGeneravimas(int& studentuSkaicius, int& namuDarbuSkaicius);
void VECTORNuskaitymasIsFailo(vector<Studentas>& studentai, int studentuSkaicius, int namuDarbuSkaicius);
void VECTORSkirstymasIGrupes(vector<Studentas>& studentai,
    vector<Studentas>& aukstesniojoLygio, vector<Studentas>& zemesniojoLygio);
void VECTORSpausdinimas(int studentuSkaicius, const vector<Studentas>& aukstesniojoLygio,
    const vector<Studentas>& zemesniojoLygio);

double VECTORNamuDarbuVidurkioSkaiciavimas(Studentas studentas) {
    double vidurkis =
        accumulate(studentas.namuDarbai.begin(), studentas.namuDarbai.end(), 0.0) / studentas.namuDarbai.size();
    return vidurkis;
}
void VECTORAtsitiktiniuStudentuDuomenuGeneravimas(int& studentuSkaicius, int& namuDarbuSkaicius) {
    string pavadinimas = "StudentaiVECTOR" + to_string(studentuSkaicius) + ".txt";
    ofstream stud(pavadinimas);
    srand(time(NULL));

    for (int i = 0; i < studentuSkaicius; i++) {
        stud << "Vardas" + to_string(i + 1) << " " << "Pavarde" + to_string(i + 1) << " ";
        for (int j = 0; j < namuDarbuSkaicius + 1; j++) { //+1 nes prisideda egzamino pazymys
            stud << rand() % 10 + 1 << " ";
        }
        stud << endl;
    }
}

void VECTORNuskaitymasIsFailo(vector<Studentas>& studentai, int studentuSkaicius, int namuDarbuSkaicius) {
    int indeksas = 0;
    ifstream fd;
    string pavadinimas = "StudentaiVECTOR" + to_string(studentuSkaicius) + ".txt";
    fd.open(pavadinimas);

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
        studentai.at(indeksas).galutinis = VECTORNamuDarbuVidurkioSkaiciavimas(studentai.at(indeksas)) * 0.4
            + studentai.at(indeksas).egzaminas * 0.6;
        indeksas++;
    }
}

void VECTORSkirstymasIGrupes(vector<Studentas>& studentai,
    vector<Studentas>& aukstesniojoLygio, vector<Studentas>& zemesniojoLygio) {

    for (auto& i : studentai) {
        if (i.galutinis < 5.00) {
            zemesniojoLygio.push_back(i);
        }
        else {
            aukstesniojoLygio.push_back(i);
        }
    }
}

void VECTORSpausdinimas(int studentuSkaicius, const vector<Studentas>& aukstesniojoLygio,
    const vector<Studentas>& zemesniojoLygio) {
    string zemesniujuPavadinimas = "ÞemesniojoLygioStudentaiVECTOR" + to_string(studentuSkaicius) + ".txt";
    ofstream zem(zemesniujuPavadinimas);
    string aukstesniujuPavadinimas = "AukðtesniojoLygioStudentaiVECTOR" + to_string(studentuSkaicius) + ".txt";
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
//2 STRATEGIJA LIST
double LIST2NamuDarbuVidurkioSkaiciavimas(Studentas studentas);
void LIST2AtsitiktiniuStudentuDuomenuGeneravimas(int& studentuSkaicius, int& namuDarbuSkaicius);
void LIST2NuskaitymasIsFailo(list<Studentas>& studentai, int studentuSkaicius, int namuDarbuSkaicius);
void LIST2SkirstymasIGrupes(list<Studentas>& studentai, list<Studentas>& zemesniojoLygio, int& zemesnioL, int& aukstesnioL);
bool Palyginimas2(Studentas studentas);
void LIST2Spausdinimas(int studentuSkaicius, list<Studentas>& studentai,
    list<Studentas>& zemesniojoLygio, int zemesnioL, int aukstesnioL);

double LIST2NamuDarbuVidurkioSkaiciavimas(Studentas studentas) {
    double vidurkis =
        accumulate(studentas.namuDarbai.begin(), studentas.namuDarbai.end(), 0.0) / studentas.namuDarbai.size();
    return vidurkis;
}

void LIST2AtsitiktiniuStudentuDuomenuGeneravimas(int& studentuSkaicius, int& namuDarbuSkaicius) {
    string pavadinimas = "StudentaiLIST2_" + to_string(studentuSkaicius) + ".txt";
    ofstream stud(pavadinimas);
    srand(time(NULL));
    for (int i = 0; i < studentuSkaicius; i++) {
        stud << "Vardas" + to_string(i + 1) << " " << "Pavarde" + to_string(i + 1) << " ";
        for (int j = 0; j < namuDarbuSkaicius + 1; j++) { //+1 nes prisideda egzamino pazymys
            stud << rand() % 10 + 1 << " ";
        }
        stud << endl;
    }
}

void LIST2NuskaitymasIsFailo(list<Studentas>& studentai, int studentuSkaicius, int namuDarbuSkaicius) {
    int indeksas = 0;
    ifstream fd;
    string pavadinimas = "StudentaiLIST2_" + to_string(studentuSkaicius) + ".txt";
    fd.open(pavadinimas);
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
        studentas.galutinis = LIST2NamuDarbuVidurkioSkaiciavimas(studentas) * 0.4
            + studentas.egzaminas * 0.6;
        studentai.push_back(studentas);
        indeksas++;
    }
}

void
LIST2SkirstymasIGrupes(list<Studentas>& studentai, list<Studentas>& zemesniojoLygio, int& zemesnioL, int& aukstesnioL) {

    list<Studentas>::iterator it;

    for (it = studentai.begin(); it != studentai.end(); ++it) {
        if (it->galutinis < 5.00) {
            Studentas zemesnis;
            zemesnis.vardas = it->vardas;
            zemesnis.pavarde = it->pavarde;
            zemesnis.galutinis = it->galutinis;
            zemesniojoLygio.push_back(zemesnis);
            zemesnioL++;
            aukstesnioL--;
        }
    }
    studentai.remove_if(Palyginimas2);
}

bool Palyginimas2(Studentas studentas) {
    return studentas.galutinis < 5.00;
}

void LIST2Spausdinimas(int studentuSkaicius, list<Studentas>& studentai,
    list<Studentas>& zemesniojoLygio, int zemesnioL, int aukstesnioL) {
    string zemesniujuPavadinimas = "ÞemesniojoLygioStudentaiLIST2_" + to_string(studentuSkaicius) + ".txt";
    ofstream zem(zemesniujuPavadinimas);
    string aukstesniujuPavadinimas = "AukðtesniojoLygioStudentaiLIST2_" + to_string(studentuSkaicius) + ".txt";
    ofstream aukst(aukstesniujuPavadinimas);

    for (Studentas zemesnis : zemesniojoLygio) {
        zem << zemesnis.vardas << " " <<
            zemesnis.pavarde << " " << fixed << setprecision(2) <<
            zemesnis.galutinis << endl;
    }
    for (Studentas aukstesnis : studentai) {
        aukst << aukstesnis.vardas << " " <<
            aukstesnis.pavarde << " " << fixed << setprecision(2) <<
            aukstesnis.galutinis << endl;
    }
    zemesniojoLygio.clear();
    studentai.clear();
}
//2 STRATEGIJA VECTOR
double VECTOR2NamuDarbuVidurkioSkaiciavimas(Studentas studentas);
void VECTOR2AtsitiktiniuStudentuDuomenuGeneravimas(int& studentuSkaicius, int& namuDarbuSkaicius);
void VECTOR2NuskaitymasIsFailo(vector<Studentas>& studentai, int studentuSkaicius, int namuDarbuSkaicius);
void VECTOR2SkirstymasIGrupes(vector<Studentas>& studentai, vector<Studentas>& zemesniojoLygio);
bool Palyginimas(Studentas studentas);
void VECTOR2Spausdinimas(int studentuSkaicius, const vector<Studentas>& studentai,
    const vector<Studentas>& zemesniojoLygio);

double VECTOR2NamuDarbuVidurkioSkaiciavimas(Studentas studentas) {
    double vidurkis =
        accumulate(studentas.namuDarbai.begin(), studentas.namuDarbai.end(), 0.0) / studentas.namuDarbai.size();
    return vidurkis;
}

void VECTOR2AtsitiktiniuStudentuDuomenuGeneravimas(int& studentuSkaicius, int& namuDarbuSkaicius) {
    string pavadinimas = "StudentaiVECTOR2_" + to_string(studentuSkaicius) + ".txt";
    ofstream stud(pavadinimas);
    srand(time(NULL));
    for (int i = 0; i < studentuSkaicius; i++) {
        stud << "Vardas" + to_string(i + 1) << " " << "Pavarde" + to_string(i + 1) << " ";
        for (int j = 0; j < namuDarbuSkaicius + 1; j++) { //+1 nes prisideda egzamino pazymys
            stud << rand() % 10 + 1 << " ";
        }
        stud << endl;
    }
}

void VECTOR2NuskaitymasIsFailo(vector<Studentas>& studentai, int studentuSkaicius, int namuDarbuSkaicius) {
    int indeksas = 0;
    ifstream fd;
    string pavadinimas = "StudentaiVECTOR2_" + to_string(studentuSkaicius) + ".txt";
    fd.open(pavadinimas);

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
        studentai.at(indeksas).galutinis = VECTOR2NamuDarbuVidurkioSkaiciavimas(studentai.at(indeksas)) * 0.4
            + studentai.at(indeksas).egzaminas * 0.6;
        indeksas++;
    }
}

void VECTOR2SkirstymasIGrupes(vector<Studentas>& studentai, vector<Studentas>& zemesniojoLygio) {

    for (auto it = studentai.begin(); it != studentai.end(); ++it) {
        if (it->galutinis < 5.00) {
            zemesniojoLygio.push_back(*it);
        }
    }
    remove_if(studentai.begin(), studentai.end(), Palyginimas);
}

bool Palyginimas(Studentas studentas) {
    return studentas.galutinis < 5.00;
}

void VECTOR2Spausdinimas(int studentuSkaicius, const vector<Studentas>& studentai,
    const vector<Studentas>& zemesniojoLygio) {
    string zemesniujuPavadinimas = "ÞemesniojoLygioStudentaiVECTOR2_" + to_string(studentuSkaicius) + ".txt";
    ofstream zem(zemesniujuPavadinimas);
    string aukstesniujuPavadinimas = "AukðtesniojoLygioStudentaiVECTOR2_" + to_string(studentuSkaicius) + ".txt";
    ofstream aukst(aukstesniujuPavadinimas);

    for (const auto& elementas : zemesniojoLygio) {
        zem << elementas.vardas << " " << elementas.pavarde << " "
            << fixed << setprecision(2) << elementas.galutinis << endl;
    }
    for (const auto& elementas : studentai) {
        aukst << elementas.vardas << " " << elementas.pavarde << " " << fixed << setprecision(2) <<
            elementas.galutinis << endl;
    }
}
// MAIN IÐVEDIMO DALIS
int main() {

    int namuDarbuSkaicius = 4;
    string pavadinimas;
    int studentuSkaiciai[1] = { 100000 };
    
    //Pirma strategija
    cout << "<PIRMOS STRATEGIJOS ANALIZE>" << endl;

    //    LIST
    cout << "LIST - " << endl;
    list<Studentas> studentai;
    list<Studentas> aukstesniojoLygio;
    list<Studentas> zemesniojoLygio;

    int aukstesnioL = 0;
    int zemesnioL = 0;
    auto start = std::chrono::high_resolution_clock::now();
    auto startas = start;
    for (int i : studentuSkaiciai) {
        int studentuSkaicius = i;
        LISTAtsitiktiniuStudentuDuomenuGeneravimas(studentuSkaicius, namuDarbuSkaicius);
        LISTNuskaitymasIsFailo(studentai, studentuSkaicius, namuDarbuSkaicius);
        LISTSkirstymasIGrupes(studentai, aukstesniojoLygio, zemesniojoLygio, zemesnioL, aukstesnioL);
        LISTSpausdinimas(studentuSkaicius, aukstesniojoLygio, zemesniojoLygio, zemesnioL, aukstesnioL);
    }
    auto end = std::chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start;
    cout << "Programos veikimo laikas naudojant 1 strategija su list - " << diff.count() << " s\n";
    cout << "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;


    //    VECTOR
    vector<Studentas> studentaiVector;
    vector<Studentas> aukstesniojoLygioVector;
    vector<Studentas> zemesniojoLygioVector;

    cout << "VECTOR - " << endl;
    auto start2 = std::chrono::high_resolution_clock::now();
    auto startas2 = start2;
    for (int i : studentuSkaiciai) {
        int studentuSkaicius = i;
        VECTORAtsitiktiniuStudentuDuomenuGeneravimas(studentuSkaicius, namuDarbuSkaicius);
        VECTORNuskaitymasIsFailo(studentaiVector, studentuSkaicius, namuDarbuSkaicius);
        VECTORSkirstymasIGrupes(studentaiVector, aukstesniojoLygioVector, zemesniojoLygioVector);
        VECTORSpausdinimas(studentuSkaicius, aukstesniojoLygioVector, zemesniojoLygioVector);
    }
    auto end2 = std::chrono::high_resolution_clock::now();
    chrono::duration<double> diff2 = end2 - start2;
    cout << "Programos veikimo laikas naudojant 1 strategija su vector -  " << diff2.count() << " s\n";
    cout << "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;

    //Antra strategija
    cout << "<ANTROS STRATEGIJOS ANALIZE>" << endl;

    //    LIST2
    cout << "LIST -" << endl;

    list<Studentas> studentaiLIST2;
    list<Studentas> zemesniojoLygioLIST2;

    int zemesnioL2 = 0;
    auto startlist2 = std::chrono::high_resolution_clock::now();
    auto startaslist2 = startlist2;
    for (int i : studentuSkaiciai) {
        int aukstesnioL2 = i;
        int studentuSkaicius = i;
        LIST2AtsitiktiniuStudentuDuomenuGeneravimas(studentuSkaicius, namuDarbuSkaicius);
        LIST2NuskaitymasIsFailo(studentaiLIST2, studentuSkaicius, namuDarbuSkaicius);
        LIST2SkirstymasIGrupes(studentaiLIST2, zemesniojoLygioLIST2, zemesnioL2, aukstesnioL2);
        LIST2Spausdinimas(studentuSkaicius, studentaiLIST2, zemesniojoLygioLIST2, zemesnioL2, aukstesnioL2);
    }
    auto endlist2 = std::chrono::high_resolution_clock::now();
    chrono::duration<double> difflist2 = endlist2 - startlist2;
    cout << "Programos veikimo laikas naudojant 2 strategijà su list -  " << difflist2.count() << " s\n";
    cout << "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;

    //    VECTOR2

    vector<Studentas> studentaiVector2;
    vector<Studentas> zemesniojoLygioVector2;

    cout << "VECTOR - " << endl;
    auto start2vec = std::chrono::high_resolution_clock::now();
    auto startas2vec = start2vec;
    for (int i : studentuSkaiciai) {
        int studentuSkaicius = i;
        VECTOR2AtsitiktiniuStudentuDuomenuGeneravimas(studentuSkaicius, namuDarbuSkaicius);
        VECTOR2NuskaitymasIsFailo(studentaiVector2, studentuSkaicius, namuDarbuSkaicius);
        VECTOR2SkirstymasIGrupes(studentaiVector2, zemesniojoLygioVector2);
        VECTOR2Spausdinimas(studentuSkaicius, studentaiVector2, zemesniojoLygioVector2);
    }
    auto end2vec = std::chrono::high_resolution_clock::now();
    chrono::duration<double> diff2vec = end2vec - start2vec;
    cout << "Programos veikimo laikas naudojant 2 strategijà su vector - " << diff2vec.count() << " s\n";
    cout << "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;

    return 0;
}