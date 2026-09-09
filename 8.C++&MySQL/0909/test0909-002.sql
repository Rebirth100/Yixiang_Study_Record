-- Active: 1788833264324@@127.0.0.1@3306@test0908
drop table emp;
CREATE TABLE emp
(
    e_Id int  AUTO_INCREMENT not NULL,
    e_name varchar(128) DEFAULT 'xxx',
    e_num char(18) UNIQUE ,
    e_dept int,
    e_gender ENUM('男','女') DEFAULT  '男',
    e_sal DECIMAL(12,2) DEFAULT  0.0,
    e_address varchar(512),
    PRIMARY KEY  (e_id),
    FOREIGN KEY  (e_dept) REFERENCES dept(d_id)
);


select   * from emp;


select  e_id,e_name,SUBSTRING(e_address,1,4) from emp ;

-- 子查询  (in  any  all)

select  * from emp where SUBSTRING(e_address,1,4)=(SELECT SUBSTRING(e_address,1,4) from emp where e_id=1093);

select  * from emp  where e_dept  in(6666,19888)

select  * from emp  where e_dept in (
SELECT e_dept FROM 
(select e_dept as e_dept, sum(e_sal)  as sal_sum from emp 
 GROUP BY e_dept HAVING sal_sum>60000) as res
 )


SELECT sal_sum FROM 
(select e_dept as e_dept, sum(e_sal)  as sal_sum from emp 
 GROUP BY e_dept HAVING sal_sum>60000) as res
 


 select  * from emp  where e_sal > any
 (
     SELECT sal_avg FROM 
    (select e_dept as e_dept, avg(e_sal)  as sal_avg from emp 
    GROUP BY e_dept HAVING sal_avg>15000) as res
 )

  select  * from emp  where e_sal > all
 (
    SELECT sal_avg FROM 
    (select e_dept as e_dept, avg(e_sal)  as sal_avg from emp 
    GROUP BY e_dept HAVING sal_avg>15000) as res
 )


select e_dept as e_dept, avg(e_sal)  as sal_avg from emp 
    GROUP BY e_dept

 SELECT sal_avg FROM 
    (select e_dept as e_dept, avg(e_sal)  as sal_avg from emp 
    GROUP BY e_dept HAVING sal_avg>15000) as res

select   *  from emp 

-- exists  相关子查询  （主查询是否执行依赖于子查询是否有结果返回）
select   *  from emp  where exists 
(select  *  from emp where SUBSTRING(e_address,1,4)='中国运城');


select  *  from emp where SUBSTRING(e_address,1,4)='中国运城'




 
-- DISTINCT   去重
select DISTINCT SUBSTRING(e_address ,1,4) from emp;


select  e_id,e_name,e_gender  from emp
UNION
select  e_id,e_name,e_gender from  employee;