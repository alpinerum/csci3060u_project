echo "Daily Script"
echo "Running Front End"
amtotests=$((1 + RANDOM % 7))
for i in $(seq 1 $amtotests); do
  testnum=$((1 + RANDOM % 7))
   rem /FrontEnd/Phase3/main
done
echo "Running Back End"
  java -classpath ../Phase5 Phase4 ./Phase6/Files/newAvailableTickets.txt ./Phase6/Files/newUserAccounts.txt ./Phase6/Files/dailyTransaction.txt
echo "Daily Script Complete"
