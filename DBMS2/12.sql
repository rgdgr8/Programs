select desig_desc from emp natural join designation where basic = (select max(basic) from emp);
