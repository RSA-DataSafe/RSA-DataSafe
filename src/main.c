#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>

#include "structure/structure.h"
#include "generation/generation_cle.h"
#include "chiffrement/chiffrement.h"
#include "dechiffrement/dechiffrement.h"

int main(void) {
	// init
	message *a = malloc(sizeof(message));
	mpz_inits(a->taille, a->nombre, NULL);

	cle_publique *publique = malloc(sizeof(cle_publique));
	mpz_inits(publique->e, publique->n, NULL);

	cle_prive *prive = malloc(sizeof(cle_prive));
	mpz_inits(prive->d, prive->n, NULL);

	message *m = malloc(sizeof(message));
	mpz_inits(m->taille, m->nombre, NULL);

	message *encodage = malloc(sizeof(message));
	mpz_inits(encodage->taille, encodage->nombre, NULL);

	message *c = malloc(sizeof(message));
	mpz_inits(c->taille, c->nombre, NULL);

	// code
	genere_cle(publique, prive, 2048);
	printf("here\n");
	mpz_set_ui(a->nombre, 1);
	mpz_set_ui(a->taille, 1);
	mpz_set_ui(encodage->nombre, 1);
	mpz_set_ui(encodage->taille, 256);

	c = chiffrement(a, publique, encodage);

	m = dechiffrement(c, prive);

	mpz_out_str(0, 2, m->nombre);
	printf("\n");

	// clear
	mpz_clears(a->taille, a->nombre, NULL);
	free(a);

	mpz_clears(publique->e, publique->n, NULL);
	free(publique);

	mpz_clears(prive->d, prive->n, NULL);
	free(prive);

	mpz_clears(m->taille, m->nombre, NULL);
	free(m);

	mpz_clears(encodage->taille, encodage->nombre, NULL);
	free(encodage);

	mpz_clears(c->taille, c->nombre, NULL);
	free(c);
	
	return 0;
}
