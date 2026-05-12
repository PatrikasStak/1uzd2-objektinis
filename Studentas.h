/**
 * @file Studentas.h
 * @brief Klasė, vaizduojanti studentą, paveldinti iš Zmogus.
 */

#ifndef STUDENTAS_H
#define STUDENTAS_H

#include "Zmogus.h"

/**
 * @class Studentas
 * @brief Vaizduoja studentą su namų darbų pažymiais ir galutiniu balu.
 *
 * Paveldi iš Zmogus ir papildo namų darbų pažymiais, egzamino balu
 * bei apskaičiuotais galutiniais balais (vidurkiu ir mediana).
 * Realizuota pilna Rule of Five: kopijavimo/perkėlimo konstruktoriai,
 * priskyrimo operatoriai ir destruktorius.
 */
class Studentas : public Zmogus {
private:
    Vector<int> nd_;             ///< Namų darbų pažymiai
    int egz_;                    ///< Egzamino balas
    double galutinis_vid_;       ///< Galutinis balas (vidurkio metodas)
    double galutinis_med_;       ///< Galutinis balas (medianos metodas)

public:
    /// Numatytasis konstruktorius — sukuria tuščią studentą.
    Studentas();

    /**
     * @brief Konstruktorius su vardu ir pavarde.
     * @param vardas   Studento vardas
     * @param pavarde  Studento pavardė
     */
    Studentas(const std::string& vardas, const std::string& pavarde);

    /**
     * @brief Kopijavimo konstruktorius.
     * @param other Kopijuojamas objektas
     */
    Studentas(const Studentas& other);

    /**
     * @brief Kopijavimo priskyrimo operatorius.
     * @param other Kopijuojamas objektas
     * @return Nuoroda į šį objektą
     */
    Studentas& operator=(const Studentas& other);

    /**
     * @brief Perkėlimo konstruktorius.
     * @param other Perkeliamas objektas (paliekamas tuščias)
     */
    Studentas(Studentas&& other) noexcept;

    /**
     * @brief Perkėlimo priskyrimo operatorius.
     * @param other Perkeliamas objektas (paliekamas tuščias)
     * @return Nuoroda į šį objektą
     */
    Studentas& operator=(Studentas&& other) noexcept;

    /// Destruktorius — išvalo visus laukus.
    ~Studentas() {
        vardas_.clear();
        pavarde_.clear();
        nd_.clear();
        egz_ = 0;
        galutinis_vid_ = 0.0;
        galutinis_med_ = 0.0;
    }

    using Zmogus::vardas;
    using Zmogus::pavarde;
    using Zmogus::setVardas;
    using Zmogus::setPavarde;

    /**
     * @brief Grąžina namų darbų pažymių sąrašą.
     * @return Const nuoroda į pažymių vektorių
     */
    inline const Vector<int>& nd() const { return nd_; }

    /**
     * @brief Grąžina egzamino balą.
     * @return Egzamino balas
     */
    inline int egz() const { return egz_; }

    /**
     * @brief Grąžina galutinį balą (vidurkio metodas).
     * @return Galutinis vidurkio balas
     */
    inline double galutinisVid() const { return galutinis_vid_; }

    /**
     * @brief Grąžina galutinį balą (medianos metodas).
     * @return Galutinis medianos balas
     */
    inline double galutinisMed() const { return galutinis_med_; }

    /**
     * @brief Nustato egzamino balą.
     * @param egz Naujas egzamino balas
     */
    inline void setEgz(int egz) { egz_ = egz; }

    /**
     * @brief Nustato galutinį vidurkio balą.
     * @param galutinis_vid Galutinis vidurkio balas
     */
    inline void setGalutinisVid(double galutinis_vid) { galutinis_vid_ = galutinis_vid; }

    /**
     * @brief Nustato galutinį medianos balą.
     * @param galutinis_med Galutinis medianos balas
     */
    inline void setGalutinisMed(double galutinis_med) { galutinis_med_ = galutinis_med; }

    /// Išvalo namų darbų pažymių sąrašą.
    inline void clearNd() { nd_.clear(); }

    /**
     * @brief Prideda namų darbo pažymį.
     * @param pazymys Pažymys (0–10)
     */
    inline void addNd(int pazymys) { nd_.push_back(pazymys); }

    /**
     * @brief Grąžina tipo pavadinimą.
     * @return Eilutė "Studentas"
     */
    std::string tipas() const override;

    /**
     * @brief Apskaičiuoja galutinius balus pagal vidurkį ir medianą.
     *
     * Formulė: galutinis = ND_vidurkis * 0.4 + egzaminas * 0.6
     */
    void skaiciuotiGalutinius();

    /**
     * @brief Įveda studento duomenis iš srauto.
     *
     * Formatas: `vardas pavarde nd1 nd2 ... egz`
     * Paskutinis skaičius laikomas egzamino balu.
     * @param is Įvesties srautas
     * @param studentas Objektas, į kurį įvedama
     * @return Nuoroda į įvesties srautą
     */
    friend std::istream& operator>>(std::istream& is, Studentas& studentas);

    /**
     * @brief Išveda studento duomenis į srautą.
     * @param os Išvesties srautas
     * @param studentas Išvedamas objektas
     * @return Nuoroda į išvesties srautą
     */
    friend std::ostream& operator<<(std::ostream& os, const Studentas& studentas);
};

#endif
