/************************
(1)
if(表达式) then
    xxxxxxxxx
end  if;
(2)
if(表达式) then
    xxxxxxxxx
else
    xxxxxxxxx
end  if;
(3)
if(表达式1) then
    xxxxxxxxx
elseif(表达式2) then
    xxxxxxxxx
elseif(表达式3) then
    xxxxxxxxx  
xxxxxxxxx
else 
    xxxxxxxxx
end  if;
(4)case语句
case 表达式
when 值1  then  xxxxx;
when 值2  then  xxxxx;
xxxxxxxxxxxx
else
xxxxxxxxxxxx
end case;
****************************/
drop  Procedure  pro__005;

create  Procedure  pro__005(in id int)
begin 
    set @cnt=0;
    select  count(*) into @cnt from emp where emp.e_Id=id;
    if(@cnt=0) THEN
        select '查无此人' 提示;
    ELSE
         select  * from emp where emp.e_Id=id;
    end if;
end

call pro__005(199);



create  Procedure  pro__006(in id int)
begin 
    DECLARE cnt int DEFAULT 0;
    select  count(*) into cnt from emp where emp.e_Id=id;
    if(cnt=0) THEN
        select '查无此人' 提示;
    ELSE
         select  * from emp where emp.e_Id=id;
    end if;
end
call  pro__006(1099);
call pro__006(199);

select avg(e_sal) from emp;

select sum(e_sal) from emp;

/***********************************
-- 员工提薪方案的设定
统计员工总薪,按总薪额度 不同方案不同
总额>500000 25%
总额>400000 15%
总额>300000 5%
总额>100000 100
**********************************/
CREATE  Procedure  pro_007()
BEGIN
    DECLARE sum_sal DECIMAL(12,2) DEFAULT  0.0;
    SELECT  sum(e_sal) into sum_sal from emp ;
    if(sum_sal>=500000) then
        select 工号,姓名,部门,工资 应发,工资*1.25 实发  from vi_e_d; 
    ELSEIF(sum_sal>400000) then 
         select 工号,姓名,部门,工资 应发,工资*1.15 实发  from vi_e_d; 
    ELSEIF(sum_sal>300000) then
        select 工号,姓名,部门,工资 应发,工资*1.05 实发  from vi_e_d; 
    ELSE
        select 工号,姓名,部门,工资 应发,工资+100 实发  from vi_e_d;
    end if;
end

call pro_007;


select  d_name from dept;

/*********************************************
-- 输入ID，按员工所在部门不同，给出方案加薪
当总薪超过400000
销售部+25%
市场部+15%
研究及开发部+10
服务支持部+5%
其他部门+300

当总薪不超过400000
销售部+500
市场部+300
研究及开发部+200
其他部门正常发
*********************************************/


drop Procedure if EXISTS pro_008;

CREATE  Procedure  pro_008(in id int)
BEGIN
    DECLARE sum_sal DECIMAL(12,2) DEFAULT  0.0;
    DECLARE in_id_cnt int  DEFAULT  0;
    DECLARE emp_did int DEFAULT  0;
    DECLARE dept_name varchar(256) DEFAULT  '';
    select count(*) into in_id_cnt from emp where e_id=id;
    if(in_id_cnt=0) THEN
        select '查无此人' 提示;
    ELSE
        SELECT  sum(e_sal) into sum_sal from emp ;
        select e_dept into emp_did  from emp  where e_id=id;
        SELECT  d_name into dept_name  from dept where d_id=emp_did;
        if(sum_sal>=400000 ) then 
            case dept_name 
            when '销售部' then 
                select 工号,姓名,部门,工资 应发,工资*1.25 实发  from vi_e_d where 工号=id ;
            when '市场部' then   
                select 工号,姓名,部门,工资 应发,工资*1.15 实发  from vi_e_d where 工号=id ;
            when '研究及开发部' then   
                select 工号,姓名,部门,工资 应发,工资*1.10 实发  from vi_e_d where 工号=id ;
            when '服务支持部' then   
                select 工号,姓名,部门,工资 应发,工资*1.05 实发  from vi_e_d where 工号=id ;
            else  
                select 工号,姓名,部门,工资 应发,工资+300 实发  from vi_e_d where 工号=id ;
            end case;
        else
             case dept_name 
            when '销售部' then 
                select 工号,姓名,部门,工资 应发,工资+500 实发  from vi_e_d where 工号=id ;
            when '市场部' then   
                select 工号,姓名,部门,工资 应发,工资+300 实发  from vi_e_d where 工号=id ;
            when '研究及开发部' then   
                select 工号,姓名,部门,工资 应发,工资+200 实发  from vi_e_d where 工号=id ;
            else  
                select 工号,姓名,部门,工资 应发,工资 实发  from vi_e_d where 工号=id ;
            end case;
        end if;
    end if;
end;
 


 call  pro_008(199);


 