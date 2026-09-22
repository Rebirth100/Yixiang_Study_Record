# 项目：0623
# 文件：homework
# 作者: Update
# 日期: 2026/6/23 11:29
# coding:utf-8



#输出摄氏温度与华氏温度的对照表，要求它从摄氏温度0度到250度，每隔20度为一项，对招标中的条目不能超过10条
#转换关系：华氏温度 = 摄氏温度 * 9 / 5.0 + 32

# ct = 0
# j=1
# print("摄氏温度\t华氏温度")
# while ct < 250 and j<=10:
#     ft = ct* 9 / 5 + 32
#     print(f"{ct}\t\t{ft}")
#     ct += 20
#     j+=1

#给20块钱买可乐，没瓶可乐3块钱，喝完之后退瓶子可以换1块钱，问最多可以喝多少瓶可乐
# money = 20
# price = 3
# count = 0
# while money >= price:
#     c = money//price
#     money = money%price
#     money += c
#     count += c
# print("买了",count,"瓶。剩余",money,"元")







#1、不使用正则验证邮箱(必须包含@和点，@在点前面，不能以@开头，不能以点结尾，@和点不能相邻)
# 1. 邮箱验证
email = input("请输入邮箱：")
# 1.必须包含@和.
if "@" not in email or "." not in email:
    print("err")
else:
    at_pos = email.find("@")
    dot_pos = email.find(".")
    # @在点前、不以@开头、不以.结尾、@和.不相邻
    if at_pos < dot_pos and not email.startswith("@") and not email.endswith(".") and email[at_pos+1] != ".":
        print("正常邮箱")
    else:
        print("err")




# 2、用户输入一组彩票号码，程序计算出彩票对应的购买金额
# 010203040506#07 = 2元
# 010203040506#07#3 = 2元*3倍=6元；
# 010203040506#070811 = 6元
# 010203040506#070811#10 = 60元








# 3、小明身高1.75米，体重80.5kg，请根据BMI公式（体重除以身高的平方）帮小明计算他的BMI指数，并根据BMI指数：
# 低于18.5：过轻
# 18.5-25：正常
# 25-28：过重
# 28-32：肥胖
# 高于32：严重肥胖

# height = 1.75
# weight = 80.5
# bmi = weight / (height ** 2)
# print(f"小明BMI指数：{bmi:.2f}")
#
# if bmi < 18.5:
#     res = "过轻"
# elif 18.5 <= bmi <= 25:
#     res = "正常"
# elif 25 < bmi <= 28:
#     res = "过重"
# elif 28 < bmi <= 32:
#     res = "肥胖"
# else:
#     res = "严重肥胖"
# print(f"身体状况：{res}")



# 4、使用循环输出1到100之内既能被3整除又能被7整除的整数
print("1到100中既能被3整除又能被7整除的数：")
for i in range(1, 101):
    if i % 3 == 0 and i % 7 == 0:
        print(i, end=' ')


#5、有一个棋盘，有64个方格，在第一个方格里面放1粒芝麻重量是0.00001kg，
#   第二个里面放2粒，第三个里面放4，计算棋盘上放的所有芝麻的重量

# total_grains = 2 ** 64 - 1  # 等比数列求和
# weight_per_grain = 0.00001   # kg
# total_weight = total_grains * weight_per_grain
#
# print(f"总芝麻粒数：{total_grains}")
# print(f"总重量：{total_weight:.2f} kg")








