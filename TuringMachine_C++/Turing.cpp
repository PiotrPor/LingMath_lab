/*
  Zadanie 3 - Maszyna Turinga
  Autor: Piotr Porembinski (253488)
  Poziom trudnosci na ocene 4
*/
#include <iostream>
#include <string>

//===== ENUMERATORY I STRUKTURY =====
enum Ruch
{
    R,
    L,
    nic
};

enum Stany
{
    Qs,
    Q0,
    Q1,
    Q2,
    Q3,
    Qe,
    pusty
};

const char Alfabet[] = {'0','1','o'};
const char nic_nie_pisz = '-';

struct Decyzja
{
    Stany nowy_stan;
    char wpisywany_symbol;
    Ruch ruch;
};

//===== KLASA =====
class MaszynaTuringa
{
private:
    Stany aktualny_stan;
public:
    const Stany stan_poczatkowy = Stany::Qs;
    MaszynaTuringa();
    std::string dodaj_trzy(std::string liczba);
    Decyzja podejmij_decyzje(char ss);
};

//===== FUNKCJA =====
std::string stan_tekstowo(Stany st);
std::string ruch_tekstowo(Ruch r);
std::string decyzja_jako_tekst(Decyzja DD);

//================
//===== MAIN =====

int main()
{
    std::string liczba_binarna;
    std::string zwiekszona_liczba;
    MaszynaTuringa MT;
    //
    std::cout << "Wpisz \'o\' a potem liczbe binarna: ";
    std::getline(std::cin, liczba_binarna);
    //
    std::cout << "Tasma przed: " << liczba_binarna << std::endl;
    zwiekszona_liczba = MT.dodaj_trzy(liczba_binarna);
    std::cout << "Tasma po: " << zwiekszona_liczba << std::endl;
    return 0;
}

//===== KLASA =====

MaszynaTuringa::MaszynaTuringa()
{
    aktualny_stan = stan_poczatkowy;
}

std::string MaszynaTuringa::dodaj_trzy(std::string liczba)
{
    std::string zwiekszona = liczba;
    //unsigned int dlugosc = liczba.size();
    unsigned int x;
    Decyzja co_zrobi;
    //x = dlugosc-1;
    x = liczba.size() - 1;
    while (x >= 0)
    {
        co_zrobi = this->podejmij_decyzje(zwiekszona[x]);
        std::cout << "Napotkano symbol " << zwiekszona[x] << std::endl;
        //stan
        if (co_zrobi.nowy_stan != Stany::pusty)
        {
            this->aktualny_stan = co_zrobi.nowy_stan;
        }
        //symbol wpisany na tasme
        if (co_zrobi.wpisywany_symbol != nic_nie_pisz)
        {
            zwiekszona[x] = co_zrobi.wpisywany_symbol;
        }
        //ruch
        if (x == 0)
        {
            if (zwiekszona[x] != Alfabet[2]) //jesli to nie symbol konca tasmy
            {
                zwiekszona.insert(0, "o");
                x++;
            }
        }
        if (co_zrobi.ruch != Ruch::nic)
        {
            if (co_zrobi.ruch == Ruch::R) { x++; }
            else { x--; }
        }
        //
        std::cout << "   " << decyzja_jako_tekst(co_zrobi) << std::endl;
        //zakoncz petle
        if (co_zrobi.nowy_stan == Stany::pusty &&
            co_zrobi.wpisywany_symbol == nic_nie_pisz && 
            co_zrobi.ruch == Ruch::nic && 
            zwiekszona[x] == Alfabet[2])
        {
            break;
        }
    }
    return zwiekszona;
}

