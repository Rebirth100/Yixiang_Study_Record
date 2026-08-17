#include  <stdio.h>
#include  "name.h"

//部门
typedef enum Dept
{
    Dev,        // 研发部
    Technology, // 技术部
    Production, // 生产部
    Finance,    // 财务部
    Sales       // 销售部
}Dept;
//部门文本
char deptText[5][20] = {
    "Dev",              //研发部
    "Technology",       // 技术部
    "Production",      // 生产部
    "Finance",         // 财务部
    "Sales"            // 销售部
};
//员工信息
typedef struct Employee
{
    Dept Dept;//部门
    char name[30]; //姓名,调用generateChineseName自动填充,
    int age;//年龄
}Employee;
//输出员工信息
void print(Employee *e)
{
    if(e)
    {
        printf("部门:%-12s 姓名:%-15s 年龄:%d\n",deptText[e->Dept],e->name,e->age);
    }
}
int main()
{
    Employee empArray[300000];
    for(int i=0;i<300000;i++)
    {
        empArray[i].Dept=rand()%5;
        generateChineseName(empArray[i].name);
        empArray[i].age=rand()%45+25;
        printf("%6d:",i);
        print(empArray+i);
    }
    //启用10个线程,快速完成所有员工的信息按部门归档(相同部门的人数据连续)
    //或者您可以自定义数据结构保存按部门分组的员工数据
}
