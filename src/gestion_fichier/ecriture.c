#include "ecriture.h"
char nom[]="connexion.txt";
int  nouvel_utilisateur(char *email , char *mdp)
{
       int taille= strlen(email);
       char *userfile1=malloc((taille+20)*sizeof(char));
       strcpy(userfile1,"MessageRecu.txt");
       char ch1[200]="../../RSA-DataSafe/rsa/";
       char dossier[300];
       strcpy(dossier,ch1);
       strcat(dossier,email);
       mkdir(dossier,S_IRWXU);
       strcat(dossier,"/");
       char dossier1[300];
       strcpy(dossier1,dossier);
       strcat(dossier,userfile1);
       int res1;int res2;
       FILE *userf1=fopen(dossier,"a+");
       if(userf1!=NULL)
       {
        fclose(userf1);
       }
       else
       {
        printf("Erreur de création d fichier\n");
       }
       char *userfile2=malloc((taille+20)*sizeof(char));
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
       if(userf2!=NULL)
       {
        fclose(userf2);
       }
       else
       {
        printf("Erreur  de création du fichier\n");
       }
       strcpy(userfile2,"MessageIndesirable.txt");
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
       char cm[200]="../../RSA-DataSafe/rsa/";
       strcat(cm,nom);
       FILE *fichier=fopen(cm,"a");
       char ligne [300]; 
      if(fichier!=NULL)
       {
      while(fgets (ligne, sizeof ligne,fichier ) != NULL && strcmp(ligne,"")!=0) ;
      res1=ecrire_fichier(cm,email);
      res2=ecrire_fichier(cm,mdp);
      if(res1!=0||res2!=0)
      {
        return ERR_ERCI;
      }
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
            break;    
      }
      else
      {
          int taille=strlen(line_buf)-1;
          if(line_buf[taille]=='\n') line_buf[taille]='\0';
          taille=strlen(line_buf1)-1;
          if(line_buf1[taille]=='\n') line_buf1[taille]='\0';
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
          break;         
      }
      else
      { 
           int taille=strlen(line_buf)-1;
          if(line_buf[taille]=='\n') line_buf[taille]='\0';
          taille=strlen(line_buf1)-1;
          if(line_buf1[taille]=='\n') line_buf1[taille]='\0';
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
  char dossier[200];
  strcpy(dossier,"../../RSA-DataSafe/rsa/");
  strcat(dossier,InfoUser->email);
  strcat(dossier,"/");
  strcat(dossier,"Cles.txt");
  char tmp[200];
  strcpy(tmp,"../../RSA-DataSafe/rsa/");
  strcat(tmp,InfoUser->email);
  strcat(tmp,"/Cles1.txt");
  FILE *fichier=fopen(dossier,"r");
  FILE * clefile=fopen(tmp,"a+");  
  char *d =malloc(2048*sizeof(char));
  char *e =malloc(2048*sizeof(char));
  char *n =malloc(2048*sizeof(char));
  mpz_get_str(d,10,InfoUser->prive.d);
  mpz_get_str(e,10,InfoUser->publique.e);
  mpz_get_str(n,10,InfoUser->publique.n);
  char *d1 =malloc(2048*sizeof(char));
  char *e1 =malloc(2048*sizeof(char));
  char *n1 =malloc(2048*sizeof(char));
  mpz_get_str(d1,10,priv->d);
  mpz_get_str(e1,10,pub->e);
  mpz_get_str(n1,10,pub->n);
  char *line_buf = NULL;
  char *line_buf1 = NULL;
  char *line_buf2 =NULL;
  size_t line_buf_size = 0;
  int res1,res2,res3;
  if(fichier!=NULL && clefile!=NULL)
  {
    while(getline(&line_buf, &line_buf_size, fichier)>=0 && getline(&line_buf1, &line_buf_size, fichier)>=0 && 
      getline(&line_buf2,&line_buf_size,fichier)>=0)
       {
        int test=0;
        for(int i=0;i<strlen(line_buf)-1;i++)
        {
          if(d[i]!=line_buf[i])
          {
             test=1;break;
         }
        }
        int test1=0;
        for(int j=0;j<strlen(line_buf1)-1;j++)
        {
          if(line_buf1[j]!=e[j])
            test1=1;break;
        }
        int test2=0;
        for(int j=0;j<strlen(line_buf2)-1;j++)
        {
          if(line_buf2[j]!=n[j])
            test2=1;break;
        }
          if(test==0 && test1==0 && test2==0)
          { 
              res1=ecrire_fichier(tmp,d1);
              res2=ecrire_fichier(tmp,e1);
              res3=ecrire_fichier(tmp,n1);
              mpz_set(InfoUser->prive.d,priv->d);
              mpz_set(InfoUser->prive.n,priv->n);
              mpz_set(InfoUser->publique.e,pub->e);
              mpz_set(InfoUser->publique.n,pub->n);
              if(res1!=0 || res2!=0 || res3!=0)
              {
                return ERR_ERCI;
              }
              break;
          } 
          else
          { 
            int taille=strlen(line_buf)-1;
            if(line_buf[taille]=='\n')
            {
              line_buf[taille]='\0';
            }
            taille=strlen(line_buf1)-1;
            if(line_buf1[taille]=='\n')
            {
              line_buf1[taille]='\0';
            }
             taille=strlen(line_buf2)-1;
            if(line_buf2[taille]=='\n')
            {
              line_buf2[taille]='\0';
            }
             res1=ecrire_fichier(tmp,line_buf);
             res2=ecrire_fichier(tmp,line_buf1);
             res3=ecrire_fichier(tmp,line_buf2);
             if(res1!=0 || res2!=0 || res3!=0)
             {
              return ERR_ERCI;
             }
          }       
       }
  fclose(fichier);
  fclose(clefile);
  remove(dossier);
  rename(tmp,dossier); 
   return 0;
  }
else
{
  return ERR_ERCI;
}}

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
     else
     {

      return ERR_ERCI;
     }
}
int envoie_message(mail *m)
{
        int res1,res2,res3,res4;
        if(m->signer ==1)
        {
              char *tmp =malloc(strlen(m->titre)*sizeof(char));
              strcpy(tmp,m->titre);
              strcat(tmp,":sig");
              char *email=malloc((strlen(m->dest_email)+50)*sizeof(char));
              strcpy(email,"Email:");
              strcat(email,m->dest_email);
              char *message=malloc((strlen(m->message)+200)*sizeof(char));
              strcpy(message,"Message Envoyé:");
              strcat(message,m->message);
              char *signature=malloc((strlen(m->signature)+200)*sizeof(char));
              strcpy(signature,"Signature Message:");
              strcat(signature,m->signature);
              char *chemin=malloc(500*sizeof(char));
              strcpy(chemin,"../../RSA-DataSafe/rsa/");
              strcat(chemin,m->env_email);
              strcat(chemin,"/");
              strcat(chemin,"MessageEnvoyer.txt");
              res1=ecrire_fichier(chemin,tmp);
              res2=ecrire_fichier(chemin,email);
              res3=ecrire_fichier(chemin,message);
              res4=ecrire_fichier(chemin,signature);
              if(res1!=0 || res2!=0 || res3!=0 || res4!=0)
              {
                return ERR_ERCI;
              }
              strcpy(chemin,"../../RSA-DataSafe/rsa/");
              strcat(chemin,m->dest_email);
              strcat(chemin,"/");
              strcat(chemin,"MessageIndesirable.txt");
              res1=ecrire_fichier(chemin,tmp);
              strcpy(email,"Email:");
              strcat(email,m->env_email);
              res2=ecrire_fichier(chemin,email);
              strcpy(message,"Message Recu:");
              strcat(message,m->message);
              res3=ecrire_fichier(chemin,message);
              strcpy(signature,"Signature Message:");
              strcat(signature,m->signature);
              res4=ecrire_fichier(chemin,signature);
              if(res1!=0 || res2!=0 || res3!=0 || res4!=0)
              {
                return ERR_ERCI;
              }

        return 0;
        }
       if(m->signer==0)
       {           
              char *tmp =malloc(strlen(m->titre)*sizeof(char));
              strcpy(tmp,m->titre);
              strcat(tmp,":Nonsig");
              char *email=malloc((strlen(m->dest_email)+50)*sizeof(char));
              strcpy(email,"Email:");
              strcat(email,m->dest_email);
              char *message=malloc((strlen(m->message)+200)*sizeof(char));
              strcpy(message,"Message Envoyé:");
              strcat(message,m->message);
              char *chemin=malloc(500*sizeof(char));
              strcpy(chemin,"../../RSA-DataSafe/rsa/");
              strcat(chemin,m->env_email);
              strcat(chemin,"/");
              strcat(chemin,"MessageEnvoyer.txt");
              res1=ecrire_fichier(chemin,tmp);
              res2=ecrire_fichier(chemin,email);
              res3=ecrire_fichier(chemin,message);
              if(res1!=0 || res2!=0 || res3!=0)
              {
                return ERR_ERCI;
              }
              strcpy(chemin,"../../RSA-DataSafe/rsa/");
              strcat(chemin,m->dest_email);
              strcat(chemin,"/");
              strcat(chemin,"MessageInvisible.txt");
              res1=ecrire_fichier(chemin,tmp);
              strcpy(email,"Email:");
              strcat(email,m->env_email);
              res2=ecrire_fichier(chemin,email);
              strcpy(message,"Message Recu:");
              strcat(message,m->message);
              res3=ecrire_fichier(chemin,message);
              if(res1!=0 || res2!=0 || res3!=0)
              {
                return ERR_ERCI;
              }
              return 0;
       }
       return 0;
}
int  stocker_message(char *email , mpz_t  messag , char *boite)
{   
   int res;
    char *str=malloc(1024*sizeof(char));
    message ms;
   mpz_init(ms.nombre);
   mpz_init(ms.taille);
   mpz_set(ms.nombre,messag);
   mpz_out_str(0,10,ms.nombre);
   size_t taille=  mpz_sizeinbase(ms.nombre,2);
   mpz_set_ui(ms.taille,taille);
   strcpy(str,conversion_mpz_char(&ms));
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
