/ m2-osr.as - Tests group 2 or with switches
/ Should or accumulator with switch settings
/ Should run in 3 cycles

*0200	/ program
Main,	cla cll		/ clear ac and l
	osr		/ or with switches
	hlt		/ halt
$Main
