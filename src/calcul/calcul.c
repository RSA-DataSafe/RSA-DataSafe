#include "calcul.h"
void expo_mod(mpz_t res, mpz_t x, mpz_t n, mpz_t m)
{
    mpz_t e1;
    mpz_init(e1);
    mpz_set_ui(res,1);
    mpz_t tmp;
    mpz_init(tmp);
    while(mpz_cmp(e1,n)<0)
    { 
      mpz_add_ui(e1,e1,1);
      mpz_mul(tmp,x,res);
      mpz_mod(res,tmp,m);
    }
}
void shift_gauche(mpz_t nombre, int decalage)
{
  mpz_mul_2exp (nombre,nombre, decalage);
}
void shift_droite(mpz_t nombre, int decalage)
{

}