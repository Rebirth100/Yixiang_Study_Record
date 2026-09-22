# 项目：0624
# 文件：homework
# 作者: Update
# 日期: 2026/6/24 11:25
# coding:utf-8


# 1、某个公司采用公用电话传递数据，数据是四位的整数，在传递过程中是加密的
#规则:每位数字都加上5然后除以10的余数代替该数字，再将第一位和第四位交换，第二位和第三位交换
"""
num = input("请输入一个四位整数：")
if len(num) != 4 or not num.isdigit():
    print("请输入有效的四位整数")
else:
    digits = [int(ch) for ch in num]
    encrypted = [(d + 5) % 10 for d in digits]

    encrypted[0], encrypted[3] = encrypted[3], encrypted[0]
    encrypted[1], encrypted[2] = encrypted[2], encrypted[1]
    result = ''.join(str(d) for d in encrypted)
    print("加密后的结果是：", result)
"""




#2、判断一个数组是否是回文数组，如[1,2,3,2,1]是回文数组，正着读和反着读是一样的(用两种方法)




#3、统计一组数据里每个值出现的次数
#['小明','张三','李四','张三','张三','小明','王五','王五']


#4、把下面列表里重复的元素去除['小明','张三','李四','张三','张三','小明','王五','王五']
'''
lst = ['小明','张三','李四','张三','张三','小明','王五','王五']
new_lst = list(set(lst))
print(new_lst)
'''




#5、设计一个函数，calc，传递两个数字和一个符号(+,-,*,/),根据符号的不同，产生不同的结果(除数不能为零)

def calc(num1, num2, op):
    if op == '+':
        return num1 + num2
    elif op == '-':
        return num1 - num2
    elif op == '*':
        return num1 * num2
    elif op == '/':
        if num2 == 0:
            return "错误：除数不能为零"
        else:
            return num1 / num2
    else:
        return "错误：不支持的运算符"


# 测试
print(calc(10, 20, '+'))   # 30
print(calc(30, 50, '-'))    # -20
print(calc(6, 7, '*'))      # 42
print(calc(10, 2, '/'))     # 5.0
print(calc(8, 0, '/'))      # 错误：除数不能为零