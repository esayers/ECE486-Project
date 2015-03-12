/ m2-and3.as - Test 3 of group 2 AND subgroup
/ Should run in 3 cycles

*0200	/ program
Main, 	cla cll	iac	/ clear ac and l, increment ac
	spa sna szl cla	/ skip on all 3
	cla cll cma  	/ should be skipped
	hlt		/ halt
$Main 
