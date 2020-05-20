#include "inter_parametre.h"

void page_parametre()
{
	imageP =gtk_image_new_from_file("Icon/logo.png"); 
	labelP= gtk_label_new ("Paramètres");
	lbparametre= gtk_label_new ("");
	gtk_widget_set_name (lbparametre,"bv");
	gtk_widget_set_name (labelP,"Titre");

	imageBP[0] = gtk_image_new_from_file("Icon/accjaune.png");
	imageBP[1] = gtk_image_new_from_file("Icon/compte1.png");
	imageBP[2] = gtk_image_new_from_file("Icon/S.png");
	imageBP[3] = gtk_image_new_from_file("Icon/Dec3.png");
	for (int i = 0  ;i < 4 ; ++i )
	{
		buttonP[i] = gtk_toggle_button_new(); 
		gtk_container_add(GTK_CONTAINER(buttonP[i]),imageBP[i]);
		gtk_widget_set_name (buttonP[i],"ButtonP");
	}

	 GtkWidget *horiz1 =gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
	 GtkWidget *h =gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
	 GtkWidget*horiz =gtk_box_new (GTK_ORIENTATION_HORIZONTAL,100);
	 GtkWidget *horiz0 =gtk_box_new (GTK_ORIENTATION_HORIZONTAL,100);

     GtkWidget *Vbtn =gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
	 gtk_button_box_set_layout ( GTK_BUTTON_BOX(Vbtn), GTK_BUTTONBOX_START);
     gtk_box_pack_start (GTK_BOX(Vbtn),GTK_WIDGET (buttonP[0]),FALSE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(Vbtn),GTK_WIDGET (buttonP[3]),FALSE,FALSE,0);
	   
     
     gtk_box_pack_start (GTK_BOX(horiz),GTK_WIDGET(imageP),TRUE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(horiz0),GTK_WIDGET(labelP),TRUE,FALSE,0);


	  gtk_box_pack_start (GTK_BOX(horiz1),GTK_WIDGET(buttonP[1]),TRUE,FALSE,0);
	  gtk_box_pack_start (GTK_BOX(horiz1),GTK_WIDGET(buttonP[2]),TRUE,FALSE,0);


	  gtk_box_pack_start (GTK_BOX(h),GTK_WIDGET(lbparametre),TRUE,FALSE,0);

	 GtkWidget *MAIN =gtk_box_new (GTK_ORIENTATION_VERTICAL,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(Vbtn),FALSE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(h),FALSE,FALSE,0);
	  gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(horiz),FALSE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET (horiz0),FALSE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET (horiz1),TRUE,FALSE,0);
	// gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(buttonP[1]),FALSE,TRUE,0);
    
	 for (int i=0 ; i< 4 ;++i)
	 	g_signal_connect(G_OBJECT(buttonP[i]),"clicked",G_CALLBACK(Slots_parametre),NULL);

	 gtk_box_pack_start (GTK_BOX(Parametre),GTK_WIDGET (MAIN),TRUE,TRUE,0);
}


