/ m2-or3.as - Test 3 of group 2 OR subgroup
/ Should run in 11 cycles

*0200	/ program
Main, 	cla cll iac	/ clear ac and l then inc
	sma sza snl cla	/ skip on all 3
	cla cll cma  	/ should not be skipped
	cla cll 	/ clear ac and l
	sma sza snl cla	/ skip on all 3
	cla cll cma	/ should be skipped
	cla cll		/ clear ac
	cma		/ complement ac
	sma sza snl cla	/ skip on all 3
	cla cll cma	/ should be skipped
	hlt		/ halt
$Main 
