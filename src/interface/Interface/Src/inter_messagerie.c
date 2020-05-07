#include "../Header/inter_messagerie.h"
void page_messagerie()
  {

  	imageMessagerie =gtk_image_new_from_file("Icon/logo.png"); 
	labelMessagerie= gtk_label_new ("Messagerie");
	lbmessagerie= gtk_label_new ("");
	gtk_widget_set_name (lbmessagerie,"bv");
	gtk_widget_set_name (labelMessagerie,"Titre");

	imageBMessagerie[0] = gtk_image_new_from_file("Icon/accjaune.png");
	imageBMessagerie[1] = gtk_image_new_from_file("Icon/Dec3.png");
	//message recu 
	imageBMessagerie[2] = gtk_image_new_from_file("Icon/MsgRecu.png");
	//message envoyée
	imageBMessagerie[3] = gtk_image_new_from_file("Icon/MSGENVOYER.png");
	//ecrire message
	imageBMessagerie[4] = gtk_image_new_from_file("Icon/EnvoeMsg.png");
	//messages indesirables
	imageBMessagerie[5] = gtk_image_new_from_file("Icon/MsgIndesirables.png");
	for (int i = 0  ;i < 6; ++i )
	{
		buttonMessagerie[i] = gtk_toggle_button_new(); 
		gtk_container_add(GTK_CONTAINER(buttonMessagerie[i]),imageBMessagerie[i]);
		gtk_widget_set_name (buttonMessagerie[i],"buttonMessagerie");
	}



	 GtkWidget *horiz1 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL,300);
	 GtkWidget *horiz  = gtk_box_new (GTK_ORIENTATION_HORIZONTAL,100);
	 GtkWidget *horiz0 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL,100);
	 GtkWidget *h      = gtk_box_new (GTK_ORIENTATION_HORIZONTAL,100);
	 
	 GtkWidget *vert   =  gtk_box_new (GTK_ORIENTATION_VERTICAL,100);
	 GtkWidget *vert2  =  gtk_box_new (GTK_ORIENTATION_VERTICAL,100);
 

     GtkWidget *Vbtn   = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
	 
	 gtk_button_box_set_layout ( GTK_BUTTON_BOX(Vbtn), GTK_BUTTONBOX_START);
     gtk_box_pack_start (GTK_BOX(Vbtn),GTK_WIDGET (buttonMessagerie[0]),FALSE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(Vbtn),GTK_WIDGET (buttonMessagerie[1]),FALSE,FALSE,0);
	    
	 gtk_box_pack_start (GTK_BOX(vert),GTK_WIDGET(buttonMessagerie[4]),FALSE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(vert),GTK_WIDGET(buttonMessagerie[3]),FALSE,FALSE,0);
     
     gtk_box_pack_start (GTK_BOX(horiz),GTK_WIDGET(imageMessagerie),TRUE,TRUE,0);
	 gtk_box_pack_start (GTK_BOX(horiz0),GTK_WIDGET(labelMessagerie),TRUE,TRUE,0);
	     
	 gtk_box_pack_start (GTK_BOX(vert2),GTK_WIDGET(buttonMessagerie[2]),FALSE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(vert2),GTK_WIDGET(buttonMessagerie[5]),FALSE,FALSE,0);
	  
     gtk_box_pack_start (GTK_BOX(horiz1),GTK_WIDGET(vert),TRUE,FALSE,0);
     gtk_box_pack_start (GTK_BOX(horiz1),GTK_WIDGET(vert2),TRUE,FALSE,0);

     gtk_box_pack_start (GTK_BOX(h),GTK_WIDGET(lbmessagerie),TRUE,FALSE,0);
  
	 GtkWidget *MAIN =gtk_box_new (GTK_ORIENTATION_VERTICAL,0);

	  gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(Vbtn),FALSE,FALSE,0);
	  gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(h),FALSE,FALSE,0);
	  gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(horiz),FALSE,FALSE,0);
	  gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET (horiz0),FALSE,FALSE,0);
   	  gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET (horiz1),TRUE,TRUE,0);
	  gtk_box_pack_start (GTK_BOX(Messagerie),GTK_WIDGET (MAIN),TRUE,TRUE,0);
	  for (int i = 0 ; i < 6 ; ++i)
	  g_signal_connect(G_OBJECT(buttonMessagerie[i]),"clicked",G_CALLBACK(Slots_Messagerie),NULL);
  }


 void Slots_Messagerie(GtkWidget * sender , gpointer * data)
 {

 if (GTK_WIDGET(buttonMessagerie[0]) == sender && !data )  
   	                             gtk_stack_set_visible_child (GTK_STACK (stack), GTK_WIDGET (Menu));
 if (GTK_WIDGET(buttonMessagerie[1]) == sender && !data )  
   	                             gtk_stack_set_visible_child (GTK_STACK (stack), GTK_WIDGET (Connexion));

 if (GTK_WIDGET(buttonMessagerie[2]) == sender && !data )
      {  
   	                             gchar * nom= g_strdup_printf("%s  %s", "Bienvenue", utilisateur.email);
                                 gtk_label_set_text(GTK_LABEL(lbmessagerierecu),nom);
                                 free(nom);                           
   	                             gtk_stack_set_visible_child (GTK_STACK (stack), GTK_WIDGET (MessagerieRecu));
      }
 if (GTK_WIDGET(buttonMessagerie[4]) == sender && !data ) 
      { 
                                 gchar * nom= g_strdup_printf("%s  %s", "Bienvenue", utilisateur.email);
                                 gtk_label_set_text(GTK_LABEL(lbmessagerieecri),nom);
                                 free(nom); 
   	                             gtk_stack_set_visible_child (GTK_STACK (stack), GTK_WIDGET (MessagerieEcr));
   	  }
 if (GTK_WIDGET(buttonMessagerie[3]) == sender && !data )
 {
 								gchar * nom= g_strdup_printf("%s  %s", "Bienvenue", utilisateur.email);
                                 gtk_label_set_text(GTK_LABEL(lbenvoyeemessagerie),nom);
                                 free(nom);
   	                             gtk_stack_set_visible_child (GTK_STACK (stack), GTK_WIDGET (EnvoyeeMessagerie));
  }
 if (GTK_WIDGET(buttonMessagerie[5]) == sender && !data ) 
 {
 								 gchar * nom= g_strdup_printf("%s  %s", "Bienvenue", utilisateur.email);
                                 gtk_label_set_text(GTK_LABEL(lbmessagerieinde),nom);
                                 free(nom);
                                 gtk_stack_set_visible_child (GTK_STACK (stack), GTK_WIDGET (MessagerieInde));
 }
}


