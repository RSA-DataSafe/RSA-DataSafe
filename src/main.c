#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>

#include "structure/structure.h"
#include "chiffrement/oaep.h"
#include "signature/sha3.h"

int main(void) {
	/*
	block *b = malloc(sizeof(block));
	b->nb_block = 1;
	b->tab = malloc(sizeof(mpz_t) * b->nb_block);

	mpz_init(b->tab[0]);
	mpz_realloc2(b->tab[0], 2500);
	mpz_set_str(b->tab[0], "99999999999946704128743738963096489578566409360644647499990647496488", 10);

	mpz_t tmp;
	mpz_init(tmp);

	b = oaep(b, tmp);

	mpz_out_str(0, 16, b->tab[0]);
	printf("\n");

	mpz_clear(tmp);
	mpz_clear(b->tab[0]);
	free(b->tab);
	free(b);
	*/
	message *a = malloc(sizeof(message));
	mpz_init(a->nombre);
	mpz_init(a->taille);
	mpz_set_str(a->nombre, "699999999999999999999946704128743738963096489578566409360644647499990647496488", 10);
	mpz_set_ui(a->taille, mpz_sizeinbase(a->nombre, 2));

	mpz_out_str(0, 10, a->nombre);
	printf("\n");
	mpz_out_str(0, 10, a->taille);
	printf("\n");

	message *tmp = NULL;
	
	for (int i = 0; i < 5; i++)
	{

		tmp = sha3(a, 256);
		mpz_out_str(0, 10, tmp->nombre);
		printf("\n");
		mpz_clear(tmp->nombre);
		mpz_clear(tmp->taille);
		free(tmp);
	}

	mpz_clear(a->nombre);
	mpz_clear(a->taille);
	free(a);

	return 0;
}
