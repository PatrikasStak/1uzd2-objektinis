#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Studentas.h"

#include <cmath>
#include <sstream>
#include <type_traits>
#include <utility>

namespace {

bool almostEqual(double a, double b, double eps = 1e-9) {
    return std::fabs(a - b) < eps;
}

Studentas makeStudent() {
    Studentas s("Jonas", "Jonaitis");
    s.addNd(8);
    s.addNd(9);
    s.addNd(10);
    s.setEgz(9);
    s.skaiciuotiGalutinius();
    return s;
}

}  // namespace

// ---------------------------------------------------------------------------
// Rule of Five
// ---------------------------------------------------------------------------

TEST_CASE("Numatytasis konstruktorius", "[rule_of_five]") {
    Studentas s;
    REQUIRE(s.vardas().empty());
    REQUIRE(s.pavarde().empty());
    REQUIRE(s.nd().empty());
    REQUIRE(s.egz() == 0);
    REQUIRE(almostEqual(s.galutinisVid(), 0.0));
    REQUIRE(almostEqual(s.galutinisMed(), 0.0));
}

TEST_CASE("Konstruktorius su parametrais", "[rule_of_five]") {
    Studentas s("Petras", "Petraitis");
    REQUIRE(s.vardas() == "Petras");
    REQUIRE(s.pavarde() == "Petraitis");
    REQUIRE(s.nd().empty());
    REQUIRE(s.egz() == 0);
}

TEST_CASE("Kopijavimo konstruktorius", "[rule_of_five]") {
    Studentas original = makeStudent();
    Studentas copy(original);

    REQUIRE(copy.vardas() == original.vardas());
    REQUIRE(copy.pavarde() == original.pavarde());
    REQUIRE(copy.nd() == original.nd());
    REQUIRE(copy.egz() == original.egz());
    REQUIRE(almostEqual(copy.galutinisVid(), original.galutinisVid()));
    REQUIRE(almostEqual(copy.galutinisMed(), original.galutinisMed()));
}

TEST_CASE("Kopijavimo priskyrimo operatorius", "[rule_of_five]") {
    Studentas original = makeStudent();
    Studentas copy;
    copy = original;

    REQUIRE(copy.vardas() == original.vardas());
    REQUIRE(copy.pavarde() == original.pavarde());
    REQUIRE(copy.nd() == original.nd());
    REQUIRE(copy.egz() == original.egz());
    REQUIRE(almostEqual(copy.galutinisVid(), original.galutinisVid()));
    REQUIRE(almostEqual(copy.galutinisMed(), original.galutinisMed()));
}

TEST_CASE("Perkėlimo konstruktorius", "[rule_of_five]") {
    Studentas original = makeStudent();
    const std::string vardas  = original.vardas();
    const std::string pavarde = original.pavarde();
    const Vector<int> nd = original.nd();
    const int egz             = original.egz();
    const double galVid       = original.galutinisVid();
    const double galMed       = original.galutinisMed();

    Studentas moved(std::move(original));

    REQUIRE(moved.vardas()  == vardas);
    REQUIRE(moved.pavarde() == pavarde);
    REQUIRE(moved.nd()      == nd);
    REQUIRE(moved.egz()     == egz);
    REQUIRE(almostEqual(moved.galutinisVid(), galVid));
    REQUIRE(almostEqual(moved.galutinisMed(), galMed));
}

TEST_CASE("Perkėlimo priskyrimo operatorius", "[rule_of_five]") {
    Studentas original = makeStudent();
    const std::string vardas  = original.vardas();
    const std::string pavarde = original.pavarde();
    const Vector<int> nd = original.nd();
    const int egz             = original.egz();
    const double galVid       = original.galutinisVid();
    const double galMed       = original.galutinisMed();

    Studentas moved;
    moved = std::move(original);

    REQUIRE(moved.vardas()  == vardas);
    REQUIRE(moved.pavarde() == pavarde);
    REQUIRE(moved.nd()      == nd);
    REQUIRE(moved.egz()     == egz);
    REQUIRE(almostEqual(moved.galutinisVid(), galVid));
    REQUIRE(almostEqual(moved.galutinisMed(), galMed));

    REQUIRE(original.vardas().empty());
    REQUIRE(original.pavarde().empty());
    REQUIRE(original.nd().empty());
    REQUIRE(original.egz() == 0);
}

// ---------------------------------------------------------------------------
// Operators
// ---------------------------------------------------------------------------

TEST_CASE("operator>> skaito studento duomenis", "[operators]") {
    std::stringstream input("Ona Onute 7 8 9 10\n");
    Studentas s;
    input >> s;

    REQUIRE((input.good() || input.eof()));
    REQUIRE(s.vardas()  == "Ona");
    REQUIRE(s.pavarde() == "Onute");
    REQUIRE(s.nd() == Vector<int>{7, 8, 9});
    REQUIRE(s.egz() == 10);
    REQUIRE(almostEqual(s.galutinisVid(), 9.2));
    REQUIRE(almostEqual(s.galutinisMed(), 9.2));
}

TEST_CASE("operator<< išveda studento duomenis", "[operators]") {
    Studentas s = makeStudent();
    std::stringstream output;
    output << s;
    const std::string text = output.str();

    REQUIRE(text.find("Jonas Jonaitis")        != std::string::npos);
    REQUIRE(text.find("ND: 8 9 10")            != std::string::npos);
    REQUIRE(text.find("Egz: 9")                != std::string::npos);
    REQUIRE(text.find("Galutinis (Vid.): 9.00") != std::string::npos);
    REQUIRE(text.find("Galutinis (Med.): 9.00") != std::string::npos);
}

// ---------------------------------------------------------------------------
// Grade calculation
// ---------------------------------------------------------------------------

TEST_CASE("Galutinio balo skaičiavimas", "[grades]") {
    Studentas s("Aiste", "Aistiene");
    s.addNd(6);
    s.addNd(10);
    s.addNd(8);
    s.setEgz(7);
    s.skaiciuotiGalutinius();

    REQUIRE(almostEqual(s.galutinisVid(), 7.4));
    REQUIRE(almostEqual(s.galutinisMed(), 7.4));
}

// ---------------------------------------------------------------------------
// Inheritance & polymorphism
// ---------------------------------------------------------------------------

TEST_CASE("Zmogus yra abstrakti klasė", "[inheritance]") {
    static_assert(std::is_abstract<Zmogus>::value,
                  "Zmogus turi buti abstrakti klase");
    static_assert(std::is_base_of<Zmogus, Studentas>::value,
                  "Studentas turi paveldeti is Zmogus");
    SUCCEED("Kompiliaciniai patikrinimai praėjo");
}

TEST_CASE("Polimorfinis naudojimas per Zmogus*", "[inheritance]") {
    Studentas s("Ieva", "Ievaite");
    Zmogus* zmogus = &s;

    REQUIRE(zmogus->vardas()  == "Ieva");
    REQUIRE(zmogus->pavarde() == "Ievaite");
    REQUIRE(zmogus->tipas()   == "Studentas");
}
