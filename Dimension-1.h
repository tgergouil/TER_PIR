#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>

/**
 * This function performs the Initialization step.
 * param :
 *      m is the array of indexes: 1 for the index the user wants, 0 otherwise
 *      n is the public key such as n = pq
 *      N is the size of the database
 *      c is the array for the results of encryption
 *      g = n+1
 *      n_square = n^2
 * */  
void EDim1(mpz_t* m, mpz_t n, int N, mpz_t* c, mpz_t g, mpz_t n_square);

/**
 * This function performs the Filtering / Splitting-and-then-filtering steps.
 * param :
 *      ct is the array of encrypted indexes
 *      N is the size of the database
 *      x is the database
 *      c is the result that the server sends to the user
 *      n_square = n^2
 * */  
void sigmaf(mpz_t* ct, int N, mpz_t* x, mpz_t c, mpz_t n_square);

/**
 * This function performs the Reconstructing step.
 * param :
 *      plain is the result
 *      n is the public key such as n = pq
 *      p,q are the primes factorizing n
 *      c is what the server sent to the user
 *      g = n+1
 *      n_square = n^2
 *      lambda = lcm(p-1,q-1)
 * */ 
void DDim1(mpz_t plain, mpz_t n, mpz_t p, mpz_t q, mpz_t c, mpz_t g, mpz_t n_square, mpz_t lambda);