#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>


void encrypt(mpz_t cyphered, mpz_t n, mpz_t plain);
void decrypt(mpz_t plain, mpz_t n, mpz_t p, mpz_t q, mpz_t c);
