declare 
	cursor c is select emp_name from emp where basic is not null order by basic desc fetch first 5 rows only;
begin
	for name in c
	loop
		dbms_output.put_line(name.emp_name);
	end loop;
end;
/
