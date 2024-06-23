#!/bin/bash
###########################################################
# Function  :统计指定目录下的普通文件、子目录及可执行文件的数目  #
#            统计该目录下所有普通文件字节数总和				  #
# Date      :2021-12-16                                   #
# Author    :庄毅非                                        #
# studentID :3200105872                                   #
###########################################################
#如果参数数量错误，那么输出用法并退出
if [[ $# != 1 ]]; then
    echo "用法: ./script2 文件夹路径"
    exit 0
fi
#分别统计文件数、文件夹数、可执行文件数
files=0
dirs=0
execs=0
bitsForFiles=0
for i in $(ls -A "$1"); do
    #为文件，那么file加一，同时统计其字节数
    if [[ -f "$i" ]]; then
        let files++
        let bitsForFiles+=$(wc -c "$i" | cut -d' ' -f1)
    #为目录，那么dirs加一
    elif [[ -d "$i" ]]; then
        let dirs++
    #为可执行文件，那么execs加一
    elif [[ -x "$i" ]]; then
        let execs++
    fi
done
#输出结果
echo -e "文件数: $files\t 总字节数:$bitsForFiles"
echo "文件夹数: $dirs"
echo "可执行文件数（不包含目录）: $execs"
