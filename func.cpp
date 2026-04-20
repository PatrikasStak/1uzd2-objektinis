#include "func.h"
#include "names.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::left;
using std::setw;
using std::vector;

void Studentas::skaiciuotiGalutinius(){
    double sum = 0.0;
    const auto& nd = nd_;
    for(size_t i=0;i<nd.size();i++) sum += nd[i];
    double avg = sum / nd.size();
    galutinis_vid_ = avg * 0.4 + egz_ * 0.6;

    std::vector<int> temp = nd;
    std::sort(temp.begin(), temp.end());
    double med;
    if(temp.size() % 2 == 0){
        med = (temp[temp.size()/2 - 1] + temp[temp.size()/2]) / 2.0;
    } else {
        med = temp[temp.size()/2];
    }
    galutinis_med_ = med * 0.4 + egz_ * 0.6;
}

void Skaityti(vector<Studentas>& X){
    string line;
    int s=0;
    srand(time(0));
    while(true){
        while(true){
            cout<<"Pasirinkite kaip norite ivesti duomenis: 1 - ranka, 2 - random pazymiai, 3 - viskas random, 4 - baigti"<<endl;
            getline(cin, line);
            if(line=="1" || line=="2" || line=="3" || line=="4") break;
            cout<<"Neteisinga ivestis. Iveskite 1, 2, 3 arba 4."<<endl;
        }
        if(line=="4") break;

        Studentas naujas;
        if(line=="1"){
            cout<<"Iveskite "<<s+1<<" studento varda: ";
            getline(cin, line);
            naujas.setVardas(line);
            cout<<"Iveskite "<<s+1<<" studento pavarde: ";
            getline(cin, line);
            naujas.setPavarde(line);
            int j=0;
            while(true){
                cout<<"Iveskite "<<s+1<<" studento "<<j+1<<" namu darbu pazymi (enter kad baigti): ";
                getline(cin, line);
                if(line.empty()){
                    if(j==0){
                        cout<<"Reikia ivesti bent viena pazymi."<<endl;
                        continue;
                    }
                    break;
                }
                try{
                    int pazymys = std::stoi(line);
                    if(pazymys>=0&&pazymys<=10){
                        naujas.addNd(pazymys);
                        j++;
                        continue;
                    }
                    cout<<"Namu darbu pazymis nera 0-10, bandykite dar karta"<<endl;
                    continue;
                }catch(const std::invalid_argument){std::cerr<<"Tai nėra skaičius, bandykite dar kartą"<<endl;
                continue;}
            }
            while(true){
                cout<<"Iveskite "<<s+1<<" studento egzamino pazymi: ";
                getline(cin, line);
                int egz;
                try{
                    egz = std::stoi(line);
                }catch(const std::invalid_argument){std::cerr<<"Tai nėra skaičius, bandykite dar kartą"<<endl;
                continue;}
                if(egz>=0&&egz<=10){
                    naujas.setEgz(egz);
                    break;
                }
                else {
                    cout<<"Egzamino pazymis nera 0-10, bandykite dar karta"<<endl;
                }
            }
            naujas.skaiciuotiGalutinius();
        }
        else if(line=="2"){
            cout<<"Iveskite "<<s+1<<" studento varda: ";
            getline(cin, line);
            naujas.setVardas(line);
            cout<<"Iveskite "<<s+1<<" studento pavarde: ";
            getline(cin, line);
            naujas.setPavarde(line);
            int j = rand() % 10 + 1; // 1-10 namu darbu pazymiu
            for(int k=0; k<j; k++){
                naujas.addNd(rand() % 10 + 1); // pazymiai 1-10
            }
            cout<<"Sugeneruoti "<<s+1<<" studento namu darbu pazymiai:";
            const auto& nd = naujas.nd();
            for(int k=0;k<j;k++){
                cout<<" "<<nd[k];
            }
            cout<<endl;
            naujas.setEgz(rand() % 10 + 1);
            cout<<"Sugeneruotas "<<s+1<<" studento egzamino pazymys: "<<naujas.egz()<<endl;
            naujas.skaiciuotiGalutinius();
        }
        else if(line=="3"){
            int kiek;
            cout<<"Kiek studentų norite sugeneruoti? ";
            while(!(cin>>kiek)){
                cout<<"Iveskite sveika skaiciu. Bandykite dar karta: ";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout<<endl;
            for(int i=0;i<kiek;i++){
            naujas.clearNd();
            int lytis = rand() % 2; // 0 - moteris ; 1 - vyras
            if(lytis == 0){
                int vardu_kiek = static_cast<int>(vardai_mot.size());
                int pavardziu_kiek = static_cast<int>(pavardes_mot.size());
                naujas.setVardas(vardai_mot[rand() % vardu_kiek]);
                naujas.setPavarde(pavardes_mot[rand() % pavardziu_kiek]);
            }
            else{
                int vardu_kiek = static_cast<int>(vardai_vyr.size());
                int pavardziu_kiek = static_cast<int>(pavardes_vyr.size());
                naujas.setVardas(vardai_vyr[rand() % vardu_kiek]);
                naujas.setPavarde(pavardes_vyr[rand() % pavardziu_kiek]);
            }
            int j = rand() % 10 + 1; // 1-10 namu darbu pazymiu
            for(int k=0; k<j; k++){
                naujas.addNd(rand() % 10 + 1); // pazymiai 1-10
            }
            cout<<"Sugeneruotas "<<s+1<<" studento vardas ir pavardė: "<<naujas.vardas()<<" "<<naujas.pavarde()<<endl;
            cout<<"Sugeneruoti "<<s+1<<" studento namu darbu pazymiai:";
            const auto& nd = naujas.nd();
            for(int k=0;k<j;k++){
                cout<<" "<<nd[k];
            }
            cout<<endl;
            naujas.setEgz(rand() % 10 + 1);
            cout<<"Sugeneruotas "<<s+1<<" studento egzamino pazymys: "<<naujas.egz()<<endl;
            naujas.skaiciuotiGalutinius();
            X.push_back(naujas);
            s++;
        }
    }
    if(line!="3"){
        naujas.skaiciuotiGalutinius();
        X.push_back(naujas);
        s++;
    }
    }

}
void SkaitytiFaila(vector<Studentas>& X){
    string header;
    string path;
    std:: ifstream in;
    in.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    auto t1 = std::chrono::high_resolution_clock::now();
    while (true){
        try{
            std::cout<<"Kokį failą norite skaityti? ";
            system("ls -1 *.txt | grep -v '^rez.txt$'");
            getline(std::cin, path);
            t1 = std::chrono::high_resolution_clock::now();
            in.open(path);
            break;
        }
        catch(const std::ifstream::failure& e){
            in.clear();
            std::cerr<<"Nepavyko atidaryti failo: "<<path<<", bandykite dar karta"<<endl;
        }
    }
    std::stringstream ss;
    ss<<in.rdbuf();
    in.close();
    getline(ss, header);

    std::stringstream hs(header);
    string token;
    int ndCount = 0;
    while(hs >> token){
        if(token.rfind("ND", 0) == 0){
            ndCount++;
        }
    }
    if(ndCount == 0){
        std::cerr << "Nepavyko nustatyti ND stulpeliu skaiciaus is antrastes." << endl;
        return;

    }

    while(true){
        Studentas naujas;
        string vardas;
        string pavarde;
        if(!(ss>>vardas>>pavarde))break;
        naujas.setVardas(vardas);
        naujas.setPavarde(pavarde);
        naujas.clearNd();
        for(int i=0;i<ndCount;i++){
            int nd;
            if(!(ss >> nd)){
                std::cerr << "Klaida skaitant ND (truksta duomenu)." << endl;
                return;
            }
            naujas.addNd(nd);
        }
        int egz;
        if(!(ss >> egz)){
            std::cerr << "Klaida skaitant egzamina (truksta duomenu)." << endl;
            return;
        }
        naujas.setEgz(egz);
        naujas.skaiciuotiGalutinius();
        X.push_back(naujas);
    }
auto t2 = std::chrono::high_resolution_clock::now();
auto dt = std::chrono::duration<double>(t2 - t1);
std::cout << "Laikas: " <<std::fixed<<std::setprecision(5)<< dt.count() << " s\n";


}


void Rezultatas(vector<Studentas>& X){
    if(X.empty()){
        std::cerr << "Nera duomenu." << endl;
        return;
    }

    cout<<"Kur isvesti rezultatus? 1 - i konsole, 2 - i rez.txt, 3 - i abu"<<endl;
    string out_choice;
    while(true){
        getline(cin, out_choice);
        if(out_choice=="1" || out_choice=="2" || out_choice=="3") break;
        std::cerr<<"Neteisinga įvestis, bandykite dar kartą: ";
    }

    std::ofstream file;
    if(out_choice=="2" || out_choice=="3"){
        file.open("rez.txt");
        if(!file){
            std::cerr << "Nepavyko atidaryti failo: rez.txt" << endl;
            return;
        }
    }

    string choice;
    cout<<"Pasirinkite rikiavimą: 1 - pagal vardą, 2 - pagal pavardę, 3 - pagal galutinį balą(vidurkio), 4 - pagal galutinį balą(medianos)"<<endl;
    while(true){
        getline(cin, choice);
        if(choice=="1" || choice=="2" || choice=="3" || choice=="4") break;
        std::cerr<<"Neteisinga įvestis, bandykite dar kartą: ";
    }

    if(choice=="1"){
        std::sort(X.begin(), X.end(), [](const Studentas& a, const Studentas& b){
            if(a.vardas() == b.vardas()) return a.pavarde() > b.pavarde();
            return a.vardas() > b.vardas();
        });
    } else if(choice=="2"){
        std::sort(X.begin(), X.end(), [](const Studentas& a, const Studentas& b){
            if(a.pavarde() == b.pavarde()) return a.vardas() > b.vardas();
            return a.pavarde() > b.pavarde();
        });
    } else if(choice=="3"){
        std::sort(X.begin(), X.end(), [](const Studentas& a, const Studentas& b){
            return a.galutinisVid() > b.galutinisVid();
        });
    } else if(choice=="4"){
        std::sort(X.begin(), X.end(), [](const Studentas& a, const Studentas& b){
            return a.galutinisMed() > b.galutinisMed();
        });
    }

    cout<<"Mediana ar vidurkis? (m/v): ";
    string pasirinkimas;
    getline(cin, pasirinkimas);
    std::transform(pasirinkimas.begin(), pasirinkimas.end(), pasirinkimas.begin(),
               [](unsigned char c){ return std::tolower(c); });
    
    size_t w1 = string("Vardas").size();
    size_t w2 = string("Pavarde").size();

    for(size_t i=0;i<X.size();++i){
        w1=std::max(w1, X[i].vardas().size());
        w2=std::max(w2, X[i].pavarde().size());
    }

    w1+=2;
    w2+=2;
    
    auto spausdinti = [&](std::ostream& os){
        if(pasirinkimas=="m"||pasirinkimas=="mediana"){
            os<<left<<setw(w1)<<"Vardas"<<setw(w2)<<"Pavarde"<<setw(12)<<"Galutinis (Med.)"<<endl;
        }
        else{
            os<<left<<setw(w1)<<"Vardas"<<setw(w2)<<"Pavarde"<<setw(12)<<"Galutinis (Vid.)"<<endl;
        }
        std::fill_n(std::ostream_iterator<char>(os), w1 + w2 + 16, '-');
        os << endl;

        if(pasirinkimas=="m"||pasirinkimas=="mediana"){
            for(size_t i=0;i<X.size();i++){
                os<<left<<setw(w1)<<X[i].vardas()<<setw(w2)<<X[i].pavarde()<<setw(12)<<std::fixed<<std::setprecision(2)<<X[i].galutinisMed()<<endl;
            }
        }
        else{
            for(size_t i=0;i<X.size();i++){
                os<<left<<setw(w1)<<X[i].vardas()<<setw(w2)<<X[i].pavarde()<<setw(12)<<std::fixed<<std::setprecision(2)<<X[i].galutinisVid()<<endl;
            }
        }
    };

    if(out_choice=="1"){
        spausdinti(cout);
    } else if(out_choice=="2"){
        spausdinti(file);
    } else {
        spausdinti(cout);
        spausdinti(file);
    }

}

void RezultatasFailo(vector<Studentas>& X){
    if(X.empty()){
        std::cerr << "Nera duomenu rikiavimui." << endl;
        return;
    }

    cout<<"Kur isvesti rezultatus? 1 - i konsole, 2 - i rez.txt, 3 - i abu"<<endl;
    string out_choice;
    while(true){
        getline(cin, out_choice);
        if(out_choice=="1" || out_choice=="2" || out_choice=="3") break;
        std::cerr<<"Neteisinga įvestis, bandykite dar kartą: ";
    }

    std::ofstream file;
    if(out_choice=="2" || out_choice=="3"){
        file.open("rez.txt");
        if(!file){
            std::cerr << "Nepavyko atidaryti failo: rez.txt" << endl;
            return;
        }
    }

    string choice;
    cout<<"Pasirinkite rikiavimą: 1 - pagal vardą, 2 - pagal pavardę, 3 - pagal galutinį balą(vidurkio), 4 - pagal galutinį balą(medianos)"<<endl;
    while(true){
        getline(cin, choice);
        if(choice=="1" || choice=="2" || choice=="3" || choice=="4") break;
        std::cerr<<"Neteisinga įvestis, bandykite dar kartą: ";
    }

    if(choice=="1"){
        std::sort(X.begin(), X.end(), [](const Studentas& a, const Studentas& b){
            if(a.vardas() == b.vardas()) return a.pavarde() > b.pavarde();
            return a.vardas() > b.vardas();
        });
    } else if(choice=="2"){
        std::sort(X.begin(), X.end(), [](const Studentas& a, const Studentas& b){
            if(a.pavarde() == b.pavarde()) return a.vardas() > b.vardas();
            return a.pavarde() > b.pavarde();
        });
    } else if(choice=="3"){
        std::sort(X.begin(), X.end(), [&](const Studentas& a, const Studentas& b){
            return a.galutinisVid() > b.galutinisVid();
        });
    } else if(choice=="4"){
        std::sort(X.begin(), X.end(), [&](const Studentas& a, const Studentas& b){
            return a.galutinisMed() > b.galutinisMed();
        });
    }

    size_t w1 = string("Vardas").size();
    size_t w2 = string("Pavarde").size();
    for(size_t i=0;i<X.size();++i){
        w1=std::max(w1, X[i].vardas().size());
        w2=std::max(w2, X[i].pavarde().size());
    }
    w1+=2;
    w2+=2;

    auto spausdinti = [&](std::ostream& os){
        os<<left<<setw(w1)<<"Vardas"
          <<setw(w2)<<"Pavarde"
          <<setw(16)<<"Galutinis (Vid.)"
          <<setw(16)<<"Galutinis (Med.)"
          <<endl;
        std::fill_n(std::ostream_iterator<char>(os), w1 + w2 + 32, '-');
        os << endl;

        for(size_t i=0;i<X.size();i++){
            os<<left<<setw(w1)<<X[i].vardas()
              <<setw(w2)<<X[i].pavarde()
              <<setw(16)<<std::fixed<<std::setprecision(2)<<X[i].galutinisVid()
              <<setw(16)<<std::fixed<<std::setprecision(2)<<X[i].galutinisMed()
              <<endl;
        }
    };

    if(out_choice=="1"){
        spausdinti(cout);
    } else if(out_choice=="2"){
        spausdinti(file);
    } else {
        spausdinti(cout);
        spausdinti(file);
    }
}

void FailuGeneravimas(){

    
    auto writeHeader = [](std::ostream& out, int x) {
    out << left<<setw(25)<<"Vardas"<<setw(25)<<"Pavarde";
    for(int i=0;i<x;i++){
        out<<setw(10)<<("ND"+std::to_string(i+1));
    }
    out<<setw(10)<<"Egz."<<endl;
    };

    auto writeStud = [](std::ostream& out, int x, int k){
        int random;
        for(int i=0;i<k;i++){
            
            out<<left<<setw(25)<<("Vardas" + std::to_string(i+1))<<setw(25)<<("Pavarde"+ std::to_string(i+1));
            for(int j=0;j<x;j++){
                random = rand() % 10 + 1;
                out<<setw(10)<<random;
            }
            random = rand() % 10 + 1;
            out<<setw(10)<<random<<endl;
        }
    };

    int nd;
    string line;
    while(true){
    cout<<"Iveskite norima ND skaiciu: ";
    getline(cin, line);
    try{
        nd=stoi(line);
    }catch(const std::invalid_argument){std::cerr<<"Tai nera skaicius, bandykite dar karta!"<<endl;
    continue;}
    if(nd<=0)std::cerr<<"Turi buti bent 1 ND"<<endl;
    else break;
    }
    auto sstart = std::chrono::high_resolution_clock::now();
    auto start = std::chrono::high_resolution_clock::now();

    std::ofstream k1("generuoti1000.txt");
    writeHeader(k1, nd);
    writeStud(k1, nd, 1000);
    k1.close();
    auto end = std::chrono::high_resolution_clock::now();
    auto sec = std::chrono::duration<double>(end - start).count();
    std::cout << "1000 failas sugeneruotas per " << sec << " s\n";

    start = std::chrono::high_resolution_clock::now();
    std::ofstream k10("generuoti10000.txt");
    writeHeader(k10, nd);
    writeStud(k10, nd, 10000);
    k10.close();
    end = std::chrono::high_resolution_clock::now();
    sec = std::chrono::duration<double>(end - start).count();
    std::cout << "10000 failas sugeneruotas per " << sec << " s\n";

    start = std::chrono::high_resolution_clock::now();
    std::ofstream k100("generuoti100000.txt");
    writeHeader(k100, nd);
    writeStud(k100, nd, 100000);
    k100.close();
    end = std::chrono::high_resolution_clock::now();
    sec = std::chrono::duration<double>(end - start).count();
    std::cout << "100000 failas sugeneruotas per " << sec << " s\n";

    start = std::chrono::high_resolution_clock::now();
    std::ofstream m1("generuoti1000000.txt");
    writeHeader(m1, nd);
    writeStud(m1, nd, 1000000);
    m1.close();
    end = std::chrono::high_resolution_clock::now();
    sec = std::chrono::duration<double>(end - start).count();
    std::cout << "1000000 failas sugeneruotas per " << sec << " s\n";

    start = std::chrono::high_resolution_clock::now();
    std::ofstream m10("generuoti10000000.txt");
    writeHeader(m10, nd);
    writeStud(m10, nd, 10000000);
    m10.close();
    end = std::chrono::high_resolution_clock::now();
    sec = std::chrono::duration<double>(end - start).count();
    std::cout << "10000000 failas sugeneruotas per " << sec << " s\n";

    auto sEnd = std::chrono::high_resolution_clock::now();
    auto totalSec = std::chrono::duration<double>(sEnd - sstart).count();
    std::cout << "Visi failai sugeneruoti per " << totalSec << " s\n";

}

template <typename Cont, typename Comp>
void sortContainer(Cont& c, Comp comp) {
    std::sort(c.begin(), c.end(), comp);
}

template <typename T, typename Alloc, typename Comp>
void sortContainer(std::list<T, Alloc>& c, Comp comp) {
    c.sort(comp);
}

static void moveVargsai(StudentVec& X, StudentVec& vargsai, bool useMed) {
    auto isVargsas = [&](const Studentas& s){
        double val = useMed ? s.galutinisMed() : s.galutinisVid();
        return val < 5.0;
    };
    auto mid = std::partition(X.begin(), X.end(), isVargsas);
    vargsai.insert(vargsai.end(), X.begin(), mid);
    X.erase(X.begin(), mid);
}

static void moveVargsai(StudentDeque& X, StudentDeque& vargsai, bool useMed) {
    for (const auto& s : X) {
        double val = useMed ? s.galutinisMed() : s.galutinisVid();
        if (val < 5.0) vargsai.push_back(s);
    }
    X.erase(std::remove_if(X.begin(), X.end(),
                           [&](const Studentas& s){
                               double val = useMed ? s.galutinisMed() : s.galutinisVid();
                               return val < 5.0;
                           }),
            X.end());
}

static void moveVargsai(StudentList& X, StudentList& vargsai, bool useMed) {
    for (auto it = X.begin(); it != X.end(); ) {
        double val = useMed ? it->galutinisMed() : it->galutinisVid();
        if (val < 5.0) {
            vargsai.push_back(*it);
            it = X.erase(it);
        } else {
            ++it;
        }
    }
}

template <typename Cont> void GeneruotuRusiavimasImpl(const std::string& path){
    auto start = std::chrono::high_resolution_clock::now();
    std::ifstream in;
    while (true){
        try{
            in.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            in.open(path);
            break;
        }
        catch(const std::ifstream::failure& e){
            in.clear();
            std::cerr<<"Nepavyko atidaryti failo: "<<path<<", tikriausiai jis dar nesugeneruotas, bandykite dar karta"<<endl;
            return;
        }
    }
    Cont X, vargsai;
    string header;
    std::stringstream ss;
    ss<<in.rdbuf();
    in.close();
    auto end = std::chrono::high_resolution_clock::now();
    auto sec = std::chrono::duration<double>(end - start).count();
    std::cout <<"\033[32m"<< path<<" failas nuskaitytas per " << sec << " s"<<"\033[0m"<<"\n";
    auto total=sec;
    getline(ss, header);

    std::stringstream hs(header);
    string token;
    int ndCount = 0;
    while(hs >> token){
        if(token.rfind("ND", 0) == 0){
            ndCount++;
        }
    }
    start = std::chrono::high_resolution_clock::now();
    while(true){
        Studentas naujas;
        string vardas;
        string pavarde;
        if(!(ss>>vardas>>pavarde))break;
        naujas.setVardas(vardas);
        naujas.setPavarde(pavarde);
        naujas.clearNd();
        for(int i=0;i<ndCount;i++){
            int nd;
            if(!(ss >> nd)){
                std::cerr << "Klaida skaitant ND (truksta duomenu)." << endl;
                return;
            }
            naujas.addNd(nd);
        }
        int egz;
        if(!(ss >> egz)){
            std::cerr << "Klaida skaitant egzamina (truksta duomenu)." << endl;
            return;
        }
        naujas.setEgz(egz);
        naujas.skaiciuotiGalutinius();
        X.push_back(naujas);
    }
    end = std::chrono::high_resolution_clock::now();
    sec = std::chrono::duration<double>(end - start).count();
    std::cout <<"\033[32m"<< path<<" duomenys sudeti i konteineri per: " << sec << " s"<<"\033[0m"<<"\n";
    total+=sec;
    string choice;
    while(true){
        cout<<"Kaip rikiuoti? 1 - pagal varda, 2 - pagal pavarde, 3 - pagal galutini(vidurkio), 4 - pagal galutini(medianos): ";
        getline(cin, choice);
        if(choice=="1"||choice=="2"||choice=="3"||choice=="4")break;
        else std::cerr<<"Neteisinga ivestis, bandykite dar karta!\n";
    }
    auto startbig = std::chrono::high_resolution_clock::now();
    auto compVardas = [](const Studentas& a, const Studentas& b){ return a.vardas() < b.vardas(); };
    auto compPavarde = [](const Studentas& a, const Studentas& b){ return a.pavarde() < b.pavarde(); };
    auto compVid = [](const Studentas& a, const Studentas& b){ return a.galutinisVid() < b.galutinisVid(); };
    auto compMed = [](const Studentas& a, const Studentas& b){ return a.galutinisMed() < b.galutinisMed(); };

    auto doSort = [&](auto comp){
        sortContainer(X, comp);
    };
    start = std::chrono::high_resolution_clock::now();
    if (choice=="1") doSort(compVardas);
    else if (choice=="2") doSort(compPavarde);
    else if (choice=="3") doSort(compVid);
    else if (choice=="4") doSort(compMed);
    end = std::chrono::high_resolution_clock::now();
    sec = std::chrono::duration<double>(end - start).count();
    std::cout <<"\033[32m"<< path<<" failas isrikiuotas per: " << sec << " s"<<"\033[0m"<<"\n";


    start = std::chrono::high_resolution_clock::now();
    moveVargsai(X, vargsai, choice=="4");
    
    
    
    end = std::chrono::high_resolution_clock::now();
    sec = std::chrono::duration<double>(end - start).count();
    std::cout <<"\033[32m"<< path<<" failas isskirstytas i 2 per " << sec << " s"<<"\033[0m"<<"\n";



    std::ofstream mldc("maladiec.txt");
    std::ofstream vrgs("vargsai.txt");

    auto writeHeader = [](std::ostream& out, string choice) {
    out << left<<setw(25)<<"Vardas"<<setw(25)<<"Pavarde";
    if(choice=="4")out<<setw(12)<<"Gal.(Med)"<<endl;
    else out<<setw(12)<<"Gal.(Vid)"<<endl;
    };

    auto writeStud = [](std::ostream& out, const auto& X, string choice){
        for (const auto& s : X){
            out<<left<<setw(25)<<s.vardas()<<setw(25)<<s.pavarde();
            if(choice=="4")out<<setw(12)<<std::fixed<<std::setprecision(2)<<s.galutinisMed()<<endl;
            else out<<setw(12)<<std::fixed<<std::setprecision(2)<<s.galutinisVid()<<endl;
        }
    };
    start = std::chrono::high_resolution_clock::now();
    writeHeader(mldc, choice);
    writeStud(mldc, X, choice);
    end = std::chrono::high_resolution_clock::now();
    sec = std::chrono::duration<double>(end - start).count();
    std::cout << path<<" failo maladiec isvesti per " << sec << " s\n";

    start = std::chrono::high_resolution_clock::now();
    writeHeader(vrgs, choice);
    writeStud(vrgs, vargsai, choice);
    end = std::chrono::high_resolution_clock::now();
    sec = std::chrono::duration<double>(end - start).count();
    std::cout << path<<" failo vargsai isvesti per " << sec << " s\n";
    mldc.close();
    vrgs.close();


    end = std::chrono::high_resolution_clock::now();
    sec = std::chrono::duration<double>(end - startbig).count();
    std::cout << path<<" failo visi rikiavimai atlikti per " << sec << " s\n";
    total+=sec;
    std::cout <<"\033[32m"<< path<<" failas uztruko: " << total << " s"<<"\033[0m"<<"\n";


}
void GeneruotuRusiavimasVec(const std::string& path) {
    GeneruotuRusiavimasImpl<StudentVec>(path);
}

void GeneruotuRusiavimasList(const std::string& path) {
    GeneruotuRusiavimasImpl<StudentList>(path);
}

void GeneruotuRusiavimasDeque(const std::string& path) {
    GeneruotuRusiavimasImpl<StudentDeque>(path);
}


void TrintiFaila(const std::string& path){
    std::remove(path.c_str());
}
