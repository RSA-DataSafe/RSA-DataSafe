#include "ecriture.h"
char nom[]="connexion.txt";

int  nouvel_utilisateur(char *email , char *mdp)
{
       int taille= strlen(email);
       char *userfile1=malloc((taille+20)*sizeof(char));
       strcpy(userfile1,"MessageRecu.txt");
       char ch1[200]="rsa/";
       char dossier[300];
       strcpy(dossier,ch1);
       strcat(dossier,email);
       mkdir(dossier,S_IRWXU);

       strcat(dossier,"/");
       char dossier1[300];
       strcpy(dossier1,dossier);
       strcat(dossier,userfile1);
       int res1 = 0,res2 = 0;
       FILE *userf1=fopen(dossier,"a+");
       if(userf1!=NULL)
       {
        fclose(userf1);
       }
       else
       {
        printf("Erreur de création d fichier\n");
       }
       char *userfile2=malloc((taille+50)*sizeof(char));
       strcpy(userfile2,"Cles.txt");
       strcat(dossier1,userfile2);
       FILE *userf2=fopen(dossier1,"a+");
       if(userf2!=NULL)
       {
        fclose(userf2);
       }  
       else
       {
        printf("Erreur de création d fichier\n");
       }
       strcpy(userfile2,"MessageEnvoyer.txt");
       strcpy(dossier,ch1);
       strcat(dossier,email);
       strcat(dossier,"/");
       strcat(dossier,userfile2);
       userf2=fopen(dossier,"a+");
       
       if(userf2!=NULL) fclose(userf2);
       
       else  printf("Erreur  de création du fichier\n");
       
       strcpy(userfile2,"MessageIndesirable.txt");
       strcpy(dossier,ch1);
       strcat(dossier,email);
       strcat(dossier,"/");
       strcat(dossier,userfile2);
       userf2=fopen(dossier,"a+");
       if(userf2!=NULL) 
                     fclose(userf2);
       else      
                  printf("Erreur  de création du fichier\n");

       strcpy(userfile2,"MessageInvisible.txt");
       strcpy(dossier,ch1);
       strcat(dossier,email);
       strcat(dossier,"/");
       strcat(dossier,userfile2);
       userf2=fopen(dossier,"a+");
       if(userf2!=NULL)
       {
        fclose(userf2);
       }
       else
       {
        printf("Erreur  de création du fichier\n");
       }
       char cm[200]="rsa/";
       strcat(cm,nom);
       FILE *fichier=fopen(cm,"a");
       char ligne [300]; 
       //char *line_buf = NULL;
      if(fichier!=NULL)
       {
            while(fgets (ligne, sizeof ligne,fichier ) != NULL && strcmp(ligne,"")) ;
            res1=ecrire_fichier(cm,email);
            res1=ecrire_fichier(cm,mdp);
            if(res1!=0 || res2!=0)
            {
              return ERR_ERCI;
            }
            fclose ( fichier );
            return 0;
       }
      
       
          return ERR_ERCI;
       
}

