#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>

void EDim3(mpz_t* ALPHA, mpz_t* GAMMA, mpz_t n, int l, mpz_t* BETA, mpz_t g, int k, mpz_t n_square, int i, int j);
void fphi(mpz_t* BETA, mpz_t** x, mpz_t** PHI, int l, mpz_t n_square, mpz_t c, mpz_t* BETA2);
void ftot(int l,mpz_t* ALPHA, mpz_t* GAMMA, mpz_t** PHI, mpz_t n, mpz_t* u, mpz_t* v, mpz_t n_square, mpz_t uu, mpz_t uv, mpz_t vu, mpz_t vv);
void DDim3(mpz_t uu, mpz_t uv, mpz_t vu, mpz_t vv, mpz_t plain, mpz_t n, mpz_t p, mpz_t q, mpz_t c, mpz_t g, mpz_t n_square, mpz_t lambda);
