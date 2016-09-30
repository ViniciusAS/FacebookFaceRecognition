# -*- encoding=utf-8 -*-

import string

import requests
#import dryscrape
from bs4 import BeautifulSoup

def getPageLinks( url, cont ):
    session = requests.Session()
    session.cookies.clear()
    response = session.get( url ).html()
    soup = BeautifulSoup(response,'lxml')
    content = soup.find(id="content")
    foundLinks = []
    for link in content.find_all('a'):
        foundLinks.append(link)
    if len(foundLinks) == 2:
        print( "Tentativa "+str(cont) )
        arq = open("./teste.html", 'w')
        arq.write(str(soup))
        arq.close()
        cont += 1
        getPageLinks( url, cont )
    else:
        print( "Found links: ", len(foundLinks) )
        print( foundLinks )
    

#getPageLinks("https://www.facebook.com/directory/people/A")

baseLinks = []
for L in list(string.ascii_uppercase):
    baseLinks.append( "http://www.facebook.com/directory/people/" + L )

getPageLinks(baseLinks[0], 0)

