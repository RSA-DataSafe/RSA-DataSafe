#ifndef H_INITIALISATION_H
#define H_INITIALISATION_H
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
#include <gmp.h>
#include "../Src/gestion_fichier/lecture.h"
#include "../Src/gestion_fichier/ecriture.h"
#include "../Src/structure/structure.h"
#include "../Src/generation/generation_cle.h"
#include"../Src/generation/bbs.h"
#include"../Src/generation/euclide.h"
#include"../Src/generation/primalite.h"
#include "../Src/calcul/calcul.h"





    GtkWidget*  MainWindow;
	GtkWidget  *button[2]  ; 
	GtkWidget  *accueil , *Connexion ,* stack ;  
	GdkPixbuf  *icon;
 
	GtkWidget * imagec[2] , *imageacc, *minilogo[2],*Inscription ,*Menu ,*Parametre,*Chiffrer,*Dechiffrer,

	*Messagerie,*MessagerieRecu,*MessagerieEcr, *EnvoyeeMessagerie , *MessagerieInde,*Compte , *Securite;

    GtkWidget   *lbmenu        ,*lbmessagerie,  *lbmessagerierecu  , *lbenvoyeemessagerie   , *lbmessagerieecri,

    *lbmessagerieinde , *lbchiffrer , *lbdechiffrer, *lbparametre , *lbsecurite , *lbcompte; 

   

   informations utilisateur; 


void CSS();
GdkPixbuf *create_pixbuf(const gchar * filename);
void initialisation();
void page_ouverture();
char * remove_n(char * chaine);

#endif