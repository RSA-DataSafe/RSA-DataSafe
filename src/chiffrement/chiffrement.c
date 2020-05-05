#include <gmp.h>
#include <time.h>
#include <stdlib.h>

#include "../structure/structure.h"
#include "../calcul/calcul.h"
#include "chiffrement.h"

message *chiffrement(message *m, cle_publique *publique, message *encodage) {
    
		// alea
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

    for(int i = 0; mpz_cmp_ui(b->nb_block, i) < 0; i++) {
        mpz_set(tmp, b->tab[i]);
        expo_mod(b->tab[i], tmp, publique->e, publique->n);
    }

    message *m = recupere_message_oaep(b);

    // Clear
    mpz_clear(tmp);
    mpz_clear(alea);
    for(int i = 0; mpz_cmp_ui(b->nb_block, i) < 0; i++) {
        mpz_clear(b->tab[i]);
    }
    free(b); 
		
    // return
    return m;
}

//Oumeima
#include <gmp.h>
#include <time.h>
#include <stdlib.h>
#include "structure.h"
#include "chiffrement.h"
#include "calcul.h"


message *chiffrement(message *m, cle_publique *publique, message *encodage) {
    
    mpz_t donnee_alea;
    mpz_init(donnee_alea);
    
    time_t tmp; 
    srand(time(&tmp));
    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed_ui(state, rand());
    mpz_urandomb(donnee_alea,state,128);

    block *b = creer_block_oaep(m,encodage,donnee_alea);
    block *c = oaep(b,donnee_alea);
    mpz_clear(donne_alea);
    free(b); 
    
    mpz_t x;
    mpz_init(x);
    int y=c->nb_block;
    for(int i = 0; i<y; i++)
    {
        mpz_set(x, c->tab[i]);
        expo_mod(c->tab[i],x,publique->e,publique->n);
    }

    message *m = recupere_message_oaep(b);
	
	
    mpz_clear(x);
    for(int i = 0; i<y; i++) {
        mpz_clear(c->tab[i]);
    }
    free(c); 
    
    return m;
}
