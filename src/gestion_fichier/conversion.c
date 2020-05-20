#include "conversion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>

message * conversion_char_mpz( char * chaine ) {
	int len_chaine = strlen(chaine);
	message *m= malloc(sizeof(message));
	
	mpz_init_set_ui(m->taille, 8 * len_chaine);
	mpz_init(m->nombre);
	
	for(int i = 0 ; i < len_chaine ; i++) {
		mpz_mul_2exp(m->nombre, m->nombre, 8);
		mpz_add_ui(m->nombre, m->nombre, chaine[i]);
	}
	return m;
}

char * conversion_mpz_char( message * m ) {
	mpz_t mpz_taille;
	mpz_init(mpz_taille);
	mpz_div_ui(mpz_taille, m->taille, 8);

	int taille = mpz_get_ui(mpz_taille);
	char * ret = malloc(sizeof(char) * ( taille + 1 ) ); // On divise par la longueur d'un byte + \0 
	ret[taille] = '\0';

	mpz_t tmp;
	mpz_init(tmp);

	mpz_t AND;
	mpz_init(AND);

	mpz_set_ui(AND, 255);

	int max = mpz_get_ui(m->taille);

	for(int i = taille - 1 ; i >= 0 ; i--) {
		mpz_set(tmp, m->nombre);
		mpz_div_2exp(tmp, tmp, max - (i + 1 ) * 8 );
		mpz_and(tmp, tmp, AND);
		ret[i] = mpz_get_ui(tmp);
	}

	return ret;
}


