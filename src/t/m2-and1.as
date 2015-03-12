/ m2-and1.as - Tests 1 of  group 2 AND subgroup
/ should not skip any instructions
/ Should run in 10 cycles

*0200	/ program
Main, 	cla cll cma	/ clear ac and l, compliment ac
	spa cla		/ skip on pos then clear ac
	cla cll cma  	/ should not be skipped
	cla cll		/ zero ac and inc
	sna cla		/ skip on non-zero ac
	cla cll cma	/ should not be skipped
	cla cll	cml	/ clear ac and l then compliment l
	szl		/ skip on non-zero link
	cla cll cma	/ should not be skipped
	hlt		/ halt
$Main 
