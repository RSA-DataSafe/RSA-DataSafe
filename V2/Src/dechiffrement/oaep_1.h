#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include "../structure/structure.h"
#include "../signature/sha3.h"
#include "../calcul/calcul.h"
#include "../chiffrement/gestion_block.h"
#include "../chiffrement/oaep.h"


#ifndef _oaep_1_h
#define _oaep_1_h

/**
 * Décompose le message chiffré en blocs de 2048 bits
 * @param b : contient tous les blocs formés avec OAEP
 * @return les blocs sans le remplissage  OAEP
 */
block *oaep_1(block *b);

#endif // !_oaep_1_h
