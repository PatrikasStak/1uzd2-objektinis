#ifndef FUNC_H
#define FUNC_H

#include "lib.h"

class Studentas {
private:
    std::string vardas_;
    std::string pavarde_;
    std::vector<int> nd_;
    int egz_;
    double galutinis_vid_;
    double galutinis_med_;
};


using StudentVec = std::vector<Studentas>;
using StudentList = std::list<Studentas>;
using StudentDeque = std::deque<Studentas>;

void Skaityti(std::vector<Studentas>& X);
void SkaitytiFaila(std::vector<Studentas>& X);
double Vidurkis(const std::vector<Studentas>& X, int x);
double Mediana(const std::vector<Studentas>& X, int x);
void Rezultatas(std::vector<Studentas>& X);
void RezultatasFailo(std::vector<Studentas>& X);
void FailuGeneravimas();
void GeneruotuRusiavimasVec(const std::string& path);
void GeneruotuRusiavimasList(const std::string& path);
void GeneruotuRusiavimasDeque(const std::string& path);
void TrintiFaila(const std::string& path);

#endif
