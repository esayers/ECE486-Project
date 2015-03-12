/ ind-2.as - Indirection test 2
/ Should store 07777 in 300 and 301
/ Should complete in 13 cycles

*020 	/ indirect from zero page
B, 	0301 

*0200 	/ program
Main,	cla cll cma	/ clear ac and l and complement ac
	dca I A		/ Store indirectly through A
	cma		/ Compliment ac
	dca I B		/ Store indirectly through B
	hlt		/ halt

*0250	/ data
A, 	0300


$Main
