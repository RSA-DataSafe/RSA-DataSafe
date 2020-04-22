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
		size_t length = 0;
		int ligne = 0;
		
		fichier = fopen("rsa/connexion","r");

	 	if (fichier == NULL) {
					return ERR_LECT;
		}
		
		while (getline(&buffer, &length, fichier) != -1) {ligne++;}
		if(buffer) free(buffer);
		
		rewind(fichier); // retour au début
	  
		for(int i = 0; i < ligne ; i++) {		
						fscanf(fichier,"%s %s",user,mot_passe);
						if(!strcmp(user,email)) {
										if(!(strcmp(mdp,mot_passe))) {
												fclose(fichier);
												return 1;
										}
										else {
												break; // Retourner le mot de passe faux, on ne vérifie pas le reste 
										}
						}
		}
		fclose(fichier);	
		return 0;
}
