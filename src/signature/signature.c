#include "signature.h"
#include "sha3.h"
#include "../calcul/calcul.h"
#include <stdlib.h>
#include <stdio.h>

void signer(mpz_t signature, message *mes, cle_prive *prive) {
	message *tmp_sha3 = NULL;

	tmp_sha3=sha3(mes,512);

	expo_mod(signature, tmp_sha3->nombre, prive->d, prive->n);

	free(tmp_sha3);
	
}

int verifie_signature(mpz_t chiffre, mpz_t signature, cle_publique *publique) {
			gmp_printf("val de la signture dansverif %Zd\n",signature );
	mpz_t signature_prime;
	mpz_init(signature_prime);
	int res = 0;
	message m;
	mpz_inits(m.nombre,m.taille,NULL);
	mpz_set(m.nombre,chiffre);
    int taille=mpz_sizeinbase(chiffre,2);
    printf("tailllle dans la fonction  %d \n" , taille );
	mpz_set_ui(m.taille,taille);
	printf("ok\n");
	message *tmp_sha3 = NULL;
	tmp_sha3=sha3(&m,512);
	printf("ok2\n");
	expo_mod(signature_prime, signature, publique->e, publique->n);
	res = mpz_cmp(signature_prime,tmp_sha3->nombre);
	mpz_clears(signature_prime, m.nombre,m.taille,NULL);
	free(tmp_sha3);
     printf("resssssss : %d\n", res );
	return res;
}
