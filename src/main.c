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

	
    /*gtk_init(&argc, &argv);
	

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
	/*message *m  = malloc(sizeof(message));
    mpz_init(m->nombre);
    mpz_init(m->taille);
    mpz_set_ui(m->nombre, 92);
    mpz_set_ui(m->taille, 8);

	message *encodage  = malloc(sizeof(message));
    mpz_init(encodage->nombre);
    mpz_init(encodage->taille);

	mpz_t alea; mpz_init(alea);

	mpz_out_str(0, 2, m->nombre);
	printf("\n");
	char *ch = conversion_mpz_char(m);
	printf("%s\n", ch);
	free(ch);
	ch = conversion_mpz_hexa(m);
	printf("%s\n", ch);
	free(ch);

	block *b = creer_block_oaep(m, encodage, alea);
	oaep(b, alea);
	message *chiff = recupere_message_oaep(b);

	block *h = creer_block_oaep_1(chiff);
	oaep_1(h);
	message *clair = recupere_message_oaep_1(h);

	mpz_out_str(0, 2, clair->nombre);
	printf("\n");

	char *sh = conversion_mpz_char(clair);
	printf("%s\n", sh);
	free(sh);
	sh = conversion_mpz_hexa(clair);
	printf("%s\n", sh);
	free(sh);

	for(int i = 0; i < (b->nb_block); i++) {
        mpz_clear(b->tab[i]);
    }
    free(b->tab); 
	for(int i = 0; i < (b->nb_block); i++) {
        mpz_clear(h->tab[i]);
    }
    free(h->tab);
	mpz_clears(m->nombre, m->taille, encodage->nombre, encodage->taille, alea, NULL);
	free(m);
	free(encodage);
	free(clair);
	free(b);
	free(h);*/
  /* mpz_t res,num,exp,mod;
   mpz_inits(res,num,exp,mod,NULL);
   mpz_set_ui(num,245155);
   mpz_set_ui(exp,56);
   mpz_set_ui(mod,98745);
	expo_mod( res,  num,  exp,  mod);
	mpz_out_str(0,10,res);*/
	cle_publique pub;
	cle_prive prive;
	mpz_inits(pub.e,pub.n,prive.d,prive.n,NULL);
	genere_cle(&pub,&prive, 1024);

	mpz_t chiff;
	mpz_init(chiff);
	mpz_t mess;
	mpz_init(mess);
	mpz_set_ui(mess,100);
	mpz_powm(chiff, mess, pub.e, pub.n);
	mpz_out_str(0,10,chiff);
	printf("\n\n");
	mpz_t dechi;
	mpz_init(dechi);
	mpz_powm(dechi,chiff,prive.d,prive.n);

	printf("dechiff= \n");
	mpz_out_str(0,10,dechi);
	printf("\n\n");
	printf("e= ");
	mpz_out_str(0,10,pub.e);
	printf("\n\n");
	printf("n= ");
	mpz_out_str(0,10,pub.n);
	printf("\n\n");
   printf("d= ");
	mpz_out_str(0,10,prive.d);
	printf("\n\n");


	/*message *chiffrer;
	message m;
	mpz_inits(m.nombre,m.taille,NULL);
	mpz_set_ui(m.nombre,25);
	mpz_set_ui(m.taille,mpz_sizeinbase(m.nombre,2));

	message encodage;
	mpz_inits(encodage.nombre,encodage.taille,NULL);
	mpz_init_set_str(encodage.nombre,"ASCCI",10);
	mpz_out_str(0,10,encodage.nombre);
	mpz_set_ui(encodage.taille,mpz_sizeinbase(encodage.nombre,2));
 
 
    chiffrer=chiffrement(&m,&pub,&encodage);
     printf("le chiffrement =");
    mpz_out_str(0,10,chiffrer->nombre);
    printf("\n\n");
    message *dechiff;
    dechiff=dechiffrement(chiffrer,&prive);
    printf("le dechiffrement =");
    mpz_out_str(0,10,dechiff->nombre);
    printf("\n\n");*/
   /* mpz_t nombre,tour;
    mpz_inits(nombre,tour,NULL);
    mpz_set_ui(nombre,117430);
    mpz_set_ui(tour,2);
    printf("%d\n", miller_rabbin(nombre,tour));*/


}