void Slots_parametre(GtkWidget * sender , gpointer * data)
{
   
   if (GTK_WIDGET(buttonP[0]) == sender && !data )
   {                             gchar * nom= g_strdup_printf("%s  %s", "Bienvenue", utilisateur.email);
   								 gtk_label_set_text(GTK_LABEL(lbmenu),nom);
   	                             gtk_stack_set_visible_child (GTK_STACK (stack), GTK_WIDGET (Menu));
   	                             free(nom);
   	}
   
   
   if (GTK_WIDGET(buttonP[3]) == sender && !data ) 
   	                             gtk_stack_set_visible_child (GTK_STACK (stack), GTK_WIDGET (Connexion));
   
   if (GTK_WIDGET(buttonP[1]) == sender && !data )
   {					char * nom= g_strdup_printf("%s  %s", "Bienvenue", utilisateur.email);
                        gtk_label_set_text(GTK_LABEL(lbcompte),nom);
                        free(nom); 
                        utilisateur.email = remove_n(utilisateur.email);
                        utilisateur.mdp = remove_n(utilisateur.mdp);
                        gtk_entry_set_placeholder_text (GTK_ENTRY(entreecomp[0]),utilisateur.email);
	                    gtk_entry_set_placeholder_text (GTK_ENTRY(entreecomp[1]),utilisateur.mdp);
   	                    gtk_stack_set_visible_child (GTK_STACK (stack), GTK_WIDGET (Compte));
   	}
   
   if (GTK_WIDGET(buttonP[2]) == sender && !data )
   {
								 char * nom= g_strdup_printf("%s  %s", "Bienvenue", utilisateur.email);
								 gtk_label_set_text(GTK_LABEL(lbsecurite),nom);
								 free(nom);  
   	                             gtk_stack_set_visible_child (GTK_STACK (stack), GTK_WIDGET (Securite));
  	}

   if (GTK_WIDGET(buttonsecurite[0]) == sender && !data )  
   {
   	                             gtk_label_set_text(GTK_LABEL(attention) , ""); 
   	                             gtk_stack_set_visible_child (GTK_STACK (stack), GTK_WIDGET (Menu));
   	}
   
   if (GTK_WIDGET(buttonsecurite[1]) == sender && !data )
   {
   	  							 gtk_label_set_text(GTK_LABEL(attention) , "");
   	                             gtk_stack_set_visible_child (GTK_STACK (stack), GTK_WIDGET (Connexion));
   }
   
   if (GTK_WIDGET(buttonsecurite[2]) == sender && !data )
   {      
         
          
       mpz_inits(utilisateur.prive.n , utilisateur.prive.d,NULL);
  	   mpz_inits(utilisateur.publique.e , utilisateur.publique.n,NULL);
       utilisateur.email = remove_n(utilisateur.email);
       genere_cle(&utilisateur.publique, &utilisateur.prive, 1024);
   	      

   	     if (!change_cle(&utilisateur,&utilisateur.publique,&utilisateur.prive))
   	     {
                printf("CHANGEMENT EFFECTUÉ \n");
                gtk_label_set_text(GTK_LABEL(attention) , "vos clés ont été renouvelé avec succès"); 
   	            gtk_widget_set_name(attention ,"vert");
   	     }
   	     else
   	     {
	   	     	 printf("CHANGEMENT NON EFFECTUÉ \n");
	   	     	 gtk_label_set_text(GTK_LABEL(attention) , "veuillez réessayer svp!"); 
	   	         gtk_widget_set_name(attention ,"vert");
   	     }
   	     
   	     gtk_widget_show(attention); 

   }

}

