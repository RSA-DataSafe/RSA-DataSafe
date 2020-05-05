#include "../Header/inter_dechiffrer.h"
void page_dechiffrer()
{

	imageD =gtk_image_new_from_file("Icon/logo.png"); 
	labelD[0]= gtk_label_new ("Déchiffrement");
	labelD[1]= gtk_label_new ("Ou");
	lbdechiffrer= gtk_label_new ("");
	gtk_widget_set_name (lbdechiffrer,"bv");
	gtk_widget_set_name (labelD[0],"Titre");
	gtk_widget_set_name (labelD[1],"Titre");

	imageBD[0] = gtk_image_new_from_file("Icon/accjaune.png");
	imageBD[1] = gtk_image_new_from_file("Icon/Dec3.png");
	for (int i = 0  ;i < 2 ; ++i )
	{
		buttonD[i] = gtk_toggle_button_new(); 
		gtk_container_add(GTK_CONTAINER(buttonD[i]),imageBD[i]);
		gtk_widget_set_name (buttonD[i],"ButtonD");
	}


    buttonD[3] =  gtk_file_chooser_button_new (_("Select a file"),GTK_FILE_CHOOSER_ACTION_OPEN);
    gtk_widget_set_name (buttonD[3],"Importer");
    gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (buttonD[3]),"/etc");
    gtk_file_chooser_button_set_title (GTK_FILE_CHOOSER_BUTTON(buttonD[3]),"Importer un fichier");
    gtk_file_chooser_button_set_width_chars(GTK_FILE_CHOOSER_BUTTON(buttonD[3]),20);
    buttonD[4] = gtk_button_new_with_label("Valider"); 
    gtk_widget_set_name (buttonD[4],"btnV");
    gtk_widget_set_name (buttonD[3],"btnV");

    g_signal_connect(G_OBJECT(buttonD[4]), "clicked",G_CALLBACK(page_chargementD),NULL);

        GtkWidget * Frame ; 
	    Frame  =gtk_frame_new ("Text");
        gtk_widget_set_name (GTK_WIDGET(Frame),"miniT");
		GtkWidget *scrolled_window = gtk_scrolled_window_new (NULL , NULL);
	 	bufferD= gtk_text_buffer_new (NULL);
		gtk_text_buffer_set_text (bufferD, "", -1);
		text_viewD= gtk_text_view_new_with_buffer (bufferD);
	   gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 10);
	   gtk_container_add (GTK_CONTAINER (scrolled_window), text_viewD);
    
	   gtk_container_add (GTK_CONTAINER (Frame), GTK_WIDGET(scrolled_window));
	   gtk_widget_set_size_request(GTK_WIDGET(Frame) , 400,300);


	   GtkWidget *horiz1 =gtk_box_new (GTK_ORIENTATION_HORIZONTAL,100);
	    GtkWidget *h =gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
	 GtkWidget*horiz =gtk_box_new (GTK_ORIENTATION_HORIZONTAL,100);
	 GtkWidget *horiz0 =gtk_box_new (GTK_ORIENTATION_HORIZONTAL,100);

     GtkWidget *Vbtn =gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
	 gtk_button_box_set_layout ( GTK_BUTTON_BOX(Vbtn), GTK_BUTTONBOX_START);
     gtk_box_pack_start (GTK_BOX(Vbtn),GTK_WIDGET (buttonD[0]),TRUE,TRUE,0);
	 gtk_box_pack_start (GTK_BOX(Vbtn),GTK_WIDGET (buttonD[1]),TRUE,TRUE,0);
	   
    
     gtk_box_pack_start (GTK_BOX(horiz),GTK_WIDGET(imageD),TRUE,TRUE,0);
	 gtk_box_pack_start (GTK_BOX(horiz0),GTK_WIDGET(labelD[0]),TRUE,TRUE,0);

    GtkWidget *Vbtn1 =gtk_button_box_new (GTK_ORIENTATION_VERTICAL);
	 gtk_button_box_set_layout ( GTK_BUTTON_BOX(Vbtn1), GTK_BUTTONBOX_SPREAD);
     gtk_box_pack_start (GTK_BOX(Vbtn1),GTK_WIDGET (buttonD[3]),TRUE,FALSE,0);

     gtk_box_pack_start (GTK_BOX(horiz1),GTK_WIDGET(Frame),TRUE,TRUE,100);
     gtk_box_pack_start (GTK_BOX(horiz1),GTK_WIDGET(Vbtn1),TRUE,TRUE,100);


     GtkWidget *Vbtn2 =gtk_button_box_new (GTK_ORIENTATION_VERTICAL);
	 gtk_button_box_set_layout ( GTK_BUTTON_BOX(Vbtn2), GTK_BUTTONBOX_SPREAD);
     gtk_box_pack_start (GTK_BOX(Vbtn2),GTK_WIDGET (buttonD[4]),TRUE,FALSE,0);

      gtk_box_pack_start (GTK_BOX(h),GTK_WIDGET (lbdechiffrer),TRUE,TRUE,0);
   
	 GtkWidget *MAIN =gtk_box_new (GTK_ORIENTATION_VERTICAL,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(Vbtn),FALSE,TRUE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(h),TRUE,TRUE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(horiz),FALSE,TRUE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(horiz0),FALSE,TRUE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(horiz1),TRUE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(Vbtn2),TRUE,FALSE,0);
     gtk_box_pack_start (GTK_BOX(Dechiffrer),GTK_WIDGET(MAIN),TRUE,TRUE,0);
	 
   	 for (int i = 0 ; i < 2 ; ++i) 
	 
	 	g_signal_connect(G_OBJECT(buttonD[i]),"clicked",G_CALLBACK(Slots_dechiffer),NULL);
  }


  void Slots_dechiffer(GtkWidget * sender , gpointer * data) 
  {
    if ( (GTK_WIDGET(buttonD[1]) == sender )   && !data ) 
                                 gtk_stack_set_visible_child (GTK_STACK (stack), GTK_WIDGET (Connexion));
   
     if ( (GTK_WIDGET(buttonD[0]) == sender )   && !data )  
                                 gtk_stack_set_visible_child (GTK_STACK (stack), GTK_WIDGET (Menu));
  }


