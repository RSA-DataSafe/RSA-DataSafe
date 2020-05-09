#ifndef _generation_cle_h
#define _generation_cle_h
#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "euclide.h"
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h> 
#include <assert.h>
#include <sys/types.h>
#include <time.h>
#include "primalite.h"
#include "bbs.h"
#include "euclide.h"
#include "../calcul/calcul.h"
#include "../structure/structure.h"

/**
 * Procédure qui permet de calculer "p", "q" et "n" de RSA
 * @param p : résultat, généré par la fonction
 * @param q : résultat, généré par la fonction
 * @param n : résultat, généré par la fonction
 * @param taille : taille du module RSA
 * */
void GenererPQRSA(mpz_t p, mpz_t q, mpz_t n, int taille);

/**
 * Procédure qui permet de calculer phi(n) = (p -1) * (q-1)
 * @param p : p de RSA
 * @param q : q de RSA
 * @param phi_n : résultat, calculer par la fonction 
 * */
void calculPhi(mpz_t p, mpz_t q, mpz_t phi_n);

/**
 * Calcul de la clé publique (n,e) tel que pgcd(e,phi(n)) = 1 et e < phi
 * @param publique : clé publique
 * */
void calculerE(cle_publique *publique,mpz_t phi);

/**
 * Calcul de l'exposant privé "d" tel que  (e*d = 1 mod phi)
 * @param prive : clé privé
 * @param publique : clé publique
 * */
void calculerD(cle_prive *prive, cle_publique *publique,mpz_t phi);

/**
 * Génère les clés
 * @param prive : clé privé
 * @param publique : clé publique
 * @param taille : taille du module RSA
 * */
void genere_cle(cle_publique *publique, cle_prive *prive, int taille);

#endif // !_generation_cle_h

