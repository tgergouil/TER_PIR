#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>

void Hyp1(mpz_t* m,mpz_t n,int N,mpz_t* c,mpz_t plain, mpz_t g, mpz_t n_square);
void sHyp1(mpz_t* ct,int N ,mpz_t* x,mpz_t plain, mpz_t n, mpz_t p, mpz_t q, mpz_t c, mpz_t g, mpz_t n_square, mpz_t p_minus, mpz_t q_minus, mpz_t lambda);