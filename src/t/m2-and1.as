/ Program : m2-and1.as
/ Desc: Tests group 2 and subgroup
/ Should run 10 instructions in 10 cycles

/
/ Code Section
/

*0200			/ start at address 0200
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
$Main 			/ End of Program; Main is entry point
