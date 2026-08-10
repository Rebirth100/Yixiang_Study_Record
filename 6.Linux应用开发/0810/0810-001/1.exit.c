#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <strings.h>
#include  <unistd.h>
//进程安全退出:
//进程启动 注册需要调用的所有函数的退出处理函数
//进程退出前调用exit结束进程
void function()
{
    fprintf(stdout,"call:%s  inLine:%d OnFile:%s",
        __FUNCTION__,__LINE__,__FILE__);
}


int main()
{
    //注册function的退出处理函数
    atexit(function);
    function();
    //_exit(0);
    exit(0);
}


// #include <unistd.h>
// void _exit(int status);

// #include <stdlib.h>
// void exit(int status);
