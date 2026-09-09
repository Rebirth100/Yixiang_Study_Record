-- Active: 1788833264324@@127.0.0.1@3306@test0908
show TABLEs;

DESCRIBE student;


-- db  dbs  dbms 

-- 常用的dbms:sqlserver/mysql/sqlite/oracle

--  sql:结构化查询语句
--  DDL 数据定义语句  管理和维护数据库对象(db数据库/table表/index索引/view视图/user用户/procedure存储过程)
--  create  创建对象
--  alter   修改对象
--  drop 删除对象

--  DCL 数据控制语句  权限管理
--  grant  授权
--  revoke 撤销权限

--  DML 数据操作语句  数据(表里面的内容)管理和操作
--  insert  into     新增数据
--  update           更新数据
--  delete           删除数据



-- DDL:

-- 范式  

CREATE DATABASE   test0908;
CREATE DATABASE  if NOT EXISTS test0908;
drop  DATABASE  if EXISTS test0908;
alter database character set utf8 ;


show create database test0908;

use  test0908

show DATABASES;

show  tables;

-- 列类型:
-- char 和varchar  ,text
 

CREATE TABLE employee
(
    e_Id int ,
    e_name varchar(128),
    e_gender ENUM('男','女'),
    e_sal DECIMAL(12,2)
);




select database();

select user();

describe employee; 

desc  employee; 


ALTER table employee add e_address varchar(1024) AFTER e_gender;

-- ALTER table employee CHANGE

-- ALTER table employee modify

ALTER table employee   drop COLUMN e_gender;

drop   table  employee;

insert into   employee values(109,'张无忌','男','山西运城',1099.5);


insert into   employee values
(109,'张无忌','男','山西运城',11099.5),
(110,'孙无忌','男','山西运城',11399.5),
(119,'刘无忌','女','山西运城',11099.5),
(134,'罗无忌','男','陕西西安',12099.5),
(156,'李无忌','男','山西运城',11099.5),
(177,'王无忌','男','山西运城',11099.5),
(109,'张大忌','男','山西运城',11099.5) 
;


select   * from employee;

insert into   employee(e_name,e_sal,e_gender) values('张无忌',9000,'男');

 insert into   employee(e_name,e_sal,e_gender) values('张无忌',9000,'男'), 
 ('李四',19000,'女'), 
 ('张无忌',9000,'男');


 -- 约束
 -- 默认值 default
 -- 主键  primary  key 用户选定的表示数据唯一的
 -- 唯一键  unique  数据必须唯一
 -- 非空   not null   必填项
 -- 外键    foreign  key

 -- check (mysql不支持)



CREATE TABLE emp
(
    e_Id int PRIMARY KEY AUTO_INCREMENT not NULL,
    e_name varchar(128) DEFAULT 'xxx',
    e_num char(18) UNIQUE ,
    e_gender ENUM('男','女') DEFAULT  '男',
    e_sal DECIMAL(12,2) DEFAULT  0.0
);


insert into   emp(e_name,e_sal,e_gender) values('张无忌',9000,'男');

 insert into   emp(e_name,e_num) values('李无忌','6101191999');

insert into   emp(e_name,e_sal,e_num,e_gender) values('张无忌',9000,'6101190989','男');
insert into   emp(e_name,e_sal,e_num,e_gender) values('张无忌',9000,'6201190989','男');
-- e_Id INTEGER PRIMARY KEY AUTO_INCREMENT,




/***************外键****************/

-- 主表
create table dept
(d_id int PRIMARY KEY  COMMENT  '部门表_部门id(主键)',
 d_name varchar(128) DEFAULT '精致部门'  COMMENT  '部门表_部门id(主键)',
 d_comment varchar(1024) DEFAULT ''   COMMENT  '部门表_部门id(主键)'
);


CREATE TABLE emp
(
    e_Id int  AUTO_INCREMENT not NULL,
    e_name varchar(128) DEFAULT 'xxx',
    e_num char(18) UNIQUE ,
    e_dept int,
    e_gender ENUM('男','女') DEFAULT  '男',
    e_sal DECIMAL(12,2) DEFAULT  0.0,
    PRIMARY KEY  (e_id),
    FOREIGN KEY  (e_dept) REFERENCES dept(d_id)
);



drop Table  emp;

ALTER  TABLE emp  add  e_dept  int;
ALTER  TABLE emp  add CONSTRAINT fk_dept_emp FOREIGN KEY  (e_dept) REFERENCES dept(d_id)


insert into dept values(6666,'演唱部','专业吼歌'); 

insert into emp values(100,'刘德华','61042090786756',6666,'女',10900);

/***************************************************************
-- 外键技术的验证   表的存储引擎必须使用 InnoDB ,Myisam不支持外键。
CREATE TABLE `emp` (
  xxxxxxx
) ENGINE=InnoDB 

ALTER TABLE XXXXXXXX;
***************************************************************/

select  * from emp;

select  * from emp where e_id=293;

/*********************
=  !=  <>  
!  not
&&  and
||  or
<=  >=  >  <
between 1000 and  2000
is  null
is  not null
***************/

-- 模糊查询  like   %   _
select  * from emp where e_name like '_子_';

select  * from emp    order by  e_sal asc;

select  * from emp    order by  e_sal desc;

-- 聚合函数
--  count(*)
select count(*) from emp where e_gender='女';

select e_gender 性别,count(*) 人数  from emp  group by e_gender;

select e_dept  部门 ,count(*) 人数 from emp group by  e_dept;


select e_dept  部门 ,count(*) 人数 from emp group by  e_dept;

--最大值  MAX  

--最小值 MIN

-- 平均数
-- AVG

-- 总和
-- sum