void page_chargementD()
{
  windowD = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_transient_for (GTK_WINDOW(windowD),GTK_WINDOW(MainWindow));
  gtk_window_set_position (GTK_WINDOW(windowD), GTK_WIN_POS_CENTER);
  gtk_window_set_title (GTK_WINDOW(windowD),"          Data Safe");
  gtk_widget_set_size_request(GTK_WIDGET(windowD) ,500,500);
  vboxCD = gtk_box_new (GTK_ORIENTATION_VERTICAL,50); 

  spinnerD = gtk_spinner_new ();

  	gtk_spinner_start (GTK_SPINNER(spinnerD));
   labelcharD= gtk_label_new("Veuillez patientez  Déchiffrement en cours ...\n");
   gtk_widget_set_name (GTK_WIDGET(labelcharD),"miniT");
   gtk_window_set_deletable (GTK_WINDOW(windowD),TRUE);
  //gtk_widget_set_size_request(GTK_WIDGET(window) ,400,200);
 
  gtk_container_add (GTK_CONTAINER (windowD),GTK_WIDGET(vboxCD));

  gtk_box_pack_start( GTK_BOX(vboxCD),GTK_WIDGET(labelcharD),TRUE,TRUE,0);
  gtk_box_pack_start( GTK_BOX(vboxCD),GTK_WIDGET(spinnerD),TRUE,TRUE,0);
  gtk_widget_set_name (spinnerD,"spin");
 
  g_timeout_add (2500,(GSourceFunc)page_resultatD, spinnerD);
  gtk_widget_show_all (GTK_WIDGET(windowD));
 
  //g_signal_connect(window, "destroy", G_CALLBACK(detuire_mini_f_resultat), window);
  	//g_signal_connect (GTK_DIALOG (dialog), "response", G_CALLBACK (on_response), NULL);
}


int page_resultatD()
{
      
      gtk_spinner_stop (GTK_SPINNER(spinnerD));
      gtk_container_remove (GTK_CONTAINER(vboxCD),GTK_WIDGET(spinnerD));
      gtk_widget_hide(GTK_WIDGET(vboxCD)); 

      GtkWidget * buttonOK = gtk_button_new_with_label ("OK"); 
      gtk_widget_set_name (buttonOK,"btnV");
  
	

	 
	  gtk_label_set_text  (GTK_LABEL(labelcharD),"Resulat du déchiffrement:");

	   GtkWidget * Frame ; 
	   Frame  =gtk_frame_new ("Votre texte déchiffré");
        gtk_widget_set_name (GTK_WIDGET(Frame),"miniT");	
		GtkWidget *scrolled_window = gtk_scrolled_window_new (NULL , NULL);
	 	bufferCD= gtk_text_buffer_new (NULL);
		gtk_text_buffer_set_text (bufferCD, "ceci est  un exemple", -1);
		text_viewCD= gtk_text_view_new_with_buffer (bufferCD);
	   gtk_text_view_set_editable (GTK_TEXT_VIEW(text_viewCD), FALSE);
	   gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 10);
	   
	   gtk_container_add (GTK_CONTAINER (scrolled_window), text_viewCD);
    
	   gtk_container_add (GTK_CONTAINER (Frame), GTK_WIDGET(scrolled_window));
	
	  
	   gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW(text_viewCD),FALSE);
	   gtk_box_pack_start(GTK_BOX(vboxCD),GTK_WIDGET(Frame),TRUE,TRUE,0);
       gtk_box_pack_start(GTK_BOX(vboxCD),GTK_WIDGET(buttonOK),FALSE,FALSE,0);
     
      g_signal_connect(G_OBJECT(buttonOK), "clicked",G_CALLBACK(detuire_mini_f_resultatD),NULL);
      
      gtk_widget_show_all(GTK_WIDGET(vboxCD));
      
      return 0;
}

void detuire_mini_f_resultatD()
{
	  gtk_widget_destroy(GTK_WIDGET(windowD));
}