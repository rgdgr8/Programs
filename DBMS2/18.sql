delete from emp where desig_code not in (select desig_code from designation);
