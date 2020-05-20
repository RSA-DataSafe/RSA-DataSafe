#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <string.h>
#include <time.h>
#include "bbs.h"
#include <math.h>

//cette fonction permet de generer un nombre p tel que p mod 4=3 
void  blum_prime(mpz_t p, int  taille)
{
  
  gmp_randstate_t etat ;
  gmp_randinit_default(etat);
  gmp_randseed_ui(etat, (unsigned)clock());
  //tant que on a pas p%4=3 on boucle 
  for(;;)
 {
  mpz_urandomb(p, etat, taille); //generation aléatoire d'un nombre p de taille 'taille'
  mpz_nextprime(p,p);//le premier nombre premier a partir de p 

  if( mpz_fdiv_ui(p,4)==3 )//si p % 4=3 alors on fait un break (on a obtenu un nombre blum prime)
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
  mpz_sub_ui(res, n, 2);//res=n-2
  mpz_urandomm (s, etat, res);// 0<=s<=n-2
  mpz_add_ui(s, s, 1);//pn ajoute 1 pour que s soit entre 1 et n-1
  mpz_clear(res);//liberer la mémoire 
  gmp_randclear( etat );

}
//générer un nombre res de taille souhaité  en appliquant l'algor blum blum shub
void  bbs(mpz_t res , int  taille)
{
    mpz_t p, q,n,s,tmp,mod;
    mpz_inits(p,q,n,s,tmp,mod,NULL);
    int j=0;
     blum_prime(p,taille/10); //generer un nombre blum prime p de taille/10
    do
    {
     blum_prime(q,taille/10);//generer un nombre blum prime q de taille/10
    }while(mpz_cmp(p,q)==0);//on boucle tant que p et q sont égaux 
    mpz_set_ui(tmp,1);
    mpz_mul(n,p,q);
    GenererS(s,n);//generer une graine aléatoire s tel que 1<=s<=n-1 
    mpz_setbit(tmp,taille);
    while(j<taille-1)
    {
      mpz_powm_ui(mod,s,2,n); //mod = s^2 mod n
      if(mpz_odd_p(mod)!=0) mpz_setbit(tmp,taille-1-j) ;//on test si mod est pair ou impair 
      //si c'est pair on affecte à tmp 1 sinon 0
      mpz_set(s,mod);
      j++;
      //si mod ==0 on arrete l'opération 
      if(mpz_cmp_ui(mod,0)==0)
        break;
    }
  
      mpz_set(res,tmp);//res = tmp
      mpz_clears(p,q,n,s,tmp,mod,NULL);//libération d la mémoire

}
