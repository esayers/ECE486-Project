/ m2-2.as - Test 2 of group 2 OR subgroup
/ Should run in 10 cycles

*0200	/ program
Main, 	cla cll		/ clear ac and l
	sma cla		/ skip on minus then clear ac
	cla cll cma  	/ should not be skipped
	cla cll	cma	/ compliment ac
	sza cla		/ skip on zero ac
	cla cll cma	/ should not be skipped
	cla cll		/ clear ac and l
	snl		/ skip on non-zero link
	cla cll cma	/ should not be skipped
	hlt		/ halt
$Main
