#include "signature.h"
#include "sha3.h"
#include "../calcul/calcul.h"

void signer(mpz_t signature, message *mes, cle_prive *prive) {
	//mpz_t hache;
	
	//mpz_init_set(hache, mess.nombre);
	//mpz_init(signature);

	sha3(mes,512);
	
	expo_mod(signature, mes->nombre, prive->d, prive->n);
	
	//mpz_clear(hache);
}

int verifie_signature(mpz_t chiffre, mpz_t signature, cle_publique *publique) {
	//mpz_t hache;
	mpz_t signature_prime;
	int res = 0;

	//mpz_init_set(hache, chiffre);
	//mpz_init(chiffre);
	message m;
	mpz_init(m.nombre);
	mpz_init(m.taille);

	sha3(&m,512);

	expo_mod(signature_prime, m.nombre, publique->e, publique->n);
	res = mpz_cmp(signature_prime,signature);
	
	mpz_clear(signature_prime);
	//mpz_clear(hache);

	return res;
}
