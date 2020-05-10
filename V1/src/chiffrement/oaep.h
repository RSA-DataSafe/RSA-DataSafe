#ifndef _oaep_h
#define _oaep_h

#include "../structure/structure.h"

/**
 * I2OSP, concatène graine et nombre
 * @param res : résultat
 * @param graine : nombre à concaténer
 * @param nombre : nombre de 32 bits
 */
void i2osp(mpz_t res, mpz_t graine, mpz_t nombre);

/**
 * MGF, consiste à réduire ou agrandir la taille d'un nombre suivant la taille souhaitée
 * @param res : résultat
 * @param graine : nombre permettant de générer un autre nombre d'une taille différente
 * @param taille : taille du nombre à générer
 */
void mgf(mpz_t res, message *graine, mpz_t taille);

/**
 * OAEP sur un bloc 
 * @param premiere_entree : première entrée
 * @param deuxieme_entree : deuxième entrée
 * @param premiere_sortie : première sortie
 * @param deuxieme_sortie : deuxième sortie
 */
void oaep_block(mpz_t premiere_entree, mpz_t deuxieme_entree, mpz_t premiere_sortie, mpz_t deuxieme_sortie);

/**
 * OAEP sur tous les blocs
 * @param b : contient tous les blocs
 * @param donnee_alea : donnée aléatoire
 * @return les blocks formés avec OAEP
 */
block *oaep(block *b, mpz_t donnee_alea);

#endif // !_oaep_h