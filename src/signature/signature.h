#ifndef _signature_h
#define _signature_h

/**
 *  Permet de signer un message. 
 * @param signature : la signature qui sera retournée après hachage de Sha-3.
 * @param message : le message à signer.
 * @param prive : clé privée qui va servir à signer un message.
*/
void signer(mpz_t signature, message *message, cle_prive *prive);

/**
 * Fonction qui vérifie si la signature est correcte en renvoyant un code selon si la signature correspond au message ou non.
 * @param chiffre : le message chiffré
 * @param signature : la signature donné par l'expéditeur
 * @param publique : la clé public
 * @return 1 si la signature ne correspond pas, 0 sinon
 * */
int verifie_signature(mpz_t chiffre, mpz_t signature, cle_publique *publique);

#endif // !_signature_h