int  Change_Email(char *email , char *mdp , char *newemail)
{
  char nomtmp[]="test1.txt";
  char dossier[300]="rsa/";
  char dossier1[300]="rsa/";
  strcat(dossier,nom);
  strcat(dossier1,nomtmp);
  FILE * fichier =fopen(dossier1,"w");
  FILE *fichier1 =fopen(dossier,"r");
  char *line_buf = NULL;
  char *line_buf1 = NULL;
  size_t line_buf_size = 0;
   if(fichier!=NULL && fichier1!=NULL)
   {
     while(getline(&line_buf, &line_buf_size, fichier1)>= 0 && getline(&line_buf1, &line_buf_size, fichier1)>=0) 
     {
      int test=0;
        for(int i=0;i<strlen(line_buf)-1;i++)
        {
          if(email[i]!=line_buf[i])
          {
             test=1;
             break;
          }
        }
        int test1=0;
        for(int j=0;j<strlen(line_buf1)-1;j++)
        {
          if(line_buf1[j]!=mdp[j]){
            test1=1;
            break;
        	}
        }
      if(test==0 && test1==0)
      {
            fputs(newemail,fichier);
            fputs("\n",fichier);
            fputs(line_buf1,fichier);  
              
      }
      else
      {
         
          fputs(line_buf,fichier);
          fputs(line_buf1,fichier);     
      }
     }
     fclose(fichier);
     fclose(fichier1);
     remove(dossier);
     rename(dossier1,dossier);
     strcpy(dossier,"rsa/");
     strcat(dossier,email);
     strcpy(dossier1,"rsa/");
     strcat(dossier1,newemail);
     rename(dossier,dossier1);
     return 0;
   }
   else
   {
    return ERR_ERCI;
   }  
}
int  Change_MotDePasse (char*email , char *mdp , char* newmdp)
{
  char nomtmp[20]="test1.txt";
  char dossier[100]="rsa/";
  char dossier1[100];
  strcat(dossier,nomtmp);
  FILE * fichier =fopen(dossier,"w");
  strcpy(dossier1,dossier);
  strcpy(dossier,"rsa/");
  strcat(dossier,nom);
  FILE *fichier1 =fopen(dossier,"r");
  char *line_buf = NULL;
  char *line_buf1 = NULL;
  size_t line_buf_size = 0;
   if(fichier!=NULL && fichier1!=NULL)
   {
     while(getline(&line_buf, &line_buf_size, fichier1)>= 0 && getline(&line_buf1, &line_buf_size, fichier1)>=0) 
     {
      int test=0;
        for(int i=0;i<strlen(line_buf)-1;i++)
        {
          if(email[i]!=line_buf[i])
          {
             test=1;break;
         }
        }
        int test1=0;
        for(int j=0;j<strlen(line_buf1)-1;j++)
        {
          if(line_buf1[j]!=mdp[j])
          {
           	 test1=1;break;
          }
        }
      if(test==0 && test1==0)
      {
          fputs(line_buf,fichier);
          fputs(newmdp,fichier);
          fputs("\n",fichier);  
                 
      }
      else
      { 
          
          fputs(line_buf,fichier);
          fputs(line_buf1,fichier);       
      }
     }
     fclose(fichier);
     remove(dossier);
     rename(dossier1,dossier);
     return 0;
   }
   else
   {
    return ERR_ERCI;
   }
}
int  change_cle(informations * InfoUser,cle_publique * pub ,cle_prive * priv)
{

    char * chemin = malloc (sizeof(char)*(strlen("rsa/")+strlen(InfoUser->email)+strlen("/Cles.txt")+3));
    char * ligne = malloc (sizeof(char) * 2048);

    sprintf(chemin, "rsa/%s/Cles.txt", InfoUser->email);
    printf("%s", chemin);
    FILE * fichier = NULL;
    fichier = fopen(chemin, "w+");

    if(!fichier) 
        return ERR_ERCI;

    InfoUser->prive = *priv;
    InfoUser->publique = *pub;

    mpz_get_str(ligne, 10, InfoUser->prive.d);
    fprintf(fichier, "%s\n", ligne);
    mpz_get_str(ligne, 10, InfoUser->publique.e);
    fprintf(fichier, "%s\n", ligne);
    mpz_get_str(ligne, 10, InfoUser->publique.n);
    fprintf(fichier, "%s\n", ligne);



    free(chemin);
    free(ligne);
    fclose(fichier); 

    return 0;
}

