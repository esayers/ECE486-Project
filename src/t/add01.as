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
Main, 	cla cll 	/ clear AC and Link
	tad Z AA 		/ add A to Accumulator
	tad AA 		/ add B
	dca I AC 		/ store sum at C
	hlt 		/ Halt program
	jmp Main	/ To continue - goto Main
/
/ Data Section
/
*0250 			/ place data at address 0250
A, 	2 		/ A equals 2
B, 	3 		/ B equals 3
C, 	0

*350
AA,	0250
AB,	0251
AC, 	0252
$Main 			/ End of Program; Main is entry point
