#include "oaep_1.h"
#include "dechiffrement.h"


message* dechiffrement(message *c, cle_prive *prive) {

	// Initialisation
	message * m;
	block * b; 
	b = creer_block_oaep_1(c);

	// Code
	// RSA
	for (int i = 0; i < b->nb_block; i++) {

		expo_mod(b->tab[i], b->tab[i], prive->d, prive->n);
	}

	// OAEP^(-1)
	oaep_1(b);
	m = recupere_message_oaep_1(b);


	return m;
}
