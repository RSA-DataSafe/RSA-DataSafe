#include "lecture.h"
#define MAX_CARACT 60

int chercher_utilisateur(char *email, char *mdp) {

    FILE * fichier = NULL;

    fichier = fopen("rsa/connexion.txt","r");

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

int recupere_cle_publique(char * email, char * mdp, cle_publique * publique) {
	
	char * chemin = calloc(sizeof(char)*MAX_CARACT + sizeof("rsa/") + sizeof("/Cles.txt"),sizeof(char));
	char * e = NULL;
	char * d = NULL;
	char * n = NULL;
	
	if(chemin == NULL) {
		return ERR_LECT;
	}
	
	strcat(chemin,"rsa/");
	strcat(chemin,email);
	strcat(chemin,"/Cles.txt");

	FILE * fichier = fopen(chemin,"r");		
	free(chemin);
	
	if(fichier == NULL) {
		return ERR_LECT;
	}
	
	size_t bufsize = 0;
	
	if(getline(&d,&bufsize,fichier) == -1) return ERR_LECT;
	free(d);
	if(getline(&e,&bufsize,fichier) == -1) return ERR_LECT;
	mpz_init_set_str(publique->e,e,10);
	free(e);
	if(getline(&n,&bufsize,fichier) == -1) return ERR_LECT;
	mpz_init_set_str(publique->n,n,10);
	free(n);
	fclose(fichier);
	return 0;	
}

int recupere_cle_privee(char * email, char * mdp, cle_prive * prive) {
	if(chercher_utilisateur(email,mdp) != ERR_LECT) {
		char * chemin = calloc(sizeof(char)*MAX_CARACT + sizeof("rsa/") + sizeof("/Cles.txt"),sizeof(char));
		char * e = NULL;
		char * d = NULL;
		char * n = NULL;
		
		if(chemin == NULL) {
			return ERR_LECT;
		}
		
		
		int i = 0;
    	while(email[i] != '\n' && email[i] != '\0') i++;
    	email[i] = '\0';
		
		strcpy(chemin,"rsa/");
		strcat(chemin,email);
		strcat(chemin,"/Cles.txt");
		FILE * fichier = fopen(chemin,"r");	
		free(chemin);	
		
		if(fichier == NULL) {
			return ERR_LECT;
		}
		
		size_t bufsize = 0;
		
		if(getline(&d,&bufsize,fichier) == -1) return ERR_LECT;
		mpz_init_set_str(prive->d,d,10);
		free(d);
		
		if(getline(&e,&bufsize,fichier) == -1) return ERR_LECT;
		free(e);
		
		if(getline(&n,&bufsize,fichier) == -1) return ERR_LECT;
		mpz_init_set_str(prive->n,n,10);
		free(n);
		
		fclose(fichier);
		return 0;
	}
	return ERR_LECT;
}


int lire_boite(char *email, boite * b)
{
	 char * chemin = malloc (sizeof(char)*500);
	 if(chemin == NULL) {
		return ERR_LECT;
	 }
	 strcpy(chemin,"rsa/");
	 strcat(chemin,email);	
	 strcat(chemin,"/");
	 strcat(chemin, b->nom_boite);

	  printf("chemiiiiiin %s\n", chemin);
	 FILE * fichier = fopen(chemin,"r");
 
	 if(fichier == NULL) {
	 
		 return ERR_LECT;
	 }
	 
	 char c;					  // Va permettre de lire caractère par caractère
	 int nbr_mail_traiter = 0;    // le nombre de mail qu'on aura traiter
	 b->m = calloc(sizeof(mail)*100,sizeof(mail)); // on peut avoir 1000 mails
	 if(b->m == NULL) return ERR_LECT;
	 
	 
	 c=fgetc(fichier);
	 // tant que le fichier n est pas vide 
	 while(c != EOF){
		 
		int a = 0;
		char * buff0 = calloc(sizeof(char) * 100,sizeof(char));
		char * buff1 = calloc(sizeof(char) * 100,sizeof(char));
		char * buff4 = calloc(sizeof(char) * 100,sizeof(char));
		
		if(buff0 == NULL || buff1==NULL || buff4==NULL) 
						                          return ERR_LECT;
					
		//titre du message
		do { 
			buff0[a] = c;
			c = fgetc(fichier);
			a++;
		} while(c != ':');

		//stock le titre 
		b->m[nbr_mail_traiter].titre = calloc(sizeof(char) *1000,sizeof(char));
		memcpy(b->m[nbr_mail_traiter].titre,buff0,strlen(buff0));
		free(buff0);
		a=0;
		//signer ou pas 
		do { 
			c = fgetc(fichier);
			buff1[a] = c;
			a++;
		} while(c != '\n');
				//printf("sigggggggggg  |%s|\n" , buff1);
		//entrer la valeur si signé ou pas
		if(strcmp(buff1,"sig\n") == 0)

			b->m[nbr_mail_traiter].signer = 1;
		else 
			b->m[nbr_mail_traiter].signer = 0;
			
		free(buff1);
		a=0;
		//emetteur du message
		do { 
			c = fgetc(fichier);
			buff4[a] = c;
			a++;
		} while(c != '\n');
		
		//stock l nom de  emetteur
		b->m[nbr_mail_traiter].env_email= calloc(sizeof(char) *1000,sizeof(char));
		memcpy(b->m[nbr_mail_traiter].env_email,buff4,strlen(buff4));
		free(buff4);
		
		//lecture du message
		a = 0;
		char * buff2 = calloc(sizeof(char) * 3000,sizeof(char));
		b->m[nbr_mail_traiter].message = calloc(sizeof(char) * 3000,sizeof(char));
		
		if(buff2 == NULL || b->m[nbr_mail_traiter].message == NULL) 
				return ERR_LECT;
		
		do {
				c = fgetc(fichier);
				buff2[a] = c;
				a++;
			} while(c!= '\n' && c!= '\0');
					
			memcpy(b->m[nbr_mail_traiter].message,buff2,strlen(buff2));
				 
			free(buff2);
		//printf("(okkkkkkkkkkkkk %d)\n",b->m[nbr_mail_traiter].signer );
		//lecture de la signature si signé	
		if(b->m[nbr_mail_traiter].signer==1){
				
			char * buff3 = calloc(sizeof(char) * 3000,sizeof(char));
			b->m[nbr_mail_traiter].signature = calloc(sizeof(char) *3000,sizeof(char));
	
			if(buff3 == NULL || b->m[nbr_mail_traiter].signature == NULL) {
					return ERR_LECT;
			}
			
			int d = 0;
			
			do {
				c = fgetc(fichier);
				buff3[d] = c;
				d++;
				} while(c!= '\n' && c !=EOF);

           
			   memcpy(b->m[nbr_mail_traiter].signature,buff3,strlen(buff3));
		     	free(buff3);
	         
	  
			}
			
			nbr_mail_traiter ++;
			c=fgetc(fichier);
		
	 };
	 
	 printf("nbr_mail_traiter : %d\n" , nbr_mail_traiter);
     	free(chemin); 
	 b->nb_mail = nbr_mail_traiter;
	 fclose(fichier);
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
