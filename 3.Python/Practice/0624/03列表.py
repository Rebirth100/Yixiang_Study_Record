# 项目：0624
# 文件：03列表
# 作者: Update
# 日期: 2026/6/24 10:19
# coding:utf-8


#列表(数组):也是有序的数据集合，可迭代，可修改，可删除，可添加，功能是最多的，使用率最高。

#1.创建
ls1=[]
print(ls1,type(ls1))
ls2=[1,2,3,(4,5,6),True,[8,9,10]]
print(ls2,type(ls2))

#2.从其他类型转换
r=range(1,11)
print(r)
ls3=list(r)
print(ls3)
ls4= list((77,88,99))
print(ls4)
#3.读取
ls5=['小芳','小梅','小明','小王']
#3.1 单个索引访问
print(ls5[1],ls5[-2])
#3.2 切片访问
print(ls5[1:])
print(ls5[1:])
print(ls5[::-1])
#3.3 拆包
a,b,c,d=ls5
print(c,d)
# 3.4 for循环
for n in ls5:
    print("你好",n)
#4.添加
ls5.append("小美")
print(ls5)
ls5.insert(1,"杰瑞")
print(ls5)
ls5.extend(("小珍","阿丽"))
#5.修改
ls5[1]="汤姆"
ls5[-2]="小娟"
print(ls5)
ls5[2:5]="Lucy","Rose","TIM"
print(ls5)
#6.删除
del ls5[-1]
print(ls5)
ls5.remove('小美')
print(ls5)
ls5.pop()
print(ls5)
ls5.pop(0)
print(ls5)
del ls5[0:2]
print(ls5)
#7.检索
ls6=["唐僧","孙悟空","白龙马","猪八戒","沙悟净"]
#根据内容返回对应的索引位置，如果不存在会报错
print(ls6.index("白龙马"))
print(ls6.index("如来佛祖"))

# count：统计某个数据出现的次数
ls7=[1,2,3,1,2,3,1,2,1,3,5,6,7,7,7]
print(ls7.count(7))
print(ls7.index(8))

#课堂小练习：设计一个安全的列表搜索功能
if ls6.count("唐僧")>0:
    print(ls6.index("唐僧"))

#8.排序
ls8=[6,4,1,2,99,14,5]
#升序
ls8.sort()
print(ls8)
#倒序(不是降序)
ls8.reverse()
print(ls8)
#降序
ls8.sort(reverse=True)
print(ls8)
#打乱顺序