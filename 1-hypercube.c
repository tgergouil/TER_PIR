#include "paillier.h"
#include "1-hypercube.h"
#include <gmp.h>

void Hyp1(mpz_t* m,mpz_t n,int N,mpz_t* c, mpz_t g, mpz_t n_square){
    
    for(int i=0;i<N;i++){
       mpz_set_ui( c[i],m[i]);
       encrypt(c[i],n,c[i] ,g,n_square);
    } 

} 

void sHyp1(mpz_t* ct,int N ,mpz_t* x,mpz_t plain, mpz_t n, mpz_t p, mpz_t q, mpz_t c, mpz_t g, mpz_t n_square, mpz_t p_minus, mpz_t q_minus, mpz_t lambda){
    for(int i=0;i<N;i++){
        mpz_pown(ct[i],ct[i],x[i]);
        mpz_mul(c,c,ct[i]);
    } 
    decrypt(plain,n,p,q,c,g,n_square,p_minus,q_minus,lambda);

} 