void page_MessageRecu()
{

	imageMR =gtk_image_new_from_file("Icon/logo.png"); 
	labelMR[0]= gtk_label_new ("Messages Reçu");
	lbmessagerierecu= gtk_label_new ("");
	gtk_widget_set_name (GTK_WIDGET(lbmessagerierecu),"bv");
	gtk_widget_set_name (GTK_WIDGET(labelMR[0]),"Titre");

	imageBMR[0] = gtk_image_new_from_file("Icon/accjaune.png");
	imageBMR[1] = gtk_image_new_from_file("Icon/Dec3.png");

	for (int i = 0  ;i < 2; ++i )
	{
		buttonMR[i] = gtk_toggle_button_new(); 
		gtk_container_add(GTK_CONTAINER(buttonMR[i]),imageBMR[i]);
		gtk_widget_set_name (buttonMR[i],"buttonMR");
	}

	labelMR[1] = gtk_label_new("Email ");
	labelMR[2] = gtk_label_new("Objet");
	labelMR[3] = gtk_label_new("");
	labelMR[4] = gtk_label_new("");
	gtk_widget_set_name (GTK_WIDGET(labelMR[1]),"miniT");
	gtk_widget_set_name (GTK_WIDGET(labelMR[2]),"miniT");

     GtkWidget *Frame[3]; 
       for (int i = 1 ; i< 3 ; ++i ) 
        { 		
        	     Frame [i] =gtk_frame_new ("");
               	 gtk_widget_set_name (GTK_WIDGET(Frame[i]),"miniT");
        }

       Frame [0] =gtk_frame_new ("Corps de l'email");
       gtk_widget_set_name (GTK_WIDGET(Frame[0]),"miniT");
	   GtkWidget *scrolled_window = gtk_scrolled_window_new (NULL , NULL);
	   bufferMR = gtk_text_buffer_new (NULL);
	   gtk_text_buffer_set_text (bufferMR, "", -1);
	   text_viewMR = gtk_text_view_new_with_buffer (bufferMR);  
	   gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 10);
	   gtk_container_add (GTK_CONTAINER (scrolled_window), text_viewMR);
	   gtk_container_add (GTK_CONTAINER (Frame[0]), GTK_WIDGET(scrolled_window));
	   gtk_widget_set_size_request(GTK_WIDGET(Frame[0]) , 500,300);
	   gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW(text_viewMR),FALSE);
	   gtk_text_view_set_editable (GTK_TEXT_VIEW(text_viewMR), FALSE);

    //contenu email 
	gtk_container_add (GTK_CONTAINER (Frame[1]), GTK_WIDGET(labelMR[3]));
	//gtk_fixed_put(GTK_FIXED(MessagerieRecu), GTK_WIDGET(Frame[1]) ,450, 290);
	gtk_widget_set_size_request(GTK_WIDGET(Frame[1]) , 450,30);
    //contenu objet 
    gtk_container_add (GTK_CONTAINER (Frame[2]), GTK_WIDGET(labelMR[4]));
 
    event_box = gtk_box_new (GTK_ORIENTATION_VERTICAL,0);
    
    //sa sert a rien pourl nstant mais bn 
    for (int i  = 0 ; i <10; ++i)
    {
    	
        gchar * nom1 ;
    	nom1= g_strdup_printf("%s%s", "Titre ", "");
    	B[i]=gtk_button_new_with_label(nom1);
    	 gtk_widget_set_name (GTK_WIDGET(B[i]),"titremail");
    	  g_signal_connect(G_OBJECT(B[i]), "clicked",G_CALLBACK(afficher_contenu_message), NULL);
    	gtk_box_pack_start (GTK_BOX(event_box),GTK_WIDGET(B[i]),FALSE,FALSE,0);
    	free(nom1); 
    }
    

         GtkWidget *Framenom; 		
         Framenom =gtk_frame_new ("Reçu");
         gtk_widget_set_name (GTK_WIDGET(Framenom),"miniT");
		 GtkWidget *scrolled_windowm = gtk_scrolled_window_new (NULL , NULL);
	     gtk_container_set_border_width (GTK_CONTAINER (scrolled_windowm), 10);
	     gtk_container_add (GTK_CONTAINER (scrolled_windowm),event_box);
	     gtk_container_add (GTK_CONTAINER (Framenom), GTK_WIDGET(scrolled_windowm));

   		GtkWidget *horiz =gtk_box_new (GTK_ORIENTATION_HORIZONTAL,100);
		GtkWidget *horiz0 =gtk_box_new (GTK_ORIENTATION_HORIZONTAL,100);
		GtkWidget *h =gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
		GtkWidget *vert =gtk_box_new (GTK_ORIENTATION_VERTICAL,20);
		GtkWidget *vert1 =gtk_box_new (GTK_ORIENTATION_VERTICAL,100);
		GtkWidget *horiz1=gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);

     //BUttons
     GtkWidget *Vbtn =gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
	 gtk_button_box_set_layout ( GTK_BUTTON_BOX(Vbtn), GTK_BUTTONBOX_START);
     gtk_box_pack_start (GTK_BOX(Vbtn),GTK_WIDGET (buttonMR[0]),FALSE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(Vbtn),GTK_WIDGET (buttonMR[1]),FALSE,FALSE,0);
	    
     
     gtk_box_pack_start (GTK_BOX(horiz),GTK_WIDGET(imageMR),TRUE,TRUE,0);
	 gtk_box_pack_start (GTK_BOX(horiz0),GTK_WIDGET(labelMR[0]),TRUE,TRUE,0);

	 gtk_box_pack_start (GTK_BOX(vert),GTK_WIDGET(Frame[1]),FALSE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(vert),GTK_WIDGET(Frame[2]),FALSE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(vert),GTK_WIDGET(Frame[0]),FALSE,FALSE,0);

	 gtk_box_pack_start (GTK_BOX(h),GTK_WIDGET(lbmessagerierecu),TRUE,TRUE,0);
	 
	 gtk_widget_set_size_request(GTK_WIDGET(Framenom),200,400);
	 gtk_box_pack_start (GTK_BOX(vert1),GTK_WIDGET(Framenom),FALSE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(horiz1),GTK_WIDGET(vert1),TRUE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(horiz1),GTK_WIDGET(vert),TRUE,FALSE,0);
	
	 GtkWidget *MAIN =gtk_box_new (GTK_ORIENTATION_VERTICAL,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(Vbtn),FALSE,FALSE,0);
	  gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(h),TRUE,TRUE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(horiz),FALSE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(horiz0),TRUE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(horiz1),TRUE,TRUE,0);

	 gtk_box_pack_start (GTK_BOX(MessagerieRecu),GTK_WIDGET(MAIN),TRUE,TRUE,0);


    g_signal_connect((G_OBJECT(buttonMR[0])),"clicked",G_CALLBACK(afficher_contenu_message),NULL);
    g_signal_connect((G_OBJECT(buttonMR[1])),"clicked",G_CALLBACK(afficher_contenu_message),NULL);

	
}
//POUR AFFICHER LE CONTENU DY MESSAGE GERE AUSSI LES SIGNAUX POUR QUITTER
void afficher_contenu_message(GtkWidget * sender , gpointer *data)
{

	 if (GTK_WIDGET(buttonMR[0]) == sender && !data )
	 {  
   	                             
   	                             gtk_label_set_label (GTK_LABEL(labelMR[3]),"");
								 gtk_label_set_label (GTK_LABEL(labelMR[4]),"");
								 gtk_text_buffer_set_text (bufferMR, "", -1);
								 gtk_stack_set_visible_child (GTK_STACK (stack), GTK_WIDGET (Menu));
   	  }
   
   else if (GTK_WIDGET(buttonMR[1]) == sender && !data ){ 
   								 gtk_label_set_label (GTK_LABEL(labelMR[3]),"");
								 gtk_label_set_label (GTK_LABEL(labelMR[4]),"");
								 gtk_text_buffer_set_text (bufferMR, "", -1);
   	                             gtk_stack_set_visible_child (GTK_STACK (stack), GTK_WIDGET (Connexion));}
   	 else {

	gtk_label_set_label (GTK_LABEL(labelMR[3]),"blalalalallalal");
	gtk_label_set_label (GTK_LABEL(labelMR[4]),"blalalal@hotmail.fr");
	gtk_text_buffer_set_text (bufferMR, "balalalallal\n blalalalal\n etc ...", -1);}
}



