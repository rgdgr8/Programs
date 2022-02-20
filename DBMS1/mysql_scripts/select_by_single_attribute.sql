delimiter $$

create procedure select_by_single_attribute(in tbl varchar(20), in attr varchar(20), in val varchar(20), in comp char(2))
BEGIN
	set @s = concat('select * from ',tbl,' where ',attr,' ', comp, ' ', val);
	select @s;
	prepare stmt from @s;
	execute stmt;
	DEALLOCATE PREPARE stmt;
END $$

delimiter ;
