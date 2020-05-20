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
//Calcul de phi(n) , avec phi(n)=(p-1)(q-1) , p et q etant des nombres premiers
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
	//e doit etre premier avec phi(n) , donc pgcd(e,phi(n))=1
	while (mpz_cmp_ui(res, 1)!= 0){
		mpz_add_ui(tmp, tmp, 2);       // on rajoute 2 car e etre obligatoirement impaire sinon il ne peut pas satisfaire la condition
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
	// calcul de d, d=e^(-1) mod phi(n)
	euclide_etendu(u , v, prive->n, publique->e);
	// si d est negatif on effectue d= d+pi(n) car congru a phi(n)
	if(mpz_cmp_ui(v,0) < 0)
	{
		
		mpz_add(v,v,prive->n);
	}
	
	mpz_set(prive->d,v);
	mpz_set(prive->n,publique->n);
	mpz_clears(u,v,gcd,NULL);
	
}
void GenererPQRSA(mpz_t p, mpz_t q, mpz_t n, int taille){
	 mpz_t t; 
         mpz_init(t);
         mpz_set_ui(t,40);
			
		// on genère p , nombre premier de 1024 bits avec bbs 
		do{
			bbs(p,taille);
			mpz_nextprime(p,p);
			
		}while(mpz_cmp_ui(p,0)<=0 || miller_rabbin(p,t)!=1  );
		// on genère q, nombre premier de 1023 bits pour avoir un N=p.q de taille 2048
		do{
			bbs(q,taille-1);
			mpz_nextprime(q,q);
			mpz_mul(n,p,q);
			
		// on verifie si p et q ne sont pas egaux et si q est different de zéro et on teste la primalité et la taille en bit de N
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
	
	// calcul de l'exposant pulique e
	calculerE(publique);
	mpz_set(publique->n,n);
	
	mpz_set(prive->n,phi_n);
	//calcul de d (clé privée) inverse de e mod(phi(n))
	calculerD(prive, publique);

	mpz_clears(p,q,n,phi_n, NULL);


}
