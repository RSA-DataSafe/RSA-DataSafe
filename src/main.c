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
	cle_publique publique;
	cle_prive prive;
	mpz_inits(publique.n, publique.e, prive.d, prive.n, NULL);
	//generation des cles,p et q de taille 1024 donc n de taille 2048
	genere_cle(&publique,&prive,1024);
	
	
	
	
	
	mpz_clears(publique.n, publique.e, prive.d, prive.n, NULL);
  

		return 0;
}
