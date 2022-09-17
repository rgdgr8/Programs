begin 
	delete from emp where dept_code=&dept_code;
	dbms_output.put_line(sql%rowcount||' rows deleted');
end;
/
