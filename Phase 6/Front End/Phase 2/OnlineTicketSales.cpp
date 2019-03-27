/**
* An online ticket sales program that allows the user to login and purchase
* or sell tickets for an event
*
* Compile like this: g++ OnlineTicketSales.cpp -o online
* If you don't have c++11 must compile like this: g++ --std=c++11 OnlineTicketSales.cpp -o online
* Run like this: ./online currentUserAccounts.txt availableTickets.txt
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

//TODO: java doc comments, not using hpp file so i deleted it

   /*
   * Declaring variables
   * The user enters username var into the cmd line for logging in
   * The name string is used for names in files
   * The choice of ticket the user wants is an integer value stored in userChoice
   */
   std::string username;
   std::string name;
   std::string line;
   std::string status;
   float balance = 0.0;
   const char *currentUserAccounts = NULL;
   const char *availableTickets = NULL;
   std::string eventName;
   std::string sellerName;
   int amountOfTickets;
   float pricePerTicket;
   std::string code;
   bool isLoggedIn = false;
   int userChoice = 0;
   int seek = 0;
   float totalTicketCost = 0.0;

   /*
   * Declaring functions
   */
   void login();
   void mainMenu();
   void create();
   void deleteUser();
   void buy();
   void sell();
   void addCredit();
   void writeToFile();
   void readFromFile();
   void logout();



   	/**
    * This is the login function that prompts the user to login to the System
    * The user must enter a username which is checked against a user file which
    * then gives the name, status, and balance of that user
    * @param  Nothing.
    * @return Nothing.
    */
    void login()
    {
        std::cout << "Welcome to our Ticket Selling System \n";
        std::cout << "Please enter your username: ";
        std::cin >> username;
        readFromFile();

      }

      /**
      * This is the main menu of the program. It prompts the user to enter a
      * value corresponding to a certain menu command. It then calls that user
      * command.
      * @param  Nothing.
      * @return Nothing.
      */
      void mainMenu()
      {
          isLoggedIn = true;
          std::cout<<"Welcome to the main menu. Please enter a command to continue \n";
          std::cout << "1 = Create Account \n";
          std::cout << "2 = Delete Account \n";
          std::cout << "3 = Buy Tickets \n";
          std::cout << "4 = Sell Tickets \n";
          std::cout << "5 = Refund Credits \n";
          std::cout << "6 = Add Credits \n";
          std::cout << "0 = Logout \n";

          int userCommand = 10;
          code.clear();
          std::cin >> userCommand;


          switch (userCommand)
          {
              case 1:
                  //create();
                  std::cout << "Create function not implemented yet \n";
                  code = "01";
                  mainMenu();
                  break;
              case 2:
                  //deleteUser();
                  std::cout << "Delete function not implemented yet \n";
                  code = "02";
                  mainMenu();
                  break;
              case 3:
                  code = "03";
                  buy();
                  break;
              case 4:
                  //sell();
                  std::cout << "Sell function not implemented yet \n";
                  code = "04";
                  mainMenu();
                  break;
              case 5:
                  //addCredit();
                  std::cout << "Refund function not implemented yet \n";
                  code = "05";
                  mainMenu();
                  break;
              case 6:
                  //addCredit();
                  std::cout << "addCredit function not implemented yet \n";
                  code = "06";
                  mainMenu();
                  break;
              case 0:
                  std::cout << "Logout Succesful! \n";
                  code = "00";
                  logout();
                  break;
              default:
                std::cerr << "Invalid \n";
                mainMenu();
          }
      }

    /**
    * The create function creates a user that can buy or sell tickets
    * @param  Nothing.
    * @return Nothing.
    */
    /*
    void create()
    {
        //TODO
    }
    */

    /**
    * This function removes a user from the user accounts file
    * @param  Nothing.
    * @return Nothing.
    */
    /*
    void deleteUser()
    {
      //TODO
    }
    */

    /**
    * This is the buy function which will first check if the user has enough
    * balance to purchase a ticket, as well as if they have permission to
    * purchase one. Then it will ask the user which ticket they want, check the
    * number of available tickets for sale and go through with the transaction
    * and subsequently subtract funds from the user and notify the user of their
    * new balance.
    * @param  Nothing.
    * @return Nothing.
    */
    void buy()
    {
        if(balance <= 0){
          std::cerr << "Invalid Funds! \n";
          mainMenu();
        } else if(status == "SS"){
          std::cerr << "You do not have permission to buy! \n";
          mainMenu();
        } else {

          int count = 0;
          std::string lines;
          std::ifstream file("availableTickets.txt");
          while (getline(file, lines)){
            count++;
          }
          std::cout << "You have $" << balance << " balance in your account. \n";
          std::cout << "Here are the current tickets for sale: \n";

          readFromFile();


          std::cout << "Enter which option you would like to buy tickets from :";
          std::cin >> userChoice;

          if(userChoice == 1){
            seek = 0;
              readFromFile();
              totalTicketCost = pricePerTicket * amountOfTickets;
              if(totalTicketCost > balance){
              std::cout << "Insufficient Funds! \n\n";
              userChoice = 0;
              buy();
            }
              balance = balance - totalTicketCost;
              writeToFile();
          } else if(userChoice >= 1 && userChoice <= count){
            seek = userChoice - 1;
            seek = 42*seek;
            readFromFile();
            totalTicketCost = pricePerTicket * amountOfTickets;
            if(totalTicketCost > balance){
              std::cout << "Insufficient Funds! \n\n";
              userChoice = 0;
              buy();
            }
            balance = balance - totalTicketCost;
            writeToFile();
          } else {
            std::cout << "invalid option! \n\n";
            buy();
          }
      }
    }

    /**
    * Sell ticket(s) to an event
    * @param  Nothing.
    * @return Nothing.
    */
    /*
    void sell()
    {
        //TODO
    }
    */

    /**
    * Add credit to the system to allow the user to purchase tickets
    * @param  Nothing.
    * @return Nothing.
    */
    /*
    void addCredit()
    {
        //TODO
    }
    */

    /**
    * Writes the transaction to the transaction file
    * @param  Nothing.
    * @return Nothing.
    */
    void writeToFile()
    {
      std::ofstream transactionFile("transaction.txt", std::ios::app);

      if(!transactionFile){
        std::cout << "Error transaction file was not created! \n";
        return;
      }

      if(transactionFile){
      transactionFile << '\n';
      transactionFile << code;
      transactionFile << ' ';
      transactionFile << eventName;
      transactionFile << ' ';
      transactionFile << sellerName;
      transactionFile << ' ';
      transactionFile << amountOfTickets;
      transactionFile << ' ';
      transactionFile << pricePerTicket;
      transactionFile.close();
      return;
    }
  }

  /**
  * Takes information from the current user accounts file. First checks if the
  * user is logged in and then reads from the file if the file is available.
  * Displays the name, status and balance of the user.
  * @param  Nothing.
  * @return Nothing.
  */
  void readFromFile()
  {
    //checks if user logged in so reads currentUserAccounts file
    if(!isLoggedIn){
      std::ifstream userLoginFile(currentUserAccounts);
      if(!userLoginFile){
        std::cerr << "File not found! \n";
        return;
      }

      /*
      * Logging in
      */
      if(userLoginFile) {
        while (std::getline(userLoginFile, line))
        {
          std::replace(line.begin(), line.end(), ' ', ' ');

          std::stringstream ss(line);

          ss >> name;
          if(name == username && name != "END"){
            ss >> status;
            ss >> balance;
            std::cout << "name = " << name << "\n";
            std::cout << "status = " << status << "\n";
            std::cout << "balance = " << balance << "\n";
            userLoginFile.close();
            mainMenu();
            return;
          } else if(name == "END") {
            std::cerr << "Username not found \n\n";
            return;
          }
        }
        userLoginFile.close();
      }


    }

    /*
    * Checks to see if user is logged in, then reads available tickets file
    */
    if(isLoggedIn){
      std::ifstream currentTicketFile(availableTickets);

      if(!currentTicketFile){
        std::cerr << "Available Tickets File not found! \n";
        return;
      }

      if(userChoice != 0){
        currentTicketFile.seekg((seek), currentTicketFile.beg);
          std::getline(currentTicketFile, line);
          std::replace(line.begin(), line.end(), ' ', ' ');

          std::stringstream ss(line);

          ss >> eventName;
          ss >> sellerName;
          ss >> amountOfTickets;
          ss >> pricePerTicket;

          std::cout << "Tickets confirmed. Event name = " << eventName << "\t";
          std::cout << "Seller name = " << sellerName << "\t";
          std::cout << "Amount of Tickets = " << amountOfTickets << "\t";
          std::cout << "Price per Ticket = $" << pricePerTicket << "\n";
          currentTicketFile.close();
         return;
      }


      if(currentTicketFile) {
        int lineNumber = 1;

        while (std::getline(currentTicketFile, line))
        {
          std::replace(line.begin(), line.end(), ' ', ' ');

          std::stringstream ss(line);

          ss >> eventName;
          ss >> sellerName;
          ss >> amountOfTickets;
          ss >> pricePerTicket;

          std::cout << lineNumber << ". eventName = " << eventName << "\t";
          std::cout << "sellerName = " << sellerName << "\t";
          std::cout << "amountOfTickets = " << amountOfTickets << "\t";
          std::cout << "pricePerTicket = $" << pricePerTicket << "\n";
          lineNumber++;
        }
        currentTicketFile.close();
        return;
      }

    }

  }


    /**
    * Ends the current session, preventing any transaction from happening afterwards.
    * Checks to see if the session is active first.
    * @param  Nothing.
    * @return Nothing.
    */
    void logout()
    {
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
      login();
    } catch (const std::exception& e) {
      return -1;
    }

    return 0;
}
