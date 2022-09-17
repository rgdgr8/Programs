select distinct dept_name from department d left join emp e on d.dept_code=e.dept_code where emp_code is null;
