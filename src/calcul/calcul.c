#include <gmp.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>


/**
 * Calcul L'exponentiation modulaire 
 * */
void expo_mod(mpz_t res, mpz_t num, mpz_t exp, mpz_t mod){

    
    // taille de l'eposant "exp" en nombre de bit
    int j=mpz_sizeinbase(exp,2);
    
    //on commence à partir de l'indice 0 et pour le premier bit on liste le nombre simplement
    j=j-2;
    mpz_set(res, num);
    
    for(int i=j; i>=0; i--){
        // si bit à 0 square
        mpz_mul(res,res,res);
        mpz_mod(res,res,mod);
		// si bit à 1 mutiply en plus du square 
        if( mpz_tstbit(exp, i) == 1 ) { 
            mpz_mul(res,res, num);
            mpz_mod(res,res,mod);
		}
    }
}


void shift_gauche(mpz_t nombre, int decalage)
{
  mpz_mul_2exp (nombre,nombre, decalage);
}
void shift_droite(mpz_t nombre, int decalage)
{
mpz_tdiv_q_2exp(nombre,nombre,decalage);
}
