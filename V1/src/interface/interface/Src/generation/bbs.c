#include "bbs.h"
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


}
     gmp_randclear( etat );

  
}
//Génère un  nombre "s" aléatoirement  tel que 1  <= s  <= n-1
void  GenererS(mpz_t s, mpz_t n)
{
  
  mpz_t res;
  mpz_init(res);
  gmp_randstate_t etat ;
  gmp_randinit_default(etat);
  gmp_randseed_ui(etat,(unsigned)time(NULL));
  mpz_sub_ui(res, n, 2);
  mpz_urandomm (s, etat, res);
  mpz_add_ui(s, s, 1);
    mpz_clear(res);
    gmp_randclear( etat );

}
//générer un nombre res d taille souhaité 
void  bbs(mpz_t res , int  taille)
{
    mpz_t p, q,n,s,tmp,mod;
    mpz_inits(p,q,n,s,tmp,mod,NULL);
    int j=0;
     blum_prime(p,taille/10);
    do
    {
     blum_prime(q,taille/10);
    }while(mpz_cmp(p,q)==0);
    mpz_set_ui(tmp,1);
    mpz_mul(n,p,q);
    GenererS(s,n);
    mpz_setbit(tmp,taille);
    while(j<taille-1)
    {
      mpz_powm_ui(mod,s,2,n);
      if(mpz_odd_p(mod)!=0) mpz_setbit(tmp,taille-1-j) ;
      mpz_set(s,mod);
      j++;
      if(mpz_cmp_ui(mod,0)==0)
        break;
    }
  
      mpz_set(res,tmp);

      mpz_clears(p,q,n,s,tmp,mod,NULL);

}