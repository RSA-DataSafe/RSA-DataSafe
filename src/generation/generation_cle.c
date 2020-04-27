#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "euclide.h"
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include <sys/types.h>
#include <time.h>
#include "primalite.h"


void calculPhi(mpz_t p, mpz_t q, mpz_t phi_n){
    mpz_t tmp1,tmp2;
    mpz_init(tmp1);
    mpz_init(tmp2);
 //pour ne pas perdre la valeur de p et q 
	mpz_sub_ui(tmp1,p,1);
	mpz_sub_ui(tmp2,q,1);
	//phi(n)=(p-1)(q-1)
	mpz_mul(phi_n,tmp1,tmp2);	
	mpz_clear(tmp2);
	mpz_clear(tmp1);
}


void calculerE(cle_publique *publique,mpz_t phi){//ici on a aussi oublier le paramtre 
	
  time_t t; 
  int seed;
  seed = (int) time(&t);
  gmp_randstate_t etat ;
  gmp_randinit_default(etat);
  gmp_randseed_ui(etat, seed);
  mpz_t gcd;
  mpz_init(gcd);
  for(;;)
  {
  	   mpz_urandomm(publique->e, etat,phi);//parce que on a oublié de mettre le paramètre phi_n
  	   mpz_gcd(gcd,publique->e,phi); 
  	   if(mpz_cmp_ui(gcd,1)==0 && mpz_cmp_ui(publique->e,0)!=0 && mpz_cmp_ui(publique->e,1)!=0)
  	   {
           break;
  	   }

  }

		
	}

void calculerD(cle_prive *prive, cle_publique *publique,mpz_t phi){ //on a oublier le paramètre phi
    mpz_t u;
	mpz_init(u);
	mpz_t v;
	mpz_init(v);
	euclide_etendu(u, v, phi, publique->e);
	
	if(mpz_cmp_ui(v, 0) < 0) {
		while( mpz_cmp_ui(v, 0) < 0) {
			mpz_add(v, v, phi);
		}
	}
	mpz_set(prive->d, v);
	mpz_clear(u);
	mpz_clear(v);
}

void GenererPQRSA(mpz_t p, mpz_t q, mpz_t n, int taille){
	
	mpz_t ite;
	mpz_init(ite);
	mpz_set_ui(ite,1);
     for(;;)
	{
		bbs(p,taille/2);
		mpz_out_str(0,10,p);
		printf("\n\n");
     if((miller_rabbin(p,ite)==1))
      {
	       break;
      }
    }
   for(;;)
		{
			bbs(q,taille/2);
			if(miller_rabbin(q,ite)==1 &&  mpz_cmp(q,p)!=0)
			{
				break;
			}
		

	}

	mpz_mul(n,p,q);
	mpz_clear(ite);

	}
void genere_cle(cle_publique *publique, cle_prive *prive, int taille){//taille c est 2048
   
	mpz_t p;
	mpz_init(p);
	mpz_t q;
	mpz_init(q);
	mpz_t n;
	mpz_init(n);
	mpz_t phi;
	mpz_init(phi);
    GenererPQRSA(p,q,n,taille);
	calculPhi(p,q,phi);
	calculerE(publique,phi);
    calculerD(prive,publique,phi);
    mpz_clear(p);
    mpz_clear(q);
    mpz_clear(phi);
    mpz_clear(n);
}
