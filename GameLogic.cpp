#include "GameLogic.h"
#include <ctime>
#include <cstdlib>
#include <math.h>
#include <iostream>

GameLogic::GameLogic():vyhra_(0), publikum_(1), padesat_(1), pritel_(1), stav_(kCekaNaStart), kolo_(1), otazky_(vector<Otazka>(15)){
}

void GameLogic::StartHry(std::vector< Otazka >& seznamOtazek){
    GameLogic();
    otazky_ = seznamOtazek;
    cout << "Hra začíná" << endl;
}
void GameLogic::UkonciHru(){
    stav_ = kKonecHryVyhra;
    if(VratCisloKola() != 16)
        cout << "Ukončil/a jste hru odnášíte si " << vyhra_ << endl;
    else
        cout << "Gratulujeme, právě jste zvítězili ve hře Chcete být milionářen" << endl;
} // muze ukoncit i predasne, prijde o vyhru

void GameLogic::UkonciAplikaci(){
    stav_ = kKonecHryBezVyhry;
    cout << "Odpověd je špatná";
    if(kolo_ > 9)
        cout << " vyhráváte 320 000" << endl;
    else if(kolo_ > 4)
        cout << " vyhráváte 10 000" << endl;
    else
        cout << " nevyhráváte nic" << endl;
}

// true, pokud je odpoved spravna, false pokud ne
bool GameLogic::ZadejOdpovedNaOtazku(EnumOdpovedi odpoved){
    Otazka o = VratAktualniOtazky();
    if(o.spravnaOdpoved == odpoved){
        switch (VratCisloKola()) {
        case 1:
            vyhra_ = 1000;
            break;
        case 3:
            vyhra_ = 3000;
            break;
        case 4:
            vyhra_ = 5000;
            break;
        case 12:
            vyhra_ = 1250000;
            break;
        default:
            vyhra_ *= 2;
            break;
        }
        kolo_++;
        return true;
    }
    else{
        stav_ = kKonecHryBezVyhry;
        return false;
    }
}

Otazka GameLogic::VratAktualniOtazky(){return otazky_[VratCisloKola()-1];}

float GameLogic::AktualniVyhra(){
    cout << "Aktuální výhra: " << vyhra_ << endl;
    return vyhra_;
}

bool GameLogic::MuzuVyuzitPadestNaPadesat(){return (padesat_ == 1)?(true):(false);}

bool GameLogic::MuzuVyuzitRaduPublika(){return (publikum_ == 1)?(true):(false);}

bool GameLogic::MuzuVyuzitPriteleNaTelefonu(){return (pritel_ == 1)?(true):(false);}

// vrati dve otazky ze kterych si potom hrac zvoli
PadesatPadest GameLogic::VyuzijPadesatNaPadesat(){
    if(MuzuVyuzitPadestNaPadesat()){
        srand((unsigned)time(0));
        int pozice = round(rand() % 1);
        int pozice1;
        Otazka o = VratAktualniOtazky();
        PadesatPadest padesat;
        padesat.Prvni = padesat.Druha = o.spravnaOdpoved;
        EnumOdpovedi pomOdp;
        do{
            pozice1 = round(rand() % 4);
            switch(pozice1){
            case 1:pomOdp = kA;break;
            case 2:pomOdp = kB;break;
            case 3:pomOdp = kC;break;
            case 4:pomOdp = kD;break;
            }
        }while(o.spravnaOdpoved == pomOdp);

        if(pozice == 1)
            padesat.Druha = pomOdp;
        else
            padesat.Prvni = pomOdp;

        this->padesat_ = 0;

        cout << "Zbývají otázky" << endl;

        switch(padesat.Prvni){
        case kA:cout << "A: " << o.textOdpovedi_A;
            break;
        case kB:cout << "B: " << o.textOdpovedi_B;
            break;
        case kC:cout << "C: " << o.textOdpovedi_C;
            break;
        case kD:cout << "D: " << o.textOdpovedi_D;
            break;
        }

        switch(padesat.Druha){
        case kA:cout << " A: " << o.textOdpovedi_A << endl;
            break;
        case kB:cout << " B: " << o.textOdpovedi_B << endl;
            break;
        case kC:cout << " C: " << o.textOdpovedi_C << endl;
            break;
        case kD:cout << " D: " << o.textOdpovedi_D << endl;
            break;
        }
        return padesat;
    }
}

