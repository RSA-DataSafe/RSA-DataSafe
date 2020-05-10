#ifndef H_INSCRIPTION_H
#define H_INSCRIPTION_H
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

//inscroption
	GtkWidget   *buttoni[2]  , *entreei[4], *labeli[5] ;
    GtkWidget * MAINi ; 
	void  Page_d_inscription();
	void SLots_inscription(GtkWidget * sender , gpointer * data);
#endif
