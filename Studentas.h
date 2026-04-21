#ifndef STUDENTAS_H
#define STUDENTAS_H

#include "Zmogus.h"

class Studentas : public Zmogus {
private:
    std::vector<int> nd_;
    int egz_;
    double galutinis_vid_;
    double galutinis_med_;

public:
    Studentas();

    Studentas(const std::string& vardas, const std::string& pavarde);
    Studentas(const Studentas& other);
    Studentas& operator=(const Studentas& other);
    Studentas(Studentas&& other) noexcept;
    Studentas& operator=(Studentas&& other) noexcept;
    ~Studentas();

    using Zmogus::vardas;
    using Zmogus::pavarde;
    using Zmogus::setVardas;
    using Zmogus::setPavarde;

    inline const std::vector<int>& nd() const { return nd_; }
    inline int egz() const { return egz_; }
    inline double galutinisVid() const { return galutinis_vid_; }
    inline double galutinisMed() const { return galutinis_med_; }

    inline void setEgz(int egz) { egz_ = egz; }
    inline void setGalutinisVid(double galutinis_vid) { galutinis_vid_ = galutinis_vid; }
    inline void setGalutinisMed(double galutinis_med) { galutinis_med_ = galutinis_med; }
    inline void clearNd() { nd_.clear(); }
    inline void addNd(int pazymys) { nd_.push_back(pazymys); }

    std::string tipas() const override;
    void skaiciuotiGalutinius();

    friend std::istream& operator>>(std::istream& is, Studentas& studentas);
    friend std::ostream& operator<<(std::ostream& os, const Studentas& studentas);
};

#endif
