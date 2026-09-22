# 项目：0622
# 文件：03输入输出
# 作者: Update
# 日期: 2026/6/2209:56
# coding:utf-8
from pymsgbox import prompt

# 输出(output):将程序信息或结果显示在控制台
# 输入(input):通过键盘打字给程序下达指令
#1.print默认以换行符结尾
print("hello")
print("world")
# 通过end来指定以什么内容结尾
print("hello",end="❤️")
print("China")
# 2.多个内容用逗号连接，实际输出逗号会变成空格
print("我今年",18,"了")
print("我今年"+"18"+"了")

# 输入(input):通过键盘打字给程序下达指令
# 会阻塞程序运行，只有用户敲回车才会继续向下执行
name = input("你叫什么：")
print("你好"+name)
year=input("你是哪年出生：")
# 输入的内容的类型都是str类型，数学运算必须用数字类型，所以需要类型转换后才能运算
print("我猜你今年",2026-int(year),"岁")