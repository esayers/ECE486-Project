/ m2-and4.as - Test 4 of group 2 AND subgroup
/ Should run in 10 cycles

*0200	/ program
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
$Main
