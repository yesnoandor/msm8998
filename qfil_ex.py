#! /usr/bin/env python
# -*- coding: utf-8 -*-

'''
                   _ooOoo_
                  o8888888o
                  88" . "88
                  (| -_- |)
                  O\  =  /O
               ____/`---'\____
             .'  \\|     |//  `.
            /  \\|||  :  |||//  \
           /  _||||| -:- |||||-  \
           |   | \\\  -  /// |   |
           | \_|  ''\---/''  |   |
           \  .-\__  `-`  ___/-. /
         ___`. .'  /--.--\  `. . __
      ."" '<  `.___\_<|>_/___.'  >'"".
     | | :  `- \`.;`\ _ /`;.`/ - ` : | |
     \  \ `-.   \_ __\ /__ _/   .-` /  /
======`-.____`-.___\_____/___.-`____.-'======
                   `=---=' 
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ 
         佛祖保佑       永无BUG 
'''
 
'''
Created on 2017年8月21日

@author: wenyu_xu
@mail: wellok@139.com

'''

import xml.etree.ElementTree as ET
import os;

if __name__ == '__main__':
    # 创建qfil目录
    cmd = "mkdir -p ./qfil"
    print(cmd)
    return_code=os.system(cmd);
    print(return_code);
    
    # 根据xml,获取下载的文件
    tree = ET.ElementTree(file='contents.xml') 
    print(tree)
    
    download_node_list = tree.findall('.//download_file')
    print(type(download_node_list))
    print(download_node_list)
    for download_node in download_node_list:
        #print(child.tag, child.attrib)
        for child in download_node:
            #print(a.tag,a.attrib)
            print(child.tag,child.text)
            
            if child.tag == "file_name":
                name = child.text
            if child.tag == "file_path":
                path = child.text 
        
        cmd = "mkdir -p ./qfil/%s" % (path)
        print(cmd)
        return_code=os.system(cmd);
        print(return_code);

        cmd = "cp -rf ./%s%s ./qfil/%s" % (path,name,path)
        print(cmd)
        return_code=os.system(cmd);
        print(return_code);
        
        
    # 抽取prog_ufs_firehose_8998_ddr.elf
    cmd = "cp -rf ./boot_images/QcomPkg/Msm8998Pkg/Bin/8998/LA/RELEASE/prog_ufs_firehose_8998_ddr.elf ./qfil/boot_images/QcomPkg/Msm8998Pkg/Bin/8998/LA/RELEASE/"
    print(cmd)
    return_code=os.system(cmd);
    print(return_code);
    
    # 抽取rawprogram_unsparse0.xml
    cmd = "cp -rf ./common/build/ufs/bin/asic/sparse_images/rawprogram_unsparse0.xml ./qfil/common/build/ufs/bin/asic/sparse_images/"
    print(cmd)
    return_code=os.system(cmd);
    print(return_code);
    
    # 抽取contents.xml
    cmd = "cp -rf ./contents.xml ./qfil/"
    print(cmd)
    return_code=os.system(cmd);
    print(return_code);
    
    #for book_list in download_node:
    #    print(type(book_list))                       # 对查找后的结果遍历  
    #    print("book_list",book_list) 
    #    for book in book_list:
    #        print(book.text)
    
    #for elem in tree.iter(tag='download_file'):
    #   print(elem.get_text())
        #print(elem.text)
    pass
