create trigger del_log
	after delete on request
	for each row
declare
	ent service_log.entry_no%type;
begin
	select count(entry_no) into ent from service_log;
	ent := ent + 1;
	insert into service_log values(ent, :old.req_no, sysdate);
end;
/
