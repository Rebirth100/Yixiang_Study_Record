# 项目：0624
# 文件：07函数
# 作者: Update
# 日期: 2026/6/24 15:19
# coding:utf-8


#创建函数:

def run():
    print("start...")
    print("run...")

run()

#函数参数
def plus (a,b):
    print(a+b)

plus(20,3)
plus(10,300)
plus(3000,1024)

plus(b=3,a=20)

def area(r,PI=3.14):
    print(PI*r*r)

area(100)
area(100,3.14159265357)

def sum(*total):
    t=0
    for x in total:
        t+=x
    print(t)


sum(1,2,3,4,5,6,7,8,9)


#课堂练习：创建一个函数max，传入任意个数字，计算最大值
# 定义函数 max，使用 *args 接收任意多个数字
def max(*args):
    if len(args) == 0:
        return "请至少传入一个数字"
    max_num = args[0]
    for num in args:
        if num > max_num:
            max_num = num
    return max_num


# 测试调用
print(max(12, 35, 9, 78, 24))  # 输出 78
print(max(5, 1, 99, -3))  # 输出 99
print(max(10))  # 输出 10


def show():
    print("----------show begin-------------")
    for x in range (1,10):
        print(x)
        if x == 8:
            return
    print("----------show end-------------")
show()