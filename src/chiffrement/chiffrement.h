#ifndef _chiffrement_h
#define _chiffrement_h
#include <time.h>
#include <stdlib.h>

/**
 * Permet le chiffrement
 * @param m : message à chiffrer
 * @param publique : clé publique
 * @param encodage : encodage du texte du message
 * @return message chiffré
 */
message *chiffrement(message *m, cle_publique *publique, message *encodage);

#endif // !_chiffrement_h
