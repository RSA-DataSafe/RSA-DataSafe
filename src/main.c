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

    message *m1 = malloc (sizeof (message));
	mpz_init(m1->taille);
	mpz_init_set_str(m1->nombre,"10",10);
	mpz_set_ui(m1->taille,mpz_sizeinbase(m1->nombre,2));


	for (int i = 0; i < 5; i++)
	{
		message *m = sha3(m1,256);
		int t=mpz_sizeinbase(m->nombre,2);
		gmp_printf("Résultat Sha-3 = %Zd",m->nombre);
		printf(" / taille = %d \n",t);
		mpz_clears(m->nombre,m->taille,NULL);
		free(m);
		mpz_add_ui(m1->nombre,m1->nombre,256);
		mpz_set_ui(m1->taille,mpz_sizeinbase(m1->nombre,2));
	}
	
	return 0;
}
