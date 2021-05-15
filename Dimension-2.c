#include "paillier.h"
#include "Dimension-2.h"
#include <gmp.h>

int I(int a,int b){
    if(a==b){
        return 1;
    }   
    else{
        return 0;
    } 
}

void EDim2(mpz_t* ALPHA, mpz_t n, int l, mpz_t* BETA, mpz_t g, mpz_t n_square, int i, int j){
    for(int k=0;k<l;k++){
        mpz_set_ui(BETA[k],I(k,j));
        mpz_set_ui(ALPHA[k],I(k,i));

        encrypt(ALPHA[k],n,ALPHA[k],g,n_square);
        encrypt(BETA[k],n,BETA[k],g,n_square);
    }
} 

void phi(mpz_t* BETA,mpz_t* x,mpz_t* SIGMA,int l,mpz_t n_square,mpz_t c,mpz_t*BETA2){
    for(int i=0; i<l; i++){
        mpz_set_ui(c, 1);

        for(int t=0;t<l;t++){
            mpz_powm(BETA2[t], BETA[t], x[(i*l)+t], n_square);
            mpz_mul(c, c, BETA2[t]);
            mpz_mod(c, c, n_square);
        }

        mpz_set(SIGMA[i], c);
    } 
} 

void f(int l, mpz_t* ALPHA, mpz_t* SIGMA, mpz_t n, mpz_t u, mpz_t v, mpz_t n_square){
    mpz_t ui,vi;
    mpz_inits(ui, vi, NULL);
    mpz_t*ALPHA2 = malloc(sizeof(mpz_t)*l);

    for (int i=0; i<l; i++){
        mpz_init(ALPHA2[i]);
    } 

    for(int i=0; i<l; i++){
        mpz_fdiv_q(ui,SIGMA[i],n);
        mpz_fdiv_r(vi,SIGMA[i],n);

        mpz_powm(ALPHA2[i],ALPHA[i],ui,n_square);
        mpz_mul(u,u,ALPHA2[i]);
        
        mpz_powm(ALPHA2[i],ALPHA[i],vi,n_square);
        mpz_mul(v,v,ALPHA2[i]);
    } 

    mpz_mod(u, u, n_square);
    mpz_mod(v, v, n_square);
    mpz_clears(ui, vi, NULL);

    for (int i=0; i<l; i++){
        mpz_clear(ALPHA2[i]);
    }

    free(ALPHA2);
} 

void DDim2(mpz_t u, mpz_t v, mpz_t plain, mpz_t n, mpz_t p, mpz_t q, mpz_t c, mpz_t g, mpz_t n_square, mpz_t lambda){
   mpz_t v1,u1;
   mpz_inits(u1,v1,NULL);

   decrypt(v1,n,p,q,v,g,n_square,lambda);
   decrypt(u1,n,p,q,u,g,n_square,lambda);

   mpz_mul(u1,u1,n);
   mpz_add(u1,u1,v1);

   decrypt(plain,n,p,q,u1,g,n_square,lambda);
   
   mpz_clears(u1,v1,NULL);
}  
   