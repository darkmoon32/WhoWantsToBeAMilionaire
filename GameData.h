#pragma once
#include <vector>
#include "MilionaireHomework.h"

using namespace std;
using namespace MillionareHomework;

class GameData: public GameDataInterface
{
private:
    vector<Otazka> otazky_;
public:
    // osetrene proti padu aplikace, vrati true pokud se nacitani povede, false podud se nepovede
    bool LoadData(std::string cesta);
    std::vector< Otazka > VratOtazkyProJednuHru();
    bool in_array(std::vector<int> o,int num);
};
