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
	mpz_init_set_str(m1->nombre,"124686523658656885233698855555555555555555588888888888888888888888885223333311447889999999956568848645148949845654169849846549849846849",10);
	mpz_set_ui(m1->taille,mpz_sizeinbase(m1->nombre,2));


	for (int i = 0; i < 5; i++)
	{
		message *m = NULL;
		mpz_inits(m->nombre,m->taille,NULL);
		m=sha3(m1,256);
		printf("apres sha3\n");
		int t=mpz_sizeinbase(m->nombre,2);
		gmp_printf("dans le main apres la fonction res obtenu  %Zd \n",m->nombre);
		printf("la taille %d \n",t);
		mpz_clears(m->nombre,m->taille,NULL);
		printf("boucle  %d \n",i);
		free(m);
		mpz_add_ui(m1->nombre,m1->nombre,256);
		mpz_set_ui(m1->taille,mpz_sizeinbase(m1->nombre,2));
		printf("apres le free \n");
	}

	return 0;
}
