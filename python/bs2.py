from urllib.request import urlopen
from bs4 import BeautifulSoup
import ssl
import sys

# Ignore SSL certificate errors
ctx = ssl.create_default_context()
ctx.check_hostname = False
ctx.verify_mode = ssl.CERT_NONE

url = input('Enter - ')
html = urlopen(url, context=ctx).read()
print('Regean')

for i in range(7):
    try:
        soup = BeautifulSoup(html, "html.parser")
        tags = soup('a')
        print(tags[17].contents[0])
        html = urlopen(tags[17].get('href', None), context=ctx).read()
    except Exception as e:
        print(e.__class__,':',e)
        sys.exit(f"No 18th name available for {tags[17].contents[0]}")
