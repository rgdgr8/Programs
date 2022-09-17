declare
	res emp%rowtype;
begin
	select * into res from emp where emp_code=&emp_code;
	dbms_output.put_line(res.emp_code||res.emp_name);
	exception
		when NO_DATA_FOUND then
			dbms_output.put_line('no emp with the given emp_code');
end;
/
