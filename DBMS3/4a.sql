select bookid, count(serial) as num_of_copies from book_nums group by bookid;
select bookid, count(serial) as num_of_copies_issued from book_nums where avail=0 group by bookid;
