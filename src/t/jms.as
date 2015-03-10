/ jms.as
/ test file for jms

/
/ program
/

*0020
J1,	0		/ return value
	iac		/ ac++
	jmp I J1	/ return
J2,	0		/ return value
	rtr		/ rotate right
	jmp I J2	/ return
*0200
Main,	cla cll		/ clear ac and l
	jms J1		/ call J1
	jms I A		/ call J2
	jms J3		/ call J3
	hlt		/ halt

J3,	0		/ return value
	cma		/ complement
	jmp I J3	/ return
/
/ data
/

*250
A,	023		/ address of J2
$Main
