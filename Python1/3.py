import itertools
even_selector = [True if x%2==0 else False for x in range(20)]
odd_selector = [False if x%2==0 else True for x in range(20)]
#print(even_selector)
#print(odd_selector)
evens = list(itertools.compress(range(20),even_selector))
odds = list(itertools.compress(range(20),odd_selector))
print(evens,odds,sep='\n')
