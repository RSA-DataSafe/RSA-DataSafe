#include "../Header/inter_initialisation.h"
void CSS() {
	// creation du pointeur et allocation
  GtkCssProvider *provider=gtk_css_provider_new();

  GdkDisplay *display=gdk_display_get_default();
  GdkScreen *screen=gdk_display_get_default_screen(display);
  gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider),
  	GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  GError *error=NULL;
  gtk_css_provider_load_from_path(provider,"Src/style.css",&error);
  if (error!=NULL)
  {
    fprintf(stderr,"Probleme dans le fichier css: %s !\n",error->message);
    g_error_free(error);
  }
  g_object_unref(provider);
}

GdkPixbuf *create_pixbuf(const gchar * filename) {
    
   GdkPixbuf *pixbuf;
   GError *error = NULL;
   pixbuf = gdk_pixbuf_new_from_file(filename, &error);
   
   if (!pixbuf) {
       
      fprintf(stderr, "%s\n", error->message);
      g_error_free(error);
   }

   return pixbuf;
}



// fonction coeur qui va itialiser la stack 

void initialisation()
{

    stack  = gtk_stack_new(); 
 	  gtk_stack_set_transition_type (GTK_STACK(stack), GTK_STACK_TRANSITION_TYPE_NONE);
    MainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
 
    gtk_window_resize ( GTK_WINDOW( MainWindow) , 1000, 1000);
    gtk_window_set_title(GTK_WINDOW(MainWindow), "Data Safe");
    gtk_window_set_position(GTK_WINDOW(MainWindow) , GTK_WIN_POS_CENTER);
    gtk_container_add(GTK_CONTAINER( MainWindow),GTK_WIDGET (stack));
    
    // le peyit logo en petit  en haut agauche 
    icon = create_pixbuf("Icon/logo.jpeg");  
    //on a une pile de fenetre 
	  // qui contenu dans la fenetre principale 
	  // pour changer de fenetre on change juste le haut de ka stack 
	  //nos pages 
	  accueil = gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
    Connexion =  gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
    Inscription =  gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
    Menu = gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
    Parametre = gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
    Chiffrer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
    Dechiffrer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
    Messagerie = gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
    MessagerieRecu =gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
    MessagerieEcr = gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
    EnvoyeeMessagerie = gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
    MessagerieInde =gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
    Compte =  gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
    Securite = gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0); 
  
  
    //Connexion
    gtk_window_set_icon(GTK_WINDOW(MainWindow), icon);
	  g_object_unref(icon);
    
  	gtk_stack_add_named (GTK_STACK (stack),GTK_WIDGET (accueil),"1");
  	gtk_stack_add_named (GTK_STACK (stack),GTK_WIDGET (Connexion),"2");
  	gtk_stack_add_named (GTK_STACK (stack),GTK_WIDGET (Inscription),"3");
  	gtk_stack_add_named (GTK_STACK (stack),GTK_WIDGET (Menu),"4");
  	gtk_stack_add_named (GTK_STACK (stack),GTK_WIDGET (Parametre),"5");
  	gtk_stack_add_named (GTK_STACK (stack),GTK_WIDGET (Chiffrer),"6");
  	gtk_stack_add_named (GTK_STACK (stack),GTK_WIDGET (Dechiffrer),"7");
  	gtk_stack_add_named (GTK_STACK (stack),GTK_WIDGET (Messagerie),"8");
  	gtk_stack_add_named (GTK_STACK (stack),GTK_WIDGET (MessagerieRecu),"9");
  	gtk_stack_add_named (GTK_STACK (stack),GTK_WIDGET (MessagerieEcr),"10");
    gtk_stack_add_named (GTK_STACK (stack),GTK_WIDGET (EnvoyeeMessagerie),"11");
    gtk_stack_add_named (GTK_STACK (stack),GTK_WIDGET (MessagerieInde),"12");
    gtk_stack_add_named (GTK_STACK (stack),GTK_WIDGET (Compte),"13");
    gtk_stack_add_named (GTK_STACK (stack),GTK_WIDGET (Securite),"14");
  	gtk_stack_set_visible_child (GTK_STACK (stack), GTK_WIDGET (accueil));
  	
	
}

void page_ouverture()
{

 imageacc = gtk_image_new_from_file("Icon/logo.jpeg"); 
 gtk_box_pack_start (GTK_BOX(accueil),GTK_WIDGET(imageacc),TRUE,TRUE,0);
}


char * remove_n(char * chaine)
{
    if (chaine == NULL)
        return NULL;
    int i = 0;
    while(chaine[i] != '\n' && chaine[i] != '\0') i++;
    chaine[i] = '\0';
    return chaine;
}