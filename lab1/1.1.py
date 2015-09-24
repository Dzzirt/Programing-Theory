# coding=utf-8 Кузин Никита ПС-21



# Псевдокод:
# из urllib подключаем urlretrieve
# из pyquery - PyQuery
# а так же request и urlparse
# с клавиатуры вводим url
# получаем страничку
# для каждого <img> на страничке :
#       собираем абсолютный адрес,  скачиваем и сохраняем картинку


from urllib import urlretrieve
from pyquery import PyQuery
import requests, urlparse

url = raw_input()
page = requests.get(url).text
count = 0
for image in PyQuery(page)("img"):
    splittedPage = image.get("src").split("/")
    fileName = splittedPage[len(splittedPage) - 1][len(splittedPage[len(splittedPage) - 1]) - 4:]
    try:
        urlretrieve(urlparse.urljoin(url, image.get("src")), './' + str(count) + fileName)
    except UnicodeError:
        count += 1
    count += 1
