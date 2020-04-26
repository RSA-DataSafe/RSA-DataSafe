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
bbs(p,1024);
printf("\n\n");
mpz_out_str(stdout,10,p);
printf("\n\n");
		return 0;
}
