#include "inter_connexion.h"

void  page_connexion ()
{ // Gère la disposition des éléments pour l'affichage de la page de connexion
	imagec[0] = gtk_image_new_from_file("Icon/per.png"); 
	minilogo[0] = gtk_image_new_from_file("Icon/logo.png");

    button[0] = gtk_button_new_with_label ("Connexion");
	PEM = gtk_button_new_with_label ("Pas encore membre?");

	for (int i =0 ; i<3 ; i++) entree[i] = gtk_entry_new();

	label[0] = gtk_label_new ("E-mail");
	label[1] = gtk_label_new ("Mot de passe");
	

    
	 horiz1 =gtk_box_new (GTK_ORIENTATION_HORIZONTAL,100);
	 GtkWidget*vert =gtk_box_new (GTK_ORIENTATION_VERTICAL,50);
	 GtkWidget*vert1 =gtk_box_new (GTK_ORIENTATION_VERTICAL,70);
	 GtkWidget*vert2 =gtk_box_new (GTK_ORIENTATION_VERTICAL,70);

	 

	 gtk_box_pack_start (GTK_BOX(vert1),GTK_WIDGET(label[0]),TRUE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(vert1),GTK_WIDGET(label[1]),TRUE,TRUE,0);
	
	 gtk_box_pack_start (GTK_BOX(vert2),GTK_WIDGET(entree[0]),TRUE,TRUE,0);
	 gtk_box_pack_start (GTK_BOX(vert2),GTK_WIDGET(entree[1]),TRUE,TRUE,0);
     
     gtk_box_pack_start (GTK_BOX(horiz1),GTK_WIDGET(vert1),TRUE,TRUE,0);
     gtk_box_pack_start (GTK_BOX(horiz1),GTK_WIDGET(vert2),TRUE,TRUE,0);

	 GtkWidget *Vbtn =gtk_button_box_new (GTK_ORIENTATION_VERTICAL);
	 gtk_button_box_set_layout ( GTK_BUTTON_BOX(Vbtn), GTK_BUTTONBOX_SPREAD);
     
     gtk_box_pack_start (GTK_BOX(Vbtn),GTK_WIDGET (button[0]),TRUE,FALSE,20);
	 gtk_box_pack_start (GTK_BOX(Vbtn),GTK_WIDGET (PEM),TRUE,FALSE,20);

	MAIN =gtk_box_new (GTK_ORIENTATION_VERTICAL,0);

	 gtk_box_pack_start (GTK_BOX(vert),GTK_WIDGET (minilogo[0]),FALSE,FALSE,0);
     gtk_box_pack_start (GTK_BOX(vert),GTK_WIDGET (imagec[0]),FALSE,FALSE,0);
	 
	  gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET (vert),TRUE,FALSE,0);
	  gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET (horiz1),TRUE,FALSE,0);
	  gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET (Vbtn),TRUE,FALSE,0);

	  gtk_box_pack_start (GTK_BOX(Connexion),GTK_WIDGET (MAIN),TRUE,FALSE,0);
   
    gtk_entry_set_visibility(GTK_ENTRY(entree[1]), FALSE);

	gtk_widget_set_name (button[0],"btnc");
	gtk_widget_set_name (PEM,"PEM");
	gtk_entry_set_invisible_char (GTK_ENTRY(entree[1]),'*');
	gtk_widget_set_name (label[0],"Identifiant");
	gtk_widget_set_name (label[1],"Motsdepasse");
	gtk_widget_set_size_request(button[0], 100, 30);
	 
	
                     label[2] = gtk_label_new ("Veuillez remplir tous les champs  svp !");
                     label[3] = gtk_label_new ("Identifiant ou mot de passe incorrect !");
                     gtk_widget_set_name (label[2],"warning");
                     gtk_widget_set_name (label[3],"warning");
   
                     
	g_signal_connect(G_OBJECT(PEM),"clicked",G_CALLBACK(Verification_connexion),NULL);
	g_signal_connect(G_OBJECT(button[0]),"clicked",G_CALLBACK(Verification_connexion),NULL);
}
 
