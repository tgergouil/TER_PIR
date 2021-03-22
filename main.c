#include "paillier.h"
#include <gmp.h>

int getPrimes(unsigned long int seed, mpz_t p, mpz_t q){
    

    mpz_t intg; //integer
    gmp_randstate_t rstate; //random state
    mp_bitcnt_t bcnt = 2048; //bit counter
    mpz_init2(intg, bcnt); //initiliaze the integer with the right amount of bits

    gmp_randinit_mt(rstate); //initialize random state 
    gmp_randseed_ui(rstate, seed); //set a value to the random state

    size_t size; //size of the integer

    do{
        mpz_urandomb(intg, rstate, bcnt);
        size = mpz_sizeinbase (intg, 2); //get a random integer between 0 and 2^bcnt - 1
    } while(size != 2048);

    //gmp_printf ("An mpz with %lu bits: %Zd\n", size, intg);
    
    mpz_init2(p, bcnt);
    mpz_nextprime(p, intg); //takes the next prime
    //gmp_printf("The next prime: %Zd", p);

    mpz_init2(q, bcnt);
    mpz_nextprime(q, p);

    return EXIT_SUCCESS;
} 

void main(int argc, char *argv[]){
    if(argc != 2){
        printf("Provide one argument: a random seed\n");
        return ;
    } 

    //p and q are initialized in getPrime
    mpz_t p, q, n;
    mpz_init(n);

    char* ptr;
    unsigned long int seed = strtol(argv[1], &ptr, 10);

    getPrimes(seed, p, q);
    mpz_mul(n, p, q);

    mpz_t g, n_square;
    mpz_inits(g, n_square, NULL);

    mpz_sub_ui(g, n, 1);
    mpz_pow_ui(n_square, n, 2);

    /** TEST ENCRYPTION **/
    printf("\n\n*****************************************************************\n\n");
    mpz_t cyphered, plain;

    mpz_init(cyphered);
    mpz_init(plain);
    mpz_set_ui(plain, 123456789012345);
    
    encrypt(cyphered, n, plain, g, n_square);
    
    /** TEST DECRYPTION **/
    decrypt(plain, n, p, q, cyphered, g, n_square);
    gmp_printf("Ca marche ? %Zd\n", plain);

    mpz_clears(p, q, n, g, n_square, cyphered, plain, NULL);
    return ;
}

