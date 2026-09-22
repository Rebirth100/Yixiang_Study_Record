# 项目：0622
# 文件：10字节串
# 作者: Update
# 日期: 2026/6/22 15:54
# coding:utf-8

b1 = bytes()
print(b1,type(b1))
b2 = bytes(3)
print(b2,type(b2))
b3 = bytes('20000','utf-8')
print(b3)
b4 = bytes([20,100,9,255,8])
print(b4)

# 2.字符串和字节串互相转换
mess = "i love xi an"
print(mess.encode())
mess2 = b'i love xianyang'
print(mess2.decode())
mess3 = "我是中国人"
print(mess3.encode())
mess4 = b'\xe6\x88\x91\xe6\x98\xaf\xe4\xb8\xad\xe5\x9b\xbd\xe4\xba\xba'
print(mess4.decode())