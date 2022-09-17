select dept_code, desig_code, count(*) as num_of_emp from emp where extract(year from jn_dt)=2000 group by dept_code, desig_code order by num_of_emp;
