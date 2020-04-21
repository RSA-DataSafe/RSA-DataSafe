#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <gmp.h>

#define ERR_LECT 100

#define ERR_ERCI 101

#define ERR_ID 102

#define ERR_EMAIL 103
 
typedef struct {
	mpz_t e;          
	mpz_t n;
} cle_publique;


typedef struct {
	mpz_t d;            
	mpz_t n;
} cle_prive;

typedef struct {
    char* email;            
    char* mdp;                 
    cle_prive prive;        
    cle_publique publique;  
                                    
} informations;
 char nom[]="test.txt";
int  nouvel_utilisateur(char *email , char *mdp)
{
	  static int nb=1;
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
   	 remove("test.txt");
   	 rename("test1.txt","test.txt");
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
   }

}
int  change_cle(informations * InfoUser)
{

}
int  stocker_message(char *email , mpz_t  message , char *boite)
{

}
int  ecrire_fichier(char *chemin , char *message)
{

}
