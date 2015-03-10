/ tad.as
/ test file for tad

/
/ program
/

*020
B, 	0301 
*0200
Main,	cla cll cma	/ clear ac and l and complement ac
	dca I A		/ Store indirectly through A
	cma		/ Compliment ac
	dca I B		/ Store indirectly through B
	hlt		/ halt
	
/
/ data
/

*0250
A, 	0300


$Main
