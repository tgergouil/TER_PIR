#include "paillier.h"
#include <gmp.h>

void encrypt(mpz_t cyphered, mpz_t n, mpz_t plain){

    /********************** INITIALIZATIONS *****************/
    
    mpz_t r, n_square, g, c1, c2; 
    mpz_inits(r, n_square, g, c1, c2, NULL);

    //r is s set to 1 for debugging purpose 
    mpz_set_ui(r, 1);
    /********************** ENCRYPTION **********************/

    
    mpz_pow_ui(n_square, n, 2);
    
    //g = n + 1 
    mpz_add_ui(g, n, 1); 
    
    // c1 = g^m mod n^2 = 1 + n*m
    mpz_powm(c1, g, plain, n_square);
    
    // c2 = r^n mod n^2
    mpz_powm(c2, r, n, n_square); 

    //cyphered = c1 * c2
    mpz_mul(cyphered, c1, c2); 
    mpz_mod(cyphered, cyphered, n_square); // cyphered = g^m * r^n mod n^2


    /********************** CLEARING ************************/

    gmp_printf("TEST : %Zd\n", cyphered);
    mpz_clears(r, n_square, g, c1, c2, NULL);
}

void decrypt(mpz_t plain, mpz_t n, mpz_t p, mpz_t q, mpz_t c){

    /********************** INITIALIZATIONS *****************/

    mpz_t n_square, g, p_minus, q_minus, c1, c2, lambda;
    mpz_inits(n_square, g, p_minus, q_minus, c1, c2, lambda, NULL);

    /********************** DECRYPTION **********************/
    //gmp_printf("TEST c : %Zd\n\n", c);
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
    //gmp_printf("TEST c1 : %Zd\n\n", c1);
    //gmp_printf("TEST l  : %Zd\n", lambda);

    //c2 = g^lambda mod n^2 --> inutile à cause de g = n + 1, ça fait autre chose mais je sais plus quoi
    mpz_powm(c2, g, lambda, n_square); 

    mpz_sub_ui(c1, c1, 1);
    mpz_divexact(c1, c1, n); //L(c1, n)
    
    mpz_sub_ui(c2, c2, 1);
    mpz_divexact(c2, c2, n); //L(c2, n)

    //inverser c2 mod n et multiplier c1 par c2
    mpz_invert(c2, c2, n);
    mpz_mul(plain, c1, c2);
    mpz_mod(plain, plain, n);

    /********************** CLEARING ************************/

    mpz_clears(n_square, g, p_minus, q_minus, c1, c2, lambda, NULL);
}



