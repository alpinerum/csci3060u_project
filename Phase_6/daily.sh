echo "Daily Script"
echo "Running Front End"
#g++ --std=c++11 ./FrontEnd/Phase3/main.cpp ./FrontEnd/Phase3/files.cpp ./FrontEnd/Phase3/transaction.cpp ./FrontEnd/Phase3/admin.cpp -o main.out
for i in $(seq 1 6); do
  num=$((1 + RANDOM % 6))
   ./FrontEnd/Phase3/main.out currentUserAccounts.txt availableTickets.txt < FrontEndFiles/run$num.txt > transSession$num.txt
   echo "Concatenating Daily Transaction File"
   cat ./FrontEnd/Phase3/transaction.txt >> Files/dailyTransaction.txt
done
echo "Running Back End"
  java -cp "../Phase_5/Classes" Phase4 ./Phase_6/Files/newAvailableTickets.txt ./Phase_6/Files/newUserAccounts.txt ./Phase_6/Files/dailyTransaction.txt
echo "Daily Script Complete"
