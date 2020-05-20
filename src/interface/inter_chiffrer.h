#ifndef H_CHIFFRER_H
#define H_CHIFFRER_H
#include <gtk/gtk.h>
#include <glib-object.h>
#include <gobject/gvaluecollector.h>
#include <string.h>
#include <glib/gi18n.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <glib.h>
#include "../structure/structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inter_initialisation.h"
 
	// Variables environnement

	GtkWidget   *imageC  , *labelC[2] , *imageBC[2] , *buttonC[4] , *entreeC  ,*text_viewC; 
	GtkTextBuffer *bufferC , *bufferCC;
	GtkWidget * dialogC , *windc ; 
	GtkWidget *spinner; 
	GtkWidget *window;
	GtkWidget * vboxCC , * labelcharc ,*text_viewCC;
	
	char* chaine;
    message *  messageachiff ;
    message* messagechiff; 
    char* path;
    message *  codage;

    // Prototypes

    /* Affiche la page de chiffrement */
	void page_chiffrement();

	/* Affiche une page de chargement lors du chiffrement */
	void page_chargementC();

	/* Affiche une page contenant le résultat du chiffrement */
	int  page_resultatC();

	/* Fonction wrap pour synthétiser une fonction gtk */
	void detuire_mini_f_resultat();

	/* Permet la gestion des intéractions avec les boutons de navigations
	*
	* @param 	sender	widget émetteur
	* @param 	data 	donnée transmise par le widget emetteur
	*/
	void Slots_Chiffrer(GtkWidget * sender , gpointer *data);

	/* Permet la gestion des intéractions avec le file selector
	*
	* @param 	chooser	widget file selector
	* @param 	user_data 	donnée transmise par le widget file selector
	*/
	void file_selected (GtkFileChooser *chooser, gpointer user_data);
	

#endif
