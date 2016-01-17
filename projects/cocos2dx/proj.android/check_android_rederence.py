#coding:uft-8
#!/usr/bin.bash
"""reorder android library reference
    Ahthor:gwang
    Date:2015-07-04
	1.traverse folder and find all project.properties file: 
	param[1]:foloder path
	2.for each project.properties, 
	检测所有以android.library.reference.[0-9]+=开头的行,
	获取到=后的字符串,并得到其数目
	3.删除原android.library.reference.行
	4.将字符串append的方式写入
"""
import os
import os.path
import sys
import codecs
import re

def get_file_list():
    print "[][get_file_list]: start"

def get_reference_str():
    print "[][get_file_list]: start"    

def del_origin_reference():
    print "[][get_file_list]: start"

def output_new_reference():
    print "[][get_file_list]: start"
    
def main():
	print "main start"
	#1. 
	get_file_list()
	#2.
    get_reference_str()
    #3.
    del_origin_reference()
    #4.output_my_reference
    output_new_reference()
	print "main complete"

if __name__ == '__main__':
	main()