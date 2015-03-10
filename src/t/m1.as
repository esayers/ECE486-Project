/ Program : m1.as
/ Desc: Tests group 1 micro ops

/
/ Code Section
/

*0200			/ start at address 0200
Main,	cla cll		/ clear ac an l
	cma cml		/ compliment ac and l
	iac		/ increment ac
	iac		/ increment ac
	rar		/ rotate right
	ral		/ rotate left
	rtr		/ rotate two right
	rtl		/ rotate two left
	hlt		/ halt
*0250
A,	07777


$Main 			/ End of Program; Main is entry point
