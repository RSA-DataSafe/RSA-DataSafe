#ifndef _structure_h
#define _structure_h
#include <gmp.h>

/*Regroupe les modules de la clé publique*/
typedef struct {
	mpz_t e;           //exposant publique
	mpz_t n;
} cle_publique;

/*Regroupe les modules de la clé privée*/
typedef struct {
	mpz_t d;            // exposant privé
	mpz_t n;
} cle_prive;

typedef struct {
	mpz_t* tab;        // tableau de mpz_t contenant les blocs
	int nb_block;      // nombre de bloc 
} block;

typedef struct {
    mpz_t nombre;       //message sous forme de nombre
    mpz_t taille;       // taille du message (nombre de bits)
} message;

typedef struct {
    char *env_email;    // email de l'expéditeur
    char *dest_email;   //email du destinataire
    char *titre;        // titre ou objet du mail
    char *message;      // le message 
    char *signature;    // la signature du message 
    int signer;         /*  permet de savoir si le message est signé               */
} mail;

typedef struct {
    char* nom_boite;    /*      nom de la boite  
                        ( reçu , envoyé ou indésirable)     */
    mail *m;            // informations sur les messages 
    int nb_mail;        // nombre de mail dans la boite 
} boite;

typedef struct {
    char* email;             // email de l'utilisateur
    
    char* mdp;               // son mot de passe
    
    cle_prive prive;         // la clé privée de l'utilisateur
    
    cle_publique publique;   /* la clé publique de 
                                     l'utilisateur      */
} informations;

#endif // !_structure_h
