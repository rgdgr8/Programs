exec desig_insert(1, 'Manager');
exec desig_insert(2, 'Executive');
exec desig_insert(3, 'Officer');
exec desig_insert(4, 'Clerk');
exec desig_insert(5, 'Helper');

exec dept_insert(1, 'Production');
exec dept_insert(2, 'Purchase');
exec dept_insert(3, 'Finance');
exec dept_insert(4, 'Research');

exec emp_insert(1, 'A', 1, 1, 'M', 'addr1', 'city1', 'state1', 'pin1', 100000.5, DATE '1987-01-01');
exec emp_insert(2, 'B', 2, 2, 'M', 'addr2', 'city2', 'state2', 'pin2', 200000.5, DATE '1988-02-02');
exec emp_insert(3, 'C', 1, 3, 'F', 'addr3', 'city3', 'state3', 'pin3', 300000.5, DATE '1989-03-03');
exec emp_insert(4, 'D', 4, 4, 'M', 'addr4', 'city4', 'state4', 'pin4', 400000.5, DATE '1990-04-04');
exec emp_insert(5, 'E', 1, 5, 'M', 'addr5', 'city5', 'state5', 'pin5', 500000.5, DATE '1991-05-05');
