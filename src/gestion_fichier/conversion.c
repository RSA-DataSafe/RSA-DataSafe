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

message *conversion_hexa_mpz ( char *chaine ) {
	int len_chaine = strlen(chaine);

	message *m = malloc(sizeof(message));
	mpz_init(m->nombre);
	mpz_init(m->taille);

	mpz_set_ui(m->taille, 4);
	mpz_mul_ui(m->taille, m->taille, len_chaine);

	for (int i = 0; i < len_chaine; i++)
	{
		int tmp = chaine[i];
		if(tmp >= 48 && tmp <= 57) {
			tmp -= 48;
		}
		else if (tmp >= 97 && tmp <= 102) {
			tmp -= (97 - 10);
		}
		else {
			exit(666);
		}
		mpz_mul_2exp(m->nombre, m->nombre, 4);
		mpz_add_ui(m->nombre, m->nombre, tmp);
	}
	
	return m;
}

char *conversion_mpz_hexa ( message *m ) {
	mpz_t mpz_taille;
	mpz_init(mpz_taille);
	mpz_div_ui(mpz_taille, m->taille, 4);

	int taille = mpz_get_ui(mpz_taille);

	char *chaine = malloc(sizeof(char) * (taille + 1) );
	chaine[taille] = '\0';

	mpz_t mpz_char;
	mpz_init(mpz_char);

	mpz_t AND;
	mpz_init(AND);
	mpz_set_ui(AND, 15);

	for (int i = 0; i < taille; i++)
	{
		mpz_tdiv_q_2exp(mpz_char, m->nombre, (taille - (i+1)) * 4);
		mpz_and(mpz_char, mpz_char, AND);
		char tmp = mpz_get_ui(mpz_char);
		if(tmp > 15 || tmp < 0) {
			exit(666);
		}
		if(tmp < 10) {
			tmp += 48;
		}
		else {
			tmp += 87;
		}
		chaine[i] = tmp;
	}
	
	return chaine;
}