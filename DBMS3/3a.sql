create table emp3 as (select e2.id as empcode, emp_name, dept_name, basic from emp2 e2 join dept2 d2 on e2.dept=d2.id where dept_name='cse' and basic=7000);

alter table emp3 add constraint emp3_pk primary key(empcode);
