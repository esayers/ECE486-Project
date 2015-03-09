/ Program : Add01.pal
/ Date : March 3, 2002
/
/ Desc : This program computes c = a + b
/
/-------------------------------------------
/
/ Code Section
/
*0200			/ start at address 0200
Main, 	cla cll	 	/ clear AC and Link
	iac
	ral
	rar
	rtl
	rtr
	rar
	ral
	rtr
	rtl
	cma
	cml
	hlt
/
/ Data Section
/
$Main 			/ End of Program; Main is entry point
