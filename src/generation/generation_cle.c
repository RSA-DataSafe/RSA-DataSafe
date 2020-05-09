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
/**
 * Procédure qui permet de calculer phi(n) = (p -1) * (q-1)
 * @param p : p de RSA
 * @param q : q de RSA
 * @param phi_n : résultat, calculer par la fonction 
 * */
void calculPhi(mpz_t p, mpz_t q, mpz_t phi_n){
	//p-1
	mpz_sub_ui(p,p,1);
	//q-1
	mpz_sub_ui(q,q,1);
	//phi(n)=(p-1)(q-1)
	mpz_mul(phi_n,p,q);	
}

/**
 * Calcul de la clé publique (n,e) tel que pgcd(e,phi(n)) = 1 et e < phi
 * @param publique : clé publique
 * */
void calculerE(cle_publique *publique, mpz_t phi){
	//valeur aléatoire ,servira pour le choix de la valeur de e 
	srand(time(NULL));
	int tmp=rand()%4;

	int val[5]={3,5,17,257,65537};

	// valeur de e
	do
	{
		mpz_set_ui(publique->e,val[tmp]);
	}while(mpz_cmp(publique->e,phi)>0);
		
	}

/**
 * Calcul de l'exposant privé "d" tel que  (e*d = 1 mod phi)
 * @param prive : clé privé
 * @param publique : clé publique
 * */
void calculerD(cle_prive *prive, cle_publique *publique, mpz_t phi){
	mpz_t u,v;
	mpz_inits(u,v,NULL);
	euclide_etendu(u , v, phi, publique->e);
	if(mpz_cmp_ui(v,0)<0)
	{
         while(mpz_cmp_ui(v,0)<0)
         {
         	mpz_add(v,v,phi);
         }
	}
	mpz_set(prive->d,v);
	mpz_clears(u,v,NULL);
}

void GenererPQRSA(mpz_t p, mpz_t q, mpz_t n, int taille){

         mpz_t t; 
         mpz_init(t);
         mpz_set_ui(t,40);
		do{
			bbs(p,taille);
			}while(mpz_cmp_ui(p,0)==0|| miller_rabbin(p,t)!=1);
				mpz_set(n,p);

		do{
			bbs(q,taille);

		}while(mpz_cmp_ui(q,0)==0 || miller_rabbin(q,t)!=1|| mpz_cmp(p,q)==0);
			mpz_mul(n,n,q);
	


   
	}
void genere_cle(cle_publique *publique, cle_prive *prive, int taille){

	mpz_t p,q,n,phi_n;
	mpz_inits(p,q,n,phi_n, NULL);
	GenererPQRSA(p,q,n,taille);
	mpz_mul(n,p,q);
	mpz_set(publique->n,n);
	mpz_set(prive->n,n);
	calculPhi(p,q,phi_n);
	calculerE(publique, phi_n);
	calculerD(prive, publique, phi_n);
	mpz_clears(p,q,n,phi_n, NULL);
}