RadaPublika GameLogic::VyuzijRaduPublika(){
    if(MuzuVyuzitRaduPublika()){
        int kolo = VratCisloKola();
        srand((unsigned)time(0));
        RadaPublika rada;
        Otazka o = VratAktualniOtazky();
        int koef;
        //výpočet kolik pro jakou možnost hlasovalo diváků
        if(kolo < 6)
            koef = rand() % 10 + 90;
        else if (kolo < 11)
            koef = rand() % 20 + 60;
        else
            koef = rand() % 10 + 15;
        int doSta = (100 - koef)/3;

        switch(o.spravnaOdpoved){
        case kA:
            rada.pocetDoporuceniA = koef;
            rada.pocetDoporuceniB = rand() % doSta;
            rada.pocetDoporuceniC = rand() % doSta;
            rada.pocetDoporuceniD = rand() % doSta;
            if(rada.pocetDoporuceniA + rada.pocetDoporuceniB + rada.pocetDoporuceniC + rada.pocetDoporuceniD != 100)
                rada.pocetDoporuceniA += 100 - (rada.pocetDoporuceniA + rada.pocetDoporuceniB + rada.pocetDoporuceniC + rada.pocetDoporuceniD);
            break;
        case kB:
            rada.pocetDoporuceniA = rand() % doSta;
            rada.pocetDoporuceniB = koef;
            rada.pocetDoporuceniC = rand() % doSta;
            rada.pocetDoporuceniD = rand() % doSta;
            if(rada.pocetDoporuceniA + rada.pocetDoporuceniB + rada.pocetDoporuceniC + rada.pocetDoporuceniD != 100)
                rada.pocetDoporuceniB += 100 - (rada.pocetDoporuceniA + rada.pocetDoporuceniB + rada.pocetDoporuceniC + rada.pocetDoporuceniD);
            break;
        case kC:
            rada.pocetDoporuceniA = rand() % doSta;
            rada.pocetDoporuceniB = rand() % doSta;
            rada.pocetDoporuceniC = koef;
            rada.pocetDoporuceniD = rand() % doSta;
            if(rada.pocetDoporuceniA + rada.pocetDoporuceniB + rada.pocetDoporuceniC + rada.pocetDoporuceniD != 100)
                rada.pocetDoporuceniC += 100 - (rada.pocetDoporuceniA + rada.pocetDoporuceniB + rada.pocetDoporuceniC + rada.pocetDoporuceniD);
            break;
        case kD:
            rada.pocetDoporuceniA = rand() % doSta;
            rada.pocetDoporuceniB = rand() % doSta;
            rada.pocetDoporuceniC = rand() % doSta;
            rada.pocetDoporuceniD = koef;
            if(rada.pocetDoporuceniA + rada.pocetDoporuceniB + rada.pocetDoporuceniC + rada.pocetDoporuceniD != 100)
                rada.pocetDoporuceniD += 100 - (rada.pocetDoporuceniA + rada.pocetDoporuceniB + rada.pocetDoporuceniC + rada.pocetDoporuceniD);
            break;
        }
        //od otázky 8+ šance 1:4, že se publikum splete
        //        if(round(rand() % 3 + 1) == 1 && kolo > 7){
        //            switch (o.spravnaOdpoved) {
        //            case kA:
        //                rada.pocetDoporuceniC = rada.pocetDoporuceniA;
        //                rada.pocetDoporuceniA = rada.pocetDoporuceniB;
        //                break;
        //            case kB:
        //                rada.pocetDoporuceniD = rada.pocetDoporuceniB;
        //                rada.pocetDoporuceniB = rada.pocetDoporuceniC;
        //            case kC:
        //                rada.pocetDoporuceniA = rada.pocetDoporuceniC;
        //                rada.pocetDoporuceniC = rada.pocetDoporuceniB;
        //            case kD:
        //                rada.pocetDoporuceniB = rada.pocetDoporuceniD;
        //                rada.pocetDoporuceniD = rada.pocetDoporuceniA;
        //            }
        //        }
        this->publikum_ = 0;
        int max = rada.pocetDoporuceniA;
        max = (max > rada.pocetDoporuceniB)?(max):(rada.pocetDoporuceniB);
        max = (max > rada.pocetDoporuceniC)?(max):(rada.pocetDoporuceniC);
        max = (max > rada.pocetDoporuceniD)?(max):(rada.pocetDoporuceniD);
        cout << "Publikum radí:" << endl;
        cout << "A) " << o.textOdpovedi_A << " s pravděpodobností " << rada.pocetDoporuceniA << "%" << endl;
        cout << "B) " << o.textOdpovedi_B << " s pravděpodobností " << rada.pocetDoporuceniB << "%" << endl;
        cout << "C) " << o.textOdpovedi_C << " s pravděpodobností " << rada.pocetDoporuceniC << "%" << endl;
        cout << "D) " << o.textOdpovedi_D << " s pravděpodobností " << rada.pocetDoporuceniD << "%" << endl;
        return rada;
    }
}

RadaPriteleNaTelefonu GameLogic::VyuzijPriteleNaTelefonu(){
    if(MuzuVyuzitPriteleNaTelefonu()){
        float jistota = (1-((kolo_-1)/16.))*100;
        srand((unsigned)time(0));
        int odp = round(rand() % 50 + 50);
//        cout << VratCisloKola() << " " << ((2-1)/16.) << " " << odp << endl;
        int odpoved;
        char radaChar;
        Otazka o = VratAktualniOtazky();
        RadaPriteleNaTelefonu rada;
        if(odp <= jistota){
            rada.Odpoved = o.spravnaOdpoved;
            switch(o.spravnaOdpoved){
            case kA:radaChar = 'A';break;
            case kB:radaChar = 'B';break;
            case kC:radaChar = 'C';break;
            case kD:radaChar = 'D';break;
            }
        }
        else{
            odpoved = rand() % 4;
            switch(odpoved){
            case 1:rada.Odpoved = kA;radaChar = 'A';break;
            case 2:rada.Odpoved = kB;radaChar = 'B';break;
            case 3:rada.Odpoved = kC;radaChar = 'C';break;
            case 4:rada.Odpoved = kD;radaChar = 'D';break;
            }
        }
        rada.jistotaOdpovedi = round(jistota);
        this->pritel_ = 0;
        cout << "Radim ti " << radaChar << " jsem si jistý asi na " << rada.jistotaOdpovedi << "%" << endl;
        return rada;
    }
}

StavyHry GameLogic::VratAktualniStav(){return stav_;}

int GameLogic::VratCisloKola(){return kolo_;}
