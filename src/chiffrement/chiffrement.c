#include <gmp.h>
#include <time.h>
#include <stdlib.h>
#include "../structure/structure.h"
#include "../calcul/calcul.h"
#include "chiffrement.h"
#include "oaep.h"
#include "gestion_block.h"
message *chiffrement(message *m, cle_publique *publique, message *encodage) {
    
		
    mpz_t alea;
    mpz_init(alea);

    time_t t; 
    srand(time(&t));
    gmp_randstate_t etat;
    gmp_randinit_default(etat);
    gmp_randseed_ui(etat, rand());
    mpz_urandomb(alea, etat, 256);

    // Code
    block *b = creer_block_oaep(m, encodage, alea);
    b = oaep(b, alea);

    mpz_t tmp;
    mpz_init(tmp);

    for(int i = 0;i<(b->nb_block); i++) {
        mpz_set(tmp, b->tab[i]);
        mpz_powm(b->tab[i], tmp, publique->e, publique->n);
    }

    message *k = recupere_message_oaep(b);

    // Clear
    mpz_clears(tmp,alea,NULL);
    for(int i = 0;i< (b->nb_block); i++) {
        mpz_clear(b->tab[i]);
    }
    free(b); 
		
    // return
    return k;
}


