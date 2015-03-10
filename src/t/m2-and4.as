/ Program : m2-and4.as
/ Desc: Tests group 2 and subgroup
/ Should run 10 instructions in 10 cycles

/
/ Code Section
/

*0200			/ start at address 0200
Main,	cla cll cma	/ clear ac and l, compliment ac
	spa sna szl cla	/ skip on all 3
	cla cll cma  	/ should not be skipped
	cla cll		/ clear ac and l
	spa sna szl cla	/ skip on all 3
	cla cll cma  	/ should not be skipped
	cla cll iac cml	/ clear ac and l, inc ac, comp l
	spa sna szl cla / skip on all 3
	cla cll cma	/ should not be skipped
	hlt		/ halt
$Main 			/ End of Program; Main is entry point
