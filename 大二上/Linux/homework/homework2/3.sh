#!/bin/bash
###########################################################
# Function  :判断字符串是否为回文                            #
# Date      :2021-12-16                                   #
# Author    :庄毅非                                        #
# studentID :3200105872                                   #
###########################################################
# 读入字符串，声明数组
read -p "请输入一个字符串: " str
declare -a alphas
counter=0
# 扫描字符串，将为字母的输入存储到数组中
for i in $(seq 0 $((${#str} - 1))); do
    temp=${str:$i:1}
    case "$temp" in
    # 如果是字母，那么添加到数组中，同时counter++
    [a-zA-Z])
        alphas[$counter]=$temp
        counter=$(($counter + 1))
        ;;
    # 如果不是字母，不执行任何操作
    *)
        :
        ;;
    esac
done
# 扫描数组，双指针检查是否为回文
length=${#alphas[@]}
for i in $(seq 0 $(($length - 1))); do
    # 双指针算法判断是否为回文
    if [[ "${alphas[$i]}" != "${alphas[$(($length - $i - 1))]}" ]]; then
        echo "输入的字符串不是回文"
        exit 0
    fi
done
echo "输入的字符串是回文"
