delimiter //

create procedure EMP_insert(in EMP_CODE char(5), in EMP_NAME char(20), in DEPT_CODE char(5), in DESIG_CODE char(5),
in SEX char(1), in ADDRESS char(25), in CITY char(20), in STATE char (20), in PIN char(6), in BASIC DECIMAL(10, 2), in JN_DT Date)
BEGIN
	insert into EMP values(EMP_CODE, EMP_NAME, DEPT_CODE, DESIG_CODE, SEX, ADDRESS, CITY, STATE, PIN, BASIC, JN_DT);
END //


create procedure DESIG_insert(in DESIG_CODE char(5), in DESIG_DESC char(20))
BEGIN
	insert into DESIGNATION values(DESIG_CODE, DESIG_DESC);
END //


create procedure DEPT_insert(in DEPT_CODE char(5), in DEPT_NAME char(15))
BEGIN
	insert into DEPARTMENT values(DEPT_CODE, DEPT_NAME);
END //

delimiter ;
