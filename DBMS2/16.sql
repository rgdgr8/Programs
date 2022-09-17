create view emp_dept as select dept_code, emp_code, basic from emp natural join department;
create view tot_basic_per_dept as select dept_code, sum(basic) as tot from emp_dept group by dept_code;
create view avg_basic_per_dept as select dept_code, avg(basic) as avrg from emp_dept group by dept_code;
create view emp_per_dept as select dept_code, count(emp_code) as emp_c from emp_dept group by dept_code;

col dept_with_max_total_basic format a25
col dept_with_max_avg_basic format a25
col dept_with_max_num_of_employee format a30

select dept_code, dept_name dept_with_max_total_basic from department natural join tot_basic_per_dept where tot = (select max(tot) from tot_basic_per_dept);
select dept_code, dept_name as dept_with_max_avg_basic from department natural join avg_basic_per_dept where avrg = (select max(avrg) from avg_basic_per_dept);
select dept_code, dept_name as dept_with_max_num_of_employee from department natural join emp_per_dept where emp_c = (select max(emp_c) from emp_per_dept);

drop view emp_dept;
drop view tot_basic_per_dept;
drop view avg_basic_per_dept;
drop view emp_per_dept;
