insert into emp3 select e2.id as empcode, emp_name, dept_name, basic from emp2 e2 join dept2 d2 on e2.dept=d2.id where e2.id not in (select empcode from emp3) and basic>=7000;
