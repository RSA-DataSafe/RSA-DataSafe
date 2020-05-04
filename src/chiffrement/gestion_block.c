#include <gmp.h>
#include <stdlib.h>

#include "../structure/structure.h"
#include "gestion_block.h"

void creer_block_oaep(message *m,message *encodage,mpz_t donnee_alea){
	
	
	  int bloc_lenght=1536; 
    int size_array;
    int zero_adding;
    
    
    if(mpz_sizeinbase(m->nombre,2)%bloc_lenght == 0){
        size_array = mpz_sizeinbase(m->nombre,2)/(bloc_lenght);
        zero_adding = 0;
	}
	
	else{
        size_array = (mpz_sizeinbase(m->nombre,2)/(bloc_lenght)) +1;
        zero_adding = (bloc_lenght)- (mpz_sizeinbase(m->nombre,2) % bloc_lenght);
	}
	mpz_mul_2exp(m->nombre,m->nombre,zero_adding);//inital message completed with 00
    
    
    int size = mpz_sizeinbase(m->nombre,2)/(bloc_lenght);
    mpz_t tmp;
  	mpz_init(tmp);
	  mpz_t array[size];
	
	//Split into blocs of 1536
	for (int i = 0; i < size ; i++) {
        mpz_init(array[i]);
        mpz_add_ui(array[i],array[i],1);
        mpz_mul_2exp(array[i],array[i],bloc_lenght-1);
        mpz_tdiv_r_2exp(tmp, m->nombre,bloc_lenght-1);
		
    mpz_ior(array[i], array[i],tmp);
        mpz_tdiv_q_2exp(m->nombre, m->nombre, bloc_lenght-1);
  
  }
	
	//Reverse the table
     	mpz_t close[size_array];
        int y=size-1;  
    for(int z=0; z<size_array; z++){
    	mpz_init_set(close[z], array[y]);
    	y--;
    	}
	
	
       
       //encodage+donne_alea
     for (int k = 0; k < size ; k++) {
        mpz_mul_2exp(close[k],close[k],256);
		mpz_ior(close[k], close[k],encodage->nombre);
        mpz_mul_2exp(close[k],close[k],256);
        mpz_ior(close[k], close[k],donnee_alea);
  }    
       
       
  mpz_clears(tmp,close,array, NULL);
}
