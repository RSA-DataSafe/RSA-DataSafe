#include "conversion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>

message * conversion_char_mpz( char * chaine ) {
	char byte[8]; 	
	int len_chaine = strlen(chaine);
	char * res = malloc((sizeof(char) * 7) * len_chaine); // Non signé
	
	if(res == NULL) {
		fprintf(stderr,"Erreur d'allocation de Mémoire");
		exit(0);
	}
   strcpy(res,"");
	message * m;
	m = malloc(sizeof(message));
	char c;
	int j;
	
	mpz_init_set_ui(m->taille, (sizeof(char) * 7) * len_chaine);	
	
	for(int i = 0 ; i < len_chaine ; i++) {
		c = chaine[i];
		for(j = 6 ; j >= 0 ; j--) {
			byte[j] = 48 + (c & 1); // On le met sous forme ascii
			c = c >> 1;
		} 	
		strcat(res,byte); // Concatene un Byte dans la chaine de caractères	
	}
	
	mpz_init_set_str(m->nombre,res,2); // Le nombre en base de deux sera en ascii
	free(res);
	mpz_out_str(stdout,10,m->nombre);
	return m;
}

char * conversion_mpz_char( message * m ) {
	char * str = malloc(sizeof(char) * mpz_get_ui(m->taille));
	char * ret = malloc(sizeof(char) * (mpz_get_ui(m->taille)/7) + 1); // On divise par la longueur d'un byte + \0 
	
	if(mpz_get_str(str,2,m->nombre) == NULL || str == NULL) { // mpz renvoie NULL si problème de stockage  
		fprintf(stderr,"Erreur d'allocation de Mémoire");
		exit(0);
	}
	
	char caractere = 0;
	int k = 0;
	for(int i = 1 ; i <= mpz_get_ui(m->taille) / 7 ; i++) {
		for(int j = 0 ; j < 7 ; j++) {
			caractere = caractere << 1; 
			caractere = caractere | !(49-str[k]); // On fait un OU comme masquage; !(49-str[k]) pour ne pas que ca fasse -1
			k++;
		}	
		ret[i-1] = caractere;
		caractere = 0;
	}
	
	free(str);
	ret[mpz_get_ui(m->taille)/7] = '\0';
	printf("%s\n", ret);
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