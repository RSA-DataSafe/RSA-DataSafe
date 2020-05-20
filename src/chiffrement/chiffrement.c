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
    //Diviser le message sous des blocks de 2048
    block *b = creer_block_oaep(m, encodage, alea);

    b = oaep(b, alea);

    mpz_t tmp;
    mpz_init(tmp);
	
    //Calcul de m^e[n]
    for(int i = 0;i<(b->nb_block); i++) {
        mpz_powm(b->tab[i], b->tab[i], publique->e, publique->n);
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


