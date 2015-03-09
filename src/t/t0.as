/ Program : Add01.pal
/ Date : March 3, 2002
/
/ Desc : This program computes c = a + b
/
/-------------------------------------------
/
/ Code Section
/
*0010
AI, 0277
*0200			/ start at address 0200
Main, 	cla cll cma
	and A
	cla cll cma
	and B
	cla cll cma
	and C
	hlt
/
/ Data Section
/
*0250
A, 	010
B, 	020
C, 	030

*0300
	0250
	0251
	0252

$Main 			/ End of Program; Main is entry point
