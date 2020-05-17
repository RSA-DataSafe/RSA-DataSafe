#include "inter_inscription.h"

void  Page_d_inscription ()
{
	imagec[1] = gtk_image_new_from_file("Icon/per.png"); 
	minilogo[1] = gtk_image_new_from_file("Icon/logo.png"); 
  	buttoni[0] = gtk_button_new_with_label ("Inscription");
	buttoni[1] = gtk_button_new_with_label ("Connexion");
	for (int i =0 ; i<4 ; i++) entreei[i] = gtk_entry_new();
	labeli[0] = gtk_label_new ("Identifiant");
	labeli[1] = gtk_label_new ("Mot de passe");
	labeli[2] = gtk_label_new ("Email");
	labeli[3] = gtk_label_new ("Numéro de Téléphone");


	
	 GtkWidget *horiz1 =gtk_box_new (GTK_ORIENTATION_HORIZONTAL,100);
	 GtkWidget*vert =gtk_box_new (GTK_ORIENTATION_VERTICAL,50);
	 GtkWidget *vert1 =gtk_box_new (GTK_ORIENTATION_VERTICAL,30);
	 GtkWidget *vert2 =gtk_box_new (GTK_ORIENTATION_VERTICAL,30);
     
     for (int i = 0 ; i< 4; ++ i)
     {
	    gtk_box_pack_start (GTK_BOX(vert1),GTK_WIDGET(labeli[i]),TRUE,FALSE,0);
	    gtk_box_pack_start (GTK_BOX(vert2),GTK_WIDGET(entreei[i]),TRUE,FALSE,0);
	 }
	 
	  
     gtk_box_pack_start (GTK_BOX(horiz1),GTK_WIDGET(vert1),TRUE,TRUE,0);
     gtk_box_pack_start (GTK_BOX(horiz1),GTK_WIDGET(vert2),TRUE,TRUE,0);

	 GtkWidget *Vbtn =gtk_button_box_new (GTK_ORIENTATION_VERTICAL);
	 gtk_button_box_set_layout ( GTK_BUTTON_BOX(Vbtn), GTK_BUTTONBOX_SPREAD);
     gtk_box_pack_start (GTK_BOX(Vbtn),GTK_WIDGET (buttoni[0]),TRUE,TRUE,10);
	 gtk_box_pack_start (GTK_BOX(Vbtn),GTK_WIDGET (buttoni[1]),TRUE,TRUE,10);

	
	MAINi =gtk_box_new (GTK_ORIENTATION_VERTICAL,0);

	 gtk_box_pack_start (GTK_BOX(vert),GTK_WIDGET (minilogo[1]),TRUE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(vert),GTK_WIDGET (imagec[1]),TRUE,FALSE,0);
	 
	  gtk_box_pack_start (GTK_BOX(MAINi),GTK_WIDGET (vert),TRUE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(MAINi),GTK_WIDGET (horiz1),TRUE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(MAINi),GTK_WIDGET (Vbtn),TRUE,FALSE,0);

	 gtk_box_pack_start (GTK_BOX(Inscription),GTK_WIDGET (MAINi),TRUE,FALSE,0);
	gtk_entry_set_visibility(GTK_ENTRY(entreei[1]), FALSE);
	gtk_entry_set_invisible_char (GTK_ENTRY(entreei[1]),'*');
	gtk_widget_set_name (buttoni[0],"bti1");
	gtk_widget_set_name (buttoni[1],"bti2");
	//pour le css 
	for (int i = 0 ; i < 4 ; ++i)
	gtk_widget_set_name (labeli[i],"Donnes");

    for (int i = 0 ; i<2 ; ++i )
		 g_signal_connect(G_OBJECT(buttoni[i]),"clicked",G_CALLBACK(SLots_inscription),NULL);

		labeli[4] = gtk_label_new ("Veuillez remplir tous les champs svp !");
                     gtk_widget_set_name (labeli[4],"warning");
	
}


int etati = 0 ; 

void SLots_inscription(GtkWidget * sender , gpointer * data)
{
		  if (sender ==buttoni[1] && !data)  { gtk_widget_hide(GTK_WIDGET(labeli[4])); gtk_stack_set_visible_child (GTK_STACK (stack), GTK_WIDGET (Connexion)); etati =0 ; }
          else
          {
          	
                     utilisateur.email = (char *)gtk_entry_get_text(GTK_ENTRY(entreei[2]));
                     utilisateur.mdp= (char *)gtk_entry_get_text(GTK_ENTRY(entreei[1]));
				     int trouver = 0 ;
				        if(!gtk_entry_get_text_length(GTK_ENTRY(entreei[0])) || !gtk_entry_get_text_length(GTK_ENTRY(entreei[1]))||
				           !gtk_entry_get_text_length(GTK_ENTRY(entreei[2])) || !gtk_entry_get_text_length(GTK_ENTRY(entreei[3]))) 
				        {          
				               if (!etati)
				                { 
				                   
				                    GList *children = gtk_container_get_children(GTK_CONTAINER(MAINi));
				                    while ((children = g_list_next(children)) != NULL)
				                    {
				                       	GtkWidget * w= children->data;
				                        if (w ==labeli[4]){trouver =1 ;break; }
				                    }
				                  if (!trouver)
				                    { 
				                   	 gtk_box_pack_start(GTK_BOX(MAINi),GTK_WIDGET (labeli[4]),TRUE,TRUE,0);
				                     gtk_box_reorder_child(GTK_BOX(MAINi),GTK_WIDGET(labeli[4]),2);
				                    }
				                     
				                     gtk_widget_show_all(GTK_WIDGET(MAINi));  
				                     etati= 1; 
				                  
				                }
				               
				        }
				        else
				        	{

				        		gtk_widget_hide(GTK_WIDGET(labeli[4])); etati = 0 ;

                      
				        		if ( !nouvel_utilisateur(utilisateur.email , utilisateur.mdp))
				        		{
				        			
				        			mpz_inits(utilisateur.prive.n , utilisateur.prive.d,NULL);
  									mpz_inits(utilisateur.publique.e , utilisateur.publique.n,NULL);
				  
				        			genere_cle(&utilisateur.publique, &utilisateur.prive, 1024);
				        			
				        		
				        		    char* chemin = malloc (sizeof (char)*200);
				        			strcpy(chemin,"rsa/");
				        			strcat(chemin,utilisateur.email);
				        			strcat(chemin,"/Cles.txt");
				        			
				        			char * clees= malloc (sizeof(char)*2048*4);
				        			strcpy(clees,mpz_get_str(NULL,10,utilisateur.prive.d));
				        			strcat(clees,"\n");
				        			strcat(clees,mpz_get_str(NULL,10,utilisateur.publique.e));
				        			strcat(clees,"\n");
				        			strcat(clees,mpz_get_str(NULL,10,utilisateur.publique.n));
				        			
				        			if (!ecrire_fichier(chemin,clees))	 printf("stockage de la clé\n");
				        			else  printf("erreur decriture\n");
				        			free(chemin);
				        			free(clees);
				        			gtk_stack_set_visible_child (GTK_STACK (stack), GTK_WIDGET (Connexion));
				        	      }
				        			
				        			
				        		}
				        		    
				        	
				        
           }
}
