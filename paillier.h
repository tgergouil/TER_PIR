#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>

/**
 * This function returns the value of Eg(plain) in the variable "ciphered".
 * param :
 *      plain is the plaintext to encrypt
 *      ciphered is the variable in which the result is stored
 *      n is the public key such as n = pq
 *      g = n+1
 *      n_square = n²
 * */  
void encrypt(mpz_t plain, mpz_t ciphered, mpz_t n, mpz_t g, mpz_t n_square);

/**
 * This functions returns the value of Dg(ciphered) in the variable "plain"
 *      plain is the variable that stores the result of Dg(ciphered)
 *      ciphered stores the value to decrypt
 *      n is the public key such as n = pq
 *      q and p are random large primes and the factors of the private key
 *      g = n+1
 *      n_square = n²
 *      p_minus = p-1
 *      q_minus = q-1
 *      lambda is the Carmichael's function on n : lambda = ppcm(p-1, q-1)
 * */
void decrypt(mpz_t plain, mpz_t ciphered, mpz_t n, mpz_t p, mpz_t q , mpz_t g, mpz_t n_square, mpz_t p_minus, mpz_t q_minus, mpz_t lambda);
