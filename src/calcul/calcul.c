#include <gmp.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>



void expo_mod(mpz_t res, mpz_t num, mpz_t exp, mpz_t mod){
    //A corriger parce que si on remplace mpz_powm par expo_mod ds la fct chiff et dechiff et sign ca donne pas d bn rslt 
    mpz_set(res, num);
    // taille de l'eposant "exp" en nombre de bit
    int j=mpz_sizeinbase(exp,2);
    //-2 car on compte pas le bit de poid fort et on commence à partir de l'indice 0
     j=j-2;
   for(int i=j; i>=0; i--)
    {
        // si bit à 0 square
        mpz_mul(res,res,res);
        mpz_mod(res,res,mod);
		// si bit à 1 mutiply en plus du square 
        if( mpz_tstbit(exp, i) == 1 ) 
        { 
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