//page pour envoyer un message 
void page_envoyer_unmsg()
{
   imageE =gtk_image_new_from_file("Icon/logo.png"); 
   labelE[0]= gtk_label_new ("Envoyer un message");
   lbmessagerieecri = gtk_label_new ("");
   gtk_widget_set_name (GTK_WIDGET(lbmessagerieecri),"bv");
   gtk_widget_set_name (GTK_WIDGET(labelE[0]),"Titre");

   imageBE[0] = gtk_image_new_from_file("Icon/accjaune.png");
   imageBE[1] = gtk_image_new_from_file("Icon/Dec3.png");

	for (int i = 0  ;i < 2; ++i )
	{
		entreeE[i] = gtk_entry_new(); 
		buttonE[i] = gtk_toggle_button_new(); 
		gtk_container_add(GTK_CONTAINER(buttonE[i]),imageBE[i]);
		gtk_widget_set_name (buttonE[i],"buttonE");
	}



         GtkWidget *Frame =gtk_frame_new ("Corps de l'email");
           gtk_widget_set_name (GTK_WIDGET(Frame),"miniT");
		GtkWidget *scrolled_window = gtk_scrolled_window_new (NULL , NULL);
	 	bufferE = gtk_text_buffer_new (NULL);
		gtk_text_buffer_set_text (bufferE, "", -1);
		text_viewE = gtk_text_view_new_with_buffer (bufferE);
	   gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 10);
	   gtk_container_add (GTK_CONTAINER (scrolled_window), text_viewE);
    
	   gtk_container_add (GTK_CONTAINER (Frame), GTK_WIDGET(scrolled_window));
	   gtk_widget_set_size_request(GTK_WIDGET(Frame) , 600,300);



	    buttonE[3] = gtk_button_new_with_label("Envoyer"); 


    GtkWidget*horiz =gtk_box_new (GTK_ORIENTATION_HORIZONTAL,100);
    GtkWidget*h=gtk_box_new (GTK_ORIENTATION_HORIZONTAL,100);
	GtkWidget *horiz0 =gtk_box_new (GTK_ORIENTATION_HORIZONTAL,100);
	GtkWidget *vert =gtk_box_new (GTK_ORIENTATION_VERTICAL,20);
	GtkWidget *horiz1=gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
	GtkWidget *horiz2=gtk_box_new (GTK_ORIENTATION_HORIZONTAL,100);


     GtkWidget *Vbtn =gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
	 gtk_button_box_set_layout ( GTK_BUTTON_BOX(Vbtn), GTK_BUTTONBOX_START);
     gtk_box_pack_start (GTK_BOX(Vbtn),GTK_WIDGET (buttonE[0]),FALSE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(Vbtn),GTK_WIDGET (buttonE[1]),FALSE,FALSE,0);
	    
     
     gtk_box_pack_start (GTK_BOX(horiz),GTK_WIDGET(imageE),TRUE,TRUE,0);
	 gtk_box_pack_start (GTK_BOX(horiz0),GTK_WIDGET(labelE[0]),TRUE,TRUE,0);

	 gtk_box_pack_start (GTK_BOX(vert),GTK_WIDGET(entreeE[0]),TRUE,TRUE,0);
	 gtk_entry_set_placeholder_text (GTK_ENTRY(entreeE[0]),"E-mail");
	 gtk_box_pack_start (GTK_BOX(vert),GTK_WIDGET(entreeE[1]),TRUE,TRUE,0);
	 gtk_entry_set_placeholder_text (GTK_ENTRY(entreeE[1]),"Objet");
	
	 gtk_box_pack_start (GTK_BOX(horiz1),GTK_WIDGET(vert),TRUE,TRUE,200);
	 
	 gtk_box_pack_start (GTK_BOX(h),GTK_WIDGET(lbmessagerieecri),TRUE,TRUE,0);
	  
     gtk_box_pack_start (GTK_BOX(horiz2),GTK_WIDGET(Frame),TRUE,TRUE,200);
     GtkWidget *Vbtn1 =gtk_button_box_new (GTK_ORIENTATION_VERTICAL);
     gtk_button_box_set_layout ( GTK_BUTTON_BOX(Vbtn1), GTK_BUTTONBOX_CENTER);
     gtk_box_pack_start (GTK_BOX(Vbtn1),GTK_WIDGET (buttonE[3]),FALSE,FALSE,0);
	 
	 GtkWidget *MAIN =gtk_box_new (GTK_ORIENTATION_VERTICAL,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(Vbtn),FALSE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(h),TRUE ,TRUE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(horiz),FALSE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(horiz0),FALSE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(horiz1),TRUE,TRUE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(horiz2),TRUE,TRUE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(Vbtn1),TRUE,TRUE,0);


	 gtk_box_pack_start (GTK_BOX(MessagerieEcr),GTK_WIDGET (MAIN),TRUE,TRUE,0);
    	gtk_widget_set_name (buttonE[3],"btnV");

     g_signal_connect (GTK_BUTTON (buttonE[3]), "clicked", G_CALLBACK (show_dialog), GTK_WINDOW (MainWindow));
     g_signal_connect (GTK_BUTTON (buttonE[0]), "clicked", G_CALLBACK (afficher_message_etat),NULL);
     g_signal_connect (GTK_BUTTON (buttonE[1]), "clicked", G_CALLBACK (afficher_message_etat),NULL);
	 

}


