#ifndef AUTOMATDETERMINISTYCZNY_H
#define AUTOMATDETERMINISTYCZNY_H

#include "enumeratory.h"

class AutomatDeterministyczny
{
  private:
	  MozliweStany stan;
	  bool czy_koniec;
  public:
	  const MozliweStany stan_poczatkowy = MozliweStany::q0;
	  AutomatDeterministyczny();
	  void funkcja_przejscia(Symbole s);
	  void przedstaw_zakonczenie();
	  bool powiedz_czy_koniec();
	  void wymuszenie_zakonczenia();
	  void zresetuj_automat();
};

#endif