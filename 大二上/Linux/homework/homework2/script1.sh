#!/bin/bash
###########################################################
# Function  :获取用文件的拥有者和最后更新时间				   #
# Date      :2021-12-16                                   #
# Author    :庄毅非                                        #
# studentID :3200105872                                   #
###########################################################

# 检查命令行参数，如果不是1，在输出用法之后退出
if [[ $# == 0 || $# -gt 1 ]]; then
    echo "用法: ./script1.sh 文件名"
    exit 0
fi
if [[ -f $1 ]]; then
    set -- $(ls -l "$1")
    #获取拥有者
    owner="$3"
    #获取最后更新时间
    updTime="$6/$7/$8"
    echo -e "owner'name : \n\t$owner\nlast updated time: \n\t$updTime"
fi
