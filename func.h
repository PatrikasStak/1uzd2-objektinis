/**
 * @file func.h
 * @brief Pagalbinės funkcijos studentų duomenų valdymui.
 */

#ifndef FUNC_H
#define FUNC_H

#include "Studentas.h"

/// Studentų vektorius (custom Vector konteineris)
using StudentVec = Vector<Studentas>;
/// Studentų sąrašas
using StudentList = std::list<Studentas>;
/// Studentų dekas
using StudentDeque = std::deque<Studentas>;

/**
 * @brief Interaktyviai skaito studentų duomenis iš konsolės.
 *
 * Siūlo tris įvesties būdus: rankinį, atsitiktinių pažymių arba
 * visiškai atsitiktinių duomenų generavimą.
 * @param X Vektorius, į kurį pridedami studentai
 */
void Skaityti(Vector<Studentas>& X);

/**
 * @brief Skaito studentų duomenis iš failo.
 *
 * Nuskaito antraštę, nustato ND stulpelių skaičių ir nuskaito
 * studentų įrašus. Matuoja ir išveda nuskaitymo laiką.
 * @param X Vektorius, į kurį pridedami studentai
 */
void SkaitytiFaila(Vector<Studentas>& X);

/**
 * @brief Skaičiuoja vidurkį iš vektoriau.
 * @param X Studentų vektorius
 * @param x Indeksas (nenaudojamas šiuo metu)
 * @return Vidurkio reikšmė
 */
double Vidurkis(const Vector<Studentas>& X, int x);

/**
 * @brief Skaičiuoja medianą iš vektoriaus.
 * @param X Studentų vektorius
 * @param x Indeksas (nenaudojamas šiuo metu)
 * @return Medianos reikšmė
 */
double Mediana(const Vector<Studentas>& X, int x);

/**
 * @brief Rikiuoja ir išveda rezultatus į konsolę arba failą.
 *
 * Leidžia pasirinkti rikiavimo kriterijų ir išvesties tikslą.
 * @param X Studentų vektorius
 */
void Rezultatas(Vector<Studentas>& X);

/**
 * @brief Rikiuoja ir išveda rezultatus (abi galutinių balų versijas).
 *
 * Išveda ir vidurkio, ir medianos galutinius balus.
 * @param X Studentų vektorius
 */
void RezultatasFailo(Vector<Studentas>& X);

/**
 * @brief Generuoja studentų duomenų failus (1k, 10k, 100k, 1m, 10m).
 *
 * Kiekvienam failui matuoja ir išveda generavimo laiką.
 */
void FailuGeneravimas();

/**
 * @brief Nuskaito, rikiuoja ir skirsto studentus iš failo naudojant vektorių.
 * @param path Failo kelias
 */
void GeneruotuRusiavimasVec(const std::string& path);

/**
 * @brief Nuskaito, rikiuoja ir skirsto studentus iš failo naudojant sąrašą.
 * @param path Failo kelias
 */
void GeneruotuRusiavimasList(const std::string& path);

/**
 * @brief Nuskaito, rikiuoja ir skirsto studentus iš failo naudojant deką.
 * @param path Failo kelias
 */
void GeneruotuRusiavimasDeque(const std::string& path);

/**
 * @brief Ištrina nurodytą failą.
 * @param path Failo kelias
 */
void TrintiFaila(const std::string& path);

#endif
