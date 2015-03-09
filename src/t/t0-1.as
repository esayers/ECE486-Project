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
AI, 0247
*0020
AZ, 0250
BZ, 0251
CZ, 0252
*0200			/ start at address 0200
Main, 	cla cll cma
	and I AZ
	cla cll cma
	and I BZ
	cla cll cma
	and I CZ
	hlt
/
/ Data Section
/
*0250
A, 	040
B, 	050
C, 	060

*0300
	0250
	0251
	0252

$Main 			/ End of Program; Main is entry point
