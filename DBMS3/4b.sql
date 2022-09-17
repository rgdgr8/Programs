select memid from members natural join trans where return_date is null and sysdate>(issue_date+7);
