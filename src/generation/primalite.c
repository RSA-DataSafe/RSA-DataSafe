/*#include <gmp.h>
#include <time.h>
#include "primalite.h"
int temoin_de_miller(mpz_t a, mpz_t n){
	mpz_t d, t,res;
	mpz_inits(t,d,res, NULL);
	mpz_sub_ui(d, n, 1);
	int s=0;
	int i=1;
	
	while(i){
		
		mpz_mod_ui(t, d, 2);
		
		if (mpz_sgn(t) == 0 ){
			++s;
			
			mpz_cdiv_q_ui(d, d, 2);
		}
		
		else
			i=0;
	}
	
	expo_mod(res,a,d,n);
	mpz_sub_ui(t, n, 1);
	if ((mpz_cmp_d(res, 1) == 0) || (mpz_cmp(res, t) == 0)) {
		mpz_clears(t, d, res ,NULL);
		return 1;
	}
	
	while(i<s){
		
		mpz_mul(res,res,res);
		mpz_mod(res, res, n);
		if (mpz_cmp(res, t) == 0){
			mpz_clears(t, d , res, NULL);
			return 1;
		}

		i++;
	}
	
	mpz_clears(t, d , res, NULL);
	//temoin de miller donc non premier
	return 0;
}

int miller_rabbin(mpz_t n, mpz_t tour){
	//1 et 2 sont premier
	if(mpz_cmp_d(n, 1) == 0 || mpz_cmp_d(n, 2) == 0)
		return 1;
		
	//graine aléatoire 
	gmp_randstate_t state;
	gmp_randinit_default (state);
	gmp_randseed_ui(state,(unsigned)time(NULL));

	mpz_t t,rand;
	mpz_inits(rand,t , NULL);
	
	// car on va jusque n-1 et aussi parsq on rajoute 2 pour avoir une valeur > 1
	mpz_sub_ui(t, n, 4);
	
	//nombre de tour 
	while (mpz_cmp_ui(tour ,0)>0){
		// rand aléatoire dans l'intervalle [0, n – 4]
		mpz_urandomm (rand, state, t);
		
		// rand aléatoire  1 < a < n-1 donc [2 , n-2]
		mpz_add_ui(rand, rand, 2);				

		if (temoin_de_miller(rand, n)==0){
			mpz_clears(t,rand , NULL);
			//composé
			return 0;
		}
		mpz_sub_ui(tour,tour,1);
	}

	mpz_clears(t, rand, NULL);
	
	//probablement premier 
	return 1;
}*/


#include <gmp.h>
#include <time.h>
#include "primalite.h"
int temoin_de_miller(mpz_t a, mpz_t n){

    mpz_t d;
	mpz_init(d);
	mpz_sub_ui(d, n, 1);
	
	mpz_t tmp;
	mpz_init(tmp);
	
	mpz_t nbr;
	mpz_init(nbr);
	
	mpz_t deux;
	mpz_init(deux);
	mpz_set_ui(deux, 2);
	
	mpz_powm_ui(tmp, d, 1, deux);
	
  while(mpz_cmp_ui(tmp, 0) == 0 ) {
    mpz_div_ui(d, d, 2);
    mpz_add_ui(nbr, nbr, 1);
    mpz_powm_ui(tmp, d, 1, deux);
	}
	
	mpz_set(d, nbr);
	
	mpz_t n_1;
	mpz_init(n_1);
	mpz_sub_ui(n_1, n, 1);
	
	mpz_t s;
	mpz_init(s);
	mpz_div(s, n_1, d);
	
	// 2
	mpz_t x;
	mpz_init(x);
	mpz_powm(x, a, s, n);
	
	if(mpz_cmp_ui(x, 1) == 0 || mpz_cmp(x, n_1) == 0) {
		mpz_clear(d);
		mpz_clear(x);
		mpz_clear(n_1);
		mpz_clear(nbr);
		mpz_clear(s);
		mpz_clear(tmp);
		return 0;
	}
	
	mpz_t i;
  mpz_init(i);
  
  mpz_sub_ui(d, d, 1);
  
  for(mpz_set_ui(i, 0); mpz_cmp(i, d) < 0; mpz_add_ui(i, i, 1)) {
		mpz_powm_ui(x, x, 2, n);
		
		if(mpz_cmp(x, n_1) == 0) {
			mpz_clear(i);
			mpz_clear(d);
			mpz_clear(x);
			mpz_clear(n_1);
			mpz_clear(nbr);
			mpz_clear(s);
			mpz_clear(tmp);
			return 0;
		}
	}
	
	mpz_clear(i);
	mpz_clear(d);
	mpz_clear(x);
	mpz_clear(n_1);
	mpz_clear(nbr);
	mpz_clear(s);
	mpz_clear(tmp);
	
	return 1;


}

int miller_rabbin(mpz_t n, mpz_t tour){
      
   
	// n = 2 ou n = 3
	if(mpz_cmp_ui(n, 2) < 0)
		return 0; 
  if(mpz_cmp_ui(n, 4) < 0)
		return 1; 
	
	// n pair
	mpz_t deux;
	mpz_init(deux);
	mpz_set_ui(deux, 2);
	
	mpz_t res;
	mpz_init(res);
	mpz_powm_ui(res, n, 1, deux);
	
	if( mpz_cmp_ui(res, 0) == 0 ) {
		mpz_clear(deux);
		mpz_clear(res);
		return 0;
	}
	
	mpz_t i;
  mpz_init(i);
  gmp_randstate_t s;
	gmp_randinit_default(s);
	gmp_randseed_ui(s, clock());
	
	mpz_t a;
	mpz_init(a);
	
	mpz_t n_4;
	mpz_init(n_4);
	mpz_sub_ui(n_4, n, 4);
	
	for(mpz_set_ui(i, 0); mpz_cmp(i, tour) < 0; mpz_add_ui(i, i, 1)) {
		
		mpz_urandomm(a, s, n_4);
		mpz_add_ui(a, a, 2);
		
		if(temoin_de_miller(a, n)) {
			mpz_clear(deux);
			mpz_clear(res);
			mpz_clear(n_4);
			mpz_clear(a);
			mpz_clear(i);
			return 0;
		}
	}
	
	mpz_clear(deux);
	mpz_clear(res);
	mpz_clear(n_4);
	mpz_clear(a);
	mpz_clear(i);
	return 1;

}
