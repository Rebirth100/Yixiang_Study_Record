# 项目：0623
# 文件：02字符串
# 作者: Update
# 日期: 2026/6/23 09:14
# coding:utf-8

# mess = "默认情况下，MySQL 数据库是无法远程访问的，需要修改配置并重启服务。"
#
# print(mess.find("MySQL"))
# print(mess.find("20",10,21))
#
# print(mess.replace("MySQL","Java"))
# print(mess.replace("Java","Python",1))

# isdigit()
# year = input("请输入你的出生年份：")
# if year.isdigit():
#     print(2026-int(year))
# else:
#     print("输入有误")

# 要求用户输入一个数字，可以是整数，可以是小数(只能有一个点)
# number = input("请输入一个数字：")
# if number.replace(".","",1).isdigit():
#     print("是数字")
# else:
#     print("err")


# title = "welcome to china"
# print(title.upper())
# print(title.lower())
# print(title.title())
# print(title.capitalize())
#
# print(title.isupper())
# print(title.islower())
# print(title.istitle())


alcohol = float(input("请输入血液酒精浓度(mg/100ml)："))
result = "醉驾" if alcohol >= 80 else ("酒驾" if alcohol >= 20 else "未喝酒")
print(f"判断结果：{result}")

alcohol = int(input("请输入血液酒精浓度(mg/100ml)："))
result = "醉驾" if alcohol >= 80 else ("酒驾" if alcohol >= 20 else "未喝酒")
print(f"检测结果：{result}")
