#include <stdlib.h>
#include <stdio.h>

#include <gmp.h>

int getPrimes(unsigned long int seed, mpz_t p, mpz_t q){
    

    mpz_t intg; //integer
    gmp_randstate_t rstate; //random state
    mp_bitcnt_t bcnt = 2048; //bit counter
    mpz_init2(intg, bcnt); //initiliaze the integer with the right amount of bits

    gmp_randinit_mt(rstate); //initialize random state 
    char* ptr;
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