from math import sqrt

l = [x for x in range(100)]
print(f"Original list is {l}")

t = list(map(lambda x: sqrt(x),filter(lambda y : True if y%2!=0 else False,l))) #square rooting the odd values from l
#print(f"Sqrt list is {t}")

def whole_number_check(x): #to check if the square root value is a whole number of not
 temp = int(x)
 if(x==temp):
    return True
 return False

t = list(map(lambda x: int(x*x),filter(whole_number_check,t))) #filtering only the odd squares whose square roots are whole numbers
print(f"\nList of odd squares is {t}")

