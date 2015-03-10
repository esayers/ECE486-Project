/ tad.as
/ test file for tad

/
/ program
/

*010
AI,	0277

*0200
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
	
/
/ data
/

*250
A, 07777		/ -1
B, 01			/ 1
C, 04000		/ smallest negative
D, 03777		/ largest positive	
$Main
