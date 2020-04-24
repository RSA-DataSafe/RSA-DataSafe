
#ifndef _euclide_h
#define _euclide_h

/**
 * Euclide étendu : permet le calcul de u*phi(n) + v*e = pgcd(phi(n),e) 
 * @param u_1 : résultat
 * @param v_1 : résultat
 * @param phi_n : le phi(n) de RSA 
 * @param e : clé publique de RSA 
 *@param pgcd :pgcd(phi_n,e)
 * */
void euclide_etendu(mpz_t u_1, mpz_t v_1, mpz_t phi_n, mpz_t e,mpz_t pgcd);

#endif // !_euclide_h
