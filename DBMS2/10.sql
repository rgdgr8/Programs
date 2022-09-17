select distinct dept_name from (select d.dept_code from department d left join emp e on d.dept_code=e.dept_code group by d.dept_code having count(emp_code)>=3) temp natural join department;
