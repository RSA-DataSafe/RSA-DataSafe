#ifndef H_PARAMETRE_H
#define H_PARAMETRE_H
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

//parametres 
	GtkWidget   *imageP , *labelP , *imageBP[4] ,*buttonP[4] ; 

//compte 
	GtkWidget    *imagecompte , *imagebtcomp[2],  *labelcompte ,*buttoncomp[4]  
	, *entreecomp[4], *labelcomp[4];

//securité 
	GtkWidget *imagesecurite , *imagebsecurite[2], *labelsecurite , *buttonsecurite[3] ;
	GtkWidget * attention; 

	void page_Parametre();
	void Slots_parametre(GtkWidget * sender , gpointer * data);
	void page_compte();
	void modificattion_donnes_compte(GtkWidget * sender , gpointer data);
	
	void page_securite();


#endif
