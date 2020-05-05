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
			fprintf(stderr,"Erreur d'allocation Mémoire");
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
	 char * chemin = malloc(sizeof("rsa/") + sizeof(email)+ 50);
	 if(chemin == NULL) {
		fprintf(stderr,"Erreur d'allocation Mémoire");
		exit(1);
	 }
	 strcat(chemin,"rsa/");
	 strcat(chemin,email);	
	 strcat(chemin,"/");
	 strcat(chemin, b->nom_boite);

	 FILE * fichier = fopen(chemin,"r");
	 char c;					  // Va permettre de lire caractère par caractère
	 int alternateur = 0;		  // permet d'alterner entre les caractères non utilisé
	 int donnee_structurelle = 0; // position à traiter
	 int nbr_mail_traiter = 0;    // le nombre de mail qu'on aura traiter
	 b->m = malloc(sizeof(mail)*1000); // on peut avoir 1000 mails
	 
	 if(b->m == NULL) {
		 fprintf(stderr,"Erreur d'allocation Mémoire");
		 exit(0);
	 }
	 
	 // Parser de lecture on lit caractere par caractere: 
	 do {
		 debut: // etiquette qui permet de revenir au début. De '\n' à ':' se trouve des caractère non utilisé
		  c = fgetc(fichier);
		 if(c == ':' || c == '\n') { 
			 alternateur = 1 - alternateur;
			 c = fgetc(fichier);
		 }
		  if(alternateur == 1) {
			  // Vérifié si message signé
			  if(donnee_structurelle == 0) {
					char * buff0 = malloc(sizeof(char) * 10);
					if(buff0 == NULL) {
						fprintf(stderr,"Erreur d'allocation Mémoire");
						exit(0);
					}
					int i = 0;
					 do {
						buff0[i] = c;
						c = fgetc(fichier);
						i++;
					} while(c != '\n');
					alternateur = 0;
					if(strcmp(buff0,"sig") == 0) {
						b->m[nbr_mail_traiter].signer = 0;
					} else {
						b->m[nbr_mail_traiter].signer = 1;
					}
					free(buff0);
					donnee_structurelle++;
					goto debut;
				}
				// Récupérer le mail du destinataire
				if(donnee_structurelle == 1) {
					char * buff1 = malloc(sizeof(char) * 150);
					b->m[nbr_mail_traiter].dest_email = malloc(sizeof(char) * 50);
					if(buff1 == NULL || b->m[nbr_mail_traiter == NULL]) {
						fprintf(stderr,"Erreur d'allocation Mémoire");
						exit(0);
					}
					int a = 0;
					do {
						c = fgetc(fichier);
						buff1[a] = c;
						a++;
					} while(c != '\n');
					alternateur = 0;
					strcpy(b->m[nbr_mail_traiter].dest_email,buff1);
					free(buff1);
					donnee_structurelle++;
					goto debut;
				}
				// Récupérer le message
				if(donnee_structurelle == 2) {
					char * buff2 = malloc(sizeof(char) * 2000);
					b->m[nbr_mail_traiter].message = malloc(sizeof(char) * 2000);
					if(buff2 == NULL || b->m[nbr_mail_traiter].message == NULL) {
						fprintf(stderr,"Erreur d'allocation Mémoire");
						exit(0);
					}
					int e = 0;
					do {
						c = fgetc(fichier);
						buff2[e] = c;
						e++;
					} while(c!= '\n');
					alternateur = 0;
					strcpy(b->m[nbr_mail_traiter].message,buff2);
					free(buff2);
					donnee_structurelle++;
					goto debut;
				}
				// Récuperer la signature
				if(donnee_structurelle == 3) {
					if(b->m[nbr_mail_traiter].signer != 0) {
						char * buff3 = malloc(sizeof(char) * 2000);
						b->m[nbr_mail_traiter].signature = malloc(sizeof(char) * 2000);
						if(buff3 == NULL || b->m[nbr_mail_traiter == NULL]) {
							fprintf(stderr,"Erreur d'allocation Mémoire");
							exit(0);
						}
						int d = 0;
						do {
							c = fgetc(fichier);
							buff3[d] = c;
							d++;
						} while(c!= '\n');
						strcpy(b->m[nbr_mail_traiter].signature,buff3);
						free(buff3);
					}
					alternateur = 0;
					nbr_mail_traiter ++;
					donnee_structurelle = 0; // remise à zéro des données 
					goto debut;
				}
			}
	 } while(c != EOF);
	 
	 free(chemin);	
	 return 0;	
}

char *lire_fichier(char * chemin) {
		char * res = malloc(sizeof(char)*5000);
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
