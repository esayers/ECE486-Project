/ m1.as - Tests group 1 micro ops
/ should manipulate the ac in the ways decribed below
/ should run in 9 cycles

*0200	/ Program
Main,	cla cll		/ clear ac an l
	cma cml		/ compliment ac and l
	iac		/ increment ac
	iac		/ increment ac
	rar		/ rotate right
	ral		/ rotate left
	rtr		/ rotate two right
	rtl		/ rotate two left
	hlt		/ halt

*0250	/ Data
A,	07777
$Main 
