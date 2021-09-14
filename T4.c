// 通过 fork/exec/pipe/dup 实现 cat </etc/passwd | wc -l >result.txt 
//
// + 父进程创建子进程
//   - 在父进程中实现功能 cat </etc/passwd
//   - 在子进程中实现功能 wc -l >result.txt
//   - 不能实现为
//     * 在子进程中实现功能 cat </etc/passwd
//     * 在父进程中实现功能 wc -l >result.txt
//
// + 该题不要求实现一个通用的 shell 程序
//   - 不需要使用 strtok 对字符串进行分割处理
//   - 假设字符串已经分割处理好了
//     * 父进程，使用 execlp("cat") 执行命令，使用 open("/etc/passwd") 打开文件
//     * 子进程，使用 execlp("wc") 执行命令，使用 open("result.txt") 打开文件
//
// + 请严格按要求完成
//   - 把作业 sh3.c 的内容复制过来，是没有分数的
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(){
    int pid;
    int fd[2];
    char buf[10000];
    int fd1,fd2;

    fd1 = open("/etc/passwd", O_RDONLY);

    pipe(fd);
    pid = fork();
    if (pid == 0) {
        // child
        fd2 = open("result.txt",O_RDWR|O_CREAT);
        dup2(fd[0], 0);
        close(fd[0]);
        close(fd[1]);

        dup2(fd2, 1);
        execlp("wc", "wc", "-l", NULL);
        close(fd2);
        
        exit(0);
    }
    // parent
    dup2(fd1, 0);
    dup2(fd[1], 1);
    close(fd[0]);
    close(fd[1]);

    execlp("cat", "cat", NULL);
    close(fd1);
    return 0;
}