#ifndef AUTOMATDETERMINISTYCZNY_H
#define AUTOMATDETERMINISTYCZNY_H

#include "enumeratory.h"

class AutomatDeterministyczny
{
  private:
	  MozliweStany stan;
  public:
	  const MozliweStany stan_poczatkowy = MozliweStany::q0;
	  AutomatDeterministyczny();
	  void funkcja_przejscia(Symbole s);
	  void przedstaw_zakonczenie();
	  void zresetuj_automat();
	  MozliweStany daj_aktualny_stan();
	  bool czy_jest_w_stanie_akceptujacym();
};

#endif