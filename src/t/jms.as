/ jms.as -test file for jms
/ should increment, rotate 2 right, compliment ac
/ should run in 18 cycles

*0020	/ Functions
J1,	0		/ return value
	iac		/ ac++
	jmp I J1	/ return
J2,	0		/ return value
	rtr		/ rotate right
	jmp I J2	/ return
*0200 	/ Program
Main,	cla cll		/ clear ac and l
	jms J1		/ call J1
	jms I A		/ call J2
	jms J3		/ call J3
	hlt		/ halt

J3,	0		/ return value
	cma		/ complement
	jmp I J3	/ return

*250	/ Data
A,	023		/ address of J2
$Main
