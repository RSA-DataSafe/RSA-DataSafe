#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>

#include "../structure/structure.h"
#include "../signature/sha3.h"
#include "../calcul/calcul.h"
#include "../chiffrement/gestion_block.h"
#include "../chiffrement/oaep.h"


block *oaep_1(block *b) {
    // init
    mpz_t m;
    mpz_init(m);

    mpz_t r;
    mpz_init(r);

    mpz_t x;
    mpz_init(x);

    mpz_t y;
    mpz_init(y);

    mpz_t tmp;
    mpz_init(tmp);

    // Code
    for(int i = 0; i < b->nb_block; i++) {
        extraction(x, y, b->tab[i]);
        oaep_block(x, y, m, r);
        shift_gauche(x, 256);
        mpz_set(b->tab[i], m);
        mpz_add(b->tab[i], b->tab[i], r);
    }

    // Clear
    mpz_clear(tmp);
    mpz_clear(y);
    mpz_clear(x);
    mpz_clear(m);
    mpz_clear(r);

    // return
    return b; // sert à rien mais bon ...
}
