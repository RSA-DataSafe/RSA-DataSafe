#include <gmp.h>
#include <stdio.h>
#include "../structure/structure.h"
#include "../calcul/calcul.h"
#include "../chiffrement/gestion_block.h"
#include "oaep_1.h"
#include <stdlib.h>
#include "dechiffrement.h"


message* dechiffrement(message *c, cle_prive *prive) {

	// Initialisation
	message * m;
	block * b; 
	b = creer_block_oaep_1(c);

	// Code
	// RSA
	for (int i = 0; i < b->nb_block; i++) {
		mpz_powm(b->tab[i], b->tab[i], prive->d, prive->n);
		gmp_printf("dans l for %Zd \n",b->tab[0]);
		printf("i %d\n",i);
		printf("taille  %d\n",mpz_sizeinbase(b->tab[i],2));
	}
	

	// OAEP^(-1)
	oaep_1(b);
	gmp_printf("apres l for %Zd \n",b->tab[0]);
	    				char* oui=malloc(sizeof(char)*3000);
    				mpz_get_str(oui,2,b->tab[0]);
    				printf("le nombre  %s\n",oui);
				free(oui);
			printf("taille app  %d\n",mpz_sizeinbase(b->tab[0],2));
	m = recupere_message_oaep_1(b);
				printf("taille app  %d\n",mpz_sizeinbase(b->tab[0],2));
	for(int i = 0; i < (b->nb_block); i++) {
        mpz_clear(b->tab[i]);
    }
    free(b->tab);

	return m;
	

	
}
