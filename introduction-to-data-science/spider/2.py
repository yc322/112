# -*- coding:utf-8 -*-
import requests
from bs4 import BeautifulSoup
import sys
import json
import re
reload(sys)
sys.setdefaultencoding("utf-8")

seed="http://5sing.kugou.com/subject/nzpd/index"

def spider(url):
    try:
        res = requests.get(url)
        res.raise_for_status()
        # print res.text
        soup = BeautifulSoup(res.text, 'html.parser')
        #print soup
        musicTitle = soup.select('.view_tit')[0].text  # 歌曲名称
        musicInfo = soup.select('.view_box')[0].select('li')

        list = []
        for item in range(0, 8):
            list.append(musicInfo[item].text)

        data = {}
        data['歌曲名称'] = musicTitle
        for item in list:
            tmp = str(item).split('：')
            data[tmp[0]] = tmp[1].decode()

        json_str = str(json.dumps(data, ensure_ascii=False))

        data_.write(json_str + '\n')
        print (json_str)
    except:
        print "have error"
        return 0


def choose(url):
    mmd=set()
    try:
        res=requests.get(url)
        soup = BeautifulSoup(res.text, 'html.parser')
        link = soup.select('a')
        for item in link:
            t = str(item.get("href"))
            if (t[:4] == "http" and t[7:12] == "5sing"):
                mmd.add(t)
        for a in mmd:
            if (ls.count(a) == 0):
                print a
                ls.append(a)
                output_.write(a + '\n')
    except:
        print "error"

ls=list() #存所有爬过的链接

output_=open('level_1_output.txt','a')
choose("http://5sing.kugou.com/subject/nzpd/index")
output_.close()


for i in range(1,6):
    f=open('level_%d_output.txt'%i,'r')
    input_=f.readlines()
    output_=open('level_%d_output.txt'%(i+1),'a')
    data_=open('level_%d_data.txt'%i,'a')
    for item in input_:
        choose(item)
    for key in input_:
        L = str(key.replace('\n', '').strip())
        # count=count+1



        if (L[:25] == 'http://5sing.kugou.com/yc' and L.find("html") != -1):
            print L
            spider(L)
    output_.close()
    f.close()
    data_.close()




