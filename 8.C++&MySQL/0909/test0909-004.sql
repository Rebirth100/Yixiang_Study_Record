-- Active: 1788833264324@@127.0.0.1@3306@test0908
/************************
CREATE   Procedure  名称(参数列表)
BEGIN
    程序体
END
************************/


-- 参数列表的形式
-- 参数类型 参数名 数据类型,参数类型 参数名 数据类型
-- 参数类型:输入参数in/输出参数out/输入输出参数inout

create Procedure  pro_001()
BEGIN
    select * from vi_e_d  ORDER BY  工资  asc;
end

call pro_001;

call pro_001();



-- in参数
create Procedure  pro_002(in id  int)
BEGIN
    select * from vi_e_d  where 工号=id;
end

call  pro_002(1099);


create Procedure  pro_003(in id  int,out dname varchar(128))
BEGIN
    select 部门 into dname  from vi_e_d  where 工号=id;
end

/******************
存储过程中的赋值 ：
select a,b,c into r_a,r_b,r_c; 
set r_a='xxxxx';

*********************/


call pro_003(1099,@d_name);

select @d_name;


-- 重定义命令结束标记，否则在命令行输入存储过程时没办法表示过程体
delimiter  $%


create   Procedure  pro_004(inout id int)
select e_dept into id from emp where emp.e_Id=id;

set  @id=1099;
 call pro_004(@id);

 select  @id;