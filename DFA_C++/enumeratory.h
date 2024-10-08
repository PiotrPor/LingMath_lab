#pragma once

#include <string>

enum Symbole 
{
    m1,
    m2,
    m5
};

enum MozliweStany 
{
    q0,
    q1,
    q2,
    q3,
    q4,
    q5,
    q6,
    q7,
    q8,
    q9,
    q10,
    q11,
    q12,
    q13,
    q14,
    q15,
    q16,
    q17,
    q18,
    q19
};

bool czy_nalezy_do_alfabetu(char sym);
Symbole zamien_na_symbol(char sym);

std::string symbol_wejsciowy_jako_string(Symbole s);
std::string stan_jako_string(MozliweStany s);