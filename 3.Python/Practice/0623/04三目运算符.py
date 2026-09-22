# 项目：0623
# 文件：04
# 作者: Update
# 日期: 2026/6/23 14:06
# coding:utf-8


# 循环1-10，遇到8的时候退出循环
# i = 1
# while i <= 10:
#     print(i,end=" ")
#     if i==8:
#         break
#     i+=1
# else:
#     print("while 1 结束")

# 循环1-10，遇到8的时候跳过(1 2 3 4 5 6 7 9)
i = 1
while i <= 10:
    if i==8:
        i += 1
        continue
    print(i, end=" ")
    i += 1
else:
    print("while 2 结束")