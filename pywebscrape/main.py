import re
import time
import requests
from bs4 import BeautifulSoup

global urls
urls = set()

global s
s = requests.Session()

global scope
scope = "duckduckgo.com"

global seen
seen = set()


global prev
prev = ''


def writefile():
    with open("links.list", "w+")as out:
        for u in globals()['urls']:
            out.write(u+"\n")






def get_url(url, counter):
    if url in globals()['urls'] or url in globals()['seen']:
        print("returning")
        return
    globals()['seen'].add(url)


    # make sure url is valid, and add to list
    # NOTE need to stop this from downloading large files
    res = s.get(url, headers={"User-Agent": "firefox"})
    if res.status_code == 200:
        globals()['urls'].add(url)
        writefile()
    else:
        print("invalid")
        return


    # get all tags
    data = res.text
    if len(data) > 100000:
        print("large =========")
        return

    if data == globals()['prev']:
        print("same")
        return
    globals()['prev'] = data



    soup = BeautifulSoup(data, 'lxml')
    tags = soup.find_all('a')


    for tag in tags:
        # get urls
        link = tag.get_attribute_list('href')[0]


        # add url to set
        if link:
            _link = ''
            # if url part like: `/api`
            if link[0:2] == '//':
                _link = "https:" + link


            elif link[0] == '/' and '?' not in url and '/#' not in url:
                _link = url + link


            # match full url
            elif bool(re.match(".*:\\/\\/.*\\.*", link)) and bool(re.search(globals()['scope'], link)):
                _link = link


            if _link:
                if _link == url or _link+'/' == url or _link == url+'/':
                    continue

                print("running: ", _link)
                get_url(_link, 0)
                globals()['urls'].add(_link)









get_url("https://duckduckgo.com/", 0)








