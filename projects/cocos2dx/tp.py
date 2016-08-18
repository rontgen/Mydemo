#!/usr/bin/python

import os
import sys
import re
import subprocess
import shutil
"""
 TexturePacker script

 author:gwang

 Date: 2015-09-01

 Descrip: run textpacker in command line according to config file : tp_config.ini
"""
is_windows=True if sys.platform=='win32' else False
path_delimiter = ';' if is_windows else ':'


def path2unix(*pathes):
    return re.sub(r'(\\\\|//|\\)', r'/', os.path.join(*pathes))


def search_iterative(searched_key, passed_object):
    if isinstance(passed_object, dict):
        if searched_key in passed_object.keys() and modify:
            return passed_object[searched_key]
        else:
            for k in passed_object.keys():
                search_iterative(searched_key, passed_object[k])


def check_tp_from_env():
    global args_tp
    is_tp_found = False
    for item in os.environ.keys():
        if re.search(r'TEXTURE(_)?PACKER', item,  flags=re.I):
            args_tp = os.environ[item]
            is_tp_found =True
    if not args_tp:
        for item in os.environ.values():
            if re.search(r'TEXTURE(_)?PACKER', item,  flags=re.I):
                list_path = item.split(path_delimiter)
                for subpath in list_path:
                    if re.search(r'TEXTURE(_)?PACKER', subpath,  flags=re.I):
                        args_tp = subpath
                        is_tp_found =True
    if not is_tp_found:
        raise EnvironmentError('TexturePacker:[%s] is not found.'%args_tp)


def readfile(*pathes):
    file_path = path2unix(*pathes)
    if not os.path.exists(file_path):
        raise LookupError("[tp][readfile]: file not exists for path = {:s}" .format(*pathes))
    with open(file_path, 'r', encoding='utf-8') as fin:
        file_str = fin.readlines()
    return file_str


def read_config(*pathes):
    file_str = readfile(*pathes)
    seach_pattern = re.compile(r'(?<=image_folder_path\=).*')
    #input_path = re.search(r'(?<=image_folder_path\=).*', lambda m:'%s, %s'%(m.group(0), x), file_str)
    print ("## path2unix(os.path.abspath(__file__) = {:s}" .format(os.path.split(os.path.abspath(__file__))[0]))
    work_dir = os.path.split(os.path.abspath(__file__))[0]
    for line in file_str:
        m = re.search(r'(?<=image_folder_path\=).*', line)
        if m:
            input_path = path2unix(work_dir, m.group(0))
    for line in file_str:
        m = re.search(r'(?<=output_folder_path\=).*', line)
        if m:
            output_path = path2unix(work_dir, m.group(0))
    return (input_path, output_path)

def list_dir(sourceDir, include_source=None, include_file=True):
    """与 :func:`os.listdir()` 类似，但提供一些筛选功能，且返回生成器对象。

     Args:
       1.str sourceDir: 待处理的文件夹。
       2. bool include_source: 遍历结果中是否包含源文件夹的路径。
       3. bool include_file:    是否包含文件。True 表示返回的内容中既包含文件，又
                                包含文件夹；Flase 代表仅包含文件夹。
     Return: 一个生成器对象。
    """
    for cur_file in os.listdir(sourceDir):
        if cur_file.lower() == ".ds_store":
            continue
        pathWithSource = os.path.join(sourceDir, cur_file)
        if include_file or os.path.isdir(pathWithSource):
            if include_source:
                yield pathWithSource
            else:
                yield cur_file

def add_plist_prefix(source, folder_name, plist_path):
    """
        add_plist_prefix

        Descrip:
                for the reason that there are no prefix path for png file after plist generate,
                hydra need to add prefix_path

        Args:
            folder_name:temp_folder name
            plist_path: plist path for modification
    """
    file_path = os.path.join(source, folder_name)
    for root, dirs, files in os.walk(file_path):
        for file in files:
            if file.endswith('.png'):
                img_path = path2unix(root, file)
                shell_path = path2unix(os.path.split(os.path.dirname(img_path))[1], file)
                prefix_path = re.search(r'(images.*)', img_path).group(0)
                with open(plist_path, 'r', encoding='utf-8') as fin:
                    plist_txt = fin.readlines()
                fin.close()
                with open(plist_path, 'w', encoding='utf-8') as fout:
                    for line in plist_txt:
                        if line.find("<key>%s</key>" %file) != -1:
                            line = re.sub(r'<key>.*</key>', "<key>%s</key>" %prefix_path, line)
                        elif line.find("<key>%s</key>" %shell_path) != -1:
                            line = re.sub(r'<key>.*</key>', "<key>%s</key>" %prefix_path, line)
                        fout.write(line)
                fout.close()

def textpacker_func(source, output):
    check_tp_from_env
    global args_tp
    args_tp = None
    if not args_tp:
        check_tp_from_env()
    print('[textpacker_func]:{0:s}' .format(args_tp))
    tp_path = os.path.join(args_tp, 'TexturePacker')
    sub_dir_list = list(filter(lambda x :x != 'package' and x != 'unpackage', list(list_dir(source))))
    temp_path = os.path.join('temp')
    if os.path.exists(temp_path):
        shutil.rmtree(temp_path)
    for item in sub_dir_list:
        src_path = os.path.join(source, item)
        temp_folder = os.path.join(temp_path, item)
        shutil.copytree(src_path, temp_folder)
        for root, dirs, files in os.walk(temp_folder, topdown=True):
            for file in files:
                if file.endswith('.png'):
                    file_path = path2unix(root, file)
                    target_path = path2unix(output, item + '.png')
                    plist_path = target_path.replace('.png', '.plist')
                    if not os.path.exists(target_path) and not os.path.exists(plist_path):
                        print("file_path = {:s}" .format(file_path))
                        print("plist_path = {:s}" .format(plist_path))
                        return_code = subprocess.call([tp_path, temp_folder,'--sheet', target_path, '--data', plist_path, '--disable-rotation', '--dither-fs-alpha'])
                        if return_code != 0:
                            raise Exception("[hydra][package_image_hydra]: return_code = %s" %return_code)
                        add_plist_prefix(source, item, plist_path)
        shutil.rmtree(temp_folder)
    shutil.rmtree(temp_path)


def pre_tp(path):
 print("[tp][post_deploy]: clean folder_path = {:s}" .format(path))
 if os.path.exists(path):
    shutil.rmtree(path)
    os.mkdir(path)
 else:
    os.mkdir(path)


def main():
    input_path, output_path = read_config("tp_config.ini")
    pre_tp(output_path)
    print ("[main] inputpath ={:s}" .format(input_path))
    print ("[main] output_path ={:s}" .format(output_path))
    textpacker_func(input_path, output_path)
    print ("[main] mission complete")

if __name__ == '__main__':
    main()
