/ Program : and.as
/ Desc: Tests tad

/
/ Code Section
/

*0200			/ start at address 0200
Main,	cla cll cma	/ clear ac and l, comp ac
	and A		/ Add 1 to 01230
	cla cll cma	/ clear ac and l, inc ac
	and B		/ add 1 to -1
	hlt		/ halt

*250
A, 01230
B, 07777
$Main 			/ End of Program; Main is entry point
