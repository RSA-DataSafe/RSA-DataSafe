#ifndef _oaep_1_h
#define _oaep_1_h

/**
 * Décompose le message chiffré en blocs de 2048 bits
 * @param b : contient tous les blocs formés avec OAEP
 * @return les blocs sans le remplissage  OAEP
 */
block *oaep_1(block *b);

#endif // !_oaep_1_h