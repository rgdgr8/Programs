x = int(input("Enter value till which primes have to be generated: "))

for i in range(2,x):
 for j in range(2,i):
  if(i%j==0):
   break
 else:
  print(i)
