def encrypt(n, plain):
    r = random.randrange(0, n)
    
    c = pow(n+1, plain, n**2)
    c *= pow(r, n, n**2)
    
    return c % n**2

def I(a,b):
     if a==b:
         return 1
     else:
         return 0

def ALPHABETA(i,j,k,l,n):
 B=[]
 A=[]
 y=[]
 for t in range(l):
   B=B+[encrypt(n,I(t,j))]
   A=A+[encrypt(n,I(t,i))]
   y=y+[encrypt(n,I(t,k))]
 return A,B,y

def var(M,l):
  k=(M//(l*l))
  N=(M-k*l*l)
  i=(N//l)+1
  j=(N%l)-1
  if i ==l:
   i=0
  return i,j,k
#Filtering

def fphi(B,l,n,x):
  c=[]
  for i in range(l):
   CO=1
   for t in range(l):
    CO=CO*B[t]**x[(i-1)*l+(t-1)+1]
   CO=mod(CO,n**2)
   c=c+[CO]
  return c

def phitot(B,l,n,x):
     phit=[]
     for i in range(i):
         phit=phit+fphi(B,l,n,x[i])]
     return phit


#Splitting-and-the-filtering

def f(phi,A,n,l):
 u=1
 v=1
 for i in range(l):
  phi[i]=Integer(phi[i])
  ui=phi[i]//n
  vi=phi[i]%n
  u=u*A[i]**ui
  v=v*A[i]**vi
 u=mod(u,n**2)
 v=mod(v,n**2)
 return u,v
def ftot(phit,A,n,l):
    u=[]
    v=[]
    for i in range(l):
        (u1,v1)=f(phit[i],A,n,l)
        u=u+[u1]
        v=v+[v1]
    return u,v
def fuv(u,v,LAMBDA,n,l):
 uu=1
 vv=1
 uv=1
 vu=1
 for i in range(l):
  u[i]=Integer(u[i])
  v[i]=Integer(v[i])
  uud=u[i]//n
  uvd=u[i]%n
  vud=v[i]//n
  vvd=v[i]%n
  uu*=pow(LAMBDA[i],uud,n**2)
  vv*=pow(LAMBDA[i],vvd,n**2)
  vu*=pow(LAMBDA[i],vud,n**2)
  uv*=pow(LAMBDA[i],uvd,n**2)
 uu=mod(uu,n**2)
 vv=mod(vv,n**2)
 uv=mod(uv,n**2)
 vu=mod(vu,n**2)
 return uu,vv,uv,vu
#Reconstructing

def decrypt(n, p, q, c):
    #lambda
    l = lcm(p-1, q-1)
    c = pow(c, l, n**2)
    #g = n+1
    g = pow(n+1, l, n**2)

    # c and g must be casted otherwise Sage looks for an inverse mod n that doesn't exist and it crashes.
    c = Integer(c)
    g = Integer(g)
    L_bot = (c - 1) / n
    L_top = (g - 1) / n
    return (L_bot // L_top) % n

def final(uu,vv,vu,uv,n,p,q):
 return decrypt(n,p,q,decrypt(n,p,q,((decrypt(n,p,q,uu)*n+decrypt(n,p,q,uv)))*n+decrypt(n,p,q,(decrypt(n,p,q,vu)*n+decrypt(n,p,q,vv))))
 