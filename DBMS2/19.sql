select emp_name from emp natural join (select dept_code, avg(basic) as avg_basic from emp group by dept_code) where sex='F' and basic>avg_basic;
