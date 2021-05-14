#include "paillier.h"
#include "2-hypercube.h"
#include "3-hypercube.h"
#include <gmp.h>

int I(int a,int b){
if(a==b){
    return 1;
}   
else 
    return 0;
} 
void Hyp3(mpz_t* ALPHA,mpz_t* GAMMA,mpz_t n,int l,mpz_t* BETA, mpz_t g, mpz_t k, mpz_t n_square,int i,int j){
    Hyp2( ALPHA, n, l, BETA, g, n_square, i, j);
    for(int n=0;n<l;n++){
       
       
       if(I(n,k)){
            mpz_set_ui( GAMMA[n],1);
       } 
       else{
           mpz_set_ui( GAMMA[n],0);
       }
       encrypt(GAMMA[n],n,GAMMA[n],g,n_square);
    } 

} 


void var(){

} 


void fphi(mpz_t* BETA,mpz_t** x,mpz_t** PHI,int l,mpz_t n_square,mpz_t c){
for(int i=0;i<l;i++){
    phi(BETA,x[i] ,PHI[i] , l, n_square, c);
    
} 

} 


void ftot(int l,mpz_t* ALPHA,mpz_t* GAMMA ,mpz_t** PHI,mpz_t n,mpz_t* u,mpz_t* v,mpz_t n_square,mpz_t uu,mpz_t uv,mpz_t vu,mpz_t vv){
    for(int i=0;i<l;i++){
        f( l, ALPHA, PHI[i] , n, u[i] , v[i] , n_square);
    }
    f( l, GAMMA, u , n, uu , uv , n_square);
    f( l, GAMMA, v , n, vu , vv , n_square);
} 

void sHyp3(mpz_t uu,mpz_t uv,mpz_t vu,mpz_t vv,mpz_t plain, mpz_t n, mpz_t p, mpz_t q, mpz_t c, mpz_t g, mpz_t n_square, mpz_t p_minus, mpz_t q_minus, mpz_t lambda){
   mpz_t vv1,uu1;
   mpz_inits(vv1,uu1,NULL);
   sHyp2( vu, vv, vv1,  n,  p,  q,  c,  g,  n_square, p_minus,  q_minus,  lambda);
   sHyp2( uu, uv, uu1,  n,  p,  q,  c,  g,  n_square, p_minus,  q_minus,  lambda);
   mpz_mul(uu1,uu1,n);
   mpz_add(uu1,uu1,vv1);
   decrypt(plain,n,p,q,uu1,g,n_square,p_minus,q_minus,lambda);
   mpz_clears(vv1,uu1,NULL);

}  