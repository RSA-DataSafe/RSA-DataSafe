#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>

#include "structure/structure.h"
#include "chiffrement/oaep.h"
#include "signature/sha3.h"

int main(void) {
	
	block *b = malloc(sizeof(block));
	b->nb_block = 1;
	b->tab = malloc(sizeof(mpz_t) * b->nb_block);

	mpz_init(b->tab[0]);
	mpz_realloc2(b->tab[0], 2500);
	mpz_set_str(b->tab[0], "9999999999999999999999999999999999999999946704128743738963096489578566409360644647499990647496488", 10);
	printf("taille = %ld\n", mpz_sizeinbase(b->tab[0], 2));
	mpz_t tmp;
	mpz_init(tmp);

	b = oaep(b, tmp);

	mpz_out_str(0, 16, b->tab[0]);
	printf("\n");
	printf("taille = %ld\n", mpz_sizeinbase(b->tab[0], 2));

	mpz_clear(tmp);
	mpz_clear(b->tab[0]);
	free(b->tab);
	free(b);
	
	
	return 0;
}
