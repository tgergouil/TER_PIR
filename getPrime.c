#include <stdlib.h>
#include <stdio.h>

#include <gmp.h>

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Provide one argument: a random seed\n");
        return EXIT_FAILURE;
    } 

    mpz_t intg; //integer
    gmp_randstate_t rstate; //random state
    mp_bitcnt_t bcnt = 2048; //bit counter
    mpz_init2(intg, bcnt); //initiliaze the integer with the right amount of bits

    gmp_randinit_mt(rstate); //initialize random state 
    char* ptr;
    unsigned long int seed = strtol(argv[1], &ptr, 10);
    gmp_randseed_ui(rstate, seed); //set a value to the random state

    size_t size; //size of the integer

    do{
        mpz_urandomb(intg, rstate, bcnt);
        size = mpz_sizeinbase (intg, 2); //get a random integer between 0 and 2^bcnt - 1
    } while(size != 2048);

    gmp_printf ("An mpz with %lu bits: %Zd\n", size, intg);
    
    mpz_t p; //integer
    mpz_init2(p, bcnt);
    
    mpz_nextprime(p, intg); //takes the next prime
    gmp_printf("The next prime: %Zd", p);
    

    return EXIT_SUCCESS;
} 