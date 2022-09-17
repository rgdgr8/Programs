select tid, memid, bookid, serial, issue_date, return_date, (return_date-issue_date-7) as delay_days from trans where return_date is not null and return_date>(issue_date+7);
