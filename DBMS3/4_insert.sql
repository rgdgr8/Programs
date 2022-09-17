insert into book_deets values(1,'b1','a1','p1',111.11);
insert into book_deets values(2,'b2','a2','p2',222.22);
insert into book_deets values(3,'b3','a3','p3',333.33);
insert into book_deets values(4,'b4','a4','p4',444.44);
insert into book_deets values(5,'b5','a5','p5',555.55);

insert into book_nums(bookid) values(1);
insert into book_nums(bookid) values(1);
insert into book_nums(bookid) values(1);
insert into book_nums(bookid) values(2);
insert into book_nums(bookid) values(2);
insert into book_nums(bookid) values(3);
insert into book_nums(bookid) values(3);
insert into book_nums(bookid) values(4);
insert into book_nums(bookid) values(4);
insert into book_nums(bookid) values(5);

insert into privi values('s',10);
insert into privi values('f',100);

insert into members(memid,memtype) values(1,'s');
insert into members(memid,memtype) values(2,'s');
insert into members(memid,memtype) values(3,'s');
insert into members(memid,memtype) values(4,'f');
insert into members(memid,memtype) values(5,'f');
insert into members(memid,memtype) values(6,'f');
insert into members(memid,memtype) values(7,'f');
insert into members(memid,memtype) values(8,'f');
insert into members(memid,memtype) values(9,'f');
insert into members(memid,memtype) values(10,'f');
insert into members(memid,memtype) values(11,'f');
insert into members(memid,memtype) values(12,'f');
insert into members(memid,memtype) values(13,'s');
insert into members(memid,memtype) values(14,'s');

insert into trans(memid, bookid, serial, issue_date) values(1,1,1,date '2022-02-02');
insert into trans(memid, bookid, serial, issue_date) values(2,1,2,date '2022-02-02');
insert into trans(memid, bookid, serial, issue_date) values(3,1,3,date '2022-02-02');
insert into trans(memid, bookid, serial, issue_date) values(4,2,2,date '2022-02-02');
insert into trans(memid, bookid, serial, issue_date) values(5,5,1,date '2022-02-02');
update trans set return_date=date '2022-02-10' where memid=6 and bookid=5 and serial=1;
update trans set return_date=date '2022-02-10' where memid=5 and bookid=5 and serial=1;
update trans set return_date=date '2022-02-10' where memid=5 and bookid=5 and serial=1;
update trans set return_date=date '2022-02-08' where memid=1 and bookid=1 and serial=1;
