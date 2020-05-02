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
	
	fichier = fopen("rsa/connexion","r");
	
	if (fichier == NULL) {
		return ERR_LECT;
	}
	
	size_t bufsize = 32;
	
	char * user = malloc(sizeof(char) * bufsize);
	char * mot_de_passe = malloc(sizeof(char) * bufsize);
	char * email_tmp = malloc(sizeof(char) * bufsize);
	char * mdp_tmp = malloc(sizeof(char) * bufsize);
	
	if(user == NULL || mot_de_passe == NULL || email_tmp==NULL || mdp_tmp == NULL) {
		fprintf(stderr,"Erreur d'allocation de mémoire");
		exit(1);
	}
	
	memcpy(email_tmp,email,strlen(email));
	memcpy(mdp_tmp,mdp,strlen(mdp));
	strcat(email_tmp,"\n");
	strcat(mdp_tmp,"\n");
	
	int est_present = 1; // si l'email et mdp sont presents 
	
	while(getline(&user,&bufsize,fichier) != -1) {
		getline(&mot_de_passe,&bufsize,fichier);
		if(strcmp(email_tmp,user) == 0) {
			if(strcmp(mdp_tmp,mot_de_passe) == 0) {
				est_present = 1 - est_present;
			}
			break; // Si le mot de passe est faux on arrete aussi
		}
	}
	
	free(user);
	free(mot_de_passe);
	free(email_tmp);
	free(mdp_tmp);
	fclose(fichier);	
	return est_present;
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
		
		mpz_init_set_str(cle_publique->e,res,10); // je ne sais pas ici
		mzp_init_set_str(cle_publique->n,res,10); // pour l'instant car je ne sais pas 

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
	// je ne sais pas comment il sera stoké	
		mpz_init_set_str(cle_prive->e,res,10);
		mpz_init_set_str(cle_prive->n,res,10);

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
	 strcat(chemin,"boite"); // nom inconnu ? 
	 // je ne sais pas comment le message sera écrit ? 
	 b->m->message = lire_fichier(chemin); 
	 free(chemin);	
	 return 0;	
}

char *lire_fichier(char * chemin) {
		char * res = malloc(sizeof(char)*2048);  
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
