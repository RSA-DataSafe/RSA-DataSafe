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
	mpz_mul_2exp(a->nombre, a->nombre, 2048);

	block *b = creer_block_oaep_1(a);
	for (int i = 0; i < b->nb_block; i++)
    {
		printf("block %d = ", i);
        mpz_out_str(0, 10, b->tab[i]);
		printf("\n");
    }
	printf("nb block = %d\n", b->nb_block);

	for (int i = 0; i < b->nb_block; i++)
    {
        mpz_clear(b->tab[i]);
    }
	free(b);
	mpz_clears(a->taille, a->nombre, NULL);
	free(a);
	
	return 0;
}
