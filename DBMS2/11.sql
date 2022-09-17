select dept_code from emp where basic = (select max(basic) from emp);
