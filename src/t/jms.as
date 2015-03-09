/ Program : jms.as
/ Desc : tests jms

/
/ Code Section
/
*0010
AI, 0247
*0020
AZ, 0300

*0200			/ start at address 0200
Main, 	cla cll		/ clear ac and l and increment ac
	jms NEXT	
	hlt		/ halt
	0
	0
	0
NEXT,	0
	iac
	hlt
	
	
	
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
