#include <gmp.h>
#include <stdio.h>
#include <string.h>
#include "generation/bbs.c"
#include "gestion_fichier/ecriture.c"
#include "calcul/calcul.c"
#include "generation/primalite.c"
#include "generation/euclide.c"
int main(void) {
	
    mpz_t u,v,phi,e;
	mpz_init(u);
	mpz_init(v);
	mpz_init(phi);
	mpz_init(e);
	mpz_set_ui(phi,5);
	mpz_set_ui(e,3);
	euclide_etendu( u, v, phi, e );
    mpz_out_str(stdout,10,u);
	printf("\n\n");
	mpz_out_str(stdout,10,v);
	printf("\n\n");
	shift_gauche(e,2);
	printf("e= ");
	mpz_out_str(stdout,10,e);
	printf("\n\n");
	
		return 0;
}
