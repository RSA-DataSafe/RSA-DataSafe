#ifndef _sha3_h
#define _sha3_h

/**
 * SHA-3
 * @param m : le message à hacher
 * @param taille : taille de la sortie
 * @return le haché sous forme d'une structure message pour différencier les tailles de sortie
 */
message *sha3(message *m, int taille);

/**
 * Padding de sha-3 : transforme la taille l'entrée en un multiple de la taille des blocs
 * @param m : le message à hasher
 * @param taille : taille de sortie
 * @return message avec le padding
 */
message *padding_sha3(message *m, int taille);

/**
 * Découpage en blocs
 * @param m : le message à hacher, avec le padding
 * @param taille : taille des blocs (en bits; dépend de la taille de la sortie)
 * @return block
 */
block *decoupage_block(message* m, int taille);

/**
 * Round
 * @param matrice : matrice de nombres de 64 bits 
 * @param taille : taille de sortie de sha3
 * @param nb_tour : nombre de tours
 */
void round_sha3(mpz_t **matrice, int nb_tour);

/**
 * keccak-f
 * @param matrice : matrice de nombres de 64 bits
 * @param RC : constante différente pour chaque round (standardisé par sha-3)
 */
void keccak_f(mpz_t **matrice, mpz_t RC);



// Fonctions suivantes non décrites dans les spécifications = trivial

/**
 * Effectue une rotation circulaire sur la donnée en entrée
 * @param x : donnée d'entrée
 * @param n : nombre de rotations
 */
void rot (mpz_t x, int n);

/**
 * Inverse bit à bit
 * @param x : donnée à inverser
 */
void invert (mpz_t x);

#endif // !_sha3_h