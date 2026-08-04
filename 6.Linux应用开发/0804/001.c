/*
作业1:输入行数n，文件中有以下内容
比如:输入6，文件内容如下:
a
ab
abc
abcd
abcde
abcdef
*/

#include <stdio.h>

int main() {
    int n;
    printf("请输入行数: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "输入无效，请输入正整数。\n");
        return 1;
    }

    FILE *fp = fopen("output.txt", "w");
    if (!fp) {
        perror("打开文件失败");
        return 1;
    }

    printf("生成内容如下：\n");   // 终端提示
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            char ch = 'a' + j;
            fputc(ch, fp);        // 写入文件
            putchar(ch);          // 输出到终端（不换行）
        }
        fputc('\n', fp);
        putchar('\n');            // 终端换行
    }

    fclose(fp);
    printf("\n文件 output.txt 已生成，共 %d 行。\n", n);
    return 0;
}