#include <gtk/gtk.h>
#include <glib-object.h>
#include <gobject/gvaluecollector.h>
#include <string.h>
#include <glib/gi18n.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header/inter_connexion.h"
#include "Header/inter_inscription.h"
#include "Header/inter_menu.h"
#include "Header/inter_chiffrer.h"
#include "Header/inter_dechiffrer.h"
#include "Header/inter_messagerie.h"
#include "Header/inter_parametre.h"



int Lancement()
{ 
    gtk_stack_set_visible_child (GTK_STACK (stack), GTK_WIDGET (Connexion)); return 0;
}

void file_selected (GtkFileChooser *chooser, gpointer user_data)
{
  gchar *filename = gtk_file_chooser_get_filename (chooser);
  if (!filename) return;
  g_print ("Path du fichier qui sera lu  : %s\n", filename);
  g_free (filename);
}

// on fera un for ici plus tard 
void Signaux()
{
	 //sert a rien c juste pour moi 
	 g_signal_connect (G_OBJECT (buttonC[3]), "selection-changed", G_CALLBACK (file_selected), NULL);

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
  
  Signaux();
	gtk_main();
    
    return EXIT_SUCCESS;
}