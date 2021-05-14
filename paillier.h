#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>


void encrypt(mpz_t cyphered, mpz_t n, mpz_t plain, mpz_t g, mpz_t n_square);
void decrypt(mpz_t plain, mpz_t n, mpz_t p, mpz_t q, mpz_t c, mpz_t g, mpz_t n_square,  mpz_t lambda);
