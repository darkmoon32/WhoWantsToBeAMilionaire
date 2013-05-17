#pragma once
#include "MilionaireHomework.h"
using namespace std;
using namespace MillionareHomework;

class GameLogic:public GameLogicInterface
{
private:
    float vyhra_;
    int publikum_;
    int padesat_;
    int pritel_;
    StavyHry stav_;
    int kolo_;
    std::vector<Otazka> otazky_;
public:
    GameLogic();
    // seznamOtazek vyuzijte pro nacteni otazek pro jednu hru
    void StartHry(std::vector< Otazka >& seznamOtazek);
    void UkonciHru(); // muze ukoncit i predasne, prijde o vyhru
    void UkonciAplikaci();
    // true, pokud je odpoved spravna, false pokud ne
    bool ZadejOdpovedNaOtazku(EnumOdpovedi odpoved);
    Otazka VratAktualniOtazky();
    float AktualniVyhra();
    bool MuzuVyuzitPadestNaPadesat();
    bool MuzuVyuzitRaduPublika();
    bool MuzuVyuzitPriteleNaTelefonu();
    // vrati dve otazky ze kterych si potom hrac zvoli
    PadesatPadest VyuzijPadesatNaPadesat();
    RadaPublika VyuzijRaduPublika();
    RadaPriteleNaTelefonu VyuzijPriteleNaTelefonu();
    StavyHry VratAktualniStav();
    int VratCisloKola();
};