int  etat =0 ;
void Verification_connexion(GtkWidget * sender , gpointer * data)
{    // Fonction callback des boutons de la page de connexion 
// redirection vers la page d'inscription 
if ( PEM == sender && !data )
{
        gtk_widget_hide(label[2]);
        gtk_widget_hide(label[3]);
        gtk_entry_set_text(GTK_ENTRY(entree[0]),"");
        gtk_entry_set_text(GTK_ENTRY(entree[1]),"");
	    gtk_stack_set_visible_child (GTK_STACK (stack), GTK_WIDGET (Inscription));
	    etat=0 ; 
	}
	  char * email = (char *)gtk_entry_get_text (GTK_ENTRY(entree[0]));
	  char * mdp = (char *)gtk_entry_get_text (GTK_ENTRY(entree[1]));
	  utilisateur.email  =  malloc(sizeof(char)*strlen(email)); 
	  utilisateur.mdp = malloc(sizeof(char)*strlen(mdp)); 
	  strcpy(utilisateur.email,email);
	  strcpy(utilisateur.mdp,mdp);

	
	 //sinon  connexion de l'utilisateur
    if (button[0] ==sender && !data ){ 
	int trouver = 0 ;
        if(!gtk_entry_get_text_length(GTK_ENTRY(entree[0])) || !gtk_entry_get_text_length(GTK_ENTRY(entree[1])))
        {          
               if (!etat)
                { 
                   
                    GList *children = gtk_container_get_children(GTK_CONTAINER(MAIN));
                    while ((children = g_list_next(children)) != NULL)
                    {
                       	GtkWidget * w= children->data;
                        if (w ==label[2]){trouver =1 ;break; }
                    }
                   if (!trouver)
                   { 
                   	 gtk_box_pack_start(GTK_BOX(MAIN),GTK_WIDGET (label[2]),TRUE,FALSE,0);
                     gtk_box_reorder_child(GTK_BOX(MAIN),GTK_WIDGET (label[2]),2);
                    }
                        gtk_widget_show_all(GTK_WIDGET(MAIN));
                        gtk_widget_hide(GTK_WIDGET(label[3]));
                      etat= 1; 
                  
                }
                else{
                	  gtk_widget_show_all(GTK_WIDGET(MAIN));
                	  gtk_widget_hide(GTK_WIDGET(label[3]));
                	  etat =1;
                	}
                    
                  }
else{	         
                  
               			// On vérifie si l'utilisateur existe et on le connecte si oui sinon on affiche un message d'erreur
                      if (!chercher_utilisateur( utilisateur.email, utilisateur.mdp))
                      {	
	 	           	    gtk_widget_hide(GTK_WIDGET(label[2]));
	 	           	    gtk_widget_hide(GTK_WIDGET(label[3]));
	 	           	    gchar * nom= g_strdup_printf("%s  %s", "Bienvenue", utilisateur.email);
                        gtk_label_set_text(GTK_LABEL(lbmenu),nom);
                        free(nom);
                        mpz_inits(utilisateur.prive.n , utilisateur.prive.d,NULL);
  						mpz_inits(utilisateur.publique.e , utilisateur.publique.n,NULL);
                         
 
  							
  							// récupération des clés de l'utilisateur
                        if (!recupere_cle_privee(utilisateur.email,utilisateur.mdp,&utilisateur.prive))
                        {
                        	gmp_printf ("cle  d recup :%Zd\n" , utilisateur.prive.d);
                        	gmp_printf ("cle  n recup :%Zd\n" , utilisateur.prive.n);
                        }
                 		 
                          utilisateur.email = remove_n(utilisateur.email);
                 	   if (!recupere_cle_publique(utilisateur.email,utilisateur.mdp,&utilisateur.publique))
                 	    {
                 	        gmp_printf ("cle  e recup :%Zd\n" , utilisateur.publique.e);
                        	gmp_printf ("cle  n recup :%Zd\n" , utilisateur.publique.n);
                        }
	 	           	  	
	 	           	  	gtk_stack_set_visible_child (GTK_STACK (stack), GTK_WIDGET (Menu));
	 	           	  	gtk_entry_set_text(GTK_ENTRY(entree[0]),"");
        				gtk_entry_set_text(GTK_ENTRY(entree[1]),"");
	 	           	  
	 	           	
	 	           	  	etat=0 ;
	 	           	  }
	 	           	  else
	 	           	  { 
				                    GList *children = gtk_container_get_children(GTK_CONTAINER(MAIN));
				                    while ((children = g_list_next(children)) != NULL)
				                    {
				                       	GtkWidget * w= children->data;
				                        if (w ==label[3]){trouver =1 ;break; }
				                    }
                   					if (!trouver)
                   					{ 
				                   	 gtk_box_pack_start(GTK_BOX(MAIN),GTK_WIDGET (label[3]),TRUE,FALSE,0);
				                     gtk_box_reorder_child(GTK_BOX(MAIN),GTK_WIDGET (label[3]),2);
                     				}
                      gtk_widget_show_all(GTK_WIDGET(MAIN));
                      gtk_widget_hide(GTK_WIDGET(label[2]));
                      etat= 1; 
	 	              } 	 	      
	 	        	  
    }

 }
  	
}