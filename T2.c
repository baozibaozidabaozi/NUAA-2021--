// 实现命令 mygrep string file
// + 该命令逐行读取文件，如果行包括目标字符串，则打印该行
// + 该命令有两个命令行参数
//   - 参数 string，要搜索的字符串
//   - 参数 file，要查找的文件名
// 
// 例子，在文件 /etc/passwd 中查找字符串 root，打印包含该字符串的行
// $ ./mygrep root /etc/passwd
// root:x:0:0:root:/root:/bin/bash
//
// 提示，可以使用函数 strstr 在字符串中查找字符串
// https://www.runoob.com/cprogramming/c-function-strstr.html
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc,char *argv[]){
    int fd1;
    char *buffer;
    int fsize;
    mode_t mode = 0777;
    char* ret;

    fd1 = open(argv[2], O_RDONLY, mode);
    if (fd1 < 0){
        //panic("open");
    }

    fsize=lseek(fd1, 0, SEEK_END);
    buffer=(char*)malloc(fsize*sizeof(char));
    if (!buffer){
        //panic("allocate space");
    }
    lseek(fd1, 0, SEEK_SET);
    int count = read(fd1, buffer, fsize*sizeof(char));
    if (count < 0){
        //panic("read");
    }

    ret = strstr(buffer, argv[1]);
    if(ret){
        printf("%s",buffer);
    }

    close(fd1);
    return 0;
}