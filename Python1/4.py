import re

pattern = re.compile('\d{10}$')
number = input("Enter a phone number: ").strip()
rslt = pattern.match(number)
#print(rslt)
try:
 print(rslt.group(0))
except:
 print("No match")
