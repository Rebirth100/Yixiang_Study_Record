#ifndef  NAME_H_TEST_HGG_20260808
#define  NAME_H_TEST_HGG_20260808
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// GBK/utf-8编码下一个汉字占2字节
#define CHN_CHAR_LEN 3
// 缓冲区最大长度：4个汉字 * 2字节 + 结束符
#define NAME_BUF_LEN (4 * CHN_CHAR_LEN + 1)

// 单姓数组（百家姓常用100个）
const char *single_surnames[] = {
    "赵", "钱", "孙", "李", "周", "吴", "郑", "王", "冯", "陈",
    "褚", "卫", "蒋", "沈", "韩", "杨", "朱", "秦", "尤", "许",
    "何", "吕", "施", "张", "孔", "曹", "严", "华", "金", "魏",
    "陶", "姜", "戚", "谢", "邹", "喻", "柏", "水", "窦", "章",
    "云", "苏", "潘", "葛", "奚", "范", "彭", "郎", "鲁", "韦",
    "昌", "马", "苗", "凤", "花", "方", "任", "袁", "柳", "鲍",
    "史", "唐", "费", "廉", "岑", "薛", "雷", "贺", "倪", "汤",
    "滕", "殷", "罗", "毕", "郝", "邵", "常", "傅", "康", "伍",
    "余", "元", "卜", "顾", "孟", "平", "黄", "和", "穆", "萧",
    "尹", "姚", "邵", "湛", "汪", "祁", "毛", "狄", "成", "宋"
};
#define SINGLE_SUR_COUNT (sizeof(single_surnames) / sizeof(single_surnames[0]))

// 复姓数组（少量经典复姓，用于生成4字姓名）
const char *double_surnames[] = {
    "欧阳", "司马", "上官", "司徒", "诸葛", "皇甫", "公孙", "慕容"
};
#define DOUBLE_SUR_COUNT (sizeof(double_surnames) / sizeof(double_surnames[0]))

// 名字常用汉字库（男女通用中性字）
const char *given_chars[] = {
    "伟", "芳", "静", "敏", "磊", "强", "娜", "丽", "杰", "娟",
    "涛", "明", "超", "秀", "霞", "平", "刚", "慧", "莹", "鹏",
    "宇", "浩", "轩", "欣", "怡", "梓", "辰", "涵", "博", "睿",
    "雨", "晨", "泽", "航", "奕", "嘉", "琪", "琳", "峰", "恒"
};
#define GIVEN_CHAR_COUNT (sizeof(given_chars) / sizeof(given_chars[0]))

/**
 * @brief 随机生成中文姓名
 * @param buf 输出缓冲区，外部定义数组传入
 * @return 无，结果存入buf
 * 姓名规则：总汉字数 2 / 3 / 4
 */
void generateChineseName(char buf[])
{
    // 清空缓冲区
    memset(buf, 0, NAME_BUF_LEN);

    // 随机决定总汉字长度：2、3、4
    int total_len = rand() % 3 + 2; // 2,3,4

    if (total_len == 2)
    {
        // 2字：单姓1字 + 名1字
        const char *sur = single_surnames[rand() % SINGLE_SUR_COUNT];
        const char *name = given_chars[rand() % GIVEN_CHAR_COUNT];
        strcat(buf, sur);
        strcat(buf, name);
    }
    else if (total_len == 3)
    {
        // 3字：单姓1字 + 名2字
        const char *sur = single_surnames[rand() % SINGLE_SUR_COUNT];
        const char *n1 = given_chars[rand() % GIVEN_CHAR_COUNT];
        const char *n2 = given_chars[rand() % GIVEN_CHAR_COUNT];
        strcat(buf, sur);
        strcat(buf, n1);
        strcat(buf, n2);
    }
    else if (total_len == 4)
    {
        // 4字：复姓2字 + 名2字
        const char *sur = double_surnames[rand() % DOUBLE_SUR_COUNT];
        const char *n1 = given_chars[rand() % GIVEN_CHAR_COUNT];
        const char *n2 = given_chars[rand() % GIVEN_CHAR_COUNT];
        strcat(buf, sur);
        strcat(buf, n1);
        strcat(buf, n2);
    }
}
#endif