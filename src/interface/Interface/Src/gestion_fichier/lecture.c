#include <gmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lecture.h"



#define MAX_CARACT 60

int chercher_utilisateur(char *email, char *mdp) {

    FILE * fichier = NULL;

    fichier = fopen("rsa/connexion","r");

    if (!fichier)
    {
        return ERR_LECT;
    }


    char * tmp_email = malloc(sizeof(email)+2);
    char * tmp_mdp = malloc(sizeof(mdp)+2);
    char * user = NULL;
    char * password = NULL;
    size_t size = 0;


    if(!tmp_email || !tmp_mdp) {
        free(user);
        free(password);
        free(tmp_email);
        free(tmp_mdp);
        fclose(fichier);
        return chercher_utilisateur(email, mdp);
    }

    strcpy(tmp_email, strcat(email, "\n"));
    strcpy(tmp_mdp, strcat(mdp, "\n"));

    while(getline(&user, &size , fichier) != -1) {

        getline(&password, &size, fichier);

        if(strcmp(user, tmp_email) == 0 && strcmp(password, tmp_mdp) == 0)
        {
            free(user);
            free(password);
            free(tmp_email);
            free(tmp_mdp);
            fclose(fichier);
            return 0;
        }
    }

    free(user);
    free(password);
    free(tmp_email);
    free(tmp_mdp);
    fclose(fichier);
    return 1;
}
/*
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
	 char c;
	 int alternateur = 0;		  // permet d'alterner entre les caractères non utilisé
	 int donnee_structurelle = 0; // position à traiter
	 int nbr_mail_traiter = 0;    // le nombre de mail qu'on aura traiter
	 //b->m = malloc(sizeof(mail)*100); // on peut avoir 100 mails
	 
	 // Parser de lecture on lit caractere par caractere: 
	 do {
		 debut:
		  c = fgetc(fichier);
		 if(c == ':' || c == '\n') {
			 alternateur = 1 - alternateur;
			 c = fgetc(fichier);
		 }
		  if(alternateur == 1) {
			  if(donnee_structurelle == 0) {
					//~ char * buff0 = malloc(sizeof(char) * 4);
					int i = 0;
					 do {
						//~ buff0[i] = c;
						printf("%c",c);
						c = fgetc(fichier);
						i++;
					} while(c != '\n');
					printf("\n");
					alternateur = 0;
					//~ if(strcmp(buff0,"sig") == 0) {
						//~ b->m[nbr_mail_traiter].signer = 0;
					//~ } else {
						//~ b->m[nbr_mail_traiter].signer = 1;
					//~ }
					//~ free(buff0);
					donnee_structurelle++;
					goto debut;
				}
				if(donnee_structurelle == 1) {
					//~ char * buff1 = malloc(sizeof(char) * 50);
					int a = 0;
					do {
							printf("%c",c);
						c = fgetc(fichier);
						//~ buff1[a] = c;
						a++;
					} while(c != '\n');
					printf("\n");
					alternateur = 0;
					//~ b->m[nbr_mail_traiter].dest_email = malloc(sizeof(char) * 50);
					//~ strcpy(b->m[nbr_mail_traiter].dest_email,buff1);
					//~ free(buff1);
					donnee_structurelle++;
					goto debut;
				}
				if(donnee_structurelle == 2) {
					//~ char * buff2 = malloc(sizeof(char) * 2000);
					int e = 0;
					do {
						c = fgetc(fichier);
						printf("%c",c);
						//~ buff2[e] = c;
						e++;
					} while(c!= '\n');
					alternateur = 0;
					//~ b->m[nbr_mail_traiter].message = malloc(sizeof(char) * 2000);
					//~ strcpy(b->m[nbr_mail_traiter].message,buff2);
					//~ free(buff2);
					donnee_structurelle++;
					goto debut;
				}
				if(donnee_structurelle == 3) {
					//~ if(b->m[nbr_mail_traiter].signer != 0) {
						//~ char * buff3 = malloc(sizeof(char) * 2000);
						int d = 0;
						do {
							c = fgetc(fichier);
							printf("%c",c);
							//~ buff3[d] = c;
							d++;
						} while(c!= '\n');
						//~ strcpy(b->m[nbr_mail_traiter].signature,buff3);
						//~ free(buff3);
					//~ }
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
*/