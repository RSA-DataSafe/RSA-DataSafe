#ifndef H_DECHIFFRER_H
#define H_DECHIFFRER_H
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
#include "../structure/structure.h"
#include "inter_initialisation.h"

	// Variables environnement 
GtkWidget   *imageD  , *labelD[2] , *imageBD[2] , *buttonD[4] , *entreeD ,  *text_viewD; 
GtkTextBuffer *bufferD , *bufferCD;
GtkWidget *spinnerD; 
GtkWidget *windowD;
GtkWidget * vboxCD , * labelcharD ,*text_viewCD;
message* messageclair;
message* chiff;
char *chaineD;
char* pathD;

	 /* Affiche la page de déchiffrement */
	void page_dechiffrement();
	/* Permet la gestion des intéractions avec les boutons de navigations
	*
	* @param 	sender	widget émetteur
	* @param 	data 	donnée transmise par le widget emetteur
	*/
	void Slots_dechiffer(GtkWidget * sender , gpointer * data);
	/* Affiche une page de chargement lors du déchiffrement */
	void page_chargementD();
	/* Affiche une page contenant le résultat du déchiffrement */
	int page_resultatD();
	/* Fonction wrap pour synthétiser une fonction gtk */
	void detuire_mini_f_resultatD();
	/* Permet la gestion des intéractions avec le file selector
	*
	* @param 	chooser	widget file selector
	* @param 	user_data 	donnée transmise par le widget file selector
	*/
	void fic_selected (GtkFileChooser *chooser, gpointer user_data);

#endif
