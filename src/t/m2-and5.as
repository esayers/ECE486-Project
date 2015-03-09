/ Program : m2-and5.as
/ Desc: Tests group 2 and subgroup or with switches

/
/ Code Section
/

*0200			/ start at address 0200
Main,	cla cll iac	/ clear ac and l
	osr		/ or with switches
	hlt		/ halt
$Main 			/ End of Program; Main is entry point
