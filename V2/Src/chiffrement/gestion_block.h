#include <gmp.h>
#include <stdlib.h>
#include <stdio.h>

#include "../structure/structure.h"
#include "../calcul/calcul.h"

#ifndef _gestion_block_h
#define _gestion_block_h

/**
 * Cette fonction permet de récupérer X et Y d'un bloc (Bloc de 2048 bit : 1792|256)
 * @param x : résultat
 * @param y : résultat
 * @param b : un bloc
 */
void extraction(mpz_t x, mpz_t y, mpz_t b);

/**
 * Cette fonction créé des blocs qui serviront par la suite dans la fonction OAEP.
 * @param m : message à transformer en blocs
 * @param encodage : encodage du texte du message
 * @param donnee_alea : donnée aléatoire
 * @return contient tous les blocs
 */
block *creer_block_oaep(message *m, message *encodage, mpz_t donnee_alea);

/**
 * Cette fonction créé des blocs qui serviront par la suite dans la fonction OAEP-1.
 * @param m : message à transformer en blocs
 * @return contient tous les blocs
 */
block *creer_block_oaep_1(message *m);

/**
 * Cette fonction permet de récupérer le message de la structure block
 * @param b : contient tous les blocs
 * @return message
 */
message *recupere_message_oaep(block *b);

/**
 * Cette fonction permet de récupérer le message de la structure block
 * @param b : contient tous les blocs
 * @return message
 */
message *recupere_message_oaep_1(block *b);

#endif // !_gestion_block_h
