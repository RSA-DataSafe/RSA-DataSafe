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

//EM = ENVOYEEMESSAGE
//Messageenvoyee
	GtkWidget   *imageEM , *imageBEM[2] ,*buttonEM[4] , *labelEM[5] , *text_viewEM;
	GtkWidget *Framemessageenvoyee ,*scrolled_windowmessageenvoye; 
	GtkTextBuffer *bufferEM;
	GtkWidget *boxEM,*BEM[30], *windowEM ,  *spinnerEM, *vboxEM , *labelcharenvoie; 
//Messageinde
	GtkWidget     *imageMI , *imageBMI[2] ,*buttonMI[4] , *labelMI[5] , *text_viewMI;
	GtkTextBuffer *bufferMI;
	GtkWidget     *boxMI,*BMI[30], *windowMI , *vboxMI , *labelsuppinde , *btn_afficher_supp[2]; 
	GtkWidget *Frameindesirables , *scrolled_windowmessageinde ;

	GtkWidget * w;
   
  
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


 

    //page global messagerie
	void messagerie_principale();
	void Slots_Messagerie(GtkWidget * sender , gpointer * data);
	
	void messagerie_recu();
	//ecrire un smg
	void page_envoyer_unmsg();
	//tous les msg quon a envoye
	void messagerie_envoye(); 
    //page pour les messages indesirables 
    void messagerie_indesirable();
    
    //appel un code enfonction de la reponse de lutilisateur oui non ou x
	void on_response(GtkDialog *dialog, gint       response_id, gpointer   user_data);

	//afficher une demande de signature sous forme de pop up 
	void show_dialog (GtkButton *button, gpointer   user_data);
	//afficher le contenu du message sur la droite uen fois quon a cliqué sur lun des messages (recu)
	void afficher_contenu_message(GtkWidget * sender , gpointer *data);
	//afficher le contenu du message sur la droite uen fois quon a cliqué sur lun des messages (envoyes)
	void afficher_contenu_message_envoyee(GtkWidget * sender , gpointer *data);
	
	//pop up message envoye
	void afficher_message_etat(GtkWidget * sender , gpointer *data);
	//une fois lutilisateur clique sur envoyer le spinner saffiche 
	void page_chargement_envoi_msg();
	//arrete le chargement et afficher le "message envoye"
	int page_resultat_chargement_envoie();
	//supprimer la mini fenetre pop up 
	void detuire_mini_f_resultat_envoie();

    //indesirables 
	//solot qui quitte si on lcique sur accueill ou deconect 
    //ou qui propo de supp ou dafficher si on clique sur lun des msg
   void afficher_proposition_supp_afficher(GtkWidget * sender , gpointer *data);
   void afficher_supprimer_msg(gpointer  * sender );
   void reponse_a_utilisateur_supp_affiche(GtkWidget * sender , gpointer * data);
    //utilisateur inexistant
   void  page_resultat_inexiste();
   // destruction de resultat inexistant
   void detuire_mini_f_resultat_inexiste();
   //verifie si l'utlisateur existe ou pas 
   int  check_user(char * name); 

#endif