//affiche a lutilisateur si le message est envoyee ou pas 
void afficher_message_etat(GtkWidget * sender , gpointer *data)
{
      
	 if (GTK_WIDGET(buttonE[0]) == sender && !data )
	 {  
   	                             
   	                             gtk_entry_set_text (GTK_ENTRY(entreeE[0]),"");
								 gtk_entry_set_text (GTK_ENTRY(entreeE[1]),"");
								 gtk_text_buffer_set_text (bufferE, "", -1);
								 gtk_stack_set_visible_child (GTK_STACK (stack), GTK_WIDGET (Menu));
   	  }
   
   else if (GTK_WIDGET(buttonE[1]) == sender && !data ){ 
   								 gtk_entry_set_text(GTK_ENTRY(entreeE[0]),"");
								 gtk_entry_set_text(GTK_ENTRY(entreeE[1]),"");
								 gtk_text_buffer_set_text (bufferE, "", -1);
   	                             gtk_stack_set_visible_child (GTK_STACK (stack), GTK_WIDGET (Connexion));}
   	 else
   	 {
         page_chargement_envoi_msg();
   	 }
}


void page_chargement_envoi_msg()
{
  windowEM = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_transient_for (GTK_WINDOW(windowEM),GTK_WINDOW(MainWindow));
  gtk_window_set_position (GTK_WINDOW(windowEM), GTK_WIN_POS_CENTER);
  gtk_window_set_title (GTK_WINDOW(windowEM),"          Data Safe");
  gtk_widget_set_size_request(GTK_WIDGET(windowEM) ,300,300);
  vboxEM = gtk_box_new (GTK_ORIENTATION_VERTICAL,50); 

  spinnerEM = gtk_spinner_new ();

   gtk_spinner_start (GTK_SPINNER(spinnerEM));
   labelcharenvoie = gtk_label_new("Envoie en cours..!\n");
   gtk_widget_set_name (GTK_WIDGET(labelcharenvoie),"miniT");
   gtk_window_set_deletable (GTK_WINDOW(windowEM),TRUE);
  //gtk_widget_set_size_request(GTK_WIDGET(window) ,400,200);
 
  gtk_container_add (GTK_CONTAINER (windowEM),GTK_WIDGET(vboxEM));

  gtk_box_pack_start( GTK_BOX(vboxEM),GTK_WIDGET(labelcharenvoie),TRUE,TRUE,0);
  gtk_box_pack_start( GTK_BOX(vboxEM),GTK_WIDGET(spinnerEM),TRUE,TRUE,0);
  gtk_widget_set_name (spinnerEM,"spin");
 
  g_timeout_add (2500,(GSourceFunc)page_resultat_chargement_envoie, spinnerEM);
  gtk_widget_show_all (GTK_WIDGET(windowEM));
 
}


