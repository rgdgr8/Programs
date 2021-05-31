import urllib.request, urllib.parse, urllib.error
import xml.etree.ElementTree as ET

try:
	while True:
		url = 'http://py4e-data.dr-chuck.net/comments_42.xml'
		if len(url) < 1: break

		uh = urllib.request.urlopen(url)
		data = uh.read().decode()
		print(data)
		tree = ET.fromstring(data)
		results = tree.findall('.//count')
		print('len={}'.format(len(results)))
		csum = 0
		for res in results:
			num = res.text
			#print(num,type(num))
			csum += int(num)

		print(csum)
		break
except:
	pass
