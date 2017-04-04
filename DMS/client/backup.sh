#!/bin/bash 
#$1表示第一个参数(日志文件)，$2表示第二个参数(备份文件)
#还可以将stderr转换成stdout,使得stderr和stdout都被重定向到同一个文件中
if cp $1 $2 >& /dev/null
then
    if cat /dev/null > $1
    then
        exit 0
    else
        exit 2
    fi
else
    exit 1
fi
