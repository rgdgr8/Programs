declare
	dup exception;
	pragma exception_init(dup, -20000);
	ecode emp.emp_code%type := &emp_code;
	dcode department.dept_code%type := &dept_code;
	etemp emp.emp_code%type;
	dtemp department.dept_code%type;
begin
	select emp_code into etemp from emp where emp_code=ecode;
	raise dup;
	exception
		when no_data_found then
			begin
				select dept_code into dtemp from department where dept_code=dcode;
				insert into emp(emp_code, dept_code) values(ecode, dcode);
			exception
				when no_data_found then
					dbms_output.put_line('row cannot be added');
			end;
		when dup then
			dbms_output.put_line('row cannot be added');
end;
/
