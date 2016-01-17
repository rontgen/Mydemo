#encoding:utf-8
#!/usr/bin/python
__author__ = 'gwang'
__date__ = '2015-09-08'

import os
import os.path
import sys
import os
import re
from configparser import ConfigParser
from tp import path2unix
import subprocess

class INIConf(ConfigParser):
    """对 INI 格式的配置文件做了一些变化，使其可以支持列表。
    只需要将 section 的名称设置为 [@list name] 即可加入一个名称为 name 的 section。
    这个 sectioni 中的每一行都作为列表的一项。
    """

    _LIST_TMPL = r"""
        @(list)?                            # @ or @list
        \s*(?P<header>\w+)                  # very permissive!
        """
   
    LISTCRE = re.compile(_LIST_TMPL, re.VERBOSE)

    def __init__(self):
        # Only use the '=' as a delimiter
        super().__init__(allow_no_value=True, delimiters=('='))

    # override RawConfigParser to protect case.
    def optionxform(self, optionstr):  
        return optionstr

    def _get_list_name(self, section):
        if not self.LISTCRE.match(section):
            section = "@list "+section
        return section

    def has_list(self, section):
        return self.has_section(self._get_list_name(section))

    def list(self, section):
        return self.options(self._get_list_name(section))

    def lists(self):
        list_sections = []
        for name in self.sections():
            m = self.LISTCRE.search(name)
            if m:
                list_sections.append(m.group('header'))
        return list_sections

class PngquantBase(object):
    #--max 50 --min 1 --speed 1 --size 0
    def __init__(self, size_limit, size_min, size_max, speed):
        self.size_limit = size_limit*1024
        self.size_min = size_min
        self.size_max = size_max
        self.speed = speed
        pqpath = None
        if sys.platform == 'win32':
            pqpath = 'pngquant/win32/pngquant.exe'
            self.pq = path2unix(pqpath)
        elif sys.platform == 'darwin':
            pqpath = 'pngquant/mac/pngquant'
            self.pq = path2unix(pqpath)
        else:
            pqpath = shutil.which('pngquant')
            self.pq = pqpath

    def _get_param(self, inputfile, outputfile):
        quality = "%s-%s"%(self.size_min, self.size_max)
        return [self.pq, '--verbose', '--force',
                '--quality', quality,
                '--speed', str(self.speed),
                '--output', outputfile,
                inputfile]

    def run_dir(self, image_dir):
        files = get_files(image_dir, ['png'])
        filterfiles = []
        for f in files:
            if os.path.getsize(f) > self.size_limit:
                filterfiles.append(f)
        for f in filterfiles:
            xargs = self._get_param(f, f)
            print('===================Optimizing...\n'+' '.join(xargs))
            subprocess.call(xargs)

class PngquantByArgs(PngquantBase):
    def __init__(self, args):
        super().__init__(args.size, args.min, args.max, args.speed)

def merge_INIConf(a, b):
    """用 b 的内容覆盖 a 的内容（若重名），并返回 a
    """
    for sname in b.sections():
        if a.has_section(sname):
            for oname in b.options(sname):
                a[sname][oname] = b[sname][oname]
        else:
            a[sname] = b[sname]
    return a

def get_files(path, ext=[], include=True):
    """遍历提供的文件夹的所有子文件夹，返回生成器对象。
    :param str path: 待处理的文件夹。
    :param list ext: 扩展名列表。
    :param bool include:    若值为 True，代表 ext 提供的是包含列表；
                            否则是排除列表。
    :returns: 一个生成器对象。
    """
    has_ext = len(ext)>0
    for p, d, fs in os.walk(path):
        for f in fs:
            if has_ext:
                in_ext = False
                for name in ext:
                    if f.endswith(name):
                        in_ext = True
                        break
                if (include and in_ext) or \
                (not include and not in_ext):
                    yield os.path.join(p,f)
            else:
                yield os.path.join(p, f)

def read_confgig():
    __conf = INIConf()
    __conf.read("tp_config.ini", encoding='utf-8')
    list_cprs = []
    list_hqrs = []
    dict_pq_params = {}
    list_cprs = list(path2unix(item) for item in __conf['@list compress_input'] if item)
    list_hqrs = list(path2unix(item) for item in __conf['@list compress hq'] if item)
    for item in __conf['pngquant_params']:
        str_arr = item.split(':')
        if len(str_arr) == 2:
            dict_pq_params[str(str_arr[0])] = int(str_arr[1])
        else:
            raise SyntaxError("[img_comprs][read_confgig]: invalid config format")
            sys.exit(1024)
    return (list_cprs, list_hqrs, dict_pq_params)

def common_cprs(input_path, size_limit=0, size_min=1, size_max=50, speed=1):
    png_ins = PngquantBase(size_limit, size_min, size_max, speed)
    png_ins.run_dir(input_path)

def main():
    cps_cfg, hq_cps_cfg, dict_pq_params = read_confgig()
    print ("[img_comprs][main]cps_cfg={!s:s}" .format(cps_cfg))
    print ("[img_comprs][main]hq_cps_cfg={!s:s}" .format(hq_cps_cfg))
    print ("[img_comprs][main]dict_pq_params=={!s:s}" .format(dict_pq_params))
    for path in cps_cfg:
        if not dict_pq_params:
            common_cprs(str(path))
        else:
            common_cprs(str(path),dict_pq_params['size_limit'], dict_pq_params['size_min'], dict_pq_params['size_max'], dict_pq_params['speed'])


#-----------main---------------
if __name__ == '__main__':
    main()