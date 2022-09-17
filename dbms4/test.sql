DECLARE
    l_name emp.emp_NAME%TYPE;
BEGIN
    /*get the customer
    SELECT emp_NAME INTO l_name FROM emp;
    
    -- show the customer name   
    dbms_output.put_line('customer name is ' || l_name);

    EXCEPTION 
        WHEN TOO_MANY_ROWS THEN
            dbms_output.put_line('Customer does not exist');*/

    raise_application_error(-20001, 'OLA');
END;
/

