//C语言练习实例1：题目：有 1、2、3、4 四个数字，能组成多少个互不相同且无重复数字的三位数？都是多少？

#include <stdio.h>

int main(void) {
    int i, j, k;        //定义三个数
    int count = 0;;     //定义初识次数
    printf("1,2,3,4可组成%d组无重复数字：\n", count);
    for (size_t i = 1; i <= 4; i++) {
        for (size_t j = 1; j <= 4; j++) {
            for (size_t k = 1; k <= 4; k++) {
                if (i != j && i != k && j != k)
                {
                    count++;
                    printf("第%d组：%d%d%d\n",count,i, j, k);
                };
            }
        }
    }
    return 0;
}
