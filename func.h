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

public:
    Studentas()
        : egz_(0), galutinis_vid_(0.0), galutinis_med_(0.0) {}

    Studentas(const std::string& vardas, const std::string& pavarde)
        : vardas_(vardas), pavarde_(pavarde), egz_(0), galutinis_vid_(0.0), galutinis_med_(0.0) {}

    ~Studentas() {
        vardas_.clear();
        pavarde_.clear();
        nd_.clear();
        egz_ = 0;
        galutinis_vid_ = 0.0;
        galutinis_med_ = 0.0;
    }

    inline const std::string& vardas() const { return vardas_; }
    inline const std::string& pavarde() const { return pavarde_; }
    inline const std::vector<int>& nd() const { return nd_; }
    inline int egz() const { return egz_; }
    inline double galutinisVid() const { return galutinis_vid_; }
    inline double galutinisMed() const { return galutinis_med_; }

    inline void setVardas(const std::string& vardas) { vardas_ = vardas; }
    inline void setPavarde(const std::string& pavarde) { pavarde_ = pavarde; }
    inline void setEgz(int egz) { egz_ = egz; }
    inline void setGalutinisVid(double galutinis_vid) { galutinis_vid_ = galutinis_vid; }
    inline void setGalutinisMed(double galutinis_med) { galutinis_med_ = galutinis_med; }
    inline void clearNd() { nd_.clear(); }
    inline void addNd(int pazymys) { nd_.push_back(pazymys); }

    void skaiciuotiGalutinius();
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
