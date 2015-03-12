/ m2-1.as - Test 1 of  group 2 OR subgroup
/ Should run in 7 cycles

*0200	/ program
Main, 	cla cll	cma	/ clear ac and l then compliment ac
	sma cla		/ skip on minus then clear ac
	cla cll cma  	/ should be skipped
	cla cll		/ zero ac
	sza cla		/ skip on zero ac
	cla cll cma	/ should be skipped
	cla cll cml	/ complement link
	snl		/ skip on non-zero link
	cla cll cma	/ should be skipped
	hlt		/ halt
$Main
