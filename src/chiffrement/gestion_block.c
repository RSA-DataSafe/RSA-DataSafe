#include <gmp.h>
#include <stdlib.h>
#include <stdio.h>

#include "../structure/structure.h"
#include "../calcul/calcul.h"
#include "gestion_block.h"

#define TAILLE_SHA3_256 256

void extraction(mpz_t x, mpz_t y, mpz_t b) {
    // Init
    mpz_t tmp;                                  // variable temporaire
    mpz_init(tmp);
    
    // Code
    mpz_set(x, b);                              // x = b
    shift_droite(x, TAILLE_SHA3_256);           // x >>= 256 (pour récupere la partie droite du bloc)

    mpz_set(y, b);                              // y = b
    mpz_set_ui(tmp, 1);                         // tmp = 1
    shift_gauche(tmp, TAILLE_SHA3_256);         // tmp = 1 << 256
    mpz_sub_ui(tmp, tmp, 1);                    // tmp = 1 << 256 - 1 (un nombre en binaire avec 256 1)
    mpz_and(y, y, tmp);                         // on extrait les 256 dernier bits

    // Clear
    mpz_clear(tmp);                             // on libère la mémoire
}

block *creer_block_oaep(message *m,message *encodage, mpz_t donnee_alea) {
    //block's number 
    mpz_t nb_block;
    mpz_init(nb_block);

    mpz_div_ui(nb_block, m->taille, 1528);

    mpz_t rest;
    mpz_init(rest);
    mpz_mod_ui(rest, m->taille, 1528);
    if (mpz_cmp_ui(rest, 0) != 0) {
        mpz_add_ui(nb_block, nb_block, 1);
        int i_rest = mpz_get_ui(rest);
        int zero_adding = 1528 - i_rest;
        mpz_mul_2exp(m->nombre,m->nombre,zero_adding);
        mpz_add_ui(m->taille, m->taille,zero_adding);
       

    } 

    int i_block = mpz_get_ui(nb_block);
    int i_taille = mpz_get_ui(m->taille);

    block *b = malloc(sizeof(block));
    b->nb_block = i_block;
    
    mpz_t tmp;
    mpz_init(tmp);

    b->tab = malloc(sizeof(mpz_t) * i_block);
   for(int i = 0; i < i_block; i++) {
        mpz_init(b->tab[i]);
        mpz_tdiv_q_2exp(b->tab[i],m->nombre,i_taille-((i+1)*1528));
         
        // Calcul 2^1528-1
        mpz_t base;
      	mpz_init(base);   
        mpz_add_ui(base,base, 2);
        mpz_pow_ui(base,base,1528);  
        mpz_sub_ui(base,base, 1);  
        mpz_and(b->tab[i],base,b->tab[i]); 
        
   }
  
       
       
    	
    	//encodage+donne_alea
    for (int k = 0; k<i_block; k++) {
        mpz_mul_2exp(b->tab[k],b->tab[k],256);
	mpz_add(b->tab[k],b->tab[k],encodage->nombre);
        mpz_mul_2exp(b->tab[k],b->tab[k],256);
        mpz_add(b->tab[k],b->tab[k],donnee_alea);
  }    
       
    	
   
    // Clear
    mpz_clears(nb_block,rest,tmp,NULL);
    
    return b;
    
}
  
       
    	

block *creer_block_oaep_1(message *m) {

    mpz_t nb_block;
    mpz_init(nb_block);
    mpz_div_ui(nb_block, m->taille, 2048);
    if(mpz_cmp_ui(nb_block,0)==0)
    	mpz_add_ui(nb_block, nb_block, 1);

    block *b = malloc(sizeof(block));
    
    int int_nb_block = mpz_get_ui(nb_block);
    b->nb_block = int_nb_block;
    b->tab = malloc(sizeof(mpz_t) * int_nb_block);

    mpz_t AND;
    mpz_init(AND);
    mpz_set_ui(AND, 1);
    shift_gauche(AND, 2048);
    mpz_sub_ui(AND, AND, 1);

    for (int i = 0; i < int_nb_block; i++)
    {
        mpz_init(b->tab[i]);
        mpz_set(b->tab[i], m->nombre);
        shift_droite(b->tab[i], 2048 * ( int_nb_block - (i + 1) ) );
        mpz_and(b->tab[i], b->tab[i], AND);
    }
    
    return b;
}

message *recupere_message_oaep(block *b){
    
    //taille du message 
    mpz_t message_lenght;
    mpz_init(message_lenght);
    
    int taille_m =b->nb_block * 2048 ;                      // calcul la taille du message
    mpz_add_ui(message_lenght,message_lenght,taille_m );    // affecte la taille du message
    
    message *m  = malloc(sizeof(message));                  // initialisation du message
    mpz_init(m->taille);
    mpz_set(m->taille,message_lenght);
    
    mpz_init(m->nombre);
    mpz_set(m->nombre,b->tab[0]);                           // on concatène le premier bloc
    
    for(int i = 1; i < b->nb_block; i++){
         mpz_mul_2exp(m->nombre,m->nombre,2048);            // on décale de 2048 qui est la taille des bloc
         mpz_ior(m->nombre,m->nombre,b->tab[i]);            // on concatène le bloc i
    } 
    
    // Clear
    mpz_clear(message_lenght);
    
    return m;
    
}
    
message *recupere_message_oaep_1(block *b) {
 
    message *m  = malloc(sizeof(message));                  // initialisation du message
    mpz_init(m->nombre);
    mpz_init(m->taille);
    mpz_set_ui(m->taille, 1528);                            // taille du message clair dans un bloc = 1528 bit
    mpz_mul_ui(m->taille, m->taille, b->nb_block);          // calcul de la taille du message

    for (int i = 0; i < b->nb_block; i++)
    {
        shift_gauche(m->nombre, 1528);                      // on décale de la taille du message clair dans un bloc
        shift_droite(b->tab[i], 512);                       // on décale de 512 bit à droite pour retirer l'encodage et la donné aléatoire
        mpz_add(m->nombre, m->nombre, b->tab[i]);           // on concatène le block
    }

    return m;
}
