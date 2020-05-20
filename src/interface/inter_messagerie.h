#ifndef H_MESSAGERIE_H
#define H_MESSAGERIE_H
#include <gtk/gtk.h>
#include <glib-object.h>
#include <gobject/gvaluecollector.h>
#include <string.h>
#include <glib/gi18n.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <glib.h>
#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../structure/structure.h"
#include "inter_initialisation.h"

// Variables environnements
//Messagerie
	GtkWidget   *imageMessagerie , *imageBMessagerie[6] ,*buttonMessagerie[6] , *labelMessagerie ;

//MessagesRecu
	GtkWidget   *imageMR , *imageBMR[2] ,*buttonMR[4] , *entreeMR[2] , *labelMR[5] , *text_viewMR;
	GtkTextBuffer *bufferMR;
	GtkWidget *event_box,*B[30];
	GtkWidget *Framemessagerecu , *scrolled_windowmessagerecu;
//Page envoyer un msg 
	GtkWidget   *imageE , *imageBE[2] ,*buttonE[4] , *entreeE[2] , *labelE[4] , *text_viewE;
	GtkTextBuffer *bufferE;


//Messageenvoyee
	GtkWidget   *imageEM , *imageBEM[2] ,*buttonEM[4] , *labelEM[5] , *text_viewEM;
	GtkWidget *Framemessageenvoyee ,*scrolled_windowmessageenvoye; 
	GtkTextBuffer *bufferEM;
	GtkWidget *boxEM,*BEM[30], *windowEM ,  *spinnerEM, *vboxEM , *labelcharenvoie; 
//Messageindesirable
	GtkWidget     *imageMI , *imageBMI[2] ,*buttonMI[4] , *labelMI[5] , *text_viewMI;
	GtkTextBuffer *bufferMI;
	GtkWidget     *boxMI,*BMI[30], *windowMI , *vboxMI , *labelsuppinde , *btn_afficher_supp[2]; 
	GtkWidget *Frameindesirables , *scrolled_windowmessageinde ;
   
  
     mail m ;
     //recu  
     boite b ;
     //envoye 
     boite boiteE;
     //indesirable
     boite BoiteInde ;

     mpz_t sig; 
     message * ret ;
     message * ch ;


 

	/* Affiche la page principale de la messagerie */
	void messagerie_principale();
	/* Permet la gestion des intéractions avec les boutons de navigations du menu messagerie
	*
	* @param 	sender	widget émetteur
	* @param 	data 	donnée transmise par le widget emetteur
	*/
	void Slots_Messagerie(GtkWidget * sender , gpointer * data);
	/* Affiche la page de messagerie "message reçu" */
	void messagerie_recu();
	/* Affiche la page de messagerie pour l'envoi de message */	
	void page_envoyer_unmsg();
	/* Affiche la page de messagerie "message envoyés" */
	void messagerie_envoye(); 
   	/* Affiche la page de messagerie "message indésirable" (les messages non-signés)*/
    void messagerie_indesirable();
    
    /* appel un code enfonction de la reponse de lutilisateur oui non ou x
	*
	* @param 	dialog			Widget permettant l'intéraction avec une boîte de dialogue
	* @param 	response_id 	réponse sous forme de gint correspondant
	* @param 	user_data 		donnée transmise par le widget 
	*/
	void on_response(GtkDialog *dialog, gint response_id, gpointer   user_data);
	
	/* Afficher une demande de signature sous forme de pop up
	*
	* @param 	button	bouton émetteur
	* @param 	user_data 	donnée transmise par le bouton emetteur
	*/
	void show_dialog (GtkButton *button, gpointer   user_data);
	
	/* Afficher le contenu du message sur la droite uen fois quon a cliqué sur lun des messages (recu)
	*
	* @param 	sender	widget émetteur
	* @param 	data 	donnée transmise par le widget emetteur
	*/
	void afficher_contenu_message(GtkWidget * sender , gpointer *data);
	
	/* 	afficher le contenu du message sur la droite une fois qu'on a cliqué sur l'un des message (envoyés)
	*
	* @param 	sender	widget émetteur
	* @param 	data 	donnée transmise par le widget emetteur
	*/
	void afficher_contenu_message_envoyee(GtkWidget * sender , gpointer *data);
	
	/* Gère l'affichage de la pop-up 
	*
	* @param 	sender	widget émetteur
	* @param 	data 	donnée transmise par le widget emetteur
	*/
	void afficher_message_etat(GtkWidget * sender , gpointer *data);

	//une fois lutilisateur clique sur envoyer le spinner saffiche 
	void page_chargement_envoi_msg();
	//arrete le chargement et afficher le "message envoye"
	int page_resultat_chargement_envoie();
	//supprimer la mini fenetre pop up 
	void detuire_mini_f_resultat_envoie();


    /* Permet la gestion des intéractions avec les boutons de navigations du menu messagerie
	*
	* @param 	sender	widget émetteur
	* @param 	data 	donnée transmise par le widget emetteur
	*/
   void afficher_proposition_supp_afficher(GtkWidget * sender , gpointer *data);
   /* idem */
   void afficher_supprimer_msg(gpointer  * sender );
   /* idem */
   void reponse_a_utilisateur_supp_affiche(GtkWidget * sender , gpointer * data);
  //utilisateur inexistant
   void  page_resultat_inexiste();
   // destruction de resultat inexistant
   void detuire_mini_f_resultat_inexiste();
   /* Vérifie si l'utilisateur existe ou non
	*
	* @param 	name identifiant de l'utilisateur
	* @return	1 si l'utilisateur existe 0 sinon 
	*/
   int check_user(char * name);
#endif
