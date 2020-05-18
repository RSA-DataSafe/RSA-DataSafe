#include "inter_menu.h"
void menu_principal()
{
	imageM= gtk_image_new_from_file("Icon/millogo.jpg"); 
	labelMenu = gtk_label_new ("Menu");
	lbmenu= gtk_label_new ("");
	gtk_widget_set_name (labelMenu,"Titre");
	gtk_widget_set_name (lbmenu,"bv");

	imageBM[0] = gtk_image_new_from_file("Icon/Messagerie.png");
	imageBM[1] = gtk_image_new_from_file("Icon/Chiffrer.png");
	imageBM[2] = gtk_image_new_from_file("Icon/Parametre.png");
	imageBM[3] = gtk_image_new_from_file("Icon/Dechiffrer.png");
	for (int i = 0  ;i < 4 ; ++i )
	{
		buttonM[i] = gtk_toggle_button_new(); 
		gtk_container_add(GTK_CONTAINER(buttonM[i]),imageBM[i]);
		gtk_widget_set_name (buttonM[i],"ButtonM");
	}



	 GtkWidget *horiz1 =gtk_box_new (GTK_ORIENTATION_HORIZONTAL,100);
	 GtkWidget *horiz =gtk_box_new (GTK_ORIENTATION_HORIZONTAL,100);
	 GtkWidget *h =gtk_box_new (GTK_ORIENTATION_HORIZONTAL,100);
	 
	 GtkWidget*vert =gtk_box_new (GTK_ORIENTATION_VERTICAL,100);
	 GtkWidget*vert1 =gtk_box_new (GTK_ORIENTATION_VERTICAL,30);
	 GtkWidget*vert2 =gtk_box_new (GTK_ORIENTATION_VERTICAL,100);

     gtk_box_pack_start (GTK_BOX(horiz),GTK_WIDGET(labelMenu),TRUE,FALSE,0);
	    
	 gtk_box_pack_start (GTK_BOX(vert),GTK_WIDGET(buttonM[0]),TRUE,FALSE,0);
	 gtk_box_pack_start (GTK_BOX(vert),GTK_WIDGET(buttonM[1]),TRUE,FALSE,0);

	  gtk_box_pack_start (GTK_BOX(vert1),GTK_WIDGET(imageM),TRUE,FALSE,0);
	     
	  gtk_box_pack_start (GTK_BOX(vert2),GTK_WIDGET(buttonM[2]),TRUE,FALSE,0);
	  gtk_box_pack_start (GTK_BOX(vert2),GTK_WIDGET(buttonM[3]),TRUE,FALSE,0);
	  
     gtk_box_pack_start (GTK_BOX(horiz1),GTK_WIDGET(vert),TRUE,TRUE,0);
     gtk_box_pack_start (GTK_BOX(horiz1),GTK_WIDGET(vert1),TRUE,TRUE,0);
     gtk_box_pack_start (GTK_BOX(horiz1),GTK_WIDGET(vert2),TRUE,TRUE,0);

	  gtk_box_pack_start (GTK_BOX(h),GTK_WIDGET(lbmenu),TRUE,TRUE,0);

	
	 GtkWidget *MAIN =gtk_box_new (GTK_ORIENTATION_VERTICAL,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET (h),TRUE,TRUE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET (horiz),TRUE,TRUE,0);
	 gtk_box_pack_start (GTK_BOX(MAIN),GTK_WIDGET (horiz1),TRUE,TRUE,0);
	 gtk_box_pack_start (GTK_BOX(Menu),GTK_WIDGET (MAIN),TRUE,FALSE,0);

	  	

	  	  for (int i = 0 ; i< 4 ; ++i )
      	g_signal_connect(G_OBJECT(buttonM[i]),"clicked",G_CALLBACK(slots_Menu),NULL);


	  

        
	

}

void slots_Menu(GtkWidget * sender, gpointer * data )
{
     gchar * nom= g_strdup_printf("%s  %s", "Bienvenue", utilisateur.email);
 if (GTK_WIDGET(buttonM[2]) == sender && !data )
 {
 	 							
                        		gtk_label_set_text(GTK_LABEL(lbparametre),nom);
                        		
                        		gtk_stack_set_visible_child (GTK_STACK (stack), GTK_WIDGET (Parametre));
 }
   	                             
if (GTK_WIDGET(buttonM[1]) == sender  && !data ) 
{             
                               
                        		gtk_label_set_text(GTK_LABEL(lbchiffrer),nom);
                       
   	                             gtk_stack_set_visible_child (GTK_STACK (stack), GTK_WIDGET (Chiffrer));
 }
 
if (GTK_WIDGET(buttonM[0]) == sender && !data ) 
{

                        gtk_label_set_text(GTK_LABEL(lbmessagerie),nom);
                    
	gtk_stack_set_visible_child (GTK_STACK (stack), GTK_WIDGET (Messagerie));

} 
   	                             
if (GTK_WIDGET(buttonM[3]) == sender && !data )
{
	 			
                     gtk_label_set_text(GTK_LABEL(lbdechiffrer),nom);
                  
                   gtk_stack_set_visible_child (GTK_STACK (stack), GTK_WIDGET (Dechiffrer));
}  
      free(nom);	                             
}