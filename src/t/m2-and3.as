/ Program : m2-and3.as
/ Desc: Tests group 2 and subgroup
/ Should run 3 instructions

/
/ Code Section
/

*0200			/ start at address 0200
Main, 	cla cll	iac	/ clear ac and l, increment ac
	spa sna szl cla	/ skip on all 3
	cla cll cma  	/ should be skipped
	hlt		/ halt
$Main 			/ End of Program; Main is entry point
