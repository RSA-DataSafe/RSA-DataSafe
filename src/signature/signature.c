#include "signature.h"
#include "sha3.h"
#include "../calcul/calcul.h"

void signer(mpz_t signature, message *message, cle_prive *prive) {
	mpz_t hache;
	
	mpz_init_set(hache, message);
	mpz_init(signature);

	hacher(hache,512);
	
	expo_mod(signature, hache, prive->d, prive->n);
	
	mpz_clear(hache);
}

int verifie_signature(mpz_t chiffre, mpz_t signature, cle_publique *publique) {
	mpz_t hache;
	mpz_t signature_prime;
	int res = 0;

	mpz_init_set(hache, chiffre);
	
	hacher(hache,512);

	expo_mod(signature_prime, hache, publique->e, publique->n);
	res = mpz_cmp(signature_prime,signature);
	
	mpz_clear(signature_prime);
	mpz_clear(hache);

	return res;
}
