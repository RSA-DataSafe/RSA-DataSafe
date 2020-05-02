#include "signature.h"
#include "../structure/structure.h"
#include "sha3.h"
#include "../calcul/calcul.h"

#include <gmp.h>

void signer(signature,message,cle_prive) {
	mpz_t hache;
	
	mpz_init_set(hache, message);
	mpz_init(signature);

	hacher(hache,512);
	
	expo_mod(signature, hache, cle_prive.d, cle_prive.n);
	
	mpz_clear(hache);
}

int verifie_signature(chiffre,signature,cle_publique) {
	mzp_t hache;
	mpz_t signature_prime;
	int res = 0;

	mpz_init_set(hache, chiffre);
	
	hacher(hache,512);

	expo_mod(signature_prime, hache, cle_publique.e, cle-publique.n);
	res = mpz_cmp(signature_prime,signature);
	
	mpz_clear(signature_prime);
	mpz_clear(hache);

	return res;
}
