/ jmp.as - test file for jmp
/ should increment and rotate right ac
/ should run in 7 cycles

*010	/ Auto Increment
AI,	0250
*017
AI2, 	0277

*0200	/ Program
Main,	cla cll		/ clear ac and l
	jmp A		/ jump to A
	hlt		/ halt
	rar		/ rotate right
	hlt		/ halt
A,	iac		/ increment
	jmp I B		/ jump indirect
	hlt		/ hlt

*250	/ Data
B,	0203		/ address of rar
$Main
