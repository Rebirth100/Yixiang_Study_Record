# 项目：0624
# 文件：10异常处理
# 作者: Update
# 日期: 2026/6/24 16:51
# coding:utf-8

def test():
    try:
        print(3/0)
        print(3+"wb")
        ls=[1,2,3]
        print(ls[5])
        return
    except ZeroDivisionError as e:
        print("除数为0",e)
    except TypeError as e:
        print("类型错误",e)
    except IndexError as e:
        print("索引越界",e)
    except Exception as e:
        print("其他错误",e)
    else:
        print("恭喜你没有报错")
    # finally: