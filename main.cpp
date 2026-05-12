#include "func.h"

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    Vector<Studentas> A;
    std::cout<<"1 - vesti ranka, 2 - skaityti iš failo, 3 - generuoti failus, 4 - failu testavimas: ";
    std::string choice;
    while(true){
    getline(std::cin, choice);
    if(choice=="1"||choice=="2"||choice=="3"||choice=="4")break;
    std::cerr<<"Neteisinga ivestis, bandykite dar karta: ";
    }
    if(choice=="1"){
    Skaityti(A);
    Rezultatas(A);
    }
    else if(choice=="2"){
        SkaitytiFaila(A);
        RezultatasFailo(A);
    }
    else if(choice=="3"){
        FailuGeneravimas();
    }
    else if (choice == "4") {
        std::string kont;
        while(true){
        std::cout << "Koki konteineri naudoti? 1 - vector, 2 - list, 3 - deque\n";
        getline(std::cin, kont);
        if(kont=="1"||kont=="2"||kont=="3")break;
        else std::cerr<<"Neteisinga ivestis!\n";
        }

        while (true) {
            std::cout << "Kuri faila rusiuoti? 1 - generuoti1000.txt 2 - generuoti10000.txt 3 - generuoti100000.txt 4 - generuoti1000000.txt 5 - generuoti10000000.txt 6 - baigti \n";
            getline(std::cin, choice);

            if (choice == "1") {
                if (kont == "1") GeneruotuRusiavimasVec("generuoti1000.txt");
                else if (kont == "2") GeneruotuRusiavimasList("generuoti1000.txt");
                else if (kont == "3") GeneruotuRusiavimasDeque("generuoti1000.txt");
                else std::cerr << "Neteisingas konteinerio pasirinkimas\n";
            } else if (choice == "2") {
                if (kont == "1") GeneruotuRusiavimasVec("generuoti10000.txt");
                else if (kont == "2") GeneruotuRusiavimasList("generuoti10000.txt");
                else if (kont == "3") GeneruotuRusiavimasDeque("generuoti10000.txt");
                else std::cerr << "Neteisingas konteinerio pasirinkimas\n";
            } else if (choice == "3") {
                if (kont == "1") GeneruotuRusiavimasVec("generuoti100000.txt");
                else if (kont == "2") GeneruotuRusiavimasList("generuoti100000.txt");
                else if (kont == "3") GeneruotuRusiavimasDeque("generuoti100000.txt");
                else std::cerr << "Neteisingas konteinerio pasirinkimas\n";
            } else if (choice == "4") {
                if (kont == "1") GeneruotuRusiavimasVec("generuoti1000000.txt");
                else if (kont == "2") GeneruotuRusiavimasList("generuoti1000000.txt");
                else if (kont == "3") GeneruotuRusiavimasDeque("generuoti1000000.txt");
                else std::cerr << "Neteisingas konteinerio pasirinkimas\n";
            } else if (choice == "5") {
                if (kont == "1") GeneruotuRusiavimasVec("generuoti10000000.txt");
                else if (kont == "2") GeneruotuRusiavimasList("generuoti10000000.txt");
                else if (kont == "3") GeneruotuRusiavimasDeque("generuoti10000000.txt");
                else std::cerr << "Neteisingas konteinerio pasirinkimas\n";
            } else if (choice == "6") {
                break;
            } else {
                std::cerr << "Neteisinga ivestis!\n";
            }
        }
    }

    return 0;
}