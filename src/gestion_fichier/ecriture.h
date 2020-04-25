#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <gmp.h>
#include "erreur.h"
#include "../structure/structure.h"
#include <sys/stat.h>
#include <sys/types.h>
#ifndef _ecriture_h
#define _ecriture_h

/**
 * Permet d'enregistrer un nouvel utilisateur dans la "base de donnée" et créer ainsi son propre dossier avec l'email comme nom du dossier.
 * @param email: email de l'utilisateur
 * @param mdp: mot de passe de l'utilisateur
 * @return 0 si ça fonctionne sinon un des signaux d'erreur
 * */
int nouvel_utilisateur(char *email, char *mdp);

/**
 * Permet de modifier l'email de l'utilisateur courant 
 * @param email : email de l'utilisateur courant
 * @param mdp : mot de passe de l'utilisateur courant
 * @param newemail : nouvel email de l'utilisateur
 * @return 0 si ça fonctionne, sinon un des signaux d'erreur
 * */
int Change_Email(char *email, char *mdp, char *newemail);

/**
 * Permet de modifier le mot de passe  de l'utilisateur courant 
 * @param email : email de l'utilisateur courant
 * @param mdp : mot de passe de l'utilisateur courant
 * @param newmdp : le nouveau mot de passe  de l'utilisateur courant 
 * @return 0 si ça fonctionne, sinon un des signaux d'erreur
 * */
int Change_MotDePasse (char*email, char *mdp, char* newmdp);

/**
 * Permet de générer de nouvelles clés  pour l'utilisateur courant
 * @param InfoUser : contient les informations de l'utilisateur 
 * @return : 0 si ça fonctionne, sinon un des signaux d'erreur
 * contenu de la structure :
 *  InfoUser->email: email de l'utilisateur
 *  InfoUser->mdp :le mot de passe de l'utilisateur courant .
 *  InfoUser->publique: nouvelle clé publique
 *  InfoUser->prive: nouvelle clé privée
 * */
int change_cle(informations * InfoUser);

/** ok mais dans cette fonction on a qu un seul parametre nn ?  ou
 * Permet l'envoie d'un message
 * @param m :les informations des emails d'un utilisateur 
 * @return: 0 si ça fonctionne, sinon un des signaux d'erreur
 * la structure contient :
 *  m->env_email : email de l'expéditeur
 *  m->dest_email : email du destinataire
 *  m->titre :titre du message   
 *  m->message : message chiffré à envoyer
 *  m->signature : signature  
 *  m->signer : bit qui montre si on a signé ou non
 * */
int envoie_message(mail *m);

/**
 * Permet de stoker un message
 * @param email: email de l'utilisateur
 * @param mpz_t message : message déchiffré à stocker
 * @param boite : boite dans laquelle stocker le message déchiffré
 * @return 0 si ça a fonctionné, sinon un des signaux d'erreur
 * */
int stocker_message(char *email, mpz_t message, char *boite);

/**
 * Permet d'écrire dans un fichier
 * @param chemin : chemin du fichier
 * @param message : chaîne de caractère à écrire dans le fichier
 * @return 0 si ça a fonctionné, sinon un des signaux d'erreur
 */
int ecrire_fichier(char *chemin, char *message);

#endif // !_ecriture_h