#ifndef _bbs_h
#define _bbs_h
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <string.h>
#include <time.h>
#include "bbs.h"
#include "primalite.h"
#include <math.h>

/**
 * Génère un blum prime "p", tel que   p mod 4 = 3
 * @param p : blum prime généré
 * @param taille : nombre de bit du nombre à générer
 * */
void blum_prime(mpz_t p, int taille);

/**
 * Génère un nombre "s" aléatoirement tel que 1 <= s <= n-1
 * @param s : résultat
 * @param n : nombre "n"
 * */
void GenererS(mpz_t s, mpz_t n);

/**
 * BBS 
 * @param res : résultat
 * @param taille : nombre de bit du nombre à générer
 * */
void bbs(mpz_t res, int taille);

#endif // !_bbs_h