// arrete le timer du spiner et affiche le bouton ok pour quitter
int page_resultat_chargement_envoie()
{
      
      gtk_spinner_stop (GTK_SPINNER(spinnerEM));
      gtk_container_remove (GTK_CONTAINER(vboxEM),GTK_WIDGET(spinnerEM));
      gtk_widget_hide(GTK_WIDGET(vboxEM)); 
      GtkWidget * buttonOK = gtk_button_new_with_label ("QUITTER"); 
      gtk_widget_set_name (buttonOK,"btnV");
      gtk_box_pack_start( GTK_BOX(vboxEM),GTK_WIDGET(buttonOK),TRUE,TRUE,0);
	  gtk_label_set_text  (GTK_LABEL(labelcharenvoie),"message envoyé !");
      g_signal_connect(G_OBJECT(buttonOK), "clicked",G_CALLBACK(detuire_mini_f_resultat_envoie),NULL);
      gtk_widget_show_all(GTK_WIDGET(vboxEM));
      return 0;
}

//detruit la mini fenetre message envoyee
void detuire_mini_f_resultat_envoie()
{
	gtk_entry_set_text (GTK_ENTRY(entreeE[0]),""); 
	gtk_entry_set_text (GTK_ENTRY(entreeE[1]),"");
	gtk_text_buffer_set_text (bufferE, "", -1);
	  gtk_widget_destroy(GTK_WIDGET(windowEM));
}
//exxutre un code fonction de la reponse de lutilisateur 
 
 void on_response (GtkDialog *dialog, gint       response_id, gpointer   user_data)
{
 
 switch (response_id)
  {
    case GTK_RESPONSE_ACCEPT:
    			afficher_message_etat(NULL,NULL);
         					printf("OUI pour la signature \n");break;
    case GTK_RESPONSE_REJECT:
    						printf("NON pour la signature \n");break;
    default:
    		printf(" par defaut  NON pour la signature \n");break;
       break;
  }
  gtk_widget_destroy (GTK_WIDGET (dialog));
}

//demande la signature 
void show_dialog (GtkButton *button, gpointer   user_data)
{
  GtkWindow *window = user_data;
  GtkWidget *dialog;
  GtkWidget *content_area;
  GtkWidget *label;


  dialog = gtk_dialog_new_with_buttons ("Singnature", window, GTK_DIALOG_MODAL,  
  	"gtk-yes", GTK_RESPONSE_ACCEPT,"gtk-no" , GTK_RESPONSE_REJECT,NULL);

  content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
  gtk_widget_set_size_request(GTK_WIDGET(content_area) ,400,200);
  label = gtk_label_new ("Voulez vous signer votre message ?");
  gtk_container_add (GTK_CONTAINER (content_area), label);

  gtk_widget_show_all (dialog);
  g_signal_connect (GTK_DIALOG (dialog), "response", G_CALLBACK (on_response), NULL);
}


