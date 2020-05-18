#ifndef _conversion_h
#define _conversion_h

#include "../structure/structure.h"
#include <gmp.h>

/**
 * Permet de convertir une cha î ne de caract è res en un message
sous forme de nombre
 * @param m : la cha î ne de caract è res
 * @return le message sous forme de nombre
**/
message * conversion_char_mpz ( char * chaine ) ;

/**
 * Permet de convertir un message sous forme de nombre en une
cha î ne de caract è res
 * @param m : le message sous forme de nombre
 * @return la chaîne de caract è res
**/
char * conversion_mpz_char ( message * m ) ;

/**
 * Permet de convertir une cha î ne de caract è res en un message
sous forme de nombre
 * @param m : la cha î ne de caract è res
 * @return le message sous forme de nombre
**/
message *conversion_hexa_mpz ( char *chaine );

/**
 * Permet de convertir un message sous forme de nombre en une
cha î ne de caract è res
 * @param m : le message sous forme de nombre
 * @return la chaîne de caract è res
**/
char *conversion_mpz_hexa ( message *m );

#endif // !_conversion_h
