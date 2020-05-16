#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "euclide.h"
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h> 
#include <assert.h>
#include <sys/types.h>
#include <time.h>
#include "primalite.h"
#include "../structure/structure.h"
#include "bbs.h"
#include "generation_cle.h"

void calculPhi(mpz_t p, mpz_t q, mpz_t phi_n){
	//p-1
	mpz_t p1,q1;
	mpz_inits(p1,q1,NULL);
	mpz_set(p1,p);
	mpz_set(q1,q);
	mpz_sub_ui(p1,p1,1);
	//p-1
	mpz_sub_ui(q1,q1,1);
	//phi(n)=(p-1)(q-1)
	mpz_lcm(phi_n,p1,q1);	
	mpz_clears(p1,q1,NULL);
}

/**
 * Calcul de la clé publique (n,e) tel que pgcd(e,phi(n)) = 1 et e < phi
 * @param publique : clé publique
 * */
void calculerE(cle_publique *publique){
	mpz_t res, tmp;
	mpz_inits(res,tmp,NULL);
	mpz_set_ui(tmp, 3);
	mpz_gcd(res, tmp, publique->n);

	while (mpz_cmp_ui(res, 1)!= 0){
		mpz_add_ui(tmp, tmp, 2);
		mpz_gcd(res, tmp, publique->n);
	}

	mpz_set(publique->e, tmp);
	mpz_clears(res, tmp, NULL);	
		
	}

/**
 * Calcul de l'exposant privé "d" tel que  (e*d = 1 mod phi)
 * @param prive : clé privé
 * @param publique : clé publique
 * */
void calculerD(cle_prive *prive, cle_publique *publique){
	mpz_t u,v,gcd;
	mpz_inits(u,v,gcd,NULL);
	mpz_gcd(gcd, publique->e,prive->n );
	euclide_etendu(u , v, prive->n, publique->e);
	mpz_set(prive->d,v);
	mpz_set(prive->n,publique->n);
	mpz_clears(u,v,gcd,NULL);
	
}
void GenererPQRSA(mpz_t p, mpz_t q, mpz_t n, int taille){
	 mpz_t t; 
         mpz_init(t);
         mpz_set_ui(t,40);
			

		do{
			bbs(p,taille);
			mpz_nextprime(p,p);
			printf("dans q\n");
		}while(mpz_cmp_ui(p,0)<=0 || miller_rabbin(p,t)!=1  );

		do{
			bbs(q,taille-1);
			mpz_nextprime(q,q);
			mpz_mul(n,p,q);
			printf("dans q\n");
	
		}while( mpz_cmp(p,q)==0 || mpz_cmp_ui(q,0)<=0 || miller_rabbin(q,t)!=1|| (mpz_sizeinbase(n,2)!=2048));
		
	mpz_clear(t);
	}
void genere_cle(cle_publique *publique, cle_prive *prive, int taille){

	mpz_t p,q,n,phi_n;
	mpz_inits(p,q,n,phi_n, NULL);
	//génération de p et q
	GenererPQRSA(p,q,n,taille);
	mpz_mul(n,p,q);
	//calcul de phi(n)
	calculPhi(p,q,phi_n);
	
	mpz_set(publique->n,phi_n);
	
	// choix de l'exposant pulique e
	calculerE(publique);
	mpz_set(publique->n,n);
	
	//pour avoir la valeur de phi(n) qui nous servira pour le calcul de d
	mpz_set(prive->n,phi_n);

	calculerD(prive, publique);
	mpz_clears(p,q,n,phi_n, NULL);
}
/*
#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "euclide.h"
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h> 
#include <assert.h>
#include <sys/types.h>
#include <time.h>
#include "primalite.h"
#include "../structure/structure.h"
#include "bbs.h"
#include "generation_cle.h"

void calculPhi(mpz_t p, mpz_t q, mpz_t phi_n){
	//p-1
	mpz_t p1,q1;
   mpz_inits(p1,q1,NULL);
	mpz_sub_ui(p1,p,1);
	//p-1
	mpz_sub_ui(q1,q,1);
	//phi(n)=(p-1)(q-1)
	mpz_mul(phi_n,p1,q1);	
}


void calculerE(cle_publique *publique){

	//valeur aléatoire ,servira pour le choix de la valeur de e 

	mpz_t pgcd;
	mpz_init(pgcd);
	gmp_randstate_t etat ;
  gmp_randinit_default(etat);
  gmp_randseed_ui(etat, (unsigned)clock());
	do{
  mpz_urandomm(publique->e,etat,publique->n);
   mpz_gcd(pgcd,publique->e,publique->n);
	}while( mpz_cmp(publique->e, publique->n)>0  || mpz_cmp_ui(pgcd,1)!=0);


		
	}


void calculerD(cle_prive *prive, cle_publique *publique){
	mpz_t u,v;
	mpz_inits(u,v,NULL);

	euclide_etendu(u , v, prive->n, publique->e);

	mpz_set(prive->d,v);
	mpz_set(prive->n,publique->n);
	mpz_clears(u,v,NULL);
}
void GenererPQRSA(mpz_t p, mpz_t q, mpz_t n, int taille){
	 mpz_t t; 
         mpz_init(t);
         mpz_set_ui(t,40);int rps;
			

		for(;;){
			bbs(p,taille);
			if((mpz_cmp_ui(p,0)!=0 && miller_rabbin(p,t)==1)) break;
		
		}

		for(;;){
			bbs(q,taille-1);
			mpz_mul(n,p,q);
			if((mpz_cmp(p,q)!=0 && mpz_cmp_ui(q,0)!=0 &&  miller_rabbin(q,t)==1
	      && (mpz_sizeinbase(n,2)==2048))) break;
	
		}


	mpz_clear(t);
	}
void genere_cle(cle_publique *publique, cle_prive *prive, int taille){

	mpz_t p,q,n,phi_n;
	mpz_inits(p,q,n,phi_n, NULL);
	//génération de p et q
	GenererPQRSA(p,q,n,taille);
	mpz_t un;
	mpz_init(un);
	mpz_set_ui(un,1);
	

	
	//calcul de phi(n)
	calculPhi(p,q,phi_n);

	//mpz_set(prive->n,phi_n);

	// choix de l'exposant pulique e
	mpz_set(publique->n,phi_n);//n=ph_n
	calculerE(publique);
	
	mpz_set(publique->n,n);

	//pour avoir la valeur de phi(n) qui nous servira pour le calcul de d
	mpz_set(prive->n,phi_n);
	

	calculerD(prive, publique);
	mpz_set(prive->n,publique->n);
	printf("phi_n =  ");
	mpz_out_str(0,10,phi_n);
	printf("\n\n");
	

 
	mpz_clears(p,q,n,phi_n, NULL);
}



*/
