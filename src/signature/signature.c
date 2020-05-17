#include "signature.h"
#include "sha3.h"
#include "../calcul/calcul.h"

void signer(mpz_t signature, message *mes, cle_prive *prive) {
	sha3(mes,512);
	expo_mod(signature, mes->nombre, prive->d, prive->n);
	
}

int verifie_signature(mpz_t chiffre, mpz_t signature, cle_publique *publique) {
	
	mpz_t signature_prime;
	mpz_init(signature_prime);
	int res = 0;
	message m;
	mpz_init(m.nombre);
	mpz_init(m.taille);
	mpz_set(m.nombre,chiffre);
       int taille=mpz_sizeinbase(chiffre,10);
	mpz_set_ui(m.taille,taille);
	sha3(&m,512);
	expo_mod(signature_prime, m.nombre, publique->e, publique->n);
	res = mpz_cmp(signature_prime,signature);
	mpz_clear(signature_prime);

	return res;
}
