#include <gmp.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef _calcul_h
#define _calcul_h

/**
 * Permet de réduire considérablement le temps de calcul des grandes puissances.
 * @param res : résultat
 * @param x : nombre
 * @param n : exposant
 * @param m : module
 * */
void expo_mod(mpz_t res, mpz_t num, mpz_t exp, mpz_t mod);

/**
 * Permet de faire une shift gauche
 * @param nombre : nombre à décaler (résultat)
 * @param decalage : nombre de bit à décaler
 */
void shift_gauche(mpz_t nombre, int decalage);

/**
 * Permet de faire une shift droite
 * @param nombre : nombre à décaler (résultat)
 * @param decalage : nombre de bit à décaler
 */
void shift_droite(mpz_t nombre, int decalage);

#endif // !_calcul_h