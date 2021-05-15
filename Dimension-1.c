#include "paillier.h"
#include "Dimension-1.h"
#include <gmp.h>

void EDim1(mpz_t* m, mpz_t n, int N, mpz_t* c, mpz_t g, mpz_t n_square){
    for(int i=0; i<N; i++){
       mpz_set(c[i], m[i]);
       encrypt(c[i], n, c[i], g, n_square);
    } 
} 

void sigmaf(mpz_t* ct, int N, mpz_t* x, mpz_t c, mpz_t n_square){
    for(int i=0;i<N;i++){
        mpz_powm(ct[i], ct[i], x[i], n_square);
        mpz_mul(c, c, ct[i]);
    } 
}

void DDim1(int N, mpz_t plain, mpz_t n, mpz_t p, mpz_t q, mpz_t c, mpz_t g, mpz_t n_square,  mpz_t lambda){
    decrypt(plain, n, p, q, c, g, n_square, lambda);
} 