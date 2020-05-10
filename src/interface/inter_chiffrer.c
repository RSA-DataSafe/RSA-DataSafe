#include "inter_chiffrer.h"

void page_chiffrer()
{

	imageC =gtk_image_new_from_file("../features/logo.png"); 
	labelC[0]= gtk_label_new ("Chiffrement");
	labelC[1]= gtk_label_new ("Ou");
	lbchiffrer= gtk_label_new ("");
	gtk_widget_set_name (lbchiffrer,"bv");
	gtk_widget_set_name (labelC[0],"Titre");
	gtk_widget_set_name (labelC[1],"Titre");

	imageBC[0] = gtk_image_new_from_file("../features/accjaune.png");
	imageBC[1] = gtk_image_new_from_file("../features/Dec3.png");
	for (int i = 0  ;i < 2 ; ++i )
	{
		buttonC[i] = gtk_toggle_button_new(); 
		gtk_container_add(GTK_CONTAINER(buttonC[i]),imageBC[i]);
		gtk_widget_set_name (buttonC[i],"ButtonC");
	}

    buttonC[3] =  gtk_file_chooser_button_new (_("Select a file"),GTK_FILE_CHOOSER_ACTION_OPEN);
    gtk_widget_set_name (buttonC[3],"Importer");
    gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (buttonC[3]),"/etc");
    gtk_file_chooser_button_set_title(GTK_FILE_CHOOSER_BUTTON(buttonC[3]),"Importer");
	gtk_file_chooser_button_set_width_chars(GTK_FILE_CHOOSER_BUTTON(buttonC[3]),20);


    buttonC[4] = gtk_button_new_with_label("Valider"); 

    gtk_widget_set_name (buttonC[4],"btnV");
    gtk_widget_set_name (buttonC[3],"btnV");

       GtkWidget * Frame ; 
	   Frame  =gtk_frame_new ("Text");
       gtk_widget_set_name (GTK_WIDGET(Frame),"miniT");
		GtkWidget *scrolled_window = gtk_scrolled_window_new (NULL , NULL);
	 	bufferC= gtk_text_buffer_new (NULL);
		gtk_text_buffer_set_text (bufferC, "",-1);
		text_viewC= gtk_text_view_new_with_buffer (bufferC);
	   gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 10);
	   gtk_container_add (GTK_CONTAINER (scrolled_window), text_viewC);
	   gtk_container_add (GTK_CONTAINER (Frame), GTK_WIDGET(scrolled_window));
	   gtk_widget_set_size_request(GTK_WIDGET(Frame) , 400,300);


	 GtkWidget *horiz1 =gtk_box_new (GTK_ORIENTATION_HORIZONTAL,100);
	 GtkWidget *h =gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
	 GtkWidget*horiz =gtk_box_new (GTK_ORIENTATION_HORIZONTAL,100);
	 GtkWidget *horiz0 =gtk_box_new (GTK_ORIENTATION_HORIZONTAL,100);

     GtkWidget *Vbtn =gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
	 gtk_button_box_set_layout ( GTK_BUTTON_BOX(Vbtn), GTK_BUTTONBOX_START);
     gtk_box_pack_start (GTK_BOX(Vbtn),GTK_WIDGET (buttonC[0]),TRUE,TRUE,0);
	 gtk_box_pack_start (GTK_BOX(Vbtn),GTK_WIDGET (buttonC[1]),TRUE,TRUE,0);
	   
    
     gtk_box_pack_start (GTK_BOX(horiz),GTK_WIDGET(imageC),TRUE,TRUE,0);
	 gtk_box_pack_start (GTK_BOX(horiz0),GTK_WIDGET(labelC[0]),TRUE,TRUE,0);

    GtkWidget *Vbtn1 =gtk_button_box_new (GTK_ORIENTATION_VERTICAL);
	 gtk_button_box_set_layout ( GTK_BUTTON_BOX(Vbtn1), GTK_BUTTONBOX_SPREAD);
     gtk_box_pack_start (GTK_BOX(Vbtn1),GTK_WIDGET (buttonC[3]),TRUE,FALSE,0);

     gtk_box_pack_start (GTK_BOX(horiz1),GTK_WIDGET(Frame),TRUE,TRUE,100);
     gtk_box_pack_start (GTK_BOX(horiz1),GTK_WIDGET(Vbtn1),TRUE,TRUE,100);
     gtk_box_pack_start (GTK_BOX(h),GTK_WIDGET(lbchiffrer),TRUE,TRUE,100);
      

     GtkWidget *Vbtn2 =gtk_button_box_new (GTK_ORIENTATION_VERTICAL);
	 gtk_button_box_set_layout ( GTK_BUTTON_BOX(Vbtn2), GTK_BUTTONBOX_SPREAD);
     gtk_box_pack_start (GTK_BOX(Vbtn2),GTK_WIDGET (buttonC[4]),TRUE,FALSE,0);
   
	 GtkWidget *MAIN =gtk_box_new (GTK_ORIENTATION_VERTICAL,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(Vbtn),FALSE,TRUE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(h),TRUE,TRUE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(horiz),FALSE,TRUE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(horiz0),FALSE,TRUE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(horiz1),TRUE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET(Vbtn2),TRUE,FALSE,0);

    gtk_box_pack_start (GTK_BOX(Chiffrer),GTK_WIDGET(MAIN),TRUE,TRUE,0);
    g_signal_connect(G_OBJECT(buttonC[4]), "clicked",G_CALLBACK(page_chargementC), NULL);
    for (int i = 0 ; i < 2 ; ++i) 
	  g_signal_connect(G_OBJECT(buttonC[i]),"clicked",G_CALLBACK(Slots_Chiffrer),NULL);
	  g_signal_connect (G_OBJECT (buttonC[3]), "selection-changed", G_CALLBACK (file_selected), NULL);
	
  }


