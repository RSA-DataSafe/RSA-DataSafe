
//eponentiation modulaire 
void square_and_multiply(mpz_t res, mpz_t num, mpz_t exp, mpz_t mod){
    
    // taille de l'eposant "exp" en nombre de bit
    int j=mpz_sizeinbase(exp,2);
    
    //on commence à partir de l'indice 0 et pour le premier bit on liste le nombre simplement
    j=j-2;
    mpz_set(res, num);
    
    for(int i=j; i>=0; i--){
        // si bit à 0 square
        mpz_mul(res,res,res);
        mpz_mod(res,res,mod);
		// si bit à 1 mutiply en plus du square 
        if( mpz_tstbit(exp, i) == 1 ) { 
            mpz_mul(res,res, num);
            mpz_mod(res,res,mod);
		}
    }
}
int temoin_miller(mpz_t a, mpz_t n){
	//calculer s et d tels que n - 1 = (2^s).d avec d impair 
	mpz_t d, tp,res;
	mpz_inits(tp,d,res, NULL);
	mpz_sub_ui(d, n, 1);
	int s=0;
	int i=1;
	
	while(i){
		//tmp=d mod 2
		mpz_mod_ui(tp, d, 2);
		//si tmp pair donc tmp=0 
		if (mpz_sgn(tp) == 0 ){
			++s;
			// d=d/2
			mpz_cdiv_q_ui(d, d, 2);
		}
		//si tmp impaire on sort de la boucle on a trouvé d
		else
			i=0;
	}

	// res= a^d mod n 
	square_and_multiply(res, a, d, n);
	
	//tmp=n-1
	mpz_sub_ui(tp, n, 1);
	
	// si res==1 ou res==n-1  alors pas temoin de miller 
	if ((mpz_cmp_d(res, 1) == 0) || (mpz_cmp(res, tp) == 0)) {
		mpz_clears(tp, d, res ,NULL);
		return 1;
	}
	
	//sinon on continu en incremetant i dans res = res(2^s i).d
	while(i<s){
		//res= res^2 
		mpz_mul(res,res,res);
		
		//res=res mod n
		mpz_mod(res, res, n);
		
		// si res=n-1 alors pas temoin de miller
		if (mpz_cmp(res, tp) == 0){
			mpz_clears(tp, d , res, NULL);
			return 1;
		}

		i++;
	}
	
	mpz_clears(tp, d , res, NULL);
	//temoin de miller donc non premier
	return 0;
}
int Miller_Rabin(mpz_t n, int tour){
	
	//1 et 2 sont premier
	if(mpz_cmp_d(n, 1) == 0 || mpz_cmp_d(n, 2) == 0)
		return 1;
		
	//graine aléatoire 
	gmp_randstate_t state;
	gmp_randinit_default (state);
	gmp_randseed_ui(state,(unsigned)time(NULL));

	mpz_t tp,rand;
	mpz_inits(rand,tp , NULL);
	
	// car on va jusque n-1 et aussi parsq on rajoute 2 pour avoir une valeur > 1
	mpz_sub_ui(tp, n, 4);
	
	//nombre de tour 
	while (tour > 0){
		// rand aléatoire dans l'intervalle [0, n – 4]
		mpz_urandomm (rand, state, tp);
		
		// rand aléatoire  1 < a < n-1 donc [2 , n-2]
		mpz_add_ui(rand, rand, 2);				

		if (temoin_miller(rand, n)==0){
			mpz_clears(tp,rand , NULL);
			//composé
			return 0;
		}
		tour--;
	}

	mpz_clears(tp, rand, NULL);
	
	//probablement premier 
	return 1;
}
