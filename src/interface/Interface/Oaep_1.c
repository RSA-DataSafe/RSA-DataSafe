#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>

#include "../structure/structure.h"
#include "../signature/sha3.h"
#include "../calcul/calcul.h"
#include "../chiffrement/gestion_block.h"
#include "../chiffrement/oaep.h"


block *oaep_1(block *b) {
    mpz_t x ,y, m , r ;
    mpz_init(x);
    mpz_init(y);
    mpz_init(r);
    mpz_init(m);


    block *retour ;
    retour -> tab = malloc(sizeof(int)*b-> nb_block);
    retour -> nb_block = b-> nb_block;
    
   
    for(int i = 0; i < b->nb_block; i++)
    {
        extraction(mpz_t x, mpz_t y, b->tab[i]);
        oaep_block(x,y,m,r);
        mpz_set(retour-> tab[i], m);
    
    }

    mpz_clear(m);
    mpz_clear(y);
    mpz_clear(r);
    mpz_clear(r);

    return retour;
}