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
    return 0;
}

