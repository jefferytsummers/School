from bs4 import BeautifulSoup
from sys import argv
from requests import get

if argv[1] == '-j':
    r   = get("https://maps.googleapis.com/maps/api/distancematrix/json?origin\
s=" + argv[2] + '&destinations=' + argv[3])
    distance = r.json()['rows'][0]['elements'][0]['distance']['text']
    print("%s between %s and %s" %(distance, argv[2], argv[3]))

elif argv[1] == '-x':
    r   = get("https://maps.googleapis.com/maps/api/distancematrix/xml?origins\
=" + argv[2] + '&destinations=' + argv[3])
    soup = BeautifulSoup(r.text, 'xml')
    distance = str(soup('text')[1])[6:str(soup('text')[1]).\
find("/") - 1]
    print("%s between %s and %s" %(distance, argv[2], argv[3]))

elif argv[1] == '-a':
    url = argv[2]
    r = get(argv[2])
    soup = BeautifulSoup(r.text, "lxml")
    for href in soup('a'):
        href = str(href)
        if 'http:' in href or 'https:' in href:
            href = href[href.find('http'):href.find('"', href.find('http'))]
            print(href)

else:
    print("Incorrect flag")
    exit()
