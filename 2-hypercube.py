#Initializing

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

def ALPHABETA(i,j,l,n):
 B=[]
 A=[]
 for t in range(l):
   B=B+[encrypt(n,I(t,j))]
   A=A+[encrypt(n,I(t,i))]
 return A,B

def var(M,l):
 i=(M//l)+1
 j=(M%l)
 if i ==l:
  i=0
 return i,j

#Filtering

def phi(B,l,n,x):
  c=[]
  for i in range(l):
   CO=1
   for t in range(l):
    CO=CO*B[t]**x[(i-1)*l+(t-1)+1]
   CO=mod(CO,n**2)
   c=c+[CO]
  return c

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

def final(u,v,n,p,q):
 return decrypt(n,p,q,(decrypt(n,p,q,u)*n+decrypt(n,p,q,v)))