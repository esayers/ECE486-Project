/ tad.as
/ test file for tad

/
/ program
/

*010
AI,	0277

*0200
Main,	cla cll cma	/ clear ac and l
Loop,	iac
	isz A
	jmp Loop
	hlt		/ halt
	
/
/ data
/

*250
A, 	07776
$Main
