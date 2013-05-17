#include "GameIO.h"
#include <iostream>
#include <ctype.h>

GameIO::GameIO(){}

std::string GameIO::ReadLine(){
    std::string str;
    getline(std::cin,str);
    return str;
} // Načte řádek z textové konzole
char GameIO::ReadChar(){
    char c;
    do{
    c = cin.get();
    //cin.ignore();
    }while(!isalnum(c));
    return c;
} // Načte jeden znak z textové konzole
void GameIO::WriteLine(std::string line){
    cout << line.c_str() << endl;
} // Zapíše řádek na textovou konzoli
void GameIO::WriteCharacter(char character){
    cout << character << endl;
} // Zapíše znak na textovou konzoli
