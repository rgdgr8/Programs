import json
import urllib.request

url = 'http://py4e-data.dr-chuck.net/comments_1247650.json'
data = urllib.request.urlopen(url).read().decode()

info = json.loads(data)['comments']
print('User count:', len(info))

jsum = 0
for item in info:
 jsum += int(item['count'])

print(jsum)
