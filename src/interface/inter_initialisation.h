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
#include "../structure/structure.h"
#include "../gestion_fichier/lecture.h"
#include "../gestion_fichier/ecriture.h"
#include "../structure/structure.h"
#include "../generation/generation_cle.h"
#include"../generation/bbs.h"
#include"../generation/euclide.h"
#include"../generation/primalite.h"
#include "../calcul/calcul.h"
#include "../chiffrement/chiffrement.h"
#include "../chiffrement/gestion_block.h"
#include "../chiffrement/oaep.h"
#include "../dechiffrement/oaep_1.h"
#include "../dechiffrement/dechiffrement.h"
#include "../signature/signature.h"
#include "../signature/sha3.h"





    GtkWidget  *MainWindow;
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
