#include <gmp.h>
#include <stdio.h>
#include <string.h>
#include "generation/bbs.c"
#include "gestion_fichier/ecriture.c"
#include "calcul/calcul.c"
#include "generation/primalite.c"
int main(void) {
	
    mpz_t x;
mpz_t n;
mpz_init(x);
mpz_init(n);
mpz_set_ui(x,19319);
mpz_set_ui(n,20);
printf("%d\n", miller_rabbin(x,n));  

printf("\n\n");
		return 0;
}
