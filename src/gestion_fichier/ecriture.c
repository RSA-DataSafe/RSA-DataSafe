#include "ecriture.h"
char nom[]="test.txt";
int  nouvel_utilisateur(char *email , char *mdp)
{
       int taille= strlen(email);
       char *userfile1=malloc((taille+20)*sizeof(char));
       strcpy(userfile1,email);
       strcat(userfile1,"message.txt");
       char ch1[200]="../../RSA-DataSafe/rsa/";
       char dossier[300];
       strcpy(dossier,ch1);
       strcat(dossier,email);
       mkdir(dossier,S_IRWXU);
       strcat(dossier,"/");
       char dossier1[300];
       strcpy(dossier1,dossier);
       strcat(dossier,userfile1);
       FILE *userf1=fopen(dossier,"w");
       if(userf1!=NULL)
       {
        fclose(userf1);
       }
       else
       {
        printf("Erreur de création d fichier\n");
       }
       char *userfile2=malloc((taille+20)*sizeof(char));
       strcpy(userfile2,email);
       strcat(userfile2,"cles.txt");
       strcat(dossier1,userfile2);
       FILE *userf2=fopen(dossier1,"w");
       if(userf2!=NULL)
       {
        fclose(userf2);
       }  
       else
       {
        printf("Erreur de création d fichier\n");
       }
       char cm[200]="../../RSA-DataSafe/rsa/";
      strcat(cm,nom);
       FILE *fichier=fopen(cm,"a");
       char ligne [300]; 
       char *line_buf = NULL;
       if(fichier!=NULL)
       {
      while(fgets (ligne, sizeof ligne,fichier ) != NULL && ligne !="") ;
      fputs(email, fichier);
      fputs("\n",fichier);
      fputs(mdp,fichier);
      fputs("\n",fichier);
      fclose ( fichier );
      return 0;
       }
       else
       {
          return ERR_ERCI;
       }

}
int  Change_Email(char *email , char *mdp , char *newemail)
{
  char nomtmp[]="test1.txt";
  char dossier[300]="../../RSA-DataSafe/rsa/";
  char dossier1[300]="../../RSA-DataSafe/rsa/";
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
             test=1;break;
         }
        }
        int test1=0;
        for(int j=0;j<strlen(line_buf1)-1;j++)
        {
          if(line_buf1[j]!=mdp[j])
            test1=1;break;
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
     strcpy(dossier,"../../RSA-DataSafe/rsa/");
     strcat(dossier,email);
     strcat(dossier,"/");
     strcat(dossier,email);
     strcat(dossier,"message.txt");
     strcpy(dossier1,"../../RSA-DataSafe/rsa/");
     strcat(dossier1,email);
     strcat(dossier1,"/");
     strcat(dossier1,newemail);
     strcat(dossier1,"message.txt");
     rename(dossier,dossier1);
     strcpy(dossier,"../../RSA-DataSafe/rsa/");
     strcat(dossier,email);
     strcat(dossier,"/");
     strcat(dossier,email);
     strcat(dossier,"cles.txt");
     strcpy(dossier1,"../../RSA-DataSafe/rsa/");
     strcat(dossier1,email);
     strcat(dossier1,"/");
     strcat(dossier1,newemail);
     strcat(dossier1,"cles.txt");
     rename(dossier,dossier1);
     strcpy(dossier,"../../RSA-DataSafe/rsa/");
     strcat(dossier,email);
     strcpy(dossier1,"../../RSA-DataSafe/rsa/");
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
  char dossier[100]="../../RSA-DataSafe/rsa/";
  char dossier1[100];
  strcat(dossier,nomtmp);
  FILE * fichier =fopen(dossier,"w");
  strcpy(dossier1,dossier);
  strcpy(dossier,"../../RSA-DataSafe/rsa/");
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
            test1=1;break;
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
int  change_cle(informations * InfoUser)
{
  mpz_set_ui(InfoUser->prive.d,213);//on va les remplcaer après avec l vrai clée
  mpz_set_ui(InfoUser->prive.n,214);
  mpz_set_ui(InfoUser->publique.e,547);
  mpz_set_ui(InfoUser->publique.n,214);
  char dossier[200];
  strcpy(dossier,"../../RSA-DataSafe/rsa/");
  strcat(dossier,InfoUser->email);
  strcat(dossier,"/");
  strcat(dossier,InfoUser->email);
  strcat(dossier,"cles.txt");
  FILE *fichier=fopen(dossier,"w");
  if(fichier!=NULL)
  {
  char *d =malloc(1024*sizeof(char));
  char *e =malloc(1024*sizeof(char));
  char *n =malloc(1024*sizeof(char));
  mpz_get_str(d,10,InfoUser->prive.d);
  mpz_get_str(e,10,InfoUser->publique.e);
  mpz_get_str(n,10,InfoUser->publique.n);
 ecrire_fichier(dossier,d);
 ecrire_fichier(dossier,e);
 ecrire_fichier(dossier,n);
  fclose(fichier);
  return 0;
}
else
{
  return ERR_ERCI;
}

}
int  stocker_message(char *email , mpz_t  message , char *boite)
{
    
}
int  ecrire_fichier(char *chemin , char *message)
{
     FILE * fichier ;
     fichier =fopen(chemin,"a");
     if(fichier!=NULL)
     {
             
              fputs(message,fichier);
              fputs("\n",fichier);
              fclose(fichier);
              return 0;
     }
     else
     {
      return ERR_ERCI;
     }
}
