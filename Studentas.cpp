#include "Studentas.h"

Studentas::Studentas()
    : egz_(0), galutinis_vid_(0.0), galutinis_med_(0.0) {}

Studentas::Studentas(const std::string& vardas, const std::string& pavarde)
    : vardas_(vardas), pavarde_(pavarde), egz_(0), galutinis_vid_(0.0), galutinis_med_(0.0) {}

Studentas::Studentas(const Studentas& other)
    : vardas_(other.vardas_),
      pavarde_(other.pavarde_),
      nd_(other.nd_),
      egz_(other.egz_),
      galutinis_vid_(other.galutinis_vid_),
      galutinis_med_(other.galutinis_med_) {}

Studentas& Studentas::operator=(const Studentas& other) {
    if (this != &other) {
        vardas_ = other.vardas_;
        pavarde_ = other.pavarde_;
        nd_ = other.nd_;
        egz_ = other.egz_;
        galutinis_vid_ = other.galutinis_vid_;
        galutinis_med_ = other.galutinis_med_;
    }

    return *this;
}

Studentas::Studentas(Studentas&& other) noexcept
    : vardas_(std::move(other.vardas_)),
      pavarde_(std::move(other.pavarde_)),
      nd_(std::move(other.nd_)),
      egz_(other.egz_),
      galutinis_vid_(other.galutinis_vid_),
      galutinis_med_(other.galutinis_med_) {
    other.egz_ = 0;
    other.galutinis_vid_ = 0.0;
    other.galutinis_med_ = 0.0;
}

Studentas& Studentas::operator=(Studentas&& other) noexcept {
    if (this != &other) {
        vardas_ = std::move(other.vardas_);
        pavarde_ = std::move(other.pavarde_);
        nd_ = std::move(other.nd_);
        egz_ = other.egz_;
        galutinis_vid_ = other.galutinis_vid_;
        galutinis_med_ = other.galutinis_med_;

        other.egz_ = 0;
        other.galutinis_vid_ = 0.0;
        other.galutinis_med_ = 0.0;
    }

    return *this;
}

void Studentas::skaiciuotiGalutinius() {
    double sum = 0.0;
    const auto& nd = nd_;
    for (size_t i = 0; i < nd.size(); i++) {
        sum += nd[i];
    }

    double avg = sum / nd.size();
    galutinis_vid_ = avg * 0.4 + egz_ * 0.6;

    std::vector<int> temp = nd;
    std::sort(temp.begin(), temp.end());

    double med;
    if (temp.size() % 2 == 0) {
        med = (temp[temp.size() / 2 - 1] + temp[temp.size() / 2]) / 2.0;
    } else {
        med = temp[temp.size() / 2];
    }

    galutinis_med_ = med * 0.4 + egz_ * 0.6;
}

std::istream& operator>>(std::istream& is, Studentas& studentas) {
    std::string line;
    if (!std::getline(is >> std::ws, line)) {
        return is;
    }

    std::stringstream ss(line);
    std::string vardas;
    std::string pavarde;
    if (!(ss >> vardas >> pavarde)) {
        is.setstate(std::ios::failbit);
        return is;
    }

    std::vector<int> pazymiai;
    int pazymys;
    while (ss >> pazymys) {
        pazymiai.push_back(pazymys);
    }

    if (pazymiai.size() < 2) {
        is.setstate(std::ios::failbit);
        return is;
    }

    studentas.vardas_ = vardas;
    studentas.pavarde_ = pavarde;
    studentas.nd_.assign(pazymiai.begin(), pazymiai.end() - 1);
    studentas.egz_ = pazymiai.back();
    studentas.skaiciuotiGalutinius();

    return is;
}

std::ostream& operator<<(std::ostream& os, const Studentas& studentas) {
    os << studentas.vardas_ << ' ' << studentas.pavarde_ << " | ND:";
    for (size_t i = 0; i < studentas.nd_.size(); ++i) {
        os << ' ' << studentas.nd_[i];
    }

    os << " | Egz: " << studentas.egz_
       << " | Galutinis (Vid.): " << std::fixed << std::setprecision(2) << studentas.galutinis_vid_
       << " | Galutinis (Med.): " << std::fixed << std::setprecision(2) << studentas.galutinis_med_;

    return os;
}
