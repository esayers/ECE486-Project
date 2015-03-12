/ isz.as -test file for isz
/ Loop should run twice
/ ac should end at two
/ should run in 9 cycles

*010	/ Auto Increment
AI,	0277

*0200	/ Program
Main,	cla cll		/ clear ac and l
Loop,	iac		/ increment ac
	isz A		/ increment a until 0
	jmp Loop	/ loop back
	hlt		/ halt
*250	/ Data
A, 	07776		/ -2
$Main
