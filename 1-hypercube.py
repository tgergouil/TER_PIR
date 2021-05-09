def encrypt(n, plain):
    r = random.randrange(0, n)
    while pgcd(r,n)!=1 :
        r = random.randrange(0, n)

    c = pow(n+1, plain, n**2)
    c *= pow(r, n, n**2)
    
    return c % n**2



def pgcd(a,b):
     if b==0:
         return a
     else:
         r=a%b
         return pgcd(b,r)

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

def hyp1(m,n):
        c=[]
        for i in range(len(m)) :   
            c=c+[encrypt(n,m[i])]
            
        return c
def shyp1(c,x):
        k=1
        for i in range(len(c)) :   
            k=k*(c[i]**x[i])
        return k

