#include <gmp.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>



void expo_mod(mpz_t result, mpz_t number, mpz_t puissance, mpz_t mod){
    mpz_set(result, number);
    for(int i=mpz_sizeinbase(puissance,2)-2; i>=0; i--){
        // si bit à 0
        mpz_mul(result,result,result);
        mpz_mod(result,result,mod);

        if( mpz_tstbit(puissance, i) == 1 ) { // si bit à 1
            mpz_mul(result,result, number);// r <- r.a
            mpz_mod(result,result,mod);
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
