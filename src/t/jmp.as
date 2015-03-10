/ jmp.as
/ test file for jmp

/
/ program
/

*010
AI,	0250
*017
AI2, 	0277

*0200
Main,	cla cll		/ clear ac and l
	jmp A		/ jump to A
	hlt		/ halt
	rar		/ rotate right
	hlt		/ halt
A,	iac		/ increment
	jmp I B		/ jump indirect
	hlt		/ hlt
/
/ data
/

*250
B,	0203
$Main
