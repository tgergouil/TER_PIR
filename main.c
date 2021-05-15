#include "paillier.h"
#include "1-hypercube.h"
#include "2-hypercube.h"
#include "3-hypercube.h"
#include <math.h>
#include <gmp.h>

int var2i(int l, int m){
   int i = m/l; 
   return i;
} 

int var2j(int l, int m){
   int j = m%l; 
   return j;
} 

int var3i(int l, int m){
   int i = m/(l*l); 
   return i;
} 

int var3j(int l, int m){
   int m2 = m%(l*l);
   int j = m2/l; 
   return j;
} 

int var3k(int l, int m){
   int m2 = m%(l*l);
   int k = m2%l; 
   return k;
}

int powX(int x, int n){
    int res = 1;

    for(int i = 0; i<n; i++){
        res *= x;
    }

    return res;
} 

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
    
    mpz_init2(p, bcnt);
    mpz_nextprime(p, intg); //takes the next prime

    mpz_init2(q, bcnt);
    mpz_nextprime(q, p);

    return EXIT_SUCCESS;
} 

void main(int argc, char *argv[]){
    if(argc != 2){
        printf("Provide one argument: a random seed\n");
        return;
    }

    printf("Initialization\n");

    //p and q are initialized in getPrimes
    mpz_t p, q, n, g, n_square, p_minus, q_minus, lambda;
    mpz_inits(n, g, n_square, p_minus, q_minus, lambda, NULL);

    char* ptr;
    unsigned long int seed = strtol(argv[1], &ptr, 10);
    getPrimes(seed, p, q);
    
    mpz_mul(n, p, q);

    mpz_add_ui(g, n, 1);
    mpz_pow_ui(n_square, n, 2);

        // p_minus = p - 1
    mpz_sub_ui(p_minus, p, 1);

        //q_minus = q - 1
    mpz_sub_ui(q_minus, q, 1);
    
        //lambda = lcm(p-1, q-1)
    mpz_lcm(lambda, p_minus, q_minus); 

    /** TEST ENCRYPTION **/

    printf("\nPaillier's cryptosystem test:\n");

    mpz_t ciphered, plain, plainResult;

    mpz_init(ciphered);
    mpz_init(plain);
    mpz_init(plainResult);
    mpz_set_ui(plain, 123456789012345);
    
    gmp_printf("Encrypting %Zd\n", plain);
    encrypt(ciphered, n, plain, g, n_square);

    /** TEST DECRYPTION **/
    decrypt(plainResult, n, p, q, ciphered, g, n_square, lambda);
    gmp_printf("Decrypted into %Zd\n", plainResult);

    //mpz_clears(p, q, n, g, n_square, ciphered, plain, NULL);

    /** TEST PIR **/

    int l = 9;
    int N, dimension;

    /** TEST 1-HYPERCUBE **/

    printf("\nPIR 1 dimension test:\n");

    dimension = 1;

    N = powX(l, dimension);

    //Must not be greater than l
    int index_i = 5;

    mpz_t z;
    mpz_init(z);

    mpz_t* m = malloc(sizeof(mpz_t)*N);
    mpz_t* c = malloc(sizeof(mpz_t)*N);
    mpz_t* x = malloc(sizeof(mpz_t)*N);

    for (int i=0; i<N; i++){
        mpz_inits(m[i], c[i], x[i], NULL);
        mpz_set_ui(x[i], i*i);
        mpz_set_ui(m[i], 0);
    }

    mpz_set_ui(m[index_i], 1);
    mpz_set_ui(z, 1);

    printf("Asking for index %d, expected value of %d.\n", index_i, index_i*index_i);

    Hyp1(m, n, N, c, g, n_square);
    sigmaf(c, N , x, z, n_square);

    sHyp1(N, plain, n, p, q, z, g, n_square, lambda);

    gmp_printf("Database answer: %Zd\n", plain);

    for (int i=0; i<N; i++){
        mpz_clears(m[i], c[i], NULL);
    }

    free(m);
    free(c);

    /** TEST 2-HYPERCUBE **/

    printf("\nPIR 2 dimensions test:\n");

    dimension = 2;

    N = powX(l, dimension);
    
    //Must not be greater than l
    index_i = 5;
    int index_j = 4;

    mpz_t c2,u,v;
    mpz_inits(c2,u,v,NULL);

    mpz_t* x2 = malloc(sizeof(mpz_t)*N);

    mpz_t* ALPHA = malloc(sizeof(mpz_t)*l);
    mpz_t* BETA = malloc(sizeof(mpz_t)*l);
    mpz_t* SIGMA = malloc(sizeof(mpz_t)*l);
    mpz_t* BETA2 = malloc(sizeof(mpz_t)*l);

    for(int i=0; i<l; i++){
        mpz_inits(ALPHA[i], BETA[i], SIGMA[i], BETA2[i], NULL);
    }
    for(int i=0; i<N; i++){
        mpz_inits(x2[i], NULL);
        mpz_set_ui(x2[i], i);
    } 
    
    mpz_set_ui(z, 1);
    mpz_set_ui(u, 1);
    mpz_set_ui(v, 1);

    printf("Asking for index (%d,%d) expected value of %d.\n", index_i, index_j, index_i*l + index_j);

    Hyp2(ALPHA, n, l, BETA, g, n_square, index_i, index_j);
    
    phi(BETA, x2, SIGMA, l, n_square, c2, BETA2);
    
    f(l, ALPHA, SIGMA, n, u, v, n_square);
    
    sHyp2(u, v, plain, n, p, q, z, g, n_square, lambda);
    
    gmp_printf("Database answer: %Zd\n", plain);

    mpz_clears(c2,u,v,z,NULL);
    for (int i=0; i<l; i++){
        mpz_clears(ALPHA[i], BETA[i], SIGMA[i], BETA2[i], NULL);
    }

    for (int i=0; i<N; i++){
        mpz_clears(x2[i], NULL);
    }

    free(ALPHA);
    free(BETA);
    free(SIGMA);
    free(x2);
    free(BETA2);


    /** TEST 3-HYPERCUBE **/

    // mpz_t c3,uu3,vu3,uv3,vv3;
    // mpz_inits(c3, uu3, vu3, uv3, vv3, NULL);

    // mpz_t* ALPHA3 = malloc(sizeof(mpz_t)*l);
    // mpz_t* BETA3 = malloc(sizeof(mpz_t)*l);
    // mpz_t** SIGMA3 = malloc(sizeof(mpz_t*)*l);
    // mpz_t* GAMMA3 = malloc(sizeof(mpz_t)*l);
    // mpz_t* BETA4 = malloc(sizeof(mpz_t)*l);
    // mpz_t** x3 = malloc(sizeof(mpz_t*)*l);
    // mpz_t* u3 = malloc(sizeof(mpz_t)*l);
    // mpz_t* v3 = malloc(sizeof(mpz_t)*l);
    
    // for (int i=0; i<l; i++){
        
    //     x3[i] = malloc(sizeof(mpz_t)*N);
        
    //     SIGMA3[i] = malloc(sizeof(mpz_t)*l);
        
    //     for(int j=0; j<N; j++){
    //         mpz_init(x3[i][j]);
    //         int e = i*l+j+1;
    //         mpz_set_ui(x3[i][j], e);

    //         if(j<3){
    //             mpz_init(SIGMA3[i][j]);
    //         } 
    //     } 

    //     mpz_inits(ALPHA3[i], BETA3[i], BETA4[i], u3[i], v3[i], GAMMA3[i], NULL);
    //     mpz_set_ui(u3[i], 1);
    //     mpz_set_ui(v3[i], 1);
    // }

    // int k=2;

    // mpz_set_ui(uu3, 1);
    // mpz_set_ui(vv3, 1);
    // mpz_set_ui(uv3, 1);
    // mpz_set_ui(vu3, 1);

    // Hyp3(ALPHA3, GAMMA3, n, l, BETA3, g, k, n_square, i1, j);

    // fphi( BETA3, x3, SIGMA3, l, n_square, c3, BETA3);

    // ftot(l, ALPHA3, GAMMA3 , SIGMA3, n,u3, v3, n_square, uu3, uv3, vu3, vv3);

    // sHyp3( uu3, uv3, vu3,vv3,plain,  n,  p,  q,  c3,  g,  n_square,   lambda);

    // gmp_printf("Ca marche le 3 ? %Zd\n", plain); 

    // for(int i=0; i<l; i++){
    //     mpz_clears(ALPHA3[i], BETA3[i], BETA4[i], u3[i], v3[i], GAMMA3[i], NULL);

    //     for(int j=0; j<N; j++){
    //         mpz_clears(x3[i][j], SIGMA3[i][j], NULL);
    //     }  

    //     free(x3[i]);
    //     free(SIGMA3[i]);
    // }

    // free(GAMMA3);
    // free(ALPHA3);
    // free(BETA3);
    // free(SIGMA3);
    // free(x3);
    // free(BETA4);
    // free(u3);
    // free(v3);
    
    // mpz_clears(c3, uu3, vu3, uv3,vv3, p, q, n, g, n_square, ciphered, plain, NULL);
    
    return;
}

