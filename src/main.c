#include <gmp.h>
#include <stdio.h>
#include <string.h>
#include "generation/bbs.c"
#include "gestion_fichier/ecriture.c"
int main(void) {
	informations user;
	//
	user.email=malloc(strlen("hadjablynda99@gmail.com") *sizeof(char));
	strcpy(user.email,"hadjablynda99@gmail.com");
	user.mdp=malloc(strlen("lynda")*sizeof(char));
	strcpy(user.mdp,"lynda");
	nouvel_utilisateur(user.email,user.mdp);
	mpz_init(user.prive.d);
	mpz_set_ui(user.prive.d,12587412);
	mpz_init(user.prive.n);
	mpz_set_ui(user.prive.n,907484875774);
	mpz_init(user.publique.e);
	mpz_set_ui(user.publique.e,878412874229655);
	mpz_init(user.publique.n);
	mpz_set_ui(user.publique.n,907484875774);
	char *d =malloc(1024*sizeof(char));
	char *e =malloc(1024*sizeof(char));
	char *n =malloc(1024*sizeof(char));
	mpz_get_str(d,10,user.prive.d);
    mpz_get_str(e,10,user.publique.e);
	mpz_get_str(n,10,user.publique.n);
    char * chemin=malloc((strlen(user.email)+15)*sizeof(char));
    strcpy(chemin,user.email);
    strcat(chemin,"cles.txt");
    ecrire_fichier(chemin,d);
    ecrire_fichier(chemin,e);
    ecrire_fichier(chemin,n);
     change_cle(&user);

    

	//Change_Email("hadjablynda99@gmail.com","lynda","hadjabLNASFNE@gmail.fr");
		return 0;
}