void page_message_envoyes()
{

    imageEM =gtk_image_new_from_file("Icon/logo.png"); 
	labelEM[0]= gtk_label_new ("Messages Envoyés");
	lbenvoyeemessagerie  = gtk_label_new ("");
	gtk_widget_set_name (GTK_WIDGET(lbenvoyeemessagerie),"bv");
	gtk_widget_set_name (GTK_WIDGET(labelEM[0]),"Titre");

	imageBEM[0] = gtk_image_new_from_file("Icon/accjaune.png");
	imageBEM[1] = gtk_image_new_from_file("Icon/Dec3.png");

	for (int i = 0  ;i < 2; ++i )
	{
		buttonEM[i] = gtk_toggle_button_new(); 
		gtk_container_add(GTK_CONTAINER(buttonEM[i]),imageBEM[i]);
		gtk_widget_set_name (buttonEM[i],"buttonEM");
	}

	labelEM[1] = gtk_label_new("Email");
	labelEM[2] = gtk_label_new("Objet");
	gtk_widget_set_name (GTK_WIDGET(labelEM[1]),"miniT");
	gtk_widget_set_name (GTK_WIDGET(labelEM[2]),"miniT");

     GtkWidget *Frame[3]; 
       for (int i = 1 ; i< 3 ; ++i ) 
        { 		
        	     Frame [i] =gtk_frame_new ("");
               	 gtk_widget_set_name (GTK_WIDGET(Frame[i]),"miniT");
        }

       Frame [0] =gtk_frame_new ("Corps de l'email");
       gtk_widget_set_name (GTK_WIDGET(Frame[0]),"miniT");
	   GtkWidget *scrolled_window = gtk_scrolled_window_new (NULL , NULL);
	   bufferEM = gtk_text_buffer_new (NULL);
	   gtk_text_buffer_set_text (bufferEM, "", -1);
	   text_viewEM = gtk_text_view_new_with_buffer (bufferEM);  
	
	   gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 10);
	   gtk_container_add (GTK_CONTAINER (scrolled_window), text_viewEM);
    
	   gtk_container_add (GTK_CONTAINER (Frame[0]), GTK_WIDGET(scrolled_window));
	   gtk_widget_set_size_request(GTK_WIDGET(Frame[0]) , 500,300);

	   gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW(text_viewEM),FALSE);

	   gtk_text_view_set_editable (GTK_TEXT_VIEW(text_viewEM), FALSE);

    //contenu email 
	gtk_container_add (GTK_CONTAINER (Frame[1]), GTK_WIDGET(labelEM[1]));
	gtk_widget_set_size_request(GTK_WIDGET(Frame[1]) , 450,30);
    gtk_container_add (GTK_CONTAINER (Frame[2]), GTK_WIDGET(labelEM[2]));
    gtk_widget_set_size_request(GTK_WIDGET(Frame[2]) , 450,30);



     boxEM = gtk_box_new (GTK_ORIENTATION_VERTICAL,0);
    for (int i  = 0 ; i < 10; ++i)
    {
    	
        gchar * nom1 ;
    	nom1= g_strdup_printf("%s%s", "Titre ", "");
    	BEM[i]=gtk_button_new_with_label(nom1);
    	 gtk_widget_set_name (GTK_WIDGET(BEM[i]),"titremail");
    	  g_signal_connect(G_OBJECT(BEM[i]), "clicked",G_CALLBACK(afficher_contenu_message_envoyee), NULL);
    	gtk_box_pack_start (GTK_BOX(boxEM),GTK_WIDGET(BEM[i]),FALSE,FALSE,0);
    	free(nom1); 
    }
    

         GtkWidget *Framenom; 		
         Framenom =gtk_frame_new ("Envoyés");
         gtk_widget_set_name (GTK_WIDGET(Framenom),"miniT");

		GtkWidget *scrolled_windowm = gtk_scrolled_window_new (NULL , NULL);
	    gtk_container_set_border_width (GTK_CONTAINER (scrolled_windowm), 10);
       	gtk_container_add (GTK_CONTAINER (scrolled_windowm),boxEM);
	   gtk_container_add (GTK_CONTAINER (Framenom), GTK_WIDGET(scrolled_windowm));
	   gtk_widget_set_size_request(GTK_WIDGET(Framenom) , 250,400);

	  
	   GtkWidget *horiz =gtk_box_new (GTK_ORIENTATION_HORIZONTAL,100);
	   GtkWidget *h=gtk_box_new (GTK_ORIENTATION_HORIZONTAL,100);
		GtkWidget *horiz0 =gtk_box_new (GTK_ORIENTATION_HORIZONTAL,100);
		GtkWidget *vert =gtk_box_new (GTK_ORIENTATION_VERTICAL,20);
		GtkWidget *vert1 =gtk_box_new (GTK_ORIENTATION_VERTICAL,100);
		GtkWidget *horiz1=gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);

     //BUttons
     GtkWidget *Vbtn =gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
	 gtk_button_box_set_layout ( GTK_BUTTON_BOX(Vbtn), GTK_BUTTONBOX_START);
     gtk_box_pack_start (GTK_BOX(Vbtn),GTK_WIDGET (buttonEM[0]),FALSE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(Vbtn),GTK_WIDGET (buttonEM[1]),FALSE,FALSE,0);
	    
     
     gtk_box_pack_start (GTK_BOX(horiz),GTK_WIDGET(imageEM),TRUE,TRUE,0);
	 gtk_box_pack_start (GTK_BOX(horiz0),GTK_WIDGET(labelEM[0]),TRUE,TRUE,0);

	 gtk_box_pack_start (GTK_BOX(vert),GTK_WIDGET(Frame[1]),FALSE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(vert),GTK_WIDGET(Frame[2]),FALSE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(vert),GTK_WIDGET(Frame[0]),FALSE,FALSE,0);
	 
	 gtk_widget_set_size_request(GTK_WIDGET(Framenom),200,400);
	 gtk_box_pack_start (GTK_BOX(vert1),GTK_WIDGET(Framenom),FALSE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(horiz1),GTK_WIDGET(vert1),TRUE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(horiz1),GTK_WIDGET(vert),TRUE,FALSE,0);
	
	 gtk_box_pack_start (GTK_BOX(h),GTK_WIDGET(lbenvoyeemessagerie),TRUE,FALSE,0);
     
	 GtkWidget *MAIN =gtk_box_new (GTK_ORIENTATION_VERTICAL,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(Vbtn),FALSE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(h),TRUE,TRUE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(horiz),FALSE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(horiz0),TRUE,TRUE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(horiz1),TRUE,TRUE,0);

	 gtk_box_pack_start (GTK_BOX(EnvoyeeMessagerie),GTK_WIDGET(MAIN),TRUE,TRUE,0);
 
  g_signal_connect((G_OBJECT(buttonEM[0])),"clicked",G_CALLBACK(afficher_contenu_message_envoyee),NULL);
  g_signal_connect((G_OBJECT(buttonEM[1])),"clicked",G_CALLBACK(afficher_contenu_message_envoyee),NULL);


}


void afficher_contenu_message_envoyee(GtkWidget * sender , gpointer *data)
{

	 if (GTK_WIDGET(buttonEM[0]) == sender && !data )
	 {  
   	                             
   	                             gtk_label_set_label (GTK_LABEL(labelEM[1]),"");
								 gtk_label_set_label (GTK_LABEL(labelEM[2]),"");
								 gtk_text_buffer_set_text (bufferEM, "", -1);
								 gtk_stack_set_visible_child (GTK_STACK (stack), GTK_WIDGET (Menu));
   	  }
   
   else if (GTK_WIDGET(buttonEM[1]) == sender && !data ){ 
   								 gtk_label_set_label (GTK_LABEL(labelEM[1]),"");
								 gtk_label_set_label (GTK_LABEL(labelEM[2]),"");
								 gtk_text_buffer_set_text (bufferEM, "", -1);
   	                             gtk_stack_set_visible_child (GTK_STACK (stack), GTK_WIDGET (Connexion));}
   	 else {

	gtk_label_set_label (GTK_LABEL(labelEM[1]),"blalalalallalal");
	gtk_label_set_label (GTK_LABEL(labelEM[2]),"blalalal@hotmail.fr");
	gtk_text_buffer_set_text (bufferEM, "balalalallal\n blalalalal\n etc ...", -1);}
}



//message indesirable


