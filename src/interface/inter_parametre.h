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

// Variables environnement
//parametres 
	GtkWidget   *imageP , *labelP , *imageBP[4] ,*buttonP[4] ; 

//compte 
	GtkWidget    *imagecompte , *imagebtcomp[2],  *labelcompte ,*buttoncomp[4]  
	, *entreecomp[4], *labelcomp[4];

//securité 
	GtkWidget *imagesecurite , *imagebsecurite[2], *labelsecurite , *buttonsecurite[3] ;
	GtkWidget * attention; 
// Fonctions 
	/* Affiche le menu des paramètres  */
	void page_parametre();

	/* Permet la gestion des intéractions avec les boutons de navigations du menu paramètre
	*
	* @param 	sender	widget émetteur
	* @param 	data 	donnée transmise par le widget emetteur
	*/
	void Slots_parametre(GtkWidget * sender , gpointer * data);

	/* Affiche la page "compte" des paramètres */
	void parametre_compte();
	/* Permet la modification des données de l'utilisateur  
	*
	* @param 	sender	widget émetteur
	* @param 	data 	donnée transmise par le widget emetteur
	*/
	void modificattion_donnes_compte(GtkWidget * sender , gpointer data);
	/* Affiche la page "sécurité" des paramètres */
	void parametre_securite();
	/* Affiche la page "A propos" des paramètres */
	void parametre_Apropos();


#endif
