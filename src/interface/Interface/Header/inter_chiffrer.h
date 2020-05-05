#ifndef H_CHIFFRER_H
#define H_CHIFFRER_H
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
#include "inter_initialisation.h"
 
//chiffrer 
	GtkWidget   *imageC  , *labelC[2] , *imageBC[2] , *buttonC[4] , *entreeC  ,*text_viewC; 
	GtkTextBuffer *bufferC , *bufferCC;
	GtkWidget * dialogC , *windc ; 
	GtkWidget *spinner; 
	GtkWidget *window;
	GtkWidget * vboxCC , * labelcharc ,*text_viewCC;

	void page_chiffrer();
	void page_chargementC();
	int  page_resultatC();
	void detuire_mini_f_resultat();
	void Slots_Chiffrer(GtkWidget * sender , gpointer *data);
	

#endif
