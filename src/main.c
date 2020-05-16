#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <glib-object.h>
#include <gobject/gvaluecollector.h>
#include <string.h>
#include <glib/gi18n.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <glib.h>
#include "structure/structure.h"
#include "interface/inter_connexion.h"
#include "interface/inter_inscription.h"
#include "interface/inter_menu.h"
#include "interface/inter_chiffrer.h"
#include "interface/inter_dechiffrer.h"
#include "interface/inter_messagerie.h"
#include "interface/inter_parametre.h"
#include "generation/generation_cle.h"
#include "chiffrement/chiffrement.h"
#include "dechiffrement/dechiffrement.h"

#include "gestion_fichier/conversion.h"
int Lancement()
{ 
    gtk_stack_set_visible_child (GTK_STACK (stack), GTK_WIDGET (Connexion)); return 0;
}


int main(int argc , char ** argv)
{
	
	 cle_publique pub;
	cle_prive prive;
	mpz_inits(pub.n, pub.e, prive.n, prive.d, NULL);
	genere_cle(&pub, &prive, 1024);
	
	message *m  = malloc(sizeof(message));
    mpz_init(m->nombre);
    mpz_init(m->taille);
    char *machaine=malloc(sizeof(char)*200);
    strcpy(machaine,"hello everyone");
    message *transf;
    transf=conversion_char_mpz(machaine);
  
    mpz_set(m->nombre, transf->nombre);
    mpz_set(m->taille, transf->taille);

	message *encodage  = malloc(sizeof(message));
    mpz_init(encodage->nombre);
    mpz_init(encodage->taille);

	mpz_t alea; mpz_init(alea);


    time_t t; 
    srand(time(&t));
    gmp_randstate_t etat;
    gmp_randinit_default(etat);
    gmp_randseed_ui(etat, rand());
    mpz_urandomb(alea, etat, 256);
	mpz_out_str(0, 2, m->nombre);
	printf("\n\n");
	printf("mpz_char = ");
	char *ch = conversion_mpz_char(m);
	printf("%s\n\n", ch);
	free(ch);
	ch = conversion_mpz_hexa(m);
	printf("%s\n\n", ch);
	free(ch);

	mpz_t tmp;
	mpz_init(tmp);
	

	block *b = creer_block_oaep(m, encodage, alea);
	oaep(b, alea);
	for (int i = 0; i < b->nb_block; i++)
	{
		mpz_set(tmp, b->tab[i]);
		mpz_powm(b->tab[i], tmp, pub.e, pub.n);
	}
	printf("oaep : \n");
	mpz_out_str(0, 10, b->tab[0]);
	printf("\n\n");
	message *chiff = recupere_message_oaep(b);

	block *h = creer_block_oaep_1(chiff);
	printf("oaep-1 : \n");
	mpz_out_str(0, 10, h->tab[0]);
	printf("\n\n");
	for (int i = 0; i < h->nb_block; i++)
	{
		mpz_set(tmp, h->tab[i]);
		mpz_powm(h->tab[i], tmp, prive.d, prive.n);
	}
	oaep_1(h);
	message *clair = recupere_message_oaep_1(h);
  printf("clair final en mpz : ");
	mpz_out_str(0, 10, clair->nombre);
	printf("\n\n");
 printf("clair final en char : ");
	char *sh = conversion_mpz_char(clair);
	printf("%s\n\n", sh);
	free(sh);
	
   /* gtk_init(&argc, &argv);
	

    initialisation();
	page_ouverture();
	Page_de_connection();
	Page_d_inscription();
	page_Menu();
	page_Parametre();
	page_chiffrer();	
	page_dechiffrer();
	page_messagerie();
	page_MessageRecu();
	page_envoyer_unmsg();
	page_message_envoyes(); 
	page_message_indesirable();
	page_compte();
	page_securite();
	
	CSS();

   g_signal_connect(G_OBJECT(MainWindow), "delete-event", G_CALLBACK(gtk_main_quit), NULL);
   g_timeout_add (2500,(GSourceFunc)Lancement, NULL);
   
   gtk_widget_show_all(MainWindow);
   gtk_main();
    
    return EXIT_SUCCESS;*/
  
    
	/*message * m =conversion_char_mpz("lynda");
	mpz_out_str(0,10,m->nombre);
	printf("\n\n");
	mpz_out_str(0,10,m->taille);
	 char * chaine;
	 chaine= conversion_mpz_char(m);
      printf("\n\n");
      printf("%s\n",chaine);
      char * ch=malloc(sizeof(char)*200);
      strcpy(ch,"2c");
message *mss;
     mss=conversion_hexa_mpz(ch);
     printf("\n");
     mpz_out_str(0,10,mss->nombre);
     printf("\n\n");
     char* mp=conversion_mpz_hexa (mss);
     printf("%s\n",mp);*/
  //  char *ch;
    // ch=conversion_mpz_hexa(m);

    /*cle_publique  publique;
    cle_prive prive;
    mpz_inits(publique.e,publique.n,NULL);
    recupere_cle_publique("test@email.com","user",&publique);
    recupere_cle_privee("test@email.com","user",&prive);
    mpz_out_str(0,10,publique.e);
    printf("\n\n");
    mpz_out_str(0,10,publique.n);
    printf("\n\n");
     mpz_out_str(0,10,prive.d);
    printf("\n\n");
    mpz_out_str(0,10,prive.n);*/
   
}
