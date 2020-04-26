#include <gmp.h>
#include <stdio.h>
#include <string.h>
#include "generation/bbs.c"
#include "gestion_fichier/ecriture.c"
#include "calcul/calcul.c"
#include "generation/primalite.c"
#include "generation/euclide.c"
int main(void) {
	

mpz_t p;
mpz_init(p);
blum_prime(p,2048);
		return 0;
}
