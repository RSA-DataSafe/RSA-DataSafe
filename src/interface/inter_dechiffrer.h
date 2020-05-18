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

GtkWidget   *imageD  , *labelD[2] , *imageBD[2] , *buttonD[4] , *entreeD ,  *text_viewD; 
GtkTextBuffer *bufferD , *bufferCD;
GtkWidget *spinnerD; 
GtkWidget *windowD;
GtkWidget * vboxCD , * labelcharD ,*text_viewCD;
message* messageclair;
message* chiff;
char *chaineD;
char* pathD;

void page_dechiffrement();
void Slots_dechiffer(GtkWidget * sender , gpointer * data);
void page_chargementD();
int page_resultatD();
void detuire_mini_f_resultatD();
void fic_selected (GtkFileChooser *chooser, gpointer user_data);

#endif
