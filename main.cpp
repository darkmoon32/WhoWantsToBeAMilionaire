#include <iostream>
#include "MilionaireHomework.h"
#include "GameData.h"
#include "GameIO.h"
#include "GameLogic.h"
#include <math.h>
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
    GameData data;
    GameIO io;
    GameLogic logic;

    GameDataInterface& dataI = data;
    GameIOInterface& ioI = io;
    GameLogicInterface& logicI = logic;

    Game hra(logicI,dataI,ioI);
    hra.Hraj();
//    srand((unsigned)time(0));
//    int koef,doSta,jedna,dva,tri,ctyri;
//    for(int i = 1 ; i < 16 ; i++){
//        if(i < 6)
//            koef = 100 - (15 / (16 - i)) - i - round(rand() % 4);
//        else if (i < 11)
//            koef = 100 - (15 / (16 - i)) - i * 3 - round(rand() % 4);
//        else
//            koef = 100 - (15 / (16 - i)) - i * 4 - round(rand() % 4);
//        doSta = (100 - koef)/3;
//        jedna = rand() % (100-koef) + koef;
//        dva = rand() % doSta;
//        tri = rand() % doSta;
//        ctyri = rand() % doSta;
//        cout << i << " " << koef << " " << jedna << "% " << dva << "% " << tri << "% " << ctyri << "% " << endl;
//    }
    return 0;
}

