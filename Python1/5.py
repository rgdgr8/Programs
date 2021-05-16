mem = [0,1]

def fib_gen(fib=-1):
 a = 1
 b = 0
 yield b
 yield a
 i = 1
 while(i!=fib):#infinite sequence by default, since default value of fib is -1
  c = a
  a = a+b
  b = c
  mem.append(a) #to memorize the series
  i = i+1
  yield a

x = int(input("First how many fibonacci numbers do you want? "))
fibs = fib_gen(x-1)
try:
 while(True):
  (next(fibs))
except:
 print(mem)
 print(f"That's the first {x} fibonacci numbers")
