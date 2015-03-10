/ Program : m2-and2.as
/ Desc: Tests group 2 and subgroup
/ Should run 7 instructions in 7 cycles

/
/ Code Section
/

*0200			/ start at address 0200
Main, 	cla cll		/ clear ac and l
	spa cla		/ skip on pos then clear ac
	cla cll cma  	/ should be skipped
	cla cll iac	/ zero ac and inc
	sna cla		/ skip on non-zero ac
	cla cll cma	/ should be skipped
	cla cll		/ clear ac and l
	szl		/ skip on zero link
	cla cll cma	/ should be skipped
	hlt		/ halt
$Main 			/ End of Program; Main is entry point
