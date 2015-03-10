/ Program : m2-1.as
/ Desc: Tests group 2 or subgroup
/ Should run 7 instructions in 7 cycles

/
/ Code Section
/

*0200			/ start at address 0200
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
$Main 			/ End of Program; Main is entry point