void Slots_Chiffrer(GtkWidget * sender , gpointer *data)
{
	if ( GTK_WIDGET(buttonC[1]) == sender    && !data ) 
   	                             gtk_stack_set_visible_child (GTK_STACK (stack), GTK_WIDGET (Connexion));
   
     if ( GTK_WIDGET(buttonC[0]) == sender  && !data )  
   	                             gtk_stack_set_visible_child (GTK_STACK (stack), GTK_WIDGET (Menu));

}

void file_selected (GtkFileChooser *chooser, gpointer user_data)
{
  gchar *filename = gtk_file_chooser_get_filename (chooser);
  if (!filename) return;
  g_print ("Path du fichier qui sera lu  : %s\n", filename);
  g_free (filename);
}

void page_chargementC()
{

    
    GtkTextIter start;
    GtkTextIter end;
    

    gtk_text_buffer_get_start_iter(bufferC,&start);
  
    gtk_text_buffer_get_end_iter(bufferC,&end);
    chaine= (char*)gtk_text_buffer_get_text(bufferC,&start, &end,FALSE);
    
     //  #####
    codage = malloc (sizeof (message));
    mpz_init (codage->taille); 
    messageachiff=conversion_char_mpz(chaine);
    mpz_init_set_str(codage->nombre ,"ASCCI", 10);
    mpz_set_ui (codage->taille , mpz_sizeinbase(codage->nombre,2));
    messagechiff=chiffrement(messageachiff, &utilisateur.publique , codage);

   

   window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_transient_for (GTK_WINDOW(window),GTK_WINDOW(MainWindow));
  gtk_window_set_position (GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_title (GTK_WINDOW(window),"Data Safe");
  gtk_widget_set_size_request(GTK_WIDGET(window) ,500,500);
  vboxCC = gtk_box_new (GTK_ORIENTATION_VERTICAL,50); 
  spinner = gtk_spinner_new ();

  	gtk_spinner_start (GTK_SPINNER(spinner));
   labelcharc= gtk_label_new("Veuillez patientez  Chiffrement en cours !\n");
   gtk_widget_set_name (GTK_WIDGET(labelcharc),"miniT");
   gtk_window_set_deletable (GTK_WINDOW(window),TRUE);
  //gtk_widget_set_size_request(GTK_WIDGET(window) ,400,200);
 
  gtk_container_add (GTK_CONTAINER (window),GTK_WIDGET(vboxCC));

  gtk_box_pack_start( GTK_BOX(vboxCC),GTK_WIDGET(labelcharc),TRUE,TRUE,0);
  gtk_box_pack_start( GTK_BOX(vboxCC),GTK_WIDGET(spinner),TRUE,TRUE,0);
  gtk_widget_set_name (spinner,"spin");
 
  g_timeout_add (2500,(GSourceFunc)page_resultatC, spinner);
  gtk_widget_show_all (GTK_WIDGET(window));
 
  //g_signal_connect(window, "destroy", G_CALLBACK(detuire_mini_f_resultat), window);
  	//g_signal_connect (GTK_DIALOG (dialog), "response", G_CALLBACK (on_response), NULL);
}


int page_resultatC(gpointer * data)
{
      
      gtk_spinner_stop (GTK_SPINNER(spinner));
      gtk_container_remove (GTK_CONTAINER(vboxCC),GTK_WIDGET(spinner));
      gtk_widget_hide(GTK_WIDGET(vboxCC)); 

	      GtkWidget * buttonOK = gtk_button_new_with_label ("OK"); 
	      gtk_widget_set_name (buttonOK,"btnV"); 
		  gtk_label_set_text  (GTK_LABEL(labelcharc),"Resulat du chiffrement:");

		   GtkWidget * Frame ; 
		   Frame  =gtk_frame_new ("Votre texte chiffré");
	       gtk_widget_set_name (GTK_WIDGET(Frame),"miniT");	
        bufferCC= gtk_text_buffer_new (NULL);
	 	GtkWidget *scrolled_window = gtk_scrolled_window_new (NULL , NULL);
	
  		
	  //######################"""""""""""""
		  chaine=malloc(2048*sizeof(char));
		  mpz_get_str(chaine,10,messagechiff->nombre);
		  gtk_text_buffer_set_text (bufferCC,chaine, -1);
			


	  text_viewCC= gtk_text_view_new_with_buffer (bufferCC);
	  gtk_text_view_set_editable (GTK_TEXT_VIEW(text_viewCC), FALSE);
	  gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 10);
	  gtk_container_add (GTK_CONTAINER (scrolled_window), text_viewCC);
    
	   gtk_container_add (GTK_CONTAINER (Frame), GTK_WIDGET(scrolled_window));
	   gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW(text_viewCC),FALSE);
	   gtk_box_pack_start(GTK_BOX(vboxCC),GTK_WIDGET(Frame),TRUE,TRUE,0);
       gtk_box_pack_start(GTK_BOX(vboxCC),GTK_WIDGET(buttonOK),FALSE,FALSE,0);
     
      g_signal_connect(G_OBJECT(buttonOK), "clicked",G_CALLBACK(detuire_mini_f_resultat),NULL);
      
      gtk_widget_show_all(GTK_WIDGET(vboxCC));
     
      return 0;
}

void detuire_mini_f_resultat()
{
	  gtk_widget_destroy(GTK_WIDGET(window));
}
