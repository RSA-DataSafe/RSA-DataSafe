#include "conversion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

message * conversion_char_mpz( char * chaine ) {
	char byte[8]; 	// Un élément de 8 bits
	int len_chaine = strlen(chaine);
	char * res = malloc((sizeof(char) * 7) * len_chaine); // Non signé
	
	if(res == NULL) {
		fprintf(stderr,"Erreur d'allocation de Mémoire");
		exit(0);
	}

	message * m;
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
	return ret;
}
