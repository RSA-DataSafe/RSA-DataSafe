#ifndef H_CONNEXION_H
#define H_CONNEXION_H

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib-object.h>
#include <gobject/gvaluecollector.h>
#include <string.h>
#include <glib/gi18n.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <glib.h>
#include <string.h>
#include "../structure/structure.h"
#include "inter_initialisation.h"

GtkWidget  *button[2] , *entree[2], *label[4] ,*PEM;
GtkWidget  *MAIN , *horiz1; 



void  page_connexion ();
void Verification_connexion(GtkWidget * sender , gpointer * data);

#endif
