select dept_code, sum(basic) as sum_of_basic from emp where sex='M' group by dept_code having sum(basic) > 50000 order by sum_of_basic desc;
