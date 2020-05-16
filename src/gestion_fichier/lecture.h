#ifndef _lecture_h
#define _lecture_h

/**
 * Permet de chercher un utilisateur dans la base de donnée.
 * @param email : email de l'utilisateur 
 * @param mdp :mot de passe de l'utilisateur 
 * @retourne 0 si l'utilisateur existe sinon un des signaux d'erreur 
 * */
int chercher_utilisateur(char *email, char *mdp);

/**
 * Permet de récupérer la clé publique d'un utilisateur dans le fichier correspondant.
 * @param email : email d'un utilisateur quelconque  
 * @param mdp : le mot de passe de l'utilisateur 
 * @param publique : clé publique
 * @retourne 0 si l'utilisateur existe sinon un des signaux d'erreur 
 * */
int recupere_cle_publique(char *email, char *mdp, cle_publique *publique);

/**
 * Permet de récupérer la clé privée d'un utilisateur dans le fichier correspondant.
 * @param email : identifiant de l'utilisateur
 * @param mdp : mot de passe de l'utilisateur
 * @param prive : clé privée
 * @retourne 0 si l'utilisateur existe sinon un des signaux d'erreur 
 * */
int recupere_cle_privee(char *email, char *mdp, cle_prive *prive);

/**
 * Permet de lire dans une boite les mails s'y trouvant.
 * @param email : email de l'utilisateur
 * @param boite : boite à lire
 * @retourne 0 si ça fonctionne, sinon un des signaux d'erreur
 * */
int lire_boite(char *email, boite *b);

/**
 * Permet de lire dans un fichier
 * @param chemin : chemin du fichier
 * @retourne la chaîne de caractère contenant le texte du fichier
 */
char *lire_fichier(char *chemin);

#endif // !_lecture_h
