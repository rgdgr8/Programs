insert into emp2 values (2, null, 1, null, null, 4000, null, null) /*insert violation*/;
update emp2 set id=3 where id=1 /*update violation*/;
delete from dept2 /*delete violation*/;

