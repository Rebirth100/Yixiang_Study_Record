#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include "student.h"
#define SIZE 12
int main()
{
    student s[SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        autoSetStudent(s + i);
    }

    for (int i = 0; i < SIZE; i++)
    {
        getStudentSum((linkNode *)(s + i));
        printf("[%d]\t", i);
        printStudent(&(s[i].node));
    }

    // 位运算 |  &  ! ^  <<  >>

    // Linux系统IO写入文件
    int fd = open("stu.db", O_CREAT | O_WRONLY, 0644);
    if (fd == -1)
    {
        perror("创建数据库文件失败");
        return 0;
    }
    fprintf(stderr, "创建数据库文件成功\n");
    for (int i = 0; i < SIZE; i++)
    {
        ssize_t writeSize = write(fd, s + i, sizeof(student));
        if (writeSize > 0)
        {
            fprintf(stderr, "写入数据%ld字节\n", writeSize);
        }
        if (writeSize == -1)
        {
            perror("写入数据出错");
            break;
        }
    }

    ssize_t writeSize = write(fd, s, sizeof(student) * SIZE);
    if (writeSize > 0)
    {
        fprintf(stderr, "写入数据%ld字节\n", writeSize);
    }
    if (writeSize == -1)
    {
        fprintf(stderr, "写入数据出错");
    }

    close(fd);

    // Linux系统IO读取文件
    student *stu = (student *)malloc(sizeof(student));
    fd = open("stu.db", O_RDWR);
    if (fd == -1)
    {
        perror("打开数据文件出错");
        return 0;
    }

    int index = 0;
    while (1)
    {
        ssize_t readSize = read(fd, (void *)stu, sizeof(student));
        if (readSize > 0)
        {
            fprintf(stderr, "[%d]\t", index);
            printStudent((linkNode *)stu);
            index++;
        }
        if (readSize == 0)
        {

            fprintf(stderr, "关闭数据文件");
            break;
        }
        if (readSize == -1)
        {
            perror("读数据出错");
            break;
        }
    }

    // 从数据库随机读取数据
    while (1)
    {
        char num[12] = "\0";
        fprintf(stderr, "请输入数据的序号:0~%d -1则退出\n", SIZE * 2 - 1);
        fgets(num, sizeof(num), stdin);
        int pos = atoi(num);
        if (pos == -1)
        {
            break;
        }
        if (pos >= 0 && pos <= SIZE * 2 - 1)
        {
            lseek(fd, pos * sizeof(student), SEEK_SET);
            ssize_t readSize = read(fd, (void *)stu, sizeof(student));
            if (readSize > 0)
            {
                fprintf(stderr, "[%d]\t", pos);
                printStudent((linkNode *)stu);
            }
        }
    }

    free(stu);
    close(fd);
    return 0;
}

// #include <unistd.h>
// ssize_t write(int fd, const void buf[.count], size_t count);

// #include <unistd.h>
// ssize_t read(int fd, void buf[.count], size_t count);

// #include <unistd.h>
// off_t lseek(int fd, off_t offset, int whence);
// SEEK_SET : The file offset is set to offset bytes.
// SEEK_CUR : The file offset is set to its current location plus offset bytes.
// SEEK_END : The file offset is set to the size of the file plus offset bytes



//作业:
//1.调用系统IO实现下列命令
//./COPY  A    B    //拷贝文件
//2.调用系统IO实现下列命令
//./COPY  A    B   C  D //合并文件
//3.修改链表实现  调用系统IO存取数据

//录屏：讲解系统io操作文件的核心API