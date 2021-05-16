d = dict(mon=10,tue=15,wed=20,thu=15,fri=10,sat=5,sun=25)
s = input("Enter day of week: ")
t = s.strip().lower()
t = t[:3]
print('discount for '+s+ f' is {d[t]}')
 
