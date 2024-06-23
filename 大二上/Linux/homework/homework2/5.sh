#!/bin/bash
###########################################################
# Function  :bash实现文件备份和同步							#
# Date      :2021-12-16                                   #
# Author    :庄毅非                                        #
# studentID :3200105872                                   #
###########################################################

#######################################
# 递归比较输入的两个文件夹，实现要求中的备份功能
# 使用的全局变量:
#   无
# 参数:
#   $1为源文件夹，$2为目标文件夹
# 返回值:
#   无
#######################################
function dirsyncHelper() {
    # 检查目标目录是否存在，如果不存在，就先创建
    if [ ! -d "$2" ]; then
        mkdir "$2"
    fi
    # 获取源目录中所有子文件，子目录列表
    dirlist=$(ls "$1")
    # 在循环中遍历文件/文件夹
    for itemName in ${dirlist[*]}; do
        if [ -f "$1/$itemName" ]; then
            # 如果是文件，目标目录不存在该文件或者目标目录中的文件的最后修改时间比源文件中早，则直接copy
            if [ ! -f "$2/$itemName" ]; then
                cp "$1/$itemName" "$2/$itemName"
            else
                # 使用test中的-nt参数比较两文件最后更新时间，如果源文件比目标文件更新时间更近，那么使用源文件更新木包文件
                if [ "$1/$itemName" -nt "$2/$itemName" ]; then
                    cp "$1/$itemName" "$2/$itemName"
                fi
            fi
        elif [ -d "$1/$itemName" ]; then
            # 如果是目录，并且目标文件夹中不存在该目录，则先创建目录
            if [ ! -d "$2/$itemName" ]; then
                mkdir -p "$2/$itemName"
            fi
            # 递归检查
            dirsyncHelper "$1/$itemName" "$2/$itemName"
        fi
    done
}

#######################################
# 递归比较输入的两个文件夹，实现要求中的同步功能（类似上述函数的逆过程）
# 使用的全局变量:
#   无
# 参数:
#   $1为目标文件夹，$2为源文件夹
# 返回值:
#   无
#######################################
function dirsyncHelper_reverse() {
    # 获取目标文件夹中的文件、文件夹列表
    dirlist=$(ls "$1")
    for itemName in ${dirlist[*]}; do
        if [ -f "$1/$itemName" ]; then
            # 如果是文件，而源文件夹中不存在该文件,那么删除当前目标文件夹中的该文件
            if [ ! -f "$2/$itemName" ]; then
                rm -i "$1/$itemName"
            else
                #检查目标文件夹中文件的修改时间，并在其早于源文件夹对应文件中修改时间的时候进行更新
                if [ "$1/$itemName" -nt "$2/$itemName" ]; then
                    # echo "$1/$name covers $2/$name"
                    cp "$1/$itemName" "$2/$itemName"
                fi
            fi
        elif [ -d "$1/$itemName" ]; then
            # tag判断文件夹是否被删除，如果没有被删除，递归执行本函数，否则进入下一轮循环
            tag="1"
            # 如果是目录，并且源文件夹不存在该目录，则直接删除当前目标文件夹中的目录
            if [ ! -e "$2/$itemName" ]; then
                rm -rf "$1/$itemName"
                tag="0"
            fi
            # 递归检查
            if [ "$tag" == "1" ]; then
                dirsyncHelper_reverse "$1/$itemName" "$2/$itemName"
            fi
        fi
    done
}

# counter=0
# 检查命令行参数
if [ ! $# -eq 2 ]; then
    echo "用法: dirsync dir1 dir2"
    exit 0
fi

# 将源文件夹复制到目标文件夹
dirsyncHelper "$1" "$2"

# 遍历目标文件夹，检查是否出现源文件夹中没有的文件或文件夹，如果有，检查源文件夹时间，更新文件夹中的旧文件
dirsyncHelper_reverse "$2" "$1"
