#include "conversion.h"

message * conversion_char_mpz( char * chaine ) {
	char byte[8]; 	// Un élément de 8 bits
	int len_chaine = strlen(chaine);
	char * res = malloc((sizeof(char) * 7) * len_chaine); // Non signé
	Message m;
	char c;
	int j;
	mpz_t message;

	message.taille = (sizeof(char) * 7) * len_chaine;	
	for(int i = 0 ; i < len_nbr ; i++) {
		c = nbr[i];
		for(j = 6 ; j >= 0 ; j--) {
			byte[j] = 48 + (c & 1); // On le met sous forme ascii
			c = c >> 1;
		} 	
		strcat(res,byte); // Concatene un Byte dans la chaine de caractères	
	}
	mpz_init_set_str(message,res,2); // Le nombre en base de deux sera en ascii
	m.message = message;
	return &m; // Pour éviter de faire un malloc pour un élément
}

char * conversion_mpz_char( message * m ) {
	return NULL;
}
