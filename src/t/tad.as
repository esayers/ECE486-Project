/ tad.as - test file for tad
/ -1 + 1 should result in 0 with a carry
/ -1 - 1 should result in 07776 with a carry
/ 03777 + 03777 should result in 07776 without a carry
/ 04000 + 04000 should result in 0 with a carry
/ 04000 + 03777 should result in 07777 without a carry
/ It should run in 51 cycles

*010	/ Auto Increment
AI,	0277

*0200	/ Program
Main,	cla cll		/ clear ac and l
	tad A		
	tad B		/ -1 + 1
	dca I AI	/ store
	cll
	tad A		
	tad A		/ -1 -1
	dca I AI	/ store
	cll
	tad D
	tad D		/ largest + largest
	dca I AI	/ store
	cll
	tad C		
	tad C		/ smallest + smallest
	dca I AI
	cll
	tad C
	tad D		/ smallest + largest
	dca I AI	/ store
	hlt

*250	/ Data
A, 07777		/ -1
B, 01			/ 1
C, 04000		/ smallest negative
D, 03777		/ largest positive	
$Main
