#include "Studentas.h"

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
