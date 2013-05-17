#pragma once
#include "MilionaireHomework.h"
#include <fstream>

using namespace MillionareHomework;
using namespace std;

class GameIO: public GameIOInterface
{
public:
    GameIO();
    std::string ReadLine(); // Načte řádek z textové konzole
    char ReadChar(); // Načte jeden znak z textové konzole
    void WriteLine(std::string line); // Zapíše řádek na textovou konzoli
    void WriteCharacter(char character); // Zapíše znak na textovou konzoli
};