void page_message_indesirable()
{
	imageMI =gtk_image_new_from_file("Icon/logo.png"); 
	labelMI[0]= gtk_label_new ("Messages Indésirables");
	lbmessagerieinde = gtk_label_new ("");
	gtk_widget_set_name (GTK_WIDGET(lbmessagerieinde),"bv");
	gtk_widget_set_name (GTK_WIDGET(labelMI[0]),"Titre");

	imageBMI[0] = gtk_image_new_from_file("Icon/accjaune.png");
	imageBMI[1] = gtk_image_new_from_file("Icon/Dec3.png");

	for (int i = 0  ;i < 2; ++i )
	{
		buttonMI[i] = gtk_toggle_button_new(); 
		gtk_container_add(GTK_CONTAINER(buttonMI[i]),imageBMI[i]);
		gtk_widget_set_name (buttonMI[i],"buttonMR");
	}

	labelMI[1] = gtk_label_new("");
	labelMI[2] = gtk_label_new("");


        GtkWidget *Frame[3]; 
       for (int i = 1 ; i< 3 ; ++i ) 
        { 		
        	     Frame [i] =gtk_frame_new ("");
               	 gtk_widget_set_name (GTK_WIDGET(Frame[i]),"miniT");
        }

       Frame [0] =gtk_frame_new ("Corps de l'email");
       gtk_widget_set_name (GTK_WIDGET(Frame[0]),"miniT");
	   GtkWidget *scrolled_window = gtk_scrolled_window_new (NULL , NULL);
	   bufferMI = gtk_text_buffer_new (NULL);
	   gtk_text_buffer_set_text (bufferMI, "", -1);
	   text_viewMI = gtk_text_view_new_with_buffer (bufferMI);  
	   gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 10);
	   gtk_container_add (GTK_CONTAINER (scrolled_window), text_viewMI);
	   gtk_container_add (GTK_CONTAINER (Frame[0]), GTK_WIDGET(scrolled_window));
	   gtk_widget_set_size_request(GTK_WIDGET(Frame[0]) , 500,300);
	   gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW(text_viewMI),FALSE);
	   gtk_text_view_set_editable (GTK_TEXT_VIEW(text_viewMI), FALSE);

	 
     
    //contenu email 
	gtk_container_add (GTK_CONTAINER (Frame[1]), GTK_WIDGET(labelMI[1]));
	gtk_widget_set_size_request(GTK_WIDGET(Frame[1]) , 450,30);
    //contenu objet 
    gtk_container_add (GTK_CONTAINER (Frame[2]), GTK_WIDGET(labelMI[2]));
    gtk_widget_set_size_request(GTK_WIDGET(Frame[2]) , 450,30);
    
    boxMI = gtk_box_new (GTK_ORIENTATION_VERTICAL,0);
    for (int i  = 0 ; i <10; ++i)
    {
    	
        gchar * nom1 ;
    	nom1= g_strdup_printf("%s%s", "Titre ", "");
    	BMI[i]=gtk_button_new_with_label(nom1);
    	gtk_widget_set_name (GTK_WIDGET(BMI[i]),"titremail");
    	g_signal_connect(G_OBJECT(BMI[i]), "clicked",G_CALLBACK(afficher_proposition_supp_afficher),(gpointer)BMI[i]);
    	gtk_box_pack_start (GTK_BOX(boxMI),GTK_WIDGET(BMI[i]),FALSE,FALSE,0);
    	free(nom1); 
    }
    

         GtkWidget *Framenom; 		
         Framenom =gtk_frame_new ("Reçu");
         gtk_widget_set_name (GTK_WIDGET(Framenom),"miniT");
		 GtkWidget *scrolled_windowm = gtk_scrolled_window_new (NULL , NULL);
	     gtk_container_set_border_width (GTK_CONTAINER (scrolled_windowm), 10);
         gtk_container_add (GTK_CONTAINER (scrolled_windowm),boxMI);
	     gtk_container_add (GTK_CONTAINER (Framenom), GTK_WIDGET(scrolled_windowm));
	     gtk_widget_set_size_request(GTK_WIDGET(Framenom) , 250,400);


	   GtkWidget *horiz =gtk_box_new (GTK_ORIENTATION_HORIZONTAL,100);
	   GtkWidget *h  = gtk_box_new (GTK_ORIENTATION_HORIZONTAL,100);
		GtkWidget *horiz0 =gtk_box_new (GTK_ORIENTATION_HORIZONTAL,100);
		GtkWidget *vert =gtk_box_new (GTK_ORIENTATION_VERTICAL,20);
		GtkWidget *vert1 =gtk_box_new (GTK_ORIENTATION_VERTICAL,100);
		GtkWidget *horiz1=gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);

     //BUttons
     GtkWidget *Vbtn =gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
	 gtk_button_box_set_layout ( GTK_BUTTON_BOX(Vbtn), GTK_BUTTONBOX_START);
     gtk_box_pack_start (GTK_BOX(Vbtn),GTK_WIDGET (buttonMI[0]),FALSE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(Vbtn),GTK_WIDGET (buttonMI[1]),FALSE,FALSE,0);
	    
     
     gtk_box_pack_start (GTK_BOX(horiz),GTK_WIDGET(imageMI),TRUE,TRUE,0);
	 gtk_box_pack_start (GTK_BOX(horiz0),GTK_WIDGET(labelMI[0]),TRUE,TRUE,0);

	 gtk_box_pack_start (GTK_BOX(vert),GTK_WIDGET(Frame[1]),FALSE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(vert),GTK_WIDGET(Frame[2]),FALSE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(vert),GTK_WIDGET(Frame[0]),FALSE,FALSE,0);
	 
	 gtk_widget_set_size_request(GTK_WIDGET(Framenom),200,400);
	 gtk_box_pack_start (GTK_BOX(vert1),GTK_WIDGET(Framenom),FALSE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(horiz1),GTK_WIDGET(vert1),TRUE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(horiz1),GTK_WIDGET(vert),TRUE,FALSE,0);

	 gtk_box_pack_start (GTK_BOX(h),GTK_WIDGET(lbmessagerieinde),TRUE,TRUE,0);
	
	 GtkWidget *MAIN =gtk_box_new (GTK_ORIENTATION_VERTICAL,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(Vbtn),FALSE,FALSE,0);
	  gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(h),TRUE,TRUE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(horiz),FALSE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(horiz0),TRUE,TRUE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(horiz1),TRUE,TRUE,0);

	 gtk_box_pack_start (GTK_BOX(MessagerieInde),GTK_WIDGET(MAIN),TRUE,TRUE,0);
	
 

    	g_signal_connect((G_OBJECT(buttonMI[0])),"clicked",G_CALLBACK(afficher_proposition_supp_afficher),NULL);
    	g_signal_connect((G_OBJECT(buttonMI[1])),"clicked",G_CALLBACK(afficher_proposition_supp_afficher),NULL);
}