int  ecrire_fichier(char *chemin , char *message)
{
     FILE * fichier ;
     fichier =fopen(chemin,"a+");
     if(fichier!=NULL)
     { 
              fputs(message,fichier);
              fputs("\n",fichier);
              fclose(fichier);
              return 0;
     }
     

      return ERR_ERCI;
     
}
int envoie_message(mail *m)
{
   cle_publique sender  ;  cle_prive receveur ;   mpz_inits(sender.e , sender.n, receveur.d , receveur.n ,NULL);
    printf (" mail 1  %s  mail2 %s " , m-> dest_email , m-> env_email);
     if (!recupere_cle_privee(m->dest_email,NULL,&receveur))
                        {
                          gmp_printf ("cle  d recup :%Zd\n" , receveur.d);
                          gmp_printf ("cle  n recup :%Zd\n" , receveur.n);
                        }
                     
      if (!recupere_cle_publique(m->env_email,NULL,&sender)){
                          gmp_printf ("cle  e recup :%Zd\n" , sender.e);
                          gmp_printf ("cle  n recup :%Zd\n" , sender.n);
        }

        //dechiffrer le message avec la cle prive du receveur 
        // pour ensuite le chiffrer avec la cle public de celui qui envoie (pour le stocker dans envoye comme cea il poura etre lu )
        message * msgcoder = malloc (sizeof(message));  mpz_inits (msgcoder->taille,msgcoder->nombre,NULL); 
        
        mpz_set_str(msgcoder->nombre,m->message,10);  

        mpz_set_ui (msgcoder->taille ,mpz_sizeinbase(msgcoder->nombre,2) );
        
        message * msgnoncoder=dechiffrement(msgcoder, &receveur);
        
        char * chaine_dans_envoie = malloc(sizeof(char*)*2100);
        
        chaine_dans_envoie =conversion_mpz_char(msgnoncoder);
        printf("chaine envoie clair %s\n",chaine_dans_envoie);
        //
        message *ch     = malloc (sizeof (message));
        message *codage = malloc (sizeof (message));
        message *ret = malloc (sizeof (message));
        mpz_inits (ch->taille , codage->taille , ch->nombre,codage->nombre,ret -> taille , ret -> nombre ,NULL);
        
        ch=conversion_char_mpz(chaine_dans_envoie); 
        codage=conversion_char_mpz("ASCII");
        mpz_set_ui (codage->taille , mpz_sizeinbase(codage->nombre,2));
         ret = chiffrement(ch, &sender , codage);
        free(chaine_dans_envoie); 
        chaine_dans_envoie = malloc(sizeof(char*)*2100);
        mpz_get_str(chaine_dans_envoie,0,ret->nombre);
         printf("chaine envoie chiff %s\n",chaine_dans_envoie);


        int res1,res2,res3,res4;
        if(m->signer ==0)
        {
          

              char *tmp =malloc(strlen(m->titre)*sizeof(char));
              strcpy(tmp,m->titre);
              strcat(tmp,":Nonsig");
              char *email=malloc((strlen(m->dest_email)+100)*sizeof(char));
              strcpy(email,"");

              strcat(email,m->dest_email);
              
            
              char *message=malloc((strlen(m->message)+300)*sizeof(char));
              strcpy(message,"");
              strcat(message,m->message);
              char *signature = NULL; 
              if (m-> signature == NULL)
              {
                char *signature=malloc(200*sizeof(char));
                strcpy(signature,"Signature Message : ");
              }
              else
              {
                signature=malloc((strlen(m->signature)+200)*sizeof(char));
                strcpy(signature,"Signature Message : ");
                strcat(signature,m->signature);
               }
            
              
              char *chemin=malloc(300*sizeof(char));
              strcpy(chemin,"rsa/");
              strcat(chemin,m->env_email);
             
              strcat(chemin,"/");
              strcat(chemin,"MessageEnvoyer.txt");
            
              res1=ecrire_fichier(chemin,tmp);
              res2=ecrire_fichier(chemin,email);
              res3=ecrire_fichier(chemin,chaine_dans_envoie);
              //res4=ecrire_fichier(chemin,signature);
              if(res1!=0 || res2!=0 || res3!=0 )
              {
                return ERR_ERCI;
              }
              free(chemin); 
              chemin=malloc(300*sizeof(char));
              strcpy(chemin,"rsa/");
              strcat(chemin,m->dest_email);
              strcat(chemin,"/");
              strcat(chemin,"MessageIndesirable.txt");
              printf(" %s  \n",chemin);
              res1=ecrire_fichier(chemin,tmp);
              strcpy(email,"");
              strcat(email,m->env_email);
              res2=ecrire_fichier(chemin,email);
              strcpy(message,"");
              strcat(message,m->message);
              res3=ecrire_fichier(chemin,message);
              //strcpy(signature,"Signature Message : ");
           // strcat(signature,m->signature);
            //res4=ecrire_fichier(chemin,signature);

              if(res1!=0 || res2!=0 || res3!=0  )
              {
                return ERR_ERCI;
              }

        return 0;
        }
       if(m->signer==1)
       {           
              char *tmp =malloc(strlen(m->titre)*sizeof(char));
              strcpy(tmp,m->titre);
              strcat(tmp,":sig");
             
              char *email=malloc((strlen(m->dest_email)+50)*sizeof(char));
              strcpy(email,"");
              strcat(email,m->dest_email);
              
              char *message=malloc((strlen(m->message)+200)*sizeof(char));
              strcpy(message,"");
              strcat(message,chaine_dans_envoie);
             
              char *chemin=malloc(300*sizeof(char));
              strcpy(chemin,"rsa/");
              strcat(chemin,m->env_email);
              strcat(chemin,"/");
              strcat(chemin,"MessageEnvoyer.txt");
              // printf ("hhhhchemin%shhhhhhhhhhh \n",chemin);
              char *signature = NULL; 
               if (m-> signature == NULL)
              {
                char *signature=malloc(200*sizeof(char));
                strcpy(signature,"Signature Message : ");
              }
              else
              {
                signature=malloc((strlen(m->signature)+200)*sizeof(char));
                strcpy(signature,"Signature Message : ");
                strcat(signature,m->signature);
               }
               printf ("hhhhhhh signature %s\n",signature);
              res1=ecrire_fichier(chemin,tmp);
              res2=ecrire_fichier(chemin,email);
              res3=ecrire_fichier(chemin,message);
              res4=ecrire_fichier(chemin,signature);
              //printf ("%d  %d   %d   %d ", res1 , res2 , res3 , res4);
              if(res1!=0 || res2!=0 || res3!=0 || res4 != 0)
              {
                return ERR_ERCI;
              }
              free(chemin);
              chemin=malloc(300*sizeof(char));
              strcpy(chemin,"rsa/");
              strcat(chemin,m->dest_email);
              strcat(chemin,"/");
              strcat(chemin,"MessageRecu.txt");
              res1=ecrire_fichier(chemin,tmp);
              strcpy(email,"");
              strcat(email,m->env_email);
              res2=ecrire_fichier(chemin,email);
              strcpy(message,"");
              strcat(message,m->message);
              res3=ecrire_fichier(chemin,message);
              res4=ecrire_fichier(chemin,signature);
              if(res1!=0 || res2!=0 || res3!=0 || res4 != 0)
              {
                return ERR_ERCI;
              }
              return 0;
       }
       return 0;
}
int  stocker_message(char *email , mpz_t  message , char *boite)
{   
   int res;
    char *str=malloc(1024*sizeof(char));
    mpz_get_str(str,10,message);//conversion_mpz_char
    char dossier[300];
    strcpy(dossier,"../../RSA-DataSafe/rsa/");
    strcat(dossier,email);
    strcat(dossier,"/");
    strcat(dossier,boite);
    res=ecrire_fichier(dossier,str);
    if(res!=0)
    {
      return ERR_ERCI;
    }
    
      return 0;
    
}

