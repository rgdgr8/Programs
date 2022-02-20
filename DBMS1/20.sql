select emp_code, emp_name, dept_code, dept_name, desig_desc, sex, address, city, state, pin, basic, jn_dt from emp e natural join designation natural join department order by dept_code, basic desc;
