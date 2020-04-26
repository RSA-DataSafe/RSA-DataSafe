#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <string.h>
#include <time.h>
#include "bbs.h"
//Génère un blum  prime "p", tel que    p mod 4 = 3 
void  blum_prime(mpz_t p, int  taille)
{
	time_t t;
	mpz_t nombre;
	mpz_init(nombre);
	mpz_t mod;
	mpz_init(mod);
	int seed;
	seed=(int) time(&t);
	gmp_randstate_t etat ;
	gmp_randinit_default(etat);
	gmp_randseed_ui(etat, seed);
	do
	{
		mpz_urandomb(nombre,etat,taille);
    printf("p=");
    mpz_out_str(stdout,10,nombre);
    printf("\n\n");
		mpz_mod_ui(mod,nombre,4);
	}while(mpz_cmp_ui(mod,3)!=0);
	mpz_set(p,nombre);
	mpz_clear(nombre);
	mpz_clear(mod);
}
//Génère un  nombre "s" aléatoirement  tel que 1  <= s  <= n-1
void  GenererS(mpz_t s, mpz_t n)
{
	time_t t;
	int seed=(int) time(&t);
	mpz_t res;
	mpz_init(res);
	gmp_randstate_t etat ;
	gmp_randinit_default(etat);
	gmp_randseed_ui(etat,seed);
	do{
         mpz_urandomm(res,etat,n);
	}while(mpz_cmp_ui(res,0)==0);
	mpz_set(s,res);
    mpz_clear(res);
}
//générer un nombre res d taille souhaité 
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
    do
    {
     blum_prime(p,taille);
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
    	if(mpz_cmp_ui(mod,0)==0)
    		break;
    }
      mpz_set(res,tmp);
      mpz_clear(p);
      mpz_clear(q);
      mpz_clear(s);
      mpz_clear(n);
      mpz_clear(tmp);
      mpz_clear(mod);

} 
