select * from members where memtype='s' and memid not in (select memid from trans);
select * from members where memtype='f' and memid not in (select memid from trans);
