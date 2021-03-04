#include "paillier.h"
#include <gmp.h>

void encrypt(mpz_t cyphered, mpz_t n, mpz_t plain){

    /********************** INITIALIZATIONS *****************/
    
    mpz_t r, n_square, g, c1, c2; //random integer
    mpz_inits(r, n_square, g, c1, c2, NULL);
    
    /********************** ENCRYPTION **********************/

    gmp_randstate_t rstate; //random state

    gmp_randinit_mt(rstate); //initialize random state 
    gmp_randseed_ui(rstate, 565565865); //set the seed, seed is const for debugging purposes 
    /** TODO CHANGE CONSTANT SEED TO RANDOM ONE WITH /dev/random **/ 
    
    mpz_urandomm(r, rstate, n - 1);
    mpz_add_ui(r, r, 1); //random in [0, n-2] now is in [1, n-1]

    // n_square = n^2
    mpz_pow_ui(n_square, n, 2);

    //g = n + 1 
    mpz_add_ui(g, n, 1); 

    // c1 = g^m mod n^2
    mpz_powm(c1, g, plain, n_square); 

    // c2 = r^n mod n^2
    mpz_powm(c2, r, n, n_square); 

    //cyphered = c1 * c2
    mpz_mul(cyphered, c1, c2); 
    mpz_mod(cyphered, cyphered, n_square); // cyphered = g^m * r^n mod n^2

    /********************** CLEARING ************************/

    mpz_clears(r, n_square, g, c1, c2, NULL);
}

void decrypt(mpz_t plain, mpz_t n, mpz_t p, mpz_t q, mpz_t c){

    /********************** INITIALIZATIONS *****************/

    mpz_t n_square, g, p_minus, q_minus, c1, c2, lambda;
    mpz_inits(n_square, g, p_minus, q_minus, c1, c2, lambda, NULL);

    /********************** DECRYPTION **********************/
    gmp_printf("TEST c : %Zd\n\n", c);
    // n_square = n^2
    mpz_pow_ui(n_square, n, 2); 

    //g = n + 1
    mpz_add_ui(g, n, 1); 

    // p_minus = p - 1
    mpz_sub_ui(p_minus, p, 1);

    //q_minus = q - 1
    mpz_sub_ui(q_minus, q, 1);
    
    //lambda = lcm(p-1, q-1)
    mpz_lcm(lambda, p_minus, q_minus); 

    //c1 = c^lambda mod n^2
    mpz_powm(c1, c, lambda, n_square); 
    gmp_printf("TEST c1 : %Zd\n\n", c1);
    gmp_printf("TEST l  : %Zd\n", lambda);

    //c2 = g^lambda mod n^2
    mpz_powm(c2, g, lambda, n_square); 

    mpz_sub_ui(c1, c1, 1);
    mpz_div(c1, c1, n); //L(c1, n)
    mpz_sub_ui(c2, c2, 1);
    mpz_div(c2, c2, n); //L(c2, n)

    mpz_div(plain, c1, c2);
    mpz_mod(plain, plain, n);

    /********************** CLEARING ************************/

    mpz_clears(n_square, g, p_minus, q_minus, c1, c2, lambda, NULL);
}



