#include "euclide.h"

void euclide_etendu(mpz_t u_1, mpz_t v_1, mpz_t phi_n, mpz_t e)
{
  mpz_t r;
  mpz_init(r);
  mpz_t u;
  mpz_init(u);
  mpz_t v;
  mpz_init(v);
  mpz_t r1;
  mpz_init(r1);
  mpz_t u1;
  mpz_init(u1);
  mpz_t v1;
  mpz_init(v1);
  mpz_t q;
  mpz_init(q);
  mpz_t rs;
  mpz_init(rs);
  mpz_t us;
  mpz_init(us);
  mpz_t vs;
  mpz_init(vs);
  mpz_set_ui(u,1);
  mpz_set_ui(v,0);
  mpz_set_ui(u1,0);
  mpz_set_ui(v1,1);
  mpz_set(r,phi_n);
  mpz_set(r1,e);
  mpz_t div;
  mpz_init(div);
  mpz_t mu;
  mpz_init(mu);

    while(mpz_cmp_ui(r1,0)!=0)
    {
          mpz_div(q,r,r1);
          mpz_set(rs,r);
          mpz_set(us,u);
          mpz_set(vs,v);
          mpz_set(r,r1);
          mpz_set(u,u1);
          mpz_set(v,v1);
          mpz_mul(mu,q,r1);
          mpz_sub(r1,rs,mu);
          mpz_mul(mu,q,u1);
          mpz_sub(u1,us,mu);
          mpz_mul(mu,q,v1);
          mpz_sub(v1,vs,mu);
    }
    mpz_set(u_1,u);
    mpz_set(v_1,v);
     

}