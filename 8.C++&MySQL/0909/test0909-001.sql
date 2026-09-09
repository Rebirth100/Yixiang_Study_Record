-- Active: 1788833264324@@127.0.0.1@3306@test0908
select e_dept, count(*)  from emp  GROUP BY e_dept;

select e_dept, sum(e_sal)  from emp  GROUP BY e_dept;

select e_dept e_dept, sum(e_sal)  sal_sum from emp  GROUP BY e_dept ORDER BY sal_sum;


select e_dept e_dept, sum(e_sal)  sal_sum from emp  GROUP BY e_dept ORDER BY sal_sum  LIMIT 0,3


select e_dept e_dept, sum(e_sal)  sal_sum from emp  GROUP BY e_dept ORDER BY sal_sum  LIMIT 6,3



-- HAVING  分组聚合的结构再次筛选用HAVING
select e_dept as e_dept, sum(e_sal)  as sal_sum from emp  GROUP BY e_dept HAVING sal_sum>35000;


SELECT * FROM 
(select e_dept e_dept, sum(e_sal)  sal_sum from emp  GROUP BY e_dept)  as res
where res.sal_sum>35000;

-- 联合查询
-- 笛卡尔积
SELECT * FROM  emp,dept;


-- 内连接
SELECT * FROM  emp,dept  where  emp.e_dept=dept.d_id;
SELECT emp.e_id,e_name,e_num,e_gender,dept.d_name,e_sal FROM  emp,dept  where  emp.e_dept=dept.d_id;

-- 内连接
SELECT * FROM  emp join dept  on emp.e_dept=dept.d_id


-- 外连接
-- 左外连接
SELECT * FROM  emp left join dept  on emp.e_dept=dept.d_id

-- 右外连接
SELECT * FROM  emp right join dept  on emp.e_dept=dept.d_id

SELECT * FROM  emp right join dept  on emp.e_dept=dept.d_id where  e_id is  null

-- 全外连接（muysql不支持）
SELECT * FROM  emp full join dept  on emp.e_dept=dept.d_id;


drop  table yk;

-- 自连接
create   table  yk
(
    yk_id int ,
    yk_name VARCHAR(20),
    yk_tel char(15),
    dy_id  int DEFAULT  100
);


DELETE  from  emp ;

-- 截断表
TRUNCATE  yk;

INSERT  into yk VALUES(100,'张导','139-9999-9999',0),(200,'李导','138-7867-6545',0),(300,'陈导','136-7878-7878',0);


 select    *  from yk;

-- 自连接
 select   youke.yk_id 序号,youke.yk_name 姓名,youke.yk_tel 电话,daoyou.yk_name 导游,daoyou.yk_tel 导游电话 
 from yk youke join  yk daoyou where youke.dy_id=daoyou.yk_id;