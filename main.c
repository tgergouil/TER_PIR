#include "paillier.h"
#include <gmp.h>

void main(int argc, char *argv[]){
    if(argc != 2){
        printf("Provide one argument: a random seed\n");
        return ;
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

    mpz_t q;
    mpz_init2(q, bcnt);
    mpz_nextprime(q, p);

    mpz_t n;
    mpz_init(n);
    mpz_mul(n, p, q);

    /** DELETE BEFORE **/

    /** TEST ENCRYPTION **/
    printf("\n\n*****************************************************************\n\n");
    mpz_t cyphered, plain;

    mpz_init(cyphered);
    mpz_init2(plain, 1234);
    
    encrypt(cyphered, n, plain);
    
    /** TEST DECRYPTION **/
    decrypt(plain, n, p, q, cyphered);
    gmp_printf("%Zd\n", plain);

    return ;
}