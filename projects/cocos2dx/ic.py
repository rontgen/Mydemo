#!/usr/bin/python
import os
import os.path
import sys
import re
import configparser

from tp import (path2unix,
                   readfile,
                   list_dir)

def read_config(*pathes):
    file_str = readfile(*pathes)
    seach_pattern = re.compile(r'(?<=image_folder_path\=).*')
    #input_path = re.search(r'(?<=image_folder_path\=).*', lambda m:'%s, %s'%(m.group(0), x), file_str)
    print ("## path2unix(os.path.abspath(__file__) = {:s}" .format(os.path.split(os.path.abspath(__file__))[0]))
    work_dir = os.path.split(os.path.abspath(__file__))[0] 
    for line in file_str:
        m = re.search(r'(?<=pngquant_path\=).*', line)
        if m:
            pngquant_path = path2unix(work_dir, m.group(0))
    for line in file_str:
        m = re.search(r'(?<=optipng_path\=).*', line)
        if m:
            optipng_path = path2unix(work_dir, m.group(0))
    return (pngquant_path, optipng_path)

def main():
    print("hello pngquant {:s}" .format(path2unix(os.getcwd())))
    pngquant_path, optipng_path = read_config("tp_config.ini")
    print("pngquant_path = {:s}" .format(path2unix(pngquant_path)))

if __name__ == '__main__':
    main()