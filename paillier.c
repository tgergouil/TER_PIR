#include "paillier.h"
#include <gmp.h>

void encrypt(mpz_t ciphered, mpz_t n, mpz_t plain, mpz_t g, mpz_t n_square){

    /********************** INITIALIZATIONS *****************/
    
    mpz_t r, c1, c2; 
    mpz_inits(r, c1, c2, NULL);

        //r is set to 1 for debugging purpose 
    mpz_set_ui(r, 1);
    /********************** ENCRYPTION **********************/

        // c1 = g^m mod n^2 = 1 + n*m
    mpz_powm(c1, g, plain, n_square);
    
        // c2 = r^n mod n^2
    mpz_powm(c2, r, n, n_square); 

        //ciphered = c1 * c2
    mpz_mul(ciphered, c1, c2); 
        //ciphered = g^m * r^n mod n^2
    mpz_mod(ciphered, ciphered, n_square); 


    /********************** CLEARING ************************/

    mpz_clears(r, c1, c2, NULL);
}

void decrypt(mpz_t plain, mpz_t n, mpz_t p, mpz_t q, mpz_t c, mpz_t g, mpz_t n_square, mpz_t lambda){

    /********************** INITIALIZATIONS *****************/

    mpz_t c1, c2;   
    mpz_inits(c1, c2, NULL);

    /********************** DECRYPTION **********************/

        //c1 = c^lambda mod n^2
    mpz_powm(c1, c, lambda, n_square); 

        //c2 = g^lambda mod n^2
    mpz_powm(c2, g, lambda, n_square); 

        //L(c1, n)
    mpz_sub_ui(c1, c1, 1);
    mpz_divexact(c1, c1, n); 
    
        //L(c2, n)
    mpz_sub_ui(c2, c2, 1);
    mpz_divexact(c2, c2, n); 

        //plain = c1 * invert(c2) 
    mpz_invert(c2, c2, n);
    mpz_mul(plain, c1, c2);
    mpz_mod(plain, plain, n);

    /********************** CLEARING ************************/

    mpz_clears(c1, c2, NULL);
}




