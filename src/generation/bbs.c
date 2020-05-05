#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <string.h>
#include <time.h>
#include "bbs.h"
#include "primalite.h"
#include <math.h>

void  blum_prime(mpz_t p, int  taille)
{
  gmp_randstate_t etat ;
  gmp_randinit_default(etat);
  gmp_randseed_ui(etat, (unsigned)clock());
  for(;;)
 {
  mpz_urandomb(p, etat, taille); 
  mpz_nextprime(p,p);
  if( mpz_fdiv_ui(p,4)==3 )
  {
         break;
  }
} gmp_randclear(etat); 
}
void  GenererS(mpz_t s, mpz_t n)
{
  gmp_randstate_t etat ;
  gmp_randinit_default(etat);
  gmp_randseed_ui(etat,(unsigned)clock());
  mpz_t res;
  mpz_init(res);
  mpz_sub_ui(res,n,2);
  mpz_urandomm (s, etat, res);
  mpz_add_ui(s,s,1);
  mpz_clear(res);
  gmp_randclear(etat);
}
void  bbs(mpz_t res , int  taille)
{
    mpz_t p;
    mpz_t q; 
    mpz_init(p);
    mpz_init(q);
    mpz_t n;
    mpz_init(n);
    mpz_t s;
    mpz_init(s);
    mpz_t tmp;
    mpz_init(tmp);
    mpz_t mod;
    mpz_init(mod);
    int j=0;
    blum_prime(p,taille);
    do
    {
     blum_prime(q,taille);
    }while(mpz_cmp(p,q)==0);
    mpz_mul(n,p,q);
    GenererS(s,n);
    mpz_setbit(tmp,taille-1);
    while(j<taille)
    {
     mpz_powm_ui(mod,s,2,n);
     if(mpz_odd_p(mod)!=0) mpz_setbit(tmp,taille-1-j) ;
     mpz_set(s,mod);
     j++;
      if(mpz_cmp_ui(mod,0)==0) break;
    }
      mpz_set(res,tmp);
      mpz_clear(p);
      mpz_clear(q);
      mpz_clear(s);
      mpz_clear(n);
      mpz_clear(tmp);
      mpz_clear(mod);

} 
