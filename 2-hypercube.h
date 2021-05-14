#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>


int I(int a,int b);
void Hyp2(mpz_t* ALPHA,mpz_t n,int l,mpz_t* BETA, mpz_t g, mpz_t n_square,int i,int j);

void phi(mpz_t* BETA,mpz_t* x,mpz_t* SIGMA,int l,mpz_t n_square,mpz_t c,mpz_t*BETA2);

void f(int l,mpz_t* ALPHA,mpz_t* SIGMA,mpz_t n,mpz_t u,mpz_t v,mpz_t n_square);

void sHyp2(mpz_t u,mpz_t v,mpz_t plain, mpz_t n, mpz_t p, mpz_t q, mpz_t c, mpz_t g, mpz_t n_square,  mpz_t lambda);