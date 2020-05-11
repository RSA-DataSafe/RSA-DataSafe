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
	
    gtk_init(&argc, &argv);
	

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
    
    return EXIT_SUCCESS;
}
