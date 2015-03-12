/ m2-and2.as - Test 2 of group 2 AND subgroup
/ Should in 8 cycles

*0200	/program
Main, 	cla cll		/ clear ac and l
	spa cla		/ skip on pos then clear ac
	cla cll cma  	/ should be skipped
	cla cll iac	/ zero ac and inc
	sna cla		/ skip on non-zero ac
	cla cll cma	/ should be skipped
	cla cll		/ clear ac and l
	szl		/ skip on zero link
	cla cll cma	/ should be skipped
	skp		/ skip always
	cla cll cma	/ should be skipped
	hlt		/ halt
$Main 
