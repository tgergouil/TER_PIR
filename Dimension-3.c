#include "paillier.h"
#include "Dimension-2.h"
#include "Dimension-3.h"
#include <gmp.h>

void EDim3(mpz_t* ALPHA, mpz_t* GAMMA, mpz_t n, int l, mpz_t* BETA, mpz_t g, int k, mpz_t n_square, int i, int j){
    EDim2(ALPHA, n, l, BETA, g, n_square, i, j);

    for(int a=0; a<l; a++){
        mpz_set_ui( GAMMA[a],I(a,k));
        encrypt(GAMMA[a],n,GAMMA[a],g,n_square);
    }
} 

void fphi(mpz_t* BETA,mpz_t** x,mpz_t** SIGMA,int l,mpz_t n_square,mpz_t c,mpz_t* BETA2){
    for(int i=0; i<l; i++){
        phi(BETA, x[i], SIGMA[i], l, n_square, c, BETA2);
    }
} 

void ftot(int l, mpz_t* ALPHA, mpz_t* GAMMA, mpz_t** SIGMA, mpz_t n, mpz_t* u, mpz_t* v, mpz_t n_square, mpz_t uu, mpz_t uv, mpz_t vu, mpz_t vv){
    for(int i=0;i<l;i++){
        f(l, ALPHA, SIGMA[i], n, u[i], v[i], n_square);
    }

    f(l, GAMMA, u, n, uu, uv, n_square);
    f(l, GAMMA, v, n, vu, vv, n_square);
} 

void DDim3(mpz_t uu,mpz_t uv,mpz_t vu,mpz_t vv,mpz_t plain, mpz_t n, mpz_t p, mpz_t q, mpz_t c, mpz_t g, mpz_t n_square, mpz_t lambda){
   mpz_t vv1,uu1;
   mpz_inits(vv1, uu1, NULL);

   DDim2(vu, vv, vv1, n, p, q, c, g, n_square, lambda);
   DDim2(uu, uv, uu1, n, p, q, c, g, n_square, lambda);

   mpz_mul(uu1, uu1, n);
   mpz_add(uu1, uu1, vv1);

   decrypt(plain, n, p, q, uu1, g, n_square, lambda);

   mpz_clears(vv1, uu1, NULL);
}  