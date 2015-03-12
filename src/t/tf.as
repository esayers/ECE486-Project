/ tf.as - test file for the tracefile
/ Should log the indicated memory accesses
/ It should run in 16 cycles

*010 	/ Auto Increment
AI,	0277
*020	/ Function
J1,	0		/ return address
	iac		/ fetch
	jmp I J1	/ fetch, read

*0200	/ Program
Main,	cla cll		/ fetch
	and A		/ fetch, read
	dca I AI	/ fetch, read, store, store
	tad A		/ fetch, read
	isz A		/ fetch, read, store
	jms J1		/ fetch, store
	hlt		/ fetch
	
*250	/ Data
A, 	07776		/ -2
$Main
