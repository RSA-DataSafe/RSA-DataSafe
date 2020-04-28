#include <gmp.h>
#include <stdio.h>
#include <string.h>
#include "generation/bbs.c"
#include "gestion_fichier/ecriture.c"
#include "calcul/calcul.c"
#include "generation/primalite.c"
#include "generation/euclide.c"
#include "generation/generation_cle.c"

int main(void) {
	
   mpz_t n;
   mpz_init(n);
   mpz_set_ui(n,23);
   mpz_t tour;
   mpz_init(tour);
   mpz_set_ui(tour,2);
   printf("%d\n", miller_rabbin(n,tour)); 

		return 0;
}
