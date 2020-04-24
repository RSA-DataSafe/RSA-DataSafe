#include "../calcul/calcul.h"
#ifndef _primalite_h
#define _primalite_h

/**
 * Test si "n" est un témoin de Miller, donc composé sinon probablement premier
 * @param a : nombre aléatoire compris dans l'intervalle [2, n – 2]
 * @param n : nombre à tester
 * @return retourne 1 si c'est un témoin de Miller, 0 sinon
 *on a oublié un paramètre 
 * */
int temoin_de_miller(mpz_t a , mpz_t n);

/**
 * Test la primalité de "n"  
 * @param n : nombre à tester
 * @param nb_tour : nombre de fois à tester 
 * @return retourne 1 si il est probablement premier, 0 si n est composé 
 * */
int miller_rabbin(mpz_t n, mpz_t nb_tour);

#endif // !_primalite_h
