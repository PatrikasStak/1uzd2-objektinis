#include "func.h"
#include "names.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::left;
using std::setw;
using std::vector;

static void SkaiciuotiGalutinius(Studentas& s){
    double sum = 0.0;
    for(size_t i=0;i<s.nd.size();i++) sum += s.nd[i];
    double avg = sum / s.nd.size();
    s.galutinis_vid = avg * 0.4 + s.egz * 0.6;

    std::vector<int> temp = s.nd;
    std::sort(temp.begin(), temp.end());
    double med;
    if(temp.size() % 2 == 0){
        med = (temp[temp.size()/2 - 1] + temp[temp.size()/2]) / 2.0;
    } else {
        med = temp[temp.size()/2];
    }
    s.galutinis_med = med * 0.4 + s.egz * 0.6;
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
            getline(cin, naujas.vardas);
            cout<<"Iveskite "<<s+1<<" studento pavarde: ";
            getline(cin, naujas.pavarde);
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
                    naujas.nd.push_back(std::stoi(line));
                    j++;
                }catch(const std::invalid_argument){std::cerr<<"Tai nėra skaičius, bandykite dar kartą"<<endl;
                continue;}
                if(naujas.nd[j-1]>=0&&naujas.nd[j-1]<=10)continue;
                else {
                    cout<<"Namu darbu pazymis nera 0-10, bandykite dar karta"<<endl;
                    j--;
                }
                
            }
            while(true){
                cout<<"Iveskite "<<s+1<<" studento egzamino pazymi: ";
                getline(cin, line);
                try{
                    naujas.egz = std::stoi(line);
                }catch(const std::invalid_argument){std::cerr<<"Tai nėra skaičius, bandykite dar kartą"<<endl;
                continue;}
                if(naujas.egz>=0&&naujas.egz<=10)break;
                else {
                    cout<<"Egzamino pazymis nera 0-10, bandykite dar karta"<<endl;
                }
            }
            SkaiciuotiGalutinius(naujas);
        }
        else if(line=="2"){
            cout<<"Iveskite "<<s+1<<" studento varda: ";
            getline(cin, naujas.vardas);
            cout<<"Iveskite "<<s+1<<" studento pavarde: ";
            getline(cin, naujas.pavarde);
            int j = rand() % 10 + 1; // 1-10 namu darbu pazymiu
            for(int k=0; k<j; k++){
                naujas.nd.push_back(rand() % 10 + 1); // pazymiai 1-10
            }
            cout<<"Sugeneruoti "<<s+1<<" studento namu darbu pazymiai:";
            for(int k=0;k<j;k++){
                cout<<" "<<naujas.nd[k];
            }
            cout<<endl;
            naujas.egz=rand() % 10 + 1;
            cout<<"Sugeneruotas "<<s+1<<" studento egzamino pazymys: "<<naujas.egz<<endl;
            SkaiciuotiGalutinius(naujas);
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
            naujas.nd.clear();
            int lytis = rand() % 2; // 0 - moteris ; 1 - vyras
            if(lytis == 0){
                int vardu_kiek = static_cast<int>(vardai_mot.size());
                int pavardziu_kiek = static_cast<int>(pavardes_mot.size());
                naujas.vardas = vardai_mot[rand() % vardu_kiek];
                naujas.pavarde = pavardes_mot[rand() % pavardziu_kiek];
            }
            else{
                int vardu_kiek = static_cast<int>(vardai_vyr.size());
                int pavardziu_kiek = static_cast<int>(pavardes_vyr.size());
                naujas.vardas = vardai_vyr[rand() % vardu_kiek];
                naujas.pavarde = pavardes_vyr[rand() % pavardziu_kiek];
            }
            int j = rand() % 10 + 1; // 1-10 namu darbu pazymiu
            for(int k=0; k<j; k++){
                naujas.nd.push_back(rand() % 10 + 1); // pazymiai 1-10
            }
            cout<<"Sugeneruotas "<<s+1<<" studento vardas ir pavardė: "<<naujas.vardas<<" "<<naujas.pavarde<<endl;
            cout<<"Sugeneruoti "<<s+1<<" studento namu darbu pazymiai:";
            for(int k=0;k<j;k++){
                cout<<" "<<naujas.nd[k];
            }
            cout<<endl;
            naujas.egz=rand() % 10 + 1;
            cout<<"Sugeneruotas "<<s+1<<" studento egzamino pazymys: "<<naujas.egz<<endl;
            SkaiciuotiGalutinius(naujas);
            X.push_back(naujas);
            s++;
        }
    }
    if(line!="3"){
        SkaiciuotiGalutinius(naujas);
        X.push_back(naujas);
        s++;
    }
    }

}

