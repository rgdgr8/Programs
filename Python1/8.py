l = [x for x in range(51)]
l = list(filter((lambda x : x%5==0),l))
print(l)
