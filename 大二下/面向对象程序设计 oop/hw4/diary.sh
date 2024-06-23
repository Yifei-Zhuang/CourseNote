#!/bin/bash
make
echo "========================================"
echo "welcome to diary management system"
echo "you have 5 commands"
echo "1.pdadd yyyy-mm-dd"
echo "2.pdlist or pdlist yyyy-mm-dd yyyy-mm-dd"
echo "3.pdshow yyyy-mm-dd"
echo "4.pdremove yyyy-mm-dd"
echo "5.quit"
echo "========================================"
while ((1)); do
    echo "input your choice, and input quit to exit"
    read Command value1 value2

    if [[ $Command == "pdadd" ]]; then
        ./pdadd $value1
    elif [[ $Command == "pdlist" ]]; then
        if [[ $value1 == "" ]]; then
            ./pdlist
        else
            ./pdlist $value1, $value2
        fi
    elif [[ $Command == "pdremove" ]]; then
        ./pdremove $value1
    elif [[ $Command == "pdshow" ]]; then
        ./pdshow $value1
    elif [[ $Command == "quit" ]]; then
        exit 0
    else
        echo "wrong input"
    fi
done
