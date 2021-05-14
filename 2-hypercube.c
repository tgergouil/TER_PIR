#include "paillier.h"
#include "2-hypercube.h"
#include <gmp.h>

int I(int a,int b){
if(a==b){
    return 1;
}   
else 
    return 0;
} 

void Hyp2(mpz_t* ALPHA,mpz_t n,int l,mpz_t* BETA, mpz_t g, mpz_t n_square,int i,int j){
    
    for(int k=0;k<l;k++){
       
       if(I(k,j)){
           mpz_set_ui( BETA[k],1);
       } 
       else{
            mpz_set_ui( BETA[k],0);
       } 
       if(I(k,i)){
            mpz_set_ui( ALPHA[k],1);
       } 
       else{
           mpz_set_ui( ALPHA[k],0);
       }
       encrypt(ALPHA[k],n,ALPHA[k],g,n_square);
       encrypt(BETA[k],n,BETA[k],g,n_square);
    } 

} 


void var(){

} 


void phi(mpz_t* BETA,mpz_t* x,mpz_t* PHI,int l,mpz_t n_square,mpz_t c){
for(int i=0;i<l;i++){
    mpz_set_ui( c,1);
    for(int t=0;t<l;t++){
        mpz_pown(BETA[t],BETA[t],x[(i*l)+t]);
        mpz_mul(c,c,BETA[t]);
        mpz_mod(c,c,n_square);
    }
    mpz_set( PHI[i],c);
} 

} 


void f(int l,mpz_t* ALPHA,mpz_t* PHI,mpz_t n,mpz_t u,mpz_t v,mpz_t n_square){
    mpz_t ui,vi;
    mpz_inits(ui,vi,NULL);
    for(int i=0;i<l;i++){
        mpz_fdiv_q(ui,PHI[i],n);
        mpz_fdiv_r(vi,PHI[i],n);
        mpz_pown(ALPHA[i],ALPHA[i],ui);
        mpz_mul(u,u,ALPHA[i]);
        
        mpz_pown(ALPHA[i],ALPHA[i],vi);
        mpz_mul(v,v,ALPHA[i]);
        
    } 
    mpz_mod(u,u,n_square);
    mpz_mod(v,v,n_square);
    mpz_clears(ui,vi,NULL);

} 

void sHyp2(mpz_t u,mpz_t v,mpz_t plain, mpz_t n, mpz_t p, mpz_t q, mpz_t c, mpz_t g, mpz_t n_square, mpz_t p_minus, mpz_t q_minus, mpz_t lambda){
   mpz_t v1,u1;
   mpz_inits(u1,v1,NULL);
   decrypt(v1,n,p,q,v,g,n_square,p_minus,q_minus,lambda);
   decrypt(u1,n,p,q,u,g,n_square,p_minus,q_minus,lambda);
   mpz_mul(u1,u1,n);
   mpz_add(u1,u1,v1);
   decrypt(plain,n,p,q,u1,g,n_square,p_minus,q_minus,lambda);
   mpz_clears(u1,v1,NULL);

}  
   