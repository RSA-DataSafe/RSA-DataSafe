#include <gmp.h>
#include <stdio.h>
#include <string.h>
#include "generation/bbs.c"
#include "gestion_fichier/ecriture.c"
#include "calcul/calcul.c"
#include "generation/primalite.c"
#include "generation/euclide.c"
int main(void) {
	
<<<<<<< HEAD
   //nouvel_utilisateur("hadjablynda99@gmail.com","lynda");
  // nouvel_utilisateur("SFNLDNLVE@gmail.fr","SFN");
	//Change_Email("SFNLDNLVE@gmail.fr","SFN","LNDSFN2015@gmail.com");
	//Change_MotDePasse("hadjablynda99@gmail.com","lynda","SFNLIFE");
/*informations user;
user.email=malloc(100*sizeof(char));
user.mdp=malloc(100*sizeof(char));
strcpy(user.email,"hadjablynda99@gmail.com");
strcpy(user.mdp,"SFNLIFE");
mpz_init(user.publique.e);
mpz_init(user.publique.n);
mpz_init(user.prive.d);
mpz_init(user.prive.n);
mpz_set_ui(user.publique.e,147);
mpz_set_ui(user.publique.n,27);
mpz_set_ui(user.prive.d,87);
mpz_set_ui(user.prive.n,27);


	change_cle(&user);*/
=======
    mpz_t u,v,phi,e;
	mpz_init(u);
	mpz_init(v);
	mpz_init(phi);
	mpz_init(e);
	mpz_set_ui(phi,5);
	mpz_set_ui(e,3);
	euclide_etendu( u, v, phi, e );
	    mpz_out_str(stdout,10,u);
	    printf("\n\n");
	    mpz_out_str(stdout,10,v);
	   printf("\n\n");
	shift_gauche(e,2);
	printf("e= ");
	mpz_out_str(stdout,10,e);
	printf("\n\n");
	
>>>>>>> 29a2df12e8351a327fc89cfa6e0c16f37afd99e6
		return 0;
}
