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
}
