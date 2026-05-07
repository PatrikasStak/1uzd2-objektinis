/**
 * @file Zmogus.h
 * @brief Abstrakti bazinė klasė, vaizduojanti žmogų.
 */

#ifndef ZMOGUS_H
#define ZMOGUS_H

#include "lib.h"

/**
 * @class Zmogus
 * @brief Abstrakti bazinė klasė su vardu ir pavarde.
 *
 * Negali būti instancijuojama tiesiogiai — reikalauja realizuoti grynai
 * virtualų metodą tipas().
 */
class Zmogus {
protected:
    std::string vardas_;   ///< Asmens vardas
    std::string pavarde_;  ///< Asmens pavardė

    Zmogus() = default;

    /**
     * @brief Konstruktorius su vardu ir pavarde.
     * @param vardas   Asmens vardas
     * @param pavarde  Asmens pavardė
     */
    Zmogus(const std::string& vardas, const std::string& pavarde)
        : vardas_(vardas), pavarde_(pavarde) {}

public:
    /// Virtualus destruktorius, išvalo vardą ir pavardę.
    virtual ~Zmogus() {
        vardas_.clear();
        pavarde_.clear();
    }

    /**
     * @brief Grąžina vardą.
     * @return Nuoroda į vardą
     */
    inline const std::string& vardas() const { return vardas_; }

    /**
     * @brief Grąžina pavardę.
     * @return Nuoroda į pavardę
     */
    inline const std::string& pavarde() const { return pavarde_; }

    /**
     * @brief Nustato vardą.
     * @param vardas Naujas vardas
     */
    inline void setVardas(const std::string& vardas) { vardas_ = vardas; }

    /**
     * @brief Nustato pavardę.
     * @param pavarde Nauja pavardė
     */
    inline void setPavarde(const std::string& pavarde) { pavarde_ = pavarde; }

    /**
     * @brief Grąžina objekto tipo pavadinimą (grynai virtualus).
     * @return Tipo pavadinimo eilutė
     */
    virtual std::string tipas() const = 0;
};

#endif
