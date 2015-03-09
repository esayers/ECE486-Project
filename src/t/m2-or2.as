/ Program : m2-2.as
/ Desc: Tests group 2 or subgroup
/ Should run 10 instructions

/
/ Code Section
/

*0200			/ start at address 0200
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
$Main 			/ End of Program; Main is entry point
