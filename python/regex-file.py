import re

f = open('actual.txt')
s = f.read()
l = [int(x) for x in re.findall('\d+',s)]
fsum = 0
for x in l:
 fsum += x
print(fsum)

