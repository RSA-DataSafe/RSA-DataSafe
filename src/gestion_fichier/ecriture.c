#include "ecriture.h"
char nom[]="test.txt";
int  nouvel_utilisateur(char *email , char *mdp)
{
       int taille= strlen(email);
       char *userfile1=malloc((taille+20)*sizeof(char));
       strcpy(userfile1,email);
       strcat(userfile1,"message.txt");
       FILE *userf1=fopen(userfile1,"w");
       char *userfile2=malloc((taille+20)*sizeof(char));
       strcpy(userfile2,email);
       strcat(userfile2,"cles.txt");
       FILE *userf2=fopen(userfile2,"w");      
       FILE *fichier=fopen(nom,"a");
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
  FILE * fichier =fopen(nomtmp,"w");
  FILE *fichier1 =fopen(nom,"r");
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
     remove("test.txt");
     rename("test1.txt","test.txt");
     char *old =malloc((strlen(email)+20)*sizeof(char));
     strcpy(old,email);
     strcat(old,"message.txt");
     char *new=malloc((strlen(email)+20)*sizeof(char));
     strcpy(new,newemail);
     strcat(new,"message.txt");
     rename(old,new);
     strcpy(old,email);
     strcat(old,"cles.txt");
     strcpy(new,newemail);
     strcat(new,"cles.txt");
     rename(old,new);
     return 0;
   }
   else
   {
    return ERR_ERCI;
   }  
}
int  Change_MotDePasse (char*email , char *mdp , char* newmdp)
{
  char nomtmp[]="test1.txt";
  FILE * fichier =fopen(nomtmp,"w");
  FILE *fichier1 =fopen(nom,"r");
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
     remove("test.txt");
     rename("test1.txt","test.txt");
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
  char *email=malloc((strlen(InfoUser->email) +20)*sizeof(char));
  strcpy(email,InfoUser->email);
  strcat(email,"cles.txt");
  FILE *fichier=fopen(email,"w");
  if(fichier!=NULL)
  {
  char *d =malloc(1024*sizeof(char));
  char *e =malloc(1024*sizeof(char));
  char *n =malloc(1024*sizeof(char));
  mpz_get_str(d,10,InfoUser->prive.d);
  mpz_get_str(e,10,InfoUser->publique.e);
  mpz_get_str(n,10,InfoUser->publique.n);
 ecrire_fichier(email,d);
 ecrire_fichier(email,e);
 ecrire_fichier(email,n);
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
