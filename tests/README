--------------------------------
- HOW TO USE THIS BATCH TESTER -
--------------------------------

The directory must contain:
  tests 	=> the file that describes all the tests to be executed
  tester.sh	=> the test-executing script
  42sh		=> your binary

'tests' file contains a series of numbered tests.
Each test is placed between markers. For instance:
	[42]		=> beginning of the test number 42
	[42-END]	=> end of the test number 42
In between those markers, the following instructions must be found:
	SETUP="script"	=> script to be executed before launching the test
	NAME="name"     => name of the test
	CLEAN="script"  => script to be executed after launching the test
	TESTS=...	=> series of commands to be sent to the shell

Arguments :
./tester.sh		=> no argument : all the tests are executed + debug mode for the KO tests only
./tester.sh 42		=> 1 argument : only this one test is executed
./tester.sh -d 42	=> debug mode : printing of the 42sh and tcsh outputs

The batch tester launches the tests with tcsh, then with 42sh and compare the results.

Binary Name and Reference Shell can be setup in tester.sh script