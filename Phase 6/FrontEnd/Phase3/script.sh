#!/bin/bash
#creating files out.out and transactions.trn
touch out.out
touch transactions.trn
#input file names that will be testing the code
for t in "login" "mainMenu" "create" "deleteUser" "buy" "sell" "addCredit" "returnTicket" "logout"
  do
    #runs the tests on all the file names
	echo "Running tests for: $t"
	for i in input/$t/*.inp
	  do
      #says the names of the tests its running
		echo "${i%.inp}"
    #running the tests via console
		cat "$i" | ./console currentUserAccounts.txt availableTickets.txt transactions.trn > out.out
    #writes output to the out.out and transactions.trn
		diff out.out "${i%.inp}.out"
		diff transactions.trn "${i%.inp}.trn"
		rm out.out
		rm transactions.trn
	done
done
