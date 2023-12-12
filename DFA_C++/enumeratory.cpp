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

std::string symbol_wejsciowy_jako_string(Symbole s)
{
    std::string tekstowo;
    if (s == Symbole::m1) { tekstowo = "m1"; }
    else if (s == Symbole::m2) { tekstowo = "m2"; }
    else { tekstowo = "m3"; }
    return tekstowo;
}

std::string stan_jako_string(MozliweStany s)
{
    std::string tekstowo;
    if (s == MozliweStany::q0) { tekstowo = "q0"; }
    else if (s == MozliweStany::q1) { tekstowo = "q1"; }
    else if (s == MozliweStany::q2) { tekstowo = "q2"; }
    else if (s == MozliweStany::q3) { tekstowo = "q3"; }
    else if (s == MozliweStany::q4) { tekstowo = "q4"; }
    else if (s == MozliweStany::q5) { tekstowo = "q5"; }
    else if (s == MozliweStany::q6) { tekstowo = "q6"; }
    else if (s == MozliweStany::q7) { tekstowo = "q7"; }
    else if (s == MozliweStany::q8) { tekstowo = "q8"; }
    else if (s == MozliweStany::q9) { tekstowo = "q9"; }
    else if (s == MozliweStany::q10) { tekstowo = "q10"; }
    else if (s == MozliweStany::q11) { tekstowo = "q11"; }
    else if (s == MozliweStany::q12) { tekstowo = "q12"; }
    else if (s == MozliweStany::q13) { tekstowo = "q13"; }
    else if (s == MozliweStany::q14) { tekstowo = "q14"; }
    else if (s == MozliweStany::q15) { tekstowo = "q15"; }
    else if (s == MozliweStany::q16) { tekstowo = "q16"; }
    else if (s == MozliweStany::q17) { tekstowo = "q17"; }
    else if (s == MozliweStany::q18) { tekstowo = "q18"; }
    else { tekstowo = "q19"; }
    return tekstowo;
}
