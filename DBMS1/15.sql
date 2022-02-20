select count(*) as "number of employee joined on jan" from emp group by jn_dt having extract(month from jn_dt)=1;
