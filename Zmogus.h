#ifndef ZMOGUS_H
#define ZMOGUS_H

#include "lib.h"

class Zmogus {
protected:
    std::string vardas_;
    std::string pavarde_;

    Zmogus() = default;

    Zmogus(const std::string& vardas, const std::string& pavarde)
        : vardas_(vardas), pavarde_(pavarde) {}

public:
    virtual ~Zmogus() = default;

    inline const std::string& vardas() const { return vardas_; }
    inline const std::string& pavarde() const { return pavarde_; }

    inline void setVardas(const std::string& vardas) { vardas_ = vardas; }
    inline void setPavarde(const std::string& pavarde) { pavarde_ = pavarde; }

    virtual std::string tipas() const = 0;
};

#endif
