-- Active: 1788833264324@@127.0.0.1@3306@test0908
-- view: 视图是一种虚拟表，不占物理空间
-- 内部记录一个查询语句，可将查询语句的结果集当表使用
-- 注意:对视图进程删除操作要考虑可行性

-- 视图可以隐藏数据库的设计细节
create  View  vi_e_d
AS
select e_id 工号,e_name 姓名,e_gender 性别,dept.d_name 部门,emp.e_num 身份证号,emp.e_sal 工资 from  emp join dept on emp.e_dept=dept.d_id;



SELECT * FROM  vi_e_d ;

SELECT * FROM  vi_e_d  ORDER BY 工资;

SELECT * FROM  vi_e_d  ORDER BY 工资 desc;

SELECT 部门,sum(工资) 工资总额 FROM  vi_e_d  group by  部门;

update  vi_e_d set 工资=10000 where 工号=1089;

DELETE  from vi_e_d  where 部门='演唱部';

update vi_e_d set 部门='xxxxxx' where 工号=1089;


-- index:索引
-- 单列索引/多列索引
-- 普通索引/主键索引/唯一键索引/外键索引
-- 全文索引 

desc  emp;

select  * from emp;


EXPLAIN
select  * from emp where e_num like '610%';

EXPLAIN
select  * from vi_e_d;

EXPLAIN
select  * from emp ORDER BY e_name desc;


EXPLAIN
select  * from vi_e_d order  by  姓名;



drop index Idx_emp_name on EMP;
create  FULLTEXT index  Idx_emp_name
on EMP(e_name);


EXPLAIN
select  * from emp where e_name like '张%';