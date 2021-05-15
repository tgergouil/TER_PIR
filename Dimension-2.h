#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>

/**
 * This function returns 1 if a == b and 0 otherwise.
 * param :
 *      a an integer
 *      b an integer
 * */
int I(int a,int b);

/**
 * This function performs the Initialization step.
 * param :
 *      ALPHA is the list of encrypted indexes
 *      n is the public key such as n = pq
 *      l is the square root of the size of the database
 *      BETA is the list of encrypted indexes
 *      g = n+1
 *      n_square = n^2
 *      i,j are the indexes of the information the user wants to retrieve
 * */
void EDim2(mpz_t* ALPHA, mpz_t n, int l, mpz_t* BETA, mpz_t g, mpz_t n_square, int i, int j);

/**
 * This function performs the Filtering step.
 * param :
 *      BETA is the list of encrypted indexes
 *      x is the database
 *      SIGMA is the list that contains the result of the filtering 
 *      l is the cube root of the size of the database
 *      n_square = n^2
 *      BETA2 transition list for the calculation of SIGMA
 * */
void phi(mpz_t* BETA, mpz_t* x, mpz_t* SIGMA, int l, mpz_t n_square, mpz_t c, mpz_t*BETA2);

/**
 * This function performs the Splitting-and-then-filtering step .
 * param :
 *      l is the cube root of the size of the database
 *      ALPHA is the list of encrypted indexes
 *      SIGMA is the list that contains the result of the filtering 
 *      n is the public key such as n = pq
 *      u,v are the answers
 *      n_square = n^2
 * */
void f(int l, mpz_t* ALPHA, mpz_t* SIGMA, mpz_t n, mpz_t u, mpz_t v, mpz_t n_square);

/**
 * This function performs the Reconstructing step.
 * param :
 *      u,v are the server's answers
 *      plain is the result
 *      n is the public key such as n = pq
 *      p,q are the primes factorizing n
 *      g = n+1
 *      n_square = n^2
 *      lambda = lcm(p-1,q-1)
 * */ 
void DDim2(mpz_t u, mpz_t v, mpz_t plain, mpz_t n, mpz_t p, mpz_t q, mpz_t g, mpz_t n_square, mpz_t lambda);