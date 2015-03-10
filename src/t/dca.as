/ tad.as
/ test file for tad

/
/ program
/

*010
AI,	0250
*017
AI2, 	0277

*0200
Main,	cla cll		/ clear ac and l
Loop,	tad I AI	/ load
	dca I AI2	/ store
	isz A		/ test
	jmp Loop	/ loop
	hlt		/ halt
	
/
/ data
/

*250
A,	07775
 	01
	020
	0300
$Main