bool SkaitytiFaila(vector<Studentas>& X, const std::string& path){
    string header;
    std::ifstream in(path);

    if(!in){
        std::cerr<<"Nepavyko atidaryti failo: "<<path<<endl;
        return false;
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
        return false;
    }

    while(true){
        Studentas naujas;
        if(!(ss>>naujas.vardas>>naujas.pavarde))break;
        naujas.nd.clear();
        for(int i=0;i<ndCount;i++){
            int nd;
            if(!(ss >> nd)){
                std::cerr << "Klaida skaitant ND (truksta duomenu)." << endl;
                return false;
            }
            naujas.nd.push_back(nd);
        }
        if(!(ss >> naujas.egz)){
            std::cerr << "Klaida skaitant egzamina (truksta duomenu)." << endl;
            return false;
        }
        SkaiciuotiGalutinius(naujas);
        X.push_back(naujas);
    }
    return true;
    

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
            if(a.vardas == b.vardas) return a.pavarde > b.pavarde;
            return a.vardas > b.vardas;
        });
    } else if(choice=="2"){
        std::sort(X.begin(), X.end(), [](const Studentas& a, const Studentas& b){
            if(a.pavarde == b.pavarde) return a.vardas > b.vardas;
            return a.pavarde > b.pavarde;
        });
    } else if(choice=="3"){
        std::sort(X.begin(), X.end(), [](const Studentas& a, const Studentas& b){
            return a.galutinis_vid > b.galutinis_vid;
        });
    } else if(choice=="4"){
        std::sort(X.begin(), X.end(), [](const Studentas& a, const Studentas& b){
            return a.galutinis_med > b.galutinis_med;
        });
    }

    cout<<"Mediana ar vidurkis? (m/v): ";
    string pasirinkimas;
    getline(cin, pasirinkimas);
    std::transform(pasirinkimas.begin(), pasirinkimas.end(), pasirinkimas.begin(),
               [](unsigned char c){ return std::tolower(c); });
    
    size_t w1 = string("Vardas").size();
    size_t w2 = string("Pavarde").size();

    for(int i=0;i<X.size();++i){
        w1=std::max(w1, X[i].vardas.size());
        w2=std::max(w2, X[i].pavarde.size());
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
            for(int i=0;i<X.size();i++){
                os<<left<<setw(w1)<<X[i].vardas<<setw(w2)<<X[i].pavarde<<setw(12)<<std::fixed<<std::setprecision(2)<<X[i].galutinis_med<<endl;
            }
        }
        else{
            for(int i=0;i<X.size();i++){
                os<<left<<setw(w1)<<X[i].vardas<<setw(w2)<<X[i].pavarde<<setw(12)<<std::fixed<<std::setprecision(2)<<X[i].galutinis_vid<<endl;
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
            if(a.vardas == b.vardas) return a.pavarde > b.pavarde;
            return a.vardas > b.vardas;
        });
    } else if(choice=="2"){
        std::sort(X.begin(), X.end(), [](const Studentas& a, const Studentas& b){
            if(a.pavarde == b.pavarde) return a.vardas > b.vardas;
            return a.pavarde > b.pavarde;
        });
    } else if(choice=="3"){
        std::sort(X.begin(), X.end(), [&](const Studentas& a, const Studentas& b){
            return a.galutinis_vid > b.galutinis_vid;
        });
    } else if(choice=="4"){
        std::sort(X.begin(), X.end(), [&](const Studentas& a, const Studentas& b){
            return a.galutinis_med > b.galutinis_med;
        });
    }

    size_t w1 = string("Vardas").size();
    size_t w2 = string("Pavarde").size();
    for(int i=0;i<X.size();++i){
        w1=std::max(w1, X[i].vardas.size());
        w2=std::max(w2, X[i].pavarde.size());
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

        for(int i=0;i<X.size();i++){
            os<<left<<setw(w1)<<X[i].vardas
              <<setw(w2)<<X[i].pavarde
              <<setw(16)<<std::fixed<<std::setprecision(2)<<X[i].galutinis_vid
              <<setw(16)<<std::fixed<<std::setprecision(2)<<X[i].galutinis_med
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
