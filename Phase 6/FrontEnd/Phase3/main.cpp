/**
* An online ticket sales program that allows the user to login and purchase
* or sell tickets for an event
*
* Compile like this: g++ main.cpp files.cpp buy.cpp -o online
* If you don't have c++11 must compile like this: g++ --std=c++11 main.cpp files.cpp buy.cpp -o online
* Run like this: ./main currentUserAccounts.txt availableTickets.txt
*
* @author  Zain Ansari
* @author Ammar Khan
* @author Sumeet Dhillon
* @version 1.0
* @since   2019-02-01
*/
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <list>
#include <iterator>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "main.h"

   /*
   * Declaring variables
   * The user enters username var into the cmd line for logging in
   * The name string is used for names in files
   * The choice of ticket the user wants is an integer value stored in userChoice
   */

   std::string username;
   bool isLoggedIn = false;
   std::string code;
   std::string eventName;
   std::string sellerName;
   std::string userCommand;
   std::string buyerUser;
   std::string sellerUser;
   float wantToAdd;
   std::string creditUser;
   int ticketAmount;
   float creditToTransfer = 0.0;
   float userCredit = 0.0;
   std::string newUser;
   std::string newUserType;
   std::string wantToDelete;
   int amountOfTickets;
   float pricePerTicket = 0.0;
   std::string line;
   int userChoice = 0;
   int seek = 0;
   float totalTicketCost = 0.0;
   std::string name;
   std::string status;
   std::string statusDeleted;
   float balance = 0.0;
   const char *currentUserAccounts = NULL;
   const char *availableTickets = NULL;


   /**
   * Ends the current session, preventing any transaction from happening afterwards.
   * Checks to see if the session is active first.
   * @param  Nothing.
   * @return Nothing.
   */
   void logout()
   {
       isLoggedIn = false;
       return;
   }


/**
* This is the main method which starts the system by calling the login function.
* @param argc 	number of command line arguments
* @param *argv	array of strings representing arguments on the command line
* @return 			Nothing.
*/
int main(int argc, char *argv[])
{
    currentUserAccounts = argv[1];
    availableTickets = argv[2];
    try {
      mainMenu();
    } catch (const std::exception& e) {
      return -1;
    }

    return 0;
}
