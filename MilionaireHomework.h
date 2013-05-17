#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;
namespace MillionareHomework
{

enum EnumOdpovedi
{
    kA,
    kB,
    kC,
    kD
};

enum StavyHry
{
    kCekaNaStart,
    kCekaNaOdpoved,
    kKonecHryMaximalniVyhra,
    kKonecHryVyhra,
    kKonecHryBezVyhry
};

struct PadesatPadest
{
    EnumOdpovedi Prvni;
    EnumOdpovedi Druha;
};

struct RadaPriteleNaTelefonu
{
    EnumOdpovedi Odpoved;
    int jistotaOdpovedi; // 0 - vubec nevi, 100 - je si stoprocetne jisty
};

struct RadaPublika
{
    int pocetDoporuceniA; // kolik lidi z publika doporucilo odpoved A
    int pocetDoporuceniB; // kolik lidi z publika doporucilo odpoved B
    int pocetDoporuceniC; // kolik lidi z publika doporucilo odpoved C
    int pocetDoporuceniD; // kolik lidi z publika doporucilo odpoved D
};

struct Otazka  {
    std::string textOtazky;
    std::string textOdpovedi_A;
    std::string textOdpovedi_B;
    std::string textOdpovedi_C;
    std::string textOdpovedi_D;
    EnumOdpovedi spravnaOdpoved;
};

// Implementace teto tridy bude obsahovat pouze logiku hry !!

class GameLogicInterface
{
public:
    // seznamOtazek vyuzijte pro nacteni otazek pro jednu hru
    virtual void StartHry(std::vector< Otazka >& seznamOtazek) = 0;
    virtual void UkonciHru() = 0; // muze ukoncit i predasne, prijde o vyhru
    virtual void UkonciAplikaci() = 0;
    // true, pokud je odpoved spravna, false pokud ne
    virtual bool ZadejOdpovedNaOtazku(EnumOdpovedi odpoved) = 0;
    virtual Otazka VratAktualniOtazky() = 0;
    virtual float AktualniVyhra() = 0;
    virtual bool MuzuVyuzitPadestNaPadesat() = 0;
    virtual bool MuzuVyuzitRaduPublika() = 0;
    virtual bool MuzuVyuzitPriteleNaTelefonu() = 0;
    // vrati dve otazky ze kterych si potom hrac zvoli
    virtual PadesatPadest VyuzijPadesatNaPadesat() = 0;
    virtual RadaPublika VyuzijRaduPublika() = 0;
    virtual RadaPriteleNaTelefonu VyuzijPriteleNaTelefonu() = 0;
    virtual StavyHry VratAktualniStav() = 0;
    virtual int VratCisloKola() = 0;
};

// Implementace teto dridy bude slouzit pouze pro nacitani otazek
class GameDataInterface
{
public:
    // osetrene proti padu aplikace, vrati true pokud se nacitani povede, false podud se nepovede
    virtual bool LoadData(std::string cesta) = 0;
    virtual std::vector< Otazka > VratOtazkyProJednuHru() = 0;
};

// Implementace teto tridy bude slouzit pro vstupne vystupni operace

class GameIOInterface
{
public:

    virtual std::string ReadLine() = 0; // Načte řádek z textové konzole
    virtual char ReadChar() = 0; // Načte jeden znak z textové konzole
    virtual void WriteLine(std::string line) = 0; // Zapíše řádek na textovou konzoli
    virtual void WriteCharacter(char character) = 0; // Zapíše znak na textovou konzoli

};

class Game
{
private:
    GameLogicInterface& gameLogic_;
    GameDataInterface& gameData_;
    GameIOInterface& gameIO_;

public:
    Game(GameLogicInterface& gameLogic, GameDataInterface& gameData, GameIOInterface& gameIO) : gameLogic_(gameLogic), gameData_(gameData), gameIO_(gameIO)
    {
        gameData_.LoadData("otazky.txt");
        cout << "Vítejte ve hře Kdo chce být milionářem" << endl;
    }

