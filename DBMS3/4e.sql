select bookid, count(*) as "num of time ever issued" from trans group by bookid;
select bookid, count(*) as "num of time currently issued" from trans where return_date is null group by bookid;
