/ ind-1.as - Indirection test 1
/ Should copy 01, 020, 0300 to memory starting at 0300

*010	/ Auto Increment
AI,	0250
*017
AI2, 	0277

*0200	/ Program
Main,	cla cll		/ clear ac and l
Loop,	tad I AI	/ load
	dca I AI2	/ store
	isz A		/ test
	jmp Loop	/ loop
	hlt		/ halt
	
*250	/ Data
A,	07775
 	01
	020
	0300
$Main
