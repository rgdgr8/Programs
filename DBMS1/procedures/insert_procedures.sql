create or replace procedure EMP_insert(EMP_CODE varchar2, EMP_NAME varchar2, DEPT_CODE varchar2, DESIG_CODE varchar2, SEX varchar2, ADDRESS varchar2, CITY varchar2, STATE varchar2, PIN varchar2, BASIC NUMBER, JN_DT Date)
AS
BEGIN
	insert into EMP values(EMP_CODE, EMP_NAME, DEPT_CODE, DESIG_CODE, SEX, ADDRESS, CITY, STATE, PIN, BASIC, JN_DT);
END ;
/

create or replace procedure DESIG_insert(DESIG_CODE varchar2, DESIG_DESC varchar2)
AS
BEGIN
	insert into DESIGNATION values(DESIG_CODE, DESIG_DESC);
END ;
/

create or replace procedure DEPT_insert(DEPT_CODE varchar2, DEPT_NAME varchar2)
AS
BEGIN
	insert into DEPARTMENT values(DEPT_CODE, DEPT_NAME);
END ;
/
