/ dca.as - test file for dca
/ 01, 020, and 0300 should be stored starting at address 0300
/ should run in 40 cycles


*010	/ Auto Increment Load
AI,	0250
*017	/ Auto Increment Store
AI2, 	0277

*0200	/ Program
Main,	cla cll		/ clear ac and l
Loop,	tad I AI	/ load
	dca I AI2	/ store
	isz A		/ test
	jmp Loop	/ loop
	hlt		/ halt

*250	/ Data
A,	07775 -3
 	01
	020
	0300
$Main
