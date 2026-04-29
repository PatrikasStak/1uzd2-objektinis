#include "Studentas.h"

#include <cassert>
#include <cmath>
#include <sstream>
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

void testDefaultConstructor() {
    Studentas s;
    assert(s.vardas().empty());
    assert(s.pavarde().empty());
    assert(s.nd().empty());
    assert(s.egz() == 0);
    assert(almostEqual(s.galutinisVid(), 0.0));
    assert(almostEqual(s.galutinisMed(), 0.0));
}

void testParameterizedConstructor() {
    Studentas s("Petras", "Petraitis");
    assert(s.vardas() == "Petras");
    assert(s.pavarde() == "Petraitis");
    assert(s.nd().empty());
    assert(s.egz() == 0);
}

void testCopyConstructor() {
    Studentas original = makeStudent();
    Studentas copy(original);

    assert(copy.vardas() == original.vardas());
    assert(copy.pavarde() == original.pavarde());
    assert(copy.nd() == original.nd());
    assert(copy.egz() == original.egz());
    assert(almostEqual(copy.galutinisVid(), original.galutinisVid()));
    assert(almostEqual(copy.galutinisMed(), original.galutinisMed()));
}

void testCopyAssignment() {
    Studentas original = makeStudent();
    Studentas copy;
    copy = original;

    assert(copy.vardas() == original.vardas());
    assert(copy.pavarde() == original.pavarde());
    assert(copy.nd() == original.nd());
    assert(copy.egz() == original.egz());
    assert(almostEqual(copy.galutinisVid(), original.galutinisVid()));
    assert(almostEqual(copy.galutinisMed(), original.galutinisMed()));
}

void testMoveConstructor() {
    Studentas original = makeStudent();
    Studentas stat=original;
    const std::string vardas = original.vardas();
    const std::string pavarde = original.pavarde();
    const std::vector<int> nd = original.nd();
    const int egz = original.egz();
    const double galVid = original.galutinisVid();
    const double galMed = original.galutinisMed();

    Studentas moved(std::move(original));

    assert(moved.vardas() == vardas);
    assert(moved.pavarde() == pavarde);
    assert(moved.nd() == nd);
    assert(moved.egz() == egz);
    assert(almostEqual(moved.galutinisVid(), galVid));
    assert(almostEqual(moved.galutinisMed(), galMed)); //add isempty
}

void testMoveAssignment() {
    Studentas original = makeStudent();
    const std::string vardas = original.vardas();
    const std::string pavarde = original.pavarde();
    const std::vector<int> nd = original.nd();
    const int egz = original.egz();
    const double galVid = original.galutinisVid();
    const double galMed = original.galutinisMed();

    Studentas moved;
    moved = std::move(original);

    assert(moved.vardas() == vardas);
    assert(moved.pavarde() == pavarde);
    assert(moved.nd() == nd);
    assert(moved.egz() == egz);
    assert(almostEqual(moved.galutinisVid(), galVid));
    assert(almostEqual(moved.galutinisMed(), galMed));
}

void testInputOperator() {
    std::stringstream input("Ona Onute 7 8 9 10\n");
    Studentas s;
    input >> s;

    assert(input.good() || input.eof());
    assert(s.vardas() == "Ona");
    assert(s.pavarde() == "Onute");
    assert((s.nd() == std::vector<int>{7, 8, 9}));
    assert(s.egz() == 10);
    assert(almostEqual(s.galutinisVid(), 9.2));
    assert(almostEqual(s.galutinisMed(), 9.2));
}

void testOutputOperator() {
    Studentas s = makeStudent();
    std::stringstream output;
    output << s;
    const std::string text = output.str();

    assert(text.find("Jonas Jonaitis") != std::string::npos);
    assert(text.find("ND: 8 9 10") != std::string::npos);
    assert(text.find("Egz: 9") != std::string::npos);
    assert(text.find("Galutinis (Vid.): 9.00") != std::string::npos);
    assert(text.find("Galutinis (Med.): 9.00") != std::string::npos);
}

void testGradeCalculation() {
    Studentas s("Aiste", "Aistiene");
    s.addNd(6);
    s.addNd(10);
    s.addNd(8);
    s.setEgz(7);
    s.skaiciuotiGalutinius();

    assert(almostEqual(s.galutinisVid(), 7.4));
    assert(almostEqual(s.galutinisMed(), 7.4));
}

}  // namespace

int main() {
    testDefaultConstructor();
    testParameterizedConstructor();
    testCopyConstructor();
    testCopyAssignment();
    testMoveConstructor();
    testMoveAssignment();
    testInputOperator();
    testOutputOperator();
    testGradeCalculation();

    std::cout << "Visi Studentas testai pavyko.\n";
    return 0;
}
