/ Program : ind.as
/ Desc : tests indirection

/
/ Code Section
/
*0010
AI, 0247
*0020
AZ, 0300

*0200			/ start at address 0200
Main, 	cla cll		/ clear ac and l
	isz A
	iac
	isz A
	iac
	hlt		/ halt
	
	
	
/
/ Data Section
/
*0250
A, 	7776
B, 	020
C, 	030
D,	040
E,	0253

*0300
	0100
	0200
	0300

$Main 			/ End of Program; Main is entry point
