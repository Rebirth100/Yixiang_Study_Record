# 项目：0624
# 文件：02元组
# 作者: Update
# 日期: 2026/6/24 10:19
# coding:utf-8



#元组(tuple):一种有序的数据集合，序号称之为索引(从0开始)，且它可被迭代，它的数据一旦被创建不允许再修改

#1创建
t1 = ()
print(t1,type(t1))

t2 = (1,2,3,True,"你好",(4,5,6))
print(t2,type(t2))

t3 = 77,88,99
print(t3,type(t3))

t4 = ("Lucy",)
print(t4,type(t4))

# 2、读取数据
t5 = ("Frank","Rose","Tony","Lucy","Jack")
print(t5,type(t5))
# 2.1 单个索引读取
print(t5[0],t5[3])   #正向索引(从左侧开始，从0计数)
print(t5[-1],t5[-3]) #反向索引(从右侧开始，从-1计数)

# 2.2 切片读取(截取一个区间)
print(t5[0:3])  #('Frank', 'Rose', 'Tony')
print(t5[0:1])  #('Frank',)
print(t5[2:])   #('Tony', 'Lucy', 'Jack')
print(t5[:2])   #('Frank', 'Rose')
print(t5[-3:])  #('Tony', 'Lucy', 'Jack')
print(t5[:-3])  #('Frank', 'Rose')
print(t5[-3::-1])
print(t5[-3::1])
print(t5[-3::2])
print(t5[-3::-3])
# 2.3 拆包(准备和元组里数量相等的变量来一次性接收数据)
a,b,c,d,e=t5
print(b,d)
x=5;y=3
w=y,x
print(w,type(w))
x,y=w
print(x,y)
# 2.4 for循环遍历(迭代)
for name in t5:
    print(name)
#3.尝试删除和修改(失败)
# del t5[0]
# t5[0]="小明"

#特殊的修改:因为列表属于可变类型，修改列表的值。不等于直接修改元组
t6 = ((-1,-2,-3),1,2,3,[4,5,6])
t6[-1][2]=7     #修改列表内部数据，元组没发现
# t6[0][0]=-100   #多层元组，任何一层都不能改
# t6[-1]=[4,5,7]  #创建一个新列表[4,5,7]，换掉原来的旧列表[4,5,6]
print(t6,type(t6))

#4.从其他类型转换(仅限可迭代类型)
#str,list,bytes,range
t7 = type(t6)


