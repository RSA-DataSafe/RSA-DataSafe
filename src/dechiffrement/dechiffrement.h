#ifndef _dechiffrement_h
#define _dechiffrement_h

/**
 * Permet le déchiffrement
 * @param c : message chiffré
 * @param prive : clé privée
 * @return message déchiffré
 */
message *dechiffrement(message *c, cle_prive *prive);

#endif // !_dechiffrement_h
