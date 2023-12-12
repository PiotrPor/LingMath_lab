/*
  ...
  Autor: Piotr Porembinski (253488)
  Poziom: ocena dobra
*/

#include <iostream>
#include <string>

#include "AutomatDeterministyczny.h"

int main()
{
    AutomatDeterministyczny DFA;
    std::string badany_ciag;
    char wczytany_znak;
    Symbole symbol_na_wejscie;

    DFA.zresetuj_automat();
    while (!DFA.czy_jest_w_stanie_akceptujacym())
    {
        std::cin >> wczytany_znak;
        if (czy_nalezy_do_alfabetu(wczytany_znak))
        {
            symbol_na_wejscie = zamien_na_symbol(wczytany_znak);
            DFA.funkcja_przejscia(symbol_na_wejscie);
        }
        else
        {
            std::cout << "Error: \""<< wczytany_znak <<"\" to symbol spoza alfabetu" << std::endl;
            DFA.zresetuj_automat();
            break;
        }
    }
    //
    if (DFA.czy_jest_w_stanie_akceptujacym())
    {
        std::cout << "Badanie ciagu zakonczone\n   ";
        DFA.przedstaw_zakonczenie();
    }
    return 0;
}

