/ and.as
/ test file for and

*010
AI,	0277

*0200	/ Program
Main,	cla cll		/ clear ac and l
	and A		/ And with zero
	dca I AI	/ save
	tad A
	and B		/ and alternating bit patterns
	dca I AI	/ save
	cma
	and A		/ and with all 1's
	dca I AI	/ save
	hlt
	
*250	/ Data
A, 	05252
B,	02525
$Main
