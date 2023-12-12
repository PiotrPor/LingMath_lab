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
    std::string testowe_ciagi[3];
    testowe_ciagi[0] = "555";
    testowe_ciagi[1] = "52215";
    testowe_ciagi[2] = "111112225";

    AutomatDeterministyczny DFA;
    unsigned int x, ktory_string;
    std::string badany_ciag;
    char wczytany_znak;
    Symbole symbol_na_wejscie;

    for (ktory_string = 0; ktory_string < 3; ktory_string++)
    {
        badany_ciag = testowe_ciagi[ktory_string];
        std::cout << "\n== Bada ciag nr " << ktory_string + 1 << ": " << badany_ciag << std::endl;
        //
        DFA.zresetuj_automat();
        for (x = 0; x < badany_ciag.size(); x++)
        {
            if (DFA.powiedz_czy_koniec())
            {
                std::cout << "Error przy analizie ciagu nr " << ktory_string + 1 << std::endl;
                std::cout << "Automat zakonczyl prace przed koncem ciagu" << std::endl;
                std::cout << "x=" << x << std::endl; //debug
                DFA.wymuszenie_zakonczenia();
                x = badany_ciag.size() + 5;
                continue;
            }
            wczytany_znak = badany_ciag[x];
            if (czy_nalezy_do_alfabetu(wczytany_znak))
            {
                symbol_na_wejscie = zamien_na_symbol(wczytany_znak);
                DFA.funkcja_przejscia(symbol_na_wejscie);
            }
        }
        //
        if (DFA.powiedz_czy_koniec() && x == badany_ciag.size())
        {
            std::cout << "Badanie ciagu nr " << ktory_string + 1 << " zakonczone\n   ";
            DFA.przedstaw_zakonczenie();
        }
    }
    return 0;
}

