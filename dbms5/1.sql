create trigger result_seg
	before insert or update on result
	for each row
declare
	cur_roll result.roll%type;
	cur_scode result.scode%type;
	bpc int;
begin
	if inserting then
		cur_roll := :new.roll;
		cur_scode := :new.cur_scode;
	else
		cur_roll := :old.roll;
		cur_scode := :old.cur_scode;
	end if;

	if :new.marks >= 50 then
		delete from backpaper where roll=cur_roll and scode=cur_scode;
	else
		select count(id) into bpc from backpaper where roll=cur_roll and scode=cur_scode;
		if bpc = 0 then
			insert into backpaper values(cur_roll, cur_scode);
		end if;
	end if;
end;
/
