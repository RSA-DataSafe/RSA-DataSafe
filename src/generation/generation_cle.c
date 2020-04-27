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
#include "miller-rabin.h"

/**
 * Procédure qui permet de calculer phi(n) = (p -1) * (q-1)
 * @param p : p de RSA
 * @param q : q de RSA
 * @param phi_n : résultat, calculer par la fonction 
 * */
void calculPhi(mpz_t p, mpz_t q, mpz_t phi_n){
	//p-1
	mpz_sub_ui(p,p,1);
	//p-1
	mpz_sub_ui(q,q,1);
	//phi(n)=(p-1)(q-1)
	mpz_mul(phi_n,p,q);	
}

/**
 * Calcul de la clé publique (n,e) tel que pgcd(e,phi(n)) = 1 et e < phi
 * @param publique : clé publique
 * */
void calculerE(cle_publique *publique){
	//valeur aléatoire ,servira pour le choix de la valeur de e 
	srand(time(NULL));
	int tmp=rand()%4;

	int val[5]={3,5,17,257,65537};

	// valeur de e
	mpz_set_ui(publique->e,val[tmp]);
		
	}

/**
 * Calcul de l'exposant privé "d" tel que  (e*d = 1 mod phi)
 * @param prive : clé privé
 * @param publique : clé publique
 * */
void calculerD(cle_prive *prive, cle_publique *publique){
	mpz_t u,v;
	mpz_inits(u,v,NULL);
	euclide_etendu(u , v, prive->n, publique->e);
	mpz_set(prive->d,v);
	mpz_set(prive->n,publique->n);
	mpz_clears(u,v,NULL);
}

void GenererPQRSA(mpz_t p, mpz_t q, mpz_t n, int taille){

		do{
			bbs(p,taille);
			}while(mpz_cmp_ui(p,0)==0 || Miller_Rabin(p,4)!=1);
				mpz_set(n,p);

		do{
			bbs(q,taille);

		}while(mpz_cmp_ui(q,0)==0 || Miller_Rabin(q,4)!=1|| mpz_cmp(p,q)==0);
			mpz_mul(n,n,q);
	


   
	}
void genere_cle(cle_publique *publique, cle_prive *prive, int taille){

	mpz_t p,q,n,phi_n;
	mpz_inits(p,q,n,phi_n, NULL);
	//génération de p et q
	GenererPQRSA(p,q,n,taille);
	mpz_mul(n,p,q);
	//calcul de phi(n)
	calculPhi(p,q,phi_n);

	//mpz_set(prive->n,phi_n);

	// choix de l'exposant pulique e
	calculerE(publique);

	mpz_set(publique->n,n);

	//pour avoir la valeur de phi(n) qui nous servira pour le calcul de d
	mpz_set(prive->n,phi_n);
	

	calculerD(prive, publique);
	mpz_set(prive->n,publique->n);


	mpz_clears(p,q,n,phi_n, NULL);
}



