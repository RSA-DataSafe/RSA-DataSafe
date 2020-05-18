#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>

#include "../structure/structure.h"
#include "../signature/sha3.h"
#include "../calcul/calcul.h"
#include "gestion_block.h"
#include "oaep.h"

#define TAILLE_INT 32
#define TAILLE_SHA3_256 256

void i2osp(mpz_t res, mpz_t graine, mpz_t nombre) {
    // Init
    mpz_t tmp;
    mpz_init(tmp);

    // Code
    mpz_set(res, graine);
    shift_gauche(res, TAILLE_INT);
    mpz_set_ui(tmp, 2);
    mpz_pow_ui(tmp, tmp, TAILLE_INT);
    mpz_sub_ui(tmp, tmp, 1);
    mpz_and(tmp, tmp, nombre);
    mpz_add(res, res, tmp);

    // Clear
    mpz_clear(tmp);
}

void mgf(mpz_t res, message *graine, mpz_t taille) {
    // Init
    mpz_t nb;
    mpz_init(nb);

    mpz_t i;
    mpz_init(i);

    message *tmp_i2osp = malloc(sizeof(message));
    mpz_init(tmp_i2osp->nombre);
    mpz_init(tmp_i2osp->taille);

    message *tmp_sha3 = NULL;

    // Code
    mpz_div_ui(nb, taille, TAILLE_SHA3_256);

    mpz_set(tmp_i2osp->taille, graine->taille);
    mpz_add_ui(tmp_i2osp->taille, tmp_i2osp->taille, TAILLE_INT);

    for(mpz_set_ui(i, 0); mpz_cmp(i, nb) < 0; mpz_add_ui(i, i, 1)) {
        i2osp(tmp_i2osp->nombre, graine->nombre, i);
        tmp_sha3 = sha3(tmp_i2osp, TAILLE_SHA3_256);
        shift_gauche(res, TAILLE_SHA3_256);
        mpz_add(res, res, tmp_sha3->nombre);

        mpz_clear(tmp_sha3->nombre);
        mpz_clear(tmp_sha3->taille);
        free(tmp_sha3);
    }

    // Clear
    mpz_clear(tmp_i2osp->nombre);
    mpz_clear(tmp_i2osp->taille);
    free(tmp_i2osp);
    mpz_clear(i);
    mpz_clear(nb);
}

void oaep_block(mpz_t premiere_entree, mpz_t deuxieme_entree, mpz_t premiere_sortie, mpz_t deuxieme_sortie) {
    // Init
    mpz_t TAILLE_BLOCK_GAUCHE;
    mpz_init(TAILLE_BLOCK_GAUCHE);
    mpz_set_ui(TAILLE_BLOCK_GAUCHE, 1536);

    mpz_t TAILLE_BLOCK_DROITE;
    mpz_init(TAILLE_BLOCK_DROITE);
    mpz_set_ui(TAILLE_BLOCK_DROITE, 256);

    message *tmp_message = malloc(sizeof(message));
    mpz_init(tmp_message->nombre);
    mpz_init(tmp_message->taille);

    // Code
    mpz_set(tmp_message->nombre, deuxieme_entree);
    mpz_set(tmp_message->taille, TAILLE_BLOCK_DROITE);
    mgf(premiere_sortie, tmp_message, TAILLE_BLOCK_GAUCHE);
    mpz_xor(premiere_sortie, premiere_entree, premiere_sortie);

    mpz_set(tmp_message->nombre, premiere_sortie);
    mpz_set(tmp_message->taille, TAILLE_BLOCK_GAUCHE);
    mgf(deuxieme_sortie, tmp_message, TAILLE_BLOCK_DROITE);
    mpz_xor(deuxieme_sortie, deuxieme_sortie, deuxieme_entree);

    // Clear
    mpz_clear(tmp_message->nombre);
    mpz_clear(tmp_message->taille);
    free(tmp_message);

    mpz_clear(TAILLE_BLOCK_GAUCHE);
    mpz_clear(TAILLE_BLOCK_DROITE);
}

block *oaep(block *b, mpz_t donnee_alea) {

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
        extraction(m, r, b->tab[i]);
        oaep_block(m, r, x, y);
        shift_gauche(x, TAILLE_SHA3_256);
        mpz_set(b->tab[i], x);
        mpz_add(b->tab[i], b->tab[i], y);
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
