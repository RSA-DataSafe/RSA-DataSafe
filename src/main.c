#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>

#include "structure/structure.h"
#include "chiffrement/gestion_block.h"

int main(void) {
	message *a = malloc(sizeof(message));
	mpz_inits(a->taille, a->nombre, NULL);

	mpz_set_ui(a->taille, 4096);
	mpz_set_ui(a->nombre, 1);
	mpz_mul_2exp(a->nombre, a->nombre, 4096);
	mpz_sub_ui(a->nombre, a->nombre, 1);

	block *b = creer_block_oaep_1(a);

	message *m =recupere_message_oaep_1(b);
	printf("message = ");
    mpz_out_str(0, 2, m->nombre);
	printf("\n");
	printf("taille = ");
    mpz_out_str(0, 10, m->taille);
	printf("\n");

	for (int i = 0; i < b->nb_block; i++)
    {
        mpz_clear(b->tab[i]);
    }
	free(b);
	mpz_clears(a->taille, a->nombre, NULL);
	free(a);
	
	return 0;
}
