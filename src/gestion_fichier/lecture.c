#include <gmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../structure/structure.h"
#include "lecture.h"
#include "erreur.h"

#define MAX_CARACT 60

int chercher_utilisateur(char *email, char *mdp) {
		FILE * fichier = NULL;
		char user[MAX_CARACT], mot_passe[MAX_CARACT];
		char* buffer = NULL;
		int ligne = 0;
		
		fichier = fopen("rsa/connexion","r");
	 	
		if (fichier == NULL) {
					return ERR_LECT;
		}
		
		while (getline(&user, NULL, fichier) != -1) {
				if(getline(&mdp,NULL,fichier) == -1) {
						if(user) free(user);
						if(mdp) free(mdp); // si ce n'est pas la première fois...
						fclose(fichier);
					 	return ERR_LECT; // Le fichier n'est pas correcte
				}
				if(!strcmp(user,email)) {
						if(!(strcmp(mdp,mot_passe))) {
							if(user) free(user);
							if(mdp) free(mdp);
							fclose(fichier)
							return 1;
							}
							else {
								break; // On ne vérifie pas le reste car le mot de passe est faux
							}
				}	
		}	 
		if(user) free(user);
		if(mdp) free(mdp);
		fclose(fichier);	
		return 0;
}

int recupere_cle_publique(char * email, char * mdp, cle_publique * publique) {
		if(!chercher_utilisateur(email,mdp) == 0) {
				char * chemin = malloc(sizeof(char)*MAX_CARACT + sizeof("rsa/") + sizeof("cle_privee"));
				if(chemin == NULL) {
						fprinf(stderr,"Erreur d'allocation Mémoire");
						exit(1);
				}
				strcat(chemin,"rsa/");
				strcat(chemin,email);
				strcat(chemin,"/cle_privee");

				char * res = lire_fichier(chemin);
				
				if(res[0] == -1) {
						return ERR_LECT;
				}
				// init cle publique avec res
				free(chemin);
				free(res);
				return 0;	
		}
		return ERR_LECT;
}

int recupere_cle_privee(char * email, char * mdp, cle_prive * prive) {
		if(!chercher_utilisateur(email,mdp) == 0) {
					char * chemin = malloc(sizeof(char) * MAX_CARACT + sizeof("rsa/") + sizeof("/cle_pub"));
					if(chemin == NULL) {
							fprintf(stderr,"Erreur d'allocation Mémoire");
							exit(1);
					}
					char * res = lire_fichier(chemin);
					
					strcat(chemin,"rsa/");
					strcat(chemin,email);
					strcat(chemin,"cle_pub");

					if(res[0] == -1) {
								return ERR_LECT;
					}
					//init cle privée avec res
					free(chemin);
					free(res);
					return 0;
		}
		return ERR_LECT;
}

int lire_boite(char *email, boite * b) {
	 char * chemin = malloc(sizeof("rsa/") + sizeof(email)+ sizeof("/boiteN"));
	 if(chemin == NULL) {
			fprintf(stderr,"Erreur d'allocation Mémoire");
			exit(1);
	 }
	 strcat(chemin,email);	
	 strcat(chemin,"boite");
	 // cat le num
	 // obtenir le numéro de la boite
	 // b.boite = lire_fichier(chemin); 
	 free(chemin);	
	 return 0;	
}

char *lire_fichier(char * chemin) {
		char * res = malloc(sizeof(char)*2000); // longueur d'une clée à changer je ne sais pas si bin ou hexa ? 
		if(res == NULL) {
			fprintf(stderr,"Erreur d'allocation Mémoire");
			exit(1);
		}
		FILE * fichier = NULL;
		fichier = fopen(chemin,"r");
		if(fichier == NULL) {
				res[0] = -1;
				return res;
		}
		
		char c;
		for(int i = 0; (c = fgetc(fichier)) != EOF; i++) {
					res[i] = c;
		}

		fclose(fichier);
		return res;
}