    void Hraj()
    {
        vector<Otazka> otazka = gameData_.VratOtazkyProJednuHru();
        gameLogic_.StartHry(otazka);
        Otazka o;
        char ch;
        bool b;
        while(gameLogic_.VratAktualniStav() != kKonecHryBezVyhry && gameLogic_.VratAktualniStav() != kKonecHryMaximalniVyhra && gameLogic_.VratAktualniStav() != kKonecHryVyhra) {
            gameLogic_.AktualniVyhra();
            o = gameLogic_.VratAktualniOtazky();
            cout << o.textOtazky << endl;
            cout << "A: " << o.textOdpovedi_A << " ";
            cout << "B: " << o.textOdpovedi_B << endl;
            cout << "C: " << o.textOdpovedi_C << " ";
            cout << "D: " <<o.textOdpovedi_D << endl;
            cout << "Vaše volba je   (Stiskni 'N' pro menu napovědy, 'K' pro konec hry): ";
            ch = tolower(gameIO_.ReadChar());
            if(ch == 'n'){
                cout << "Stiskni P=publikum, T=přitel na telefonu, F=padesát na padesát, K=nechci nápovědu" << endl;
                cout << "Přítel na telefonu " << ((gameLogic_.MuzuVyuzitPriteleNaTelefonu() == true)?("Ano"):("Ne")) << endl;
                cout << "Padesát na padesát " << ((gameLogic_.MuzuVyuzitPadestNaPadesat() == true)?("Ano"):("Ne")) << endl;
                cout << "Publikum " << ((gameLogic_.MuzuVyuzitRaduPublika() == true)?("Ano"):("Ne")) << endl;
                cout << "Zvolte [F,P,T]" << endl;
                ch = tolower(gameIO_.ReadChar());
                switch (ch) {
                case 'p':
                    if(gameLogic_.MuzuVyuzitRaduPublika() == true)
                        gameLogic_.VyuzijRaduPublika();
                    else
                        gameIO_.WriteLine("Již nemůžete využít radu publika");
                    break;
                case 't':
                    if(gameLogic_.MuzuVyuzitPriteleNaTelefonu() == true)
                        gameLogic_.VyuzijPriteleNaTelefonu();
                    else
                        gameIO_.WriteLine("Již nemůžete využít radu přítele");
                    break;
                case 'f':
                    if(gameLogic_.MuzuVyuzitPadestNaPadesat() == true)
                        gameLogic_.VyuzijPadesatNaPadesat();
                    else
                        gameIO_.WriteLine("Již nemůžete využít padesát na padesát");
                    break;
                }
                cout << "Vaše volba:";
                ch = tolower(gameIO_.ReadChar());
            }
            switch (ch) {
            case 'a':
                b = gameLogic_.ZadejOdpovedNaOtazku(kA);
                break;
            case 'b':
                b = gameLogic_.ZadejOdpovedNaOtazku(kB);
                break;
            case 'c':
                b = gameLogic_.ZadejOdpovedNaOtazku(kC);
                break;
            case 'd':
                b = gameLogic_.ZadejOdpovedNaOtazku(kD);
                break;
            case 'k':
                gameLogic_.UkonciHru();
                break;
            }
            if(gameLogic_.VratAktualniStav() != kKonecHryVyhra){
                if(b == true)
                    cout << "Dobře ty" << endl << "----------------------------------------------------------------------" << endl;
                else{
                    cout << "tududumtum" << endl;
                    gameLogic_.UkonciAplikaci();
                }
            }

            if(gameLogic_.VratCisloKola() == 16 && b == true){
                gameLogic_.UkonciHru();
            }
        }

        // Tyto body musi byt bezpodminecne splneny:
        // logika hry bude obsazena pouze v objektu gameLogic
        // otazky pro hru se budou nacitat pouze pomoci objektu gameData
        // vstupne vystupni operace budou provadeny pouze pomoci objektu gameIO
        // doplnte kod zde



    }

};

}
