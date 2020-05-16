#include <gmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../structure/structure.h"
#include "lecture.h"
#include "erreur.h"

int chercher_utilisateur(char *email, char *mdp) {
	
	FILE * fichier = NULL;
	
	fichier = fopen("rsa/connexion.txt","r");
	
	if (fichier == NULL) {
		return ERR_LECT;
	}
	// Variables email_tmp et mdp_tmp pour ajouté \n à la fin quand on va comparer chaque mail en lisant ligne par ligne
	char * user = NULL;
	char * mot_de_passe = NULL;	
	char * email_tmp = calloc(sizeof(email) + 2, sizeof(char));
	char * mdp_tmp = calloc(sizeof(mdp) + 2, sizeof(char));
	
	if(email_tmp==NULL || mdp_tmp == NULL) {
		return ERR_LECT;
	}
	
	size_t bufsize = 0;
	
	strcpy(email_tmp,email);
	strcpy(mdp_tmp,mdp);
	strcat(email_tmp,"\n");
	strcat(mdp_tmp,"\n");
	
	int est_present = ERR_LECT; // si l'email et mdp sont presents 
	
	// Lecture ligne par ligne
	while(getline(&user,&bufsize,fichier) != -1) {
		getline(&mot_de_passe,&bufsize,fichier);
		if(strcmp(email_tmp,user) == 0) {
			if(strcmp(mdp_tmp,mot_de_passe) == 0) {
				est_present = 0;
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
	char * chemin = calloc(sizeof(char)*200 + sizeof("rsa/") + sizeof("/Cles.txt"),sizeof(char));
	/* Buffer temporaire */
	char * e = calloc(sizeof(char)*2048,sizeof(char));
	char * n = calloc(sizeof(char)*2048,sizeof(char));
	/* ----------------- */
	
	if(chemin == NULL || e == NULL || n == NULL) {
		return ERR_LECT;
	}
	
	strcat(chemin,"rsa/");
	strcat(chemin,email);
	strcat(chemin,"/Cles.txt");
	
	char * res = lire_fichier(chemin);	// Ouverture et lecture du fichier 
	free(chemin);	
		
	if(strcmp(res,"erreur lecture") == 0) {
		return ERR_LECT;
	}
	// Automate de lecture (voir ecriture de comment est stoké les Cles): 

	int head = 0;	 // tête de lecture
	
	while(res[head] != '\n') head++;
	head++;
	int cmp1 = 0;
	while(res[head] != '\n') {
		e[cmp1] = res[head];
		head++;
		cmp++;
	}
	mpz_init_set_str(publique->e,e,10);
	free(e);
	head++;
	int cmp2 = 0;
	while(res[head] != '\0' && res[head] != '\n') { // Ca depend si on ouvre un fichier avec un ide qui ajoute un retour chariot à la fin
		n[cmp2] = res[head];
		head++;
		cmp2++;
	}
	mpz_init_set_str(publique->n,n,10);
	free(n);
	
	return 0;	
}

int recupere_cle_privee(char * email, char * mdp, cle_prive * prive) {
	if(chercher_utilisateur(email,mdp) != ERR_LECT) {
		char * chemin = calloc(sizeof(char)*200 + sizeof("rsa/") + sizeof("/Cles.txt"),sizeof(char));
		/* Buffer temporaire */
		char * d = calloc(sizeof(char)*2048,sizeof(char));
		char * n = calloc(sizeof(char)*2048,sizeof(char));
		/* ----------------- */
		
		if(chemin == NULL || d == NULL || n == NULL) {
			return ERR_LECT;
		}
		
		strcat(chemin,"rsa/");
		strcat(chemin,email);
		strcat(chemin,"/Cles.txt");
		
		char * res = lire_fichier(chemin);	// Ouverture et lecture du fichier 
		free(chemin);	
			
		if(strcmp(res,"erreur lecture") == 0) {
			return ERR_LECT;
		}
		
		int head = 0;	
		
		while(res[head] != '\n') {
			d[head] = res[head];
			head++;
		}
		
		mpz_init_set_str(prive->d,d,10);
		free(d);
		head++;
		while(res[head] != '\n') head++;
		head++;
		int cmp = 0;
		while(res[head] != '\0' && res[head] != '\n') { // Ca depend si on ouvre un fichier avec un ide qui ajoute un retour chariot à la fin
			n[cmp] = res[head];
			head++;
			cmp++;
		}
		mpz_init_set_str(prive->n,n,10);
		free(n);
		
		return 0;
	}
	return ERR_LECT;
}

int lire_boite(char *email, boite * b) {
	 char * chemin = calloc(sizeof("rsa/") + sizeof(email)+ 50,sizeof(char));
	 if(chemin == NULL) {
		return ERR_LECT;
	 }
	 strcat(chemin,"rsa/");
	 strcat(chemin,email);	
	 strcat(chemin,"/");
	 strcat(chemin, b->nom_boite);
	
	 FILE * fichier = fopen(chemin,"r");
	 free(chemin);
	 
	 if(fichier == NULL) {
		 return ERR_LECT;
	 }
	 
	 char c;					  // Va permettre de lire caractère par caractère
	 int alternateur = 0;		  // permet d'alterner entre les caractères non utilisé
	 int donnee_structurelle = 0; // position à traiter
	 int nbr_mail_traiter = 0;    // le nombre de mail qu'on aura traiter
	 b->m = calloc(sizeof(mail)*1000,sizeof(mail)); // on peut avoir 1000 mails
	 
	 if(b->m == NULL) {
		 return ERR_LECT;
	 }
	 
	 // Automate de lecture on lit caractere par caractere: 
	  while(c != EOF) {
		 debut: // etiquette qui permet de revenir au début. De '\n' à ':' se trouve des caractères non utilisées
		  c = fgetc(fichier);
		 if(c == ':' || c == '\n') { 
			 alternateur = 1 - alternateur;
			 c = fgetc(fichier);
		 }
		  if(alternateur == 1) {
			  // Vérifier si message signé 
			  if(donnee_structurelle == 0) {
					char * buff0 = calloc(sizeof(char) * 10,sizeof(char));
					if(buff0 == NULL) {
						return ERR_LECT;
					}
					int i = 0;
					 do {
						buff0[i] = c;
						c = fgetc(fichier);
						i++;
					} while(c != '\n');
					alternateur = 0;
					buff0[i] = '\0';
					if(strcmp(buff0,"sig") == 0) {
						b->m[nbr_mail_traiter].signer = 1;
					} else {
						b->m[nbr_mail_traiter].signer = 0;
					}
					free(buff0);
					donnee_structurelle++;
					goto debut;
				}
				// Récupérer le mail du destinataire
				if(donnee_structurelle == 1) {
					char * buff1 = calloc(sizeof(char) * 150,sizeof(char));
					b->m[nbr_mail_traiter].env_email = calloc(sizeof(char) * 150,sizeof(char));
					if(buff1 == NULL || b->m[nbr_mail_traiter].env_email == NULL) {
						return ERR_LECT;
					}
					int a = 0;
					do { 
						c = fgetc(fichier);
						buff1[a] = c;
						a++;
					} while(c != '\n');
					alternateur = 0;
					memcpy(b->m[nbr_mail_traiter].env_email,buff1,strlen(buff1));
					free(buff1);
					donnee_structurelle++;
					goto debut;
				}
				// Récupérer le message
				if(donnee_structurelle == 2) {
					char * buff2 = calloc(sizeof(char) * 2000,sizeof(char));
					b->m[nbr_mail_traiter].message = calloc(sizeof(char) * 2000,sizeof(char));
					if(buff2 == NULL || b->m[nbr_mail_traiter].message == NULL) {
						return ERR_LECT;
					}
					int e = 0;
					do {
						c = fgetc(fichier);
						buff2[e] = c;
						e++;
					} while(c!= '\n');
					alternateur = 0;
					memcpy(b->m[nbr_mail_traiter].message,buff2,strlen(buff2));
					free(buff2);
					donnee_structurelle++;
					goto debut;
				}
				// Récuperer la signature
				if(donnee_structurelle == 3) {
					char * buff3 = calloc(sizeof(char) * 2000,sizeof(char));
					b->m[nbr_mail_traiter].signature = calloc(sizeof(char) * 2000,sizeof(char));
					if(buff3 == NULL || b->m[nbr_mail_traiter].signature == NULL) {
						return ERR_LECT;
					}
					int d = 0;
					do {
						c = fgetc(fichier);
						buff3[d] = c;
						d++;
					} while(c!= '\n');
					memcpy(b->m[nbr_mail_traiter].signature,buff3,strlen(buff3));
					free(buff3);
					alternateur = 0;
					nbr_mail_traiter ++;
					donnee_structurelle = 0; // remise à zéro des données 
					goto debut;
				}
			}
	 }
	 b->nb_mail = nbr_mail_traiter;
	 return 0;	
}

char *lire_fichier(char * chemin) {
	char * res = calloc((sizeof(char)*2048)*3 + (sizeof(char)* 5), sizeof(char));
	if(res == NULL) {
		res = "erreur lecture"; // pour lecture des clés, la lettre 'r' ne sera pas presente
		return res;
	}
	FILE * fichier = fopen(chemin,"r");
	if(fichier == NULL) {
		res = "erreur lecture";
		return res;
	}
	
	char c;
	for(int i = 0; (c = fgetc(fichier)) != EOF; i++) {
		res[i] = c;
	}

	fclose(fichier);
	return res;
}
