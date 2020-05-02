#include <gmp.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>



void expo_mod(mpz_t res, mpz_t num, mpz_t exp, mpz_t mod){
    mpz_set(res, num);
    
    
    int j=mpz_sizeinbase(exp,2);
      j=j-2;
    
    for(int i=j; i>=0; i--)
    {
        
        mpz_mul(res,res,res);
        mpz_mod(res,res,mod);
		
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

}