void parametre_compte()
{

    imagecompte =gtk_image_new_from_file("Icon/logo.png"); 
	labelcompte= gtk_label_new ("Compte");
	lbcompte= gtk_label_new ("");
	gtk_widget_set_name (lbcompte,"bv");
	gtk_widget_set_name (labelcompte,"Titre");


	imagebtcomp[0] = gtk_image_new_from_file("Icon/accjaune.png");
	imagebtcomp[1] = gtk_image_new_from_file("Icon/Dec3.png");
	for (int i = 0  ;i < 2 ; ++i )
	{
		buttoncomp[i] = gtk_toggle_button_new(); 
		gtk_container_add(GTK_CONTAINER(buttoncomp[i]),imagebtcomp[i]);
		gtk_widget_set_name (buttoncomp[i],"ButtonC");
	}

	
  	buttoncomp[2] = gtk_button_new_with_label ("Modifier");
	buttoncomp[3] = gtk_button_new_with_label ("Sauvegarder");
	
	for (int i =0 ; i<4 ; i++)
	{ 
		 		entreecomp[i] = gtk_entry_new();
		 		gtk_editable_set_editable(GTK_EDITABLE(entreecomp[i]), FALSE);
    }
	labelcomp[0] = gtk_label_new ("E-mail");
	labelcomp[1] = gtk_label_new ("Mot de passe");
	
	
	


	 GtkWidget *horiz1 =gtk_box_new (GTK_ORIENTATION_HORIZONTAL,50);
	  GtkWidget*h =gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
	 GtkWidget*horiz =gtk_box_new (GTK_ORIENTATION_HORIZONTAL,300);
	 GtkWidget *horiz0 =gtk_box_new (GTK_ORIENTATION_HORIZONTAL,300);

     GtkWidget *Vbtn =gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
	 gtk_button_box_set_layout ( GTK_BUTTON_BOX(Vbtn), GTK_BUTTONBOX_START);
     gtk_box_pack_start (GTK_BOX(Vbtn),GTK_WIDGET (buttoncomp[0]),TRUE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(Vbtn),GTK_WIDGET (buttoncomp[1]),TRUE,FALSE,0);
	   
    
     gtk_box_pack_start (GTK_BOX(horiz),GTK_WIDGET(imagecompte),TRUE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(horiz0),GTK_WIDGET(labelcompte),TRUE,FALSE,0);

	 gtk_box_pack_start (GTK_BOX(h),GTK_WIDGET(lbcompte),TRUE,TRUE,0);


	 GtkWidget *vert1 =gtk_box_new (GTK_ORIENTATION_VERTICAL,30);
	 GtkWidget *vert2 =gtk_box_new (GTK_ORIENTATION_VERTICAL,30);
    
     for (int i = 0 ; i< 2; ++ i)
     {
	    gtk_box_pack_start (GTK_BOX(vert1),GTK_WIDGET(labelcomp[i]),TRUE,TRUE,0);
	    gtk_box_pack_start (GTK_BOX(vert2),GTK_WIDGET(entreecomp[i]),TRUE,TRUE,0);
	 }
	 
	  
     gtk_box_pack_start (GTK_BOX(horiz1),GTK_WIDGET(vert1),TRUE,TRUE,100);
     gtk_box_pack_start (GTK_BOX(horiz1),GTK_WIDGET(vert2),TRUE,TRUE,100);
     

    GtkWidget * Vbtn1 =gtk_button_box_new (GTK_ORIENTATION_VERTICAL);
	 gtk_button_box_set_layout ( GTK_BUTTON_BOX(Vbtn1), GTK_BUTTONBOX_SPREAD);
     gtk_box_pack_start (GTK_BOX(Vbtn1),GTK_WIDGET (buttoncomp[2]),TRUE,TRUE,0);
	 
	
	 GtkWidget *MAIN =gtk_box_new (GTK_ORIENTATION_VERTICAL,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(Vbtn),FALSE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(h),TRUE,TRUE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(horiz),FALSE,TRUE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(horiz0),FALSE,TRUE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(horiz1),TRUE,FALSE,0);
	  gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(Vbtn1),TRUE,TRUE,0);
	
	
    gtk_box_pack_start (GTK_BOX(Compte),GTK_WIDGET(MAIN),TRUE,TRUE,0);

	
	gtk_entry_set_icon_sensitive (GTK_ENTRY(entreecomp[1]),GTK_ENTRY_ICON_PRIMARY,FALSE);
	
	gtk_box_pack_start(GTK_BOX(Vbtn1),GTK_WIDGET (buttoncomp[3]),TRUE,TRUE,0);
	gtk_entry_set_visibility(GTK_ENTRY( entreecomp[1]), FALSE);
	gtk_entry_set_invisible_char (GTK_ENTRY( entreecomp[1]),'*');
    
  
	gtk_widget_set_name (buttoncomp[2],"bti1");
	gtk_widget_set_name (buttoncomp[3],"bti2");
	//pour le css 
	gtk_widget_set_name (labelcomp[0],"Donnes");
	gtk_widget_set_name (labelcomp[1],"Donnes");


    for (int i =0 ; i< 4 ; ++i)
	g_signal_connect(G_OBJECT(buttoncomp[i]),"clicked",G_CALLBACK(modificattion_donnes_compte),NULL);
	
	
}


void modificattion_donnes_compte(GtkWidget * sender , gpointer data)
{
	 
	if (GTK_WIDGET(buttoncomp[0]) == sender && !data ){
										char * nom= g_strdup_printf("%s  %s", "Bienvenue", utilisateur.email);
		                        		gtk_label_set_text(GTK_LABEL(lbmenu),nom);
		                        		free(nom); 
										gtk_stack_set_visible_child (GTK_STACK (stack), GTK_WIDGET (Menu));
								}
   
   else if (GTK_WIDGET(buttoncomp[1]) == sender && !data )
   	                             gtk_stack_set_visible_child (GTK_STACK (stack), GTK_WIDGET (Connexion));
   else if (GTK_WIDGET(buttoncomp[2]) == sender && !data )
   	 {
        
   	 	for (int i =0 ; i<2; i++)
	        { 
		 		gtk_editable_set_editable(GTK_EDITABLE(entreecomp[i]), TRUE);
             }
          
            gtk_widget_hide(buttoncomp[2]);
            gtk_widget_show(buttoncomp[3]);
            
   	 }

   	 else if (GTK_WIDGET(buttoncomp[3]) == sender && !data )
   	 {
       
       if (gtk_entry_get_text_length(GTK_ENTRY(entreecomp[0]))){
       				
       				if (!Change_Email(utilisateur.email , utilisateur.mdp, (char*)gtk_entry_get_text(GTK_ENTRY(entreecomp[0]))))
       				{
 					  utilisateur.email = remove_n((char*)gtk_entry_get_text(GTK_ENTRY(entreecomp[0])));	
 					 
 				 	  char * nom= g_strdup_printf("%s  %s", "Bienvenue", utilisateur.email);
                 	  gtk_label_set_text(GTK_LABEL(lbcompte),nom);
                 	  free(nom);
                    }
             }
  	    			if (gtk_entry_get_text_length(GTK_ENTRY(entreecomp[1])))
  	    			{
  	   					if ( !Change_MotDePasse (utilisateur.email , utilisateur.mdp , (char*)gtk_entry_get_text(GTK_ENTRY(entreecomp[1]))))
  	   					{
	  	   	        		utilisateur.mdp = remove_n((char*)gtk_entry_get_text(GTK_ENTRY(entreecomp[1])));
	  	   	         		
  	   	         	    }   
         }
           utilisateur.email = remove_n(utilisateur.email);
           utilisateur.mdp = remove_n(utilisateur.mdp);
           gtk_entry_set_placeholder_text (GTK_ENTRY(entreecomp[0]),utilisateur.email);
	       gtk_entry_set_placeholder_text (GTK_ENTRY(entreecomp[1]),utilisateur.mdp);

	       for (int i =0 ; i<2 ; i++)
		 		gtk_editable_set_editable(GTK_EDITABLE(entreecomp[i]), FALSE);
        
            gtk_widget_hide(buttoncomp[3]);
            gtk_widget_show(buttoncomp[2]);
   	 }

}


