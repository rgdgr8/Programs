class x:
 def __init__(self):
  self.__a = 1
 def get(self):
  return self.__a

def __add__(a,b):
 return a.get()+b.get()

print(x()+x())

