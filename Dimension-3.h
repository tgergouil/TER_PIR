#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>

/**
 * This function performs the Initialization step.
 * param :
 *      ALPHA is the list of encrypted indexes
 *      GAMMA is the list of encrypted indexes
 *      n is the public key such as n = pq
 *      l is the cube root of the size of the database
 *      BETA is the list of encrypted indexes
 *      g = n+1
 *      n_square = n^2
 *      i,j,k are the indexes of the information the user wants to retrieve
 * */
void EDim3(mpz_t* ALPHA, mpz_t* GAMMA, mpz_t n, int l, mpz_t* BETA, mpz_t g, int k, mpz_t n_square, int i, int j);

/**
 * This function performs .
 * param :
 *      BETA is the list of encrypted indexes
 *      x is the database
 *      PHI
 *      l is the cube root of the size of the database
 *      n_square = n^2
 *      BETA2
 * */
void fphi(mpz_t* BETA, mpz_t** x, mpz_t** PHI, int l, mpz_t n_square, mpz_t c, mpz_t* BETA2);

/**
 * This function performs .
 * param :
 *      l is the cube root of the size of the database
 *      ALPHA is the list of encrypted indexes
 *      GAMMA is the list of encrypted indexes
 *      PHI
 *      n is the public key such as n = pq
 *      u,v are the answers of dimension 2
 *      n_square = n^2
 *      uu,uv,vv,vu are the answers
 * */
void ftot(int l, mpz_t* ALPHA, mpz_t* GAMMA, mpz_t** PHI, mpz_t n, mpz_t* u, mpz_t* v, mpz_t n_square, mpz_t uu, mpz_t uv, mpz_t vu, mpz_t vv);

/**
 * This function performs the Reconstructing step.
 * param :
 *      uu,uv,vu,vv are the server's answers
 *      plain is the result
 *      n is the public key such as n = pq
 *      p,q are the primes factorizing n
 *      g = n+1
 *      n_square = n^2
 *      lambda = lcm(p-1,q-1)
 * */
void DDim3(mpz_t uu, mpz_t uv, mpz_t vu, mpz_t vv, mpz_t plain, mpz_t n, mpz_t p, mpz_t q, mpz_t g, mpz_t n_square, mpz_t lambda);