Decyzja MaszynaTuringa::podejmij_decyzje(char ss)
{
    Decyzja co_robic;
    switch (aktualny_stan)
    {
        case Stany::Qs:
        {
            if (ss == Alfabet[0]) { co_robic = {Stany::Q0, Alfabet[1], Ruch::L}; }
            else if (ss == Alfabet[1]) { co_robic = { Stany::Q1, Alfabet[0], Ruch::L }; }
            else { co_robic = { Stany::Q0, Alfabet[1], Ruch::L }; }
            break;
        }
        case Stany::Q0:
        {
            if (ss == Alfabet[0]) { co_robic = { Stany::Q2, Alfabet[1], Ruch::L }; }
            else if (ss == Alfabet[1]) { co_robic = { Stany::Q3, Alfabet[0], Ruch::L }; }
            else { co_robic = { Stany::Q2, Alfabet[1], Ruch::L }; }
            break;
        }
        case Stany::Q1:
        {
            if (ss == Alfabet[0]) { co_robic = { Stany::Q3, nic_nie_pisz, Ruch::L }; }
            else if (ss == Alfabet[1]) { co_robic = { Stany::Q3, nic_nie_pisz, Ruch::L }; }
            else { co_robic = { Stany::Q3, Alfabet[0], Ruch::L }; }
            break;
        }
        case Stany::Q2:
        {
            if (ss == Alfabet[0]) { co_robic = { Stany::pusty, nic_nie_pisz, Ruch::L }; }
            else if (ss == Alfabet[1]) { co_robic = { Stany::pusty, nic_nie_pisz, Ruch::L }; }
            else { co_robic = { Stany::pusty, nic_nie_pisz, Ruch::nic }; }
            break;
        }
        case Stany::Q3: //todo
        {
            if (ss == Alfabet[0]) { co_robic = { Stany::Q2, Alfabet[1], Ruch::L }; }
            else if (ss == Alfabet[1]) { co_robic = { Stany::pusty, Alfabet[0], Ruch::L }; }
            else { co_robic = { Stany::Q2, Alfabet[1], Ruch::nic }; }
            break;
        }
        case Stany::Qe: //todo
        {
            if (ss == Alfabet[0]) { co_robic = { Stany::pusty, nic_nie_pisz, Ruch::nic }; }
            else if (ss == Alfabet[1]) { co_robic = { Stany::pusty, nic_nie_pisz, Ruch::nic }; }
            else { co_robic = { Stany::pusty, nic_nie_pisz, Ruch::nic }; }
            break;
        }
        default:
        {
            co_robic = { Stany::pusty, nic_nie_pisz, Ruch::nic };
            break;
        }
    }
    return co_robic;
}


//===== FUNKCJE =====

std::string stan_tekstowo(Stany st)
{
    switch (st)
    {
        case Stany::Qs: {return "Qs"; break; }
        case Stany::Q0: {return "Q0"; break; }
        case Stany::Q1: {return "Q1"; break; }
        case Stany::Q2: {return "Q2"; break; }
        case Stany::Q3: {return "Q3"; break; }
        default: {return "[none]"; }
    }
}

std::string ruch_tekstowo(Ruch r)
{
    switch (r)
    {
        case Ruch::L: {return "w lewo"; break; }
        case Ruch::R: {return "w prawo"; break; }
        default: {return "[none]"; }
    }
}

std::string decyzja_jako_tekst(Decyzja DD)
{
    std::string opis = "";
    if (DD.nowy_stan != Stany::pusty)
    {
        opis += "Przechodzi do stanu " + stan_tekstowo(DD.nowy_stan);
    }
    else
    {
        opis += "Nie zmienia stanu";
    }
    opis += ". ";
    if (DD.wpisywany_symbol != nic_nie_pisz)
    {
        opis += "Wpisuje \"";
        opis.append(1, DD.wpisywany_symbol); //dopisz raz ten 'char'
        opis += "\" na tasme";
    }
    else
    {
        std::cout << "Nie wpisuje symbolu na tasme";
    }
    opis += ". ";
    if (DD.ruch != Ruch::nic)
    {
        opis += "Przesuwa glowice " + ruch_tekstowo(DD.ruch);
    }
    else
    {
        opis += "Glowica nie rusza sie";
    }
    opis += ".";
    return opis;
}
