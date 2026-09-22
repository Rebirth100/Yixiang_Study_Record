# 项目：0622
# 文件：09字符串格式化
# 作者: Update
# 日期: 2026/6/22 15:54
# coding:utf-8


#亲爱的xxx你好，你xx月份的花费是：xxx元，余额：xxx元。
name = "小美"
month = 5
pay = 100
amount = 545.35
#方案一：传统的加号对字符串进行连接

print("亲爱的"+name+"你好，"+"你"+str(month)+"月份的花费是："+str(pay)+"元，余额："+str(amount)+"元。")
#方案二：借鉴自C语言的格式化(%s:字符串、%d:整形、%f:浮点型、%.2f:保留两位小数、%e:科学计数法、%g:自动判断)
print("亲爱的%s你好，你%d月份话费是：%.2f元，余额：%g元"%(name,month,pay,amount))
#方案三：format处理
print("亲爱的{}你好，你{}月份的花费是：{:.2f}元，余额：{:.2f}元。".format(name,month,pay,amount))
print("亲爱的{0}你好，你{3}月份的花费是：{1:.2f}元，余额：{2:.2f}元。".format(name,pay,amount,month))
