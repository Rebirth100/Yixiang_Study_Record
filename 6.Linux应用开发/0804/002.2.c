/*
//作业2:使用按字符操作和按字符串操作两种方式，实现多文件合并
//./app  a b c d e ...g //将a b c d e ...合并到g
*/


#include <stdio.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "用法: %s 源文件1 源文件2 ... 源文件N 目标文件\n", argv[0]);
        return 1;
    }

    char *dest_name = argv[argc - 1];
    FILE *dest = fopen(dest_name, "w");
    if (!dest) {
        perror("打开目标文件失败");
        return 1;
    }

    printf("开始合并（字符串方式）...\n");
    char buf[BUF_SIZE];
    for (int i = 1; i < argc - 1; i++) {
        FILE *src = fopen(argv[i], "r");
        if (!src) {
            fprintf(stderr, "警告：无法打开源文件 %s，跳过。\n", argv[i]);
            continue;
        }
        printf("正在合并: %s\n", argv[i]);

        while (fgets(buf, sizeof(buf), src) != NULL) {
            fputs(buf, dest);
        }

        fclose(src);
    }

    fclose(dest);
    printf("合并完成，目标文件: %s\n", dest_name);
    return 0;
}