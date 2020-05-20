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

    message *in = malloc(sizeof(message));
    mpz_init(in->nombre);
    mpz_init(in->taille);

    mpz_t taille;
    mpz_init(taille);

    // Code
    for(int i = 0; i < b->nb_block; i++) {
        extraction(x, y, b->tab[i]);

        mpz_set(in->nombre, x);
        mpz_set_ui(in->taille, 256);
        mpz_set_ui(taille, 256);
        mgf(r, in, taille);
        mpz_xor(r, r, y);

        mpz_set(in->nombre, r);
        mpz_set_ui(in->taille, 1792);
        mpz_set_ui(taille, 1792);
        mgf(m, in, taille);
        mpz_xor(m, m, x);

        shift_gauche(m, 256);
        mpz_set(b->tab[i], m);
        mpz_add(b->tab[i], b->tab[i], r);
    }

    // Clear
    mpz_clear(tmp);
    mpz_clear(y);
    mpz_clear(x);
    mpz_clear(m);
    mpz_clear(r);
    mpz_clear(taille);
    mpz_clear(in->nombre);
    mpz_clear(in->taille);
    free(in);

    // return
    return b; 
}
