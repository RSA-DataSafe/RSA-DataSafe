#include <gmp.h>
#include <stdlib.h>

#include "../structure/structure.h"
#include "../calcul/calcul.h"
#include "gestion_block.h"

#define TAILLE_SHA3_256 256

void extraction(mpz_t x, mpz_t y, mpz_t b) {
    // Init
    mpz_t tmp;
    mpz_init(tmp);
    
    // Code
    mpz_set(x, b);
    shift_droite(x, TAILLE_SHA3_256);

    mpz_set(y, b);
    mpz_set_ui(tmp, 1);
    shift_gauche(tmp, TAILLE_SHA3_256);
    mpz_sub_ui(tmp, tmp, 1);
    mpz_and(y, y, tmp);

    // Clear
    mpz_clear(tmp);
}

block *creer_block_oaep(message *m,message *encodage , mpz_t donnee_alea) {
    //block's number 
    mpz_t nb_block;
    mpz_init(nb_block);

    mpz_div_ui(nb_block, m->taille, 1536);

    mpz_t rest;
    mpz_init(rest);
    mpz_mod_ui(rest, m->taille, 1536);
    if (mpz_cmp_ui(rest, 0) != 0) {
        mpz_add_ui(nb_block, nb_block, 1);
        int i_rest = mpz_get_ui(rest);
        int zero_adding = 1536- i_rest;
        mpz_mul_2exp(m->nombre,m->nombre,zero_adding);
    } 

    int i_block = mpz_get_ui(nb_block);
    

    block *b = malloc(sizeof(block));
    b->nb_block = i_block;
    
    mpz_t tmp;
    mpz_init(tmp);

    b->tab = malloc(sizeof(mpz_t) * i_block);
    for(int i = 0; i < i_block; i++) {
        mpz_init(b->tab[i]);
        mpz_tdiv_q_2exp(tmp,m->nombre, (i_block-i)*1536);
        // Calcul 2^1536-1
        mpz_t base;
      	mpz_init(base);   
        mpz_add_ui(base,base, 2);
        mpz_pow_ui(base,base,1536);  
        mpz_sub_ui(base,base, 1);  
        mpz_and(b->tab[i],base,tmp);        
    }
       
        //Reverse the table
        mpz_t array[i_block];
        int y=i_block-1;  
    for(int z=0; z<i_block; z++){
    	mpz_init_set(array[z],b->tab[y]);
    	y--;
    	}
    	
    	
    	//encodage+donne_alea
     for (int k = 0; k<i_block; k++) {
        mpz_mul_2exp(b->tab[k],array[k],256);
		mpz_and(b->tab[k],array[k],encodage->nombre);
        mpz_mul_2exp(b->tab[k],array[k],256);
        mpz_and(b->tab[k],array[k],donnee_alea);
  }    
       
    	
   
    // Clear
    mpz_clears(nb_block,rest,array,NULL);
    
    return b;
    
}



message *recupere_message_oaep(block *b){
    
    //taille du message 
    mpz_t message_lenght;
    mpz_init(message_lenght);
    
    int taille_m =b->nb_block * 2048 ;
    mpz_add_ui(message_lenght,message_lenght,taille_m );
    
    message *m  = malloc(sizeof(message));
    mpz_init(m->taille);
    mpz_set(m->taille,message_lenght);
    
    mpz_init(m->nombre);
    mpz_set(m->nombre,b->tab[0]);
    
    for(int i = 1; i < b->nb_block; i++){
         mpz_mul_2exp(m->nombre,m->nombre,2048);
         mpz_ior(m->nombre,m->nombre,b->tab[i]);   
    } 
    
    // Clear
    mpz_clear(message_lenght);
    
    return m;
    
}
    
