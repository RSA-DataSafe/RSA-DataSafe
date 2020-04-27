#include "primalite.h"
int temoin_de_miller(mpz_t a , mpz_t n)
{
    mpz_t d;
	mpz_init(d);
	mpz_sub_ui(d, n, 1);
	mpz_t tmp;
	mpz_init(tmp);
	mpz_t nbr;
	mpz_init(nbr);
	mpz_mod_ui(tmp,d,2);
  while(mpz_cmp_ui(tmp, 0) == 0 ) {
    mpz_div_ui(d, d, 2);
    mpz_add_ui(nbr, nbr, 1);
    mpz_mod_ui(tmp,d,2);
	}
	mpz_set(d, nbr);
	mpz_t n1;
	mpz_init(n1);
	mpz_sub_ui(n1, n, 1);
	mpz_t s;
	mpz_init(s);
	mpz_div(s, n1, d);
	mpz_t x;
	mpz_init(x);
	expo_mod(x,a,s,n);
	if(mpz_cmp_ui(x, 1) == 0 || mpz_cmp(x, n1) == 0) {
		mpz_clear(d);
		mpz_clear(x);
		mpz_clear(n1);
		mpz_clear(nbr);
		mpz_clear(s);
		mpz_clear(tmp);
		return 0;
	}
  mpz_t i;
  mpz_init(i);
  mpz_sub_ui(d, d, 1);
  mpz_t deux;
  mpz_init(deux);
  mpz_set_ui(deux,2);
  for(mpz_set_ui(i, 0); mpz_cmp(i, d) < 0; mpz_add_ui(i, i, 1)) {
  	    expo_mod(x,x,deux,n);
		if(mpz_cmp(x, n1) == 0) {
			mpz_clear(x);
			mpz_clear(n1);
			mpz_clear(nbr);
			mpz_clear(s);
			mpz_clear(tmp);
			mpz_clear(i);
			mpz_clear(d);
			return 0;
		}
	}
	mpz_clear(n1);
	mpz_clear(nbr);
	mpz_clear(s);
	mpz_clear(tmp);
	mpz_clear(i);
	mpz_clear(d);
	mpz_clear(x);
	return 1;

}
int miller_rabbin(mpz_t n, mpz_t nb_tour)
{
	if(mpz_cmp_ui(n, 3)==0  || mpz_cmp_ui(n,2)==0)
		return 1; 
	if(mpz_cmp_ui(n, 1) <= 0)
		return 0; 
	mpz_t res;
	mpz_init(res);
	mpz_mod_ui(res,n,2);
	if( mpz_cmp_ui(res, 0) == 0 ) {
		mpz_clear(res);
		return 0;
	}
  time_t t;
  t = time(NULL);
  srand(t);
  gmp_randstate_t etat;
  gmp_randinit_default(etat);
  gmp_randseed_ui(etat, rand());
  mpz_t i;
  mpz_init(i);
  mpz_t a;
  mpz_init(a);
  mpz_t n1;
  mpz_init(n1);
  mpz_sub_ui(n1, n, 4);
	for(mpz_set_ui(i, 0); mpz_cmp(i, nb_tour) < 0; mpz_add_ui(i, i, 1)) {
		mpz_urandomm(a, etat, n1);
		mpz_add_ui(a, a, 2);
		if(temoin_de_miller(a,n)) {
			mpz_clear(res);
			mpz_clear(n1);
			mpz_clear(a);
			mpz_clear(i);
			return 0;
		}
	}	
	mpz_clear(res);
	mpz_clear(n1);
	mpz_clear(a);
	mpz_clear(i);
	return 1;
 
}