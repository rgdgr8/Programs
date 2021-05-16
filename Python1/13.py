import time

a,q = [int(x) for x in input("Value of a and q for a,aq,... GP: ").split()]
t1 = time.time()
while(a<100000):
 print(a)
 a = a*q
t2 = time.time()
print("That's the GP")
print(f'Loop time is {(t2-t1)}')
t3 = time.time()
print(f'Total time is {(t3-t1)}')
