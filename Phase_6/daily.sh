echo "Daily Script"
echo "Running Front End"
amtotests=$((1 + RANDOM % 7))
for i in $(seq 1 $amtotests); do
  testnum=$((1 + RANDOM % 7))
   /FrontEnd/Phase3/main.cpp availableTickets.txt currentUserAccounts.txt < FrontEndFiles/day$testnum.txt > tmp$testnum.txt
done
echo "Running Back End"
  java -classpath ../Phase5 Phase4 ./Phase_6/Files/newAvailableTickets.txt ./Phase_6/Files/newUserAccounts.txt ./Phase_6/Files/dailyTransaction.txt
echo "Daily Script Complete"
