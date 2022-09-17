select dept_code, c as num_of_managers from (select dept_code, desig_desc, count(*) as c from emp natural join designation group by dept_code, desig_desc) temp where temp.desig_desc='Manager';
