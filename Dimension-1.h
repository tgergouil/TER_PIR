#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>

void EDim1(mpz_t* m, mpz_t n, int N, mpz_t* c, mpz_t g, mpz_t n_square);
void sigmaf(mpz_t* ct, int N, mpz_t* x, mpz_t c, mpz_t n_square);
void DDim1(int N, mpz_t plain, mpz_t n, mpz_t p, mpz_t q, mpz_t c, mpz_t g, mpz_t n_square, mpz_t lambda);