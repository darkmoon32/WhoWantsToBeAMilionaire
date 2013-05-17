#include "GameData.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

bool GameData::LoadData(string cesta){

    string str1,str2,str3,str4,str5;
    char c;
    int cislo = 0;
    Otazka otazka;
    fstream f;
    f.open(cesta.c_str());
    if(f.is_open()){
        while(!f.eof()){
            if(f.good())
                getline(f,str1);
            if(f.good())
                getline(f,str2);
            if(f.good())
                getline(f,str3);
            if(f.good())
                getline(f,str4);
            if(f.good())
                getline(f,str5);
            if(f.good()){
                c = f.get();
                cislo = c - '0';
            }
            if(f.good() && cislo > 0 && cislo < 5){
                switch(cislo){
                case 1:otazka.spravnaOdpoved = kA;break;
                case 2:otazka.spravnaOdpoved = kB;break;
                case 3:otazka.spravnaOdpoved = kC;break;
                case 4:otazka.spravnaOdpoved = kD;break;
                }
                otazka.textOtazky = str1;
                otazka.textOdpovedi_A = str2;
                otazka.textOdpovedi_B = str3;
                otazka.textOdpovedi_C = str4;
                otazka.textOdpovedi_D = str5;
                otazky_.push_back(otazka);
                //cout << str1 << " " << str2 << " " << str3 << " " << str4 << " " << str5 << " " << cislo << endl;
            }
            f.ignore();
        }
        f.close();
        cout << "Soubor otevřen a otázky načteny" << endl;
        return true;
    }
    else
        return false;
}

std::vector< Otazka > GameData::VratOtazkyProJednuHru(){
    vector<Otazka> otazky;
    vector<int> o;
    otazky.reserve(15);
    srand((unsigned)time(0));
    int pocet = otazky_.size();
    int i = 0;
    if(pocet < 15)
        cout << "Nedostatek otázek" << endl;
    else
    {
        while(i < 15){
            int random = rand() % pocet;
            if(in_array(o,random) == false){
                //cout << random << endl;
                o.push_back(random);
                otazky.push_back(otazky_[random]);
                i++;
            }
        }
    }
    return otazky;
}

bool GameData::in_array(std::vector<int> o,int num){
    for(unsigned int i = 0 ; i < o.size() ; i++){
        if(o[i] == num){
            return true;
        }
    }
    return false;
}
