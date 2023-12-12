#include "enumeratory.h"

bool czy_nalezy_do_alfabetu(char sym)
{
    return (sym == '1' || sym == '2' || sym == '5');
}

Symbole zamien_na_symbol(char sym)
{
    Symbole symbol_alfabetu;
    if (sym == '1')
    {
        symbol_alfabetu = Symbole::m1;
    }
    else if (sym == '2')
    {
        symbol_alfabetu = Symbole::m2;
    }
    else
    {
        symbol_alfabetu = Symbole::m5;
    }
    return symbol_alfabetu;
}