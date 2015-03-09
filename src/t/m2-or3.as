/ Program : m2-or3.as
/ Desc: Tests group 2 or subgroup
/ Should run 11 instructions

/
/ Code Section
/

*0200			/ start at address 0200
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
	cll cla cml	/ compliment link
	sma sza snl cla / skip on all 3
	cla cll cma	/ should be skipped
	hlt		/ halt
$Main 			/ End of Program; Main is entry point
