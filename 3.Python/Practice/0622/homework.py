# 项目：0622
# 文件：homework
# 作者: Update
# 日期: 2026/6/2210:26
# coding:utf-8

# 1、从控制台获取一个人的姓名，年龄，性别，地址，组合输出一句通顺的话
name = input("请输入你的姓名: ")
age = input("请输入你的年龄: ")
sex = input("请输入你的性别：")
address = input("请输入你的地址：")
print(name+"你好。"+"作为一个"+sex+"同学,"+"今年已经"+age+"岁了,"+"目前居住在"+address+"。")



# 2、连续从控制台获取三个价格，将他们相加并保留两位小数点(round(总和,2))
num1 = float(input("请输入第一个数字: "))
num2 = float(input("请输入第二个数字: "))
num3 = float(input("请输入第三个数字: "))

addnum = num1 + num2 + num3
print(round(addnum,2))

# 3、变量a=5,b=10,至少用两种方式将a和b的值进行交换

a = 5
b = 10
a, b = b, a
print(f"a = {a}, b = {b}")

a = 5
b = 10
temp = a
a = b
b = temp
print(f"a = {a}, b = {b}")
# 4、用户输入姓名、性别、年龄、余额、地址。进行格式化输出（四种格式化输出）
name = input("请输入姓名：")
gender = input("请输入性别：")
age = int(input("请输入年龄："))
amount = float(input("请输入余额："))
address = input("请输入地址：")
print("方法一（拼接）：姓名：" + name + "，性别：" + gender + "，年龄：" + str(age) + "，余额：" + str(amount) + "，地址：" + address)
print("方法二（%%格式化）：姓名：%s，性别：%s，年龄：%d，余额：%.2f，地址：%s" % (name, gender, age, amount, address))
print("方法三（format）：姓名：{}，性别：{}，年龄：{}，余额：{:.2f}，地址：{}".format(name, gender, age, amount, address))
print(f"方法四（f-string）：姓名：{name}，性别：{gender}，年龄：{age}，余额：{amount:.2f}，地址：{address}")