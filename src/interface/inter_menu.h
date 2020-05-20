#ifndef H_MENU_H
#define H_MENU_H
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
   extern int a ;
	GtkWidget   *imageM , *imageBM[5] ,*buttonM[5] , *labelMenu , *labelBMenu ;
	
	/* Affiche le menu principal */
	void menu_principal();

	/* Permet la gestion des intéractions avec les boutons d'intéraction du menu
	*
	* @param 	sender	widget émetteur
	* @param 	data 	donnée transmise par le widget emetteur
	*/
	void slots_Menu(GtkWidget * sender , gpointer *data);


#endif