//solot qui quitte si on lcique sur accueill ou deconect 
//ou qui propo de supp ou dafficher si on clique sur lun des msg
void afficher_proposition_supp_afficher(GtkWidget * sender , gpointer *data)
{

	 if (GTK_WIDGET(buttonMI[0]) == sender && !data )
	 {  
   	                             
   	                             gtk_label_set_label (GTK_LABEL(labelMI[1]),"");
								 gtk_label_set_label (GTK_LABEL(labelMI[2]),"");
								 gtk_text_buffer_set_text (bufferMI, "", -1);
						gtk_stack_set_visible_child (GTK_STACK (stack), GTK_WIDGET (Menu));
   	  }
     else if (GTK_WIDGET(buttonMI[1]) == sender && !data )
     { 
   								 gtk_label_set_label (GTK_LABEL(labelMI[1]),"");
								 gtk_label_set_label (GTK_LABEL(labelMI[2]),"");
								 gtk_text_buffer_set_text (bufferMI, "", -1);
   	                 gtk_stack_set_visible_child (GTK_STACK (stack), GTK_WIDGET (Connexion));
   	 }
   	 else {  afficher_supprimer_msg ((gpointer)sender);}
}

void afficher_supprimer_msg(gpointer * sender )
{
  windowMI = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_transient_for (GTK_WINDOW(windowMI),GTK_WINDOW(MainWindow));
  gtk_window_set_position (GTK_WINDOW(windowMI),GTK_WIN_POS_CENTER);
  gtk_window_set_title (GTK_WINDOW(windowMI),"          Data Safe");
  gtk_widget_set_size_request(GTK_WIDGET(windowMI) ,300,300);

  GtkWidget * hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL,10); 
 
  vboxMI = gtk_box_new (GTK_ORIENTATION_VERTICAL,50); 
  btn_afficher_supp[0] = gtk_button_new_with_label("Afficher");
  btn_afficher_supp[1] = gtk_button_new_with_label("Supprimer");
  
  for (int i =0 ; i< 2; ++i)
  {
  	g_signal_connect(G_OBJECT(btn_afficher_supp[i]),"clicked",G_CALLBACK(reponse_a_utilisateur_supp_affiche),sender);
  	gtk_widget_set_name (GTK_WIDGET( btn_afficher_supp[i]),"btnV");
   }
  
  gtk_box_pack_start( GTK_BOX(hbox),GTK_WIDGET(btn_afficher_supp[0]),TRUE,TRUE,0);
  gtk_box_pack_start( GTK_BOX(hbox),GTK_WIDGET(btn_afficher_supp[1]),TRUE,TRUE,0);
   
  labelsuppinde = gtk_label_new ("Voulez vous afficher ou supprimer ce message!\n");
   gtk_widget_set_name (GTK_WIDGET(labelsuppinde),"miniT");
   gtk_window_set_deletable (GTK_WINDOW(windowMI),TRUE);
 
  gtk_container_add (GTK_CONTAINER (windowMI),GTK_WIDGET(vboxMI));
  gtk_box_pack_start( GTK_BOX(vboxMI),GTK_WIDGET(labelsuppinde),TRUE,TRUE,0);
  gtk_box_pack_start( GTK_BOX(vboxMI),GTK_WIDGET(hbox),FALSE,TRUE,0);
  gtk_widget_show_all (GTK_WIDGET(windowMI));
 
}

 

void reponse_a_utilisateur_supp_affiche(GtkWidget * sender , gpointer * data)
{    
	//
	if (sender == btn_afficher_supp [0] && data)
	{
				gtk_label_set_label (GTK_LABEL(labelMI[1]),"covid");
				gtk_label_set_label (GTK_LABEL(labelMI[2]),"blalalal@hotmail.fr");
				gtk_text_buffer_set_text (bufferMI, "inchalah le 10 mai c fini par ce que jpp de ce confinement ", -1);
	}
	else if(sender == btn_afficher_supp [1] && data)
	{
		for (int i = 0 ; i< 10 ; ++i){
		if (BMI[i] == GTK_WIDGET(data))
		{
         //gtk_container_remove (GTK_CONTAINER(boxMI),GTK_WIDGET(BMI[i]));
			gtk_label_set_label (GTK_LABEL(labelMI[1]),"");
			gtk_label_set_label (GTK_LABEL(labelMI[2]),"");
			gtk_text_buffer_set_text (bufferMI, "", -1);
			 gtk_widget_hide(BMI[i]);
        //gtk_widget_destroy(GTK_WIDGET(BMI[i]));
     	}

     }
	}

   
    gtk_widget_destroy(GTK_WIDGET(windowMI));
}