void parametre_securite()
{

	imagesecurite =gtk_image_new_from_file("Icon/logo.png"); 
	labelsecurite= gtk_label_new ("Sécurité");
	lbsecurite= gtk_label_new ("");
    gtk_widget_set_name (lbsecurite,"bv");
	gtk_widget_set_name (labelsecurite,"Titre");

	imagebsecurite[0] = gtk_image_new_from_file("Icon/accjaune.png");
	imagebsecurite[1] = gtk_image_new_from_file("Icon/Dec3.png");
	for (int i = 0  ;i < 2 ; ++i )
	{
		buttonsecurite[i] = gtk_toggle_button_new(); 
		gtk_container_add(GTK_CONTAINER(buttonsecurite[i]),imagebsecurite[i]);
		gtk_widget_set_name (buttonsecurite[i],"ButtonC");
	}
	
  	buttonsecurite[2] = gtk_button_new_with_label ("Renouveler Clées");
  	gtk_widget_set_name (buttonsecurite[2],"btnCLE");



	 GtkWidget*horiz =gtk_box_new (GTK_ORIENTATION_HORIZONTAL,300);
	 GtkWidget*h =gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
	 GtkWidget *horiz0 =gtk_box_new (GTK_ORIENTATION_HORIZONTAL,300);

     GtkWidget *Vbtn =gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
	 gtk_button_box_set_layout ( GTK_BUTTON_BOX(Vbtn), GTK_BUTTONBOX_START);
     gtk_box_pack_start (GTK_BOX(Vbtn),GTK_WIDGET (buttonsecurite[0]),TRUE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(Vbtn),GTK_WIDGET (buttonsecurite[1]),TRUE,FALSE,0);
	   
     gtk_box_pack_start (GTK_BOX(horiz),GTK_WIDGET(imagesecurite),TRUE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(horiz0),GTK_WIDGET(labelsecurite),TRUE,FALSE,0);

    
     gtk_box_pack_start (GTK_BOX(h),GTK_WIDGET(lbsecurite),TRUE,TRUE,0);

     GtkWidget *Vbtn1 =gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
	 gtk_button_box_set_layout ( GTK_BUTTON_BOX(Vbtn1), GTK_BUTTONBOX_SPREAD);
     gtk_box_pack_start (GTK_BOX(Vbtn1),GTK_WIDGET (buttonsecurite[2]),TRUE,FALSE,0);
    
 
	 attention = gtk_label_new ("");
	 gtk_widget_set_name (attention,"warning");
	 GtkWidget *MAIN =gtk_box_new (GTK_ORIENTATION_VERTICAL,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(Vbtn),FALSE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(h),FALSE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(horiz),FALSE,TRUE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(horiz0),FALSE,TRUE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(attention),TRUE,TRUE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(Vbtn1),TRUE,FALSE,0);

	  gtk_box_pack_start (GTK_BOX(Securite),GTK_WIDGET(MAIN),TRUE,TRUE,0);

	  for (int i = 0 ; i < 3 ; ++i) 
 	 	g_signal_connect(G_OBJECT(buttonsecurite[i]),"clicked",G_CALLBACK(Slots_parametre),NULL);